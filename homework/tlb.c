#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h> /* for sleep() */

int PAGENUM = 8096*64;
int PAGESIZE = 4096;

int main(int argc, char *argv[]) {
    clock_t tic = clock();

    int *a = malloc(PAGENUM * PAGESIZE);
    for (int i = 0; i < PAGENUM * PAGESIZE / sizeof(int); i += PAGESIZE/sizeof(int))
    {
        a[i] = 1;
    }
    
    clock_t toc = clock();

    int sum = 0;
    for (int i = 0; i < PAGENUM * PAGESIZE / sizeof(int); i += PAGESIZE/sizeof(int))
    {
        sum += a[i];
    }
    printf("Sum: %d\n", sum);

    printf("Elapsed: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

    return 0;
}