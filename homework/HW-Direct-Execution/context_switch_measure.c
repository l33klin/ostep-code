/* Context switch overhead of OS measure
 *  1. create a pipe, two processes bind to one CPU;
 *  2. write a byte to pipe in process a;
 *  3. read a byte from pipe in process b;
 *  4. loop 2 and 3 many times, and count the time elapse;
 *  5. time of each loop to may be the context switch overhead;
 * 
 * Concerns:
 *  1. may introduce overhead of syscall.
 * 
*/

#define _GNU_SOURCE             /* See feature_test_macros(7) */
#include    <sched.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <unistd.h>
#include    <inttypes.h>

#define	oops(m,x)	{ perror(m); exit(x); }

main(int ac, char **av)
{
    int	pipea[2],			/* two file descriptors	*/
        pipeb[2],
            newfd,				/* useful for pipes	*/
            pid;				/* and the pid		*/
    uintmax_t times;

    cpu_set_t cpu_set;

    if ( ac < 2 ){
        fprintf(stderr, "usage: %s times\n", av[0]);
        exit(1);
    }

    times = strtoumax(av[1], NULL, 10);
    if (times == UINTMAX_MAX)
        oops("Cannot convert times", 1);

    if ( pipe( pipea ) == -1 || pipe(pipeb) == -1)		/* get a pipe		*/
        oops("Cannot get a pipe", 1);

    CPU_ZERO(&cpu_set);

    /* ------------------------------------------------------------ */
    /*	now we have a pipe, now let's get two processes		*/

    if ( (pid = fork()) == -1 )			/* get a proc	*/
        oops("Cannot fork", 2);

    /* ------------------------------------------------------------ */
    /* 	Right Here, there are two processes			*/
    /*             parent loop to write pipe			*/

    if ( pid > 0 ){			/* parent will exec av[2]	*/
        CPU_SET(0, &cpu_set);
        if(sched_setaffinity(getpid(), sizeof(cpu_set), &cpu_set) == -1)
            perror("sched_setaffinity failed");

        close(pipea[0]);
        close(pipeb[1]);
        char p_w_b[2] = "a";
        char p_r_b[2];

        // TODO: loop write and read

        write(pipea[1], p_w_b, 1);
        int n = read(pipeb[0], p_r_b, 1);
        if(n != 1)
            perror("Parent read error");
        printf("Parent read from pipeb: %s\n", p_r_b);
        write(pipea[1], p_w_b, 1);

        close(pipea[1]);	
        close(pipeb[0]);
        wait(pid);
        exit(0);
    }

    /*	 child execs av[1] and writes into pipe*/
    CPU_SET(0, &cpu_set);
    if(sched_setaffinity(getpid(), sizeof(cpu_set), &cpu_set) == -1)
        perror("sched_setaffinity failed");

    close(pipea[1]);		/* child doesn't read from pipe	*/
    close(pipeb[0]);
    char c_w_b[2] = "b";
    char c_r_b[2]; 

    int m;
    do
    {
        m = read(pipea[0], c_r_b, 1);
        printf("Child read m: %d\n", m);
        printf("Child read from pipea: %s\n", c_r_b);
        write(pipeb[1], c_w_b, 1);
    } while (m == 1);

    close(pipea[0]);
    close(pipeb[1]);
    printf("Child exit!\n");
}