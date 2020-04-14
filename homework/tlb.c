#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h> /* for sleep() */

// int PAGENUM = 8096*64;
int PAGESIZE = 4096;

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Require at least two arguments!\n");
        exit(1);
    }

    int loop = atoi(argv[1]);
    int pagenum = atoi(argv[2]);
    printf("Loop:%d\n", loop);
    printf("Pagenum:%d\n", pagenum);

    clock_t tic = clock();
    int *a = (int *)malloc(pagenum * PAGESIZE);
    int i = 0;
    for (size_t j = 0; j < loop; j++)
    {
        for (i = 0; i < pagenum; i++)
        {
            a[i * PAGESIZE / sizeof(int)]++;
        }
    }
    clock_t toc = clock();

    int sum = 0;
    for (int i = 0; i < pagenum ; i++)
    {
        sum += a[i * PAGESIZE / sizeof(int)];
    }
    printf("Sum: %d\n", sum);

    printf("Elapsed: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);
    printf("Visit Page time: %0.2f ns\n", (double)(toc - tic) / (loop * pagenum));

    return 0;
}