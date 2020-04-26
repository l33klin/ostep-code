//
// Created by Klin on 2020/4/13.
// https://coolshell.cn/articles/20793.html#%E7%A4%BA%E4%BE%8B%E4%B8%80
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h> /* for sleep() */


int main(int argc, char *argv[]) {
    if (argc < 2)
    {
        perror("need at least one arguements");
        return 1;
    }
    
    int step = atoi(argv[1]);
    const int LEN = 64*1024*1024;
    int *arr = malloc(LEN * sizeof(int));
    clock_t tic = clock();
    for (int i = 0; i < LEN; i += step) arr[i] *= i;
    clock_t toc = clock();
    printf("Step %d , Elapsed: %f seconds\n", step, (double)(toc - tic) / CLOCKS_PER_SEC);

    return 0;
}
