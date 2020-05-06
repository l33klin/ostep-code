//
// Created by Klin on 2020/4/27.
// https://coolshell.cn/articles/20793.html#%E7%A4%BA%E4%BE%8B%E4%BA%8C
//

#include <stdio.h>
#include <stdlib.h> /* for atoi() */
#include <time.h>  /* for clock() */ 
#include <unistd.h> /* for sleep() */


int main(int argc, char *argv[]) {
    if (argc < 3)
    {
        perror("need at least two arguements");
        return 1;
    }
    
    int increment = atoi(argv[1]);
    int times = atoi(argv[2]);
    const int LEN = increment * times;
    int *arr = malloc(LEN * sizeof(int));
    clock_t tic = clock();
    for (int i = 0; i < 10000000; i++) {
        for (int j = 0; j < LEN; j += increment) {
                arr[j] += j;
            }
    }
    clock_t toc = clock();
    // printf("increment %d for %d times, Elapsed: %f seconds\n", increment, times, (double)(toc - tic) / CLOCKS_PER_SEC);
    int elapse = (int)(toc - tic);
    char out_s[12];
    int len = sprintf(out_s, "%d", elapse);

    write(STDOUT_FILENO, out_s, len);
    return 0;
}
