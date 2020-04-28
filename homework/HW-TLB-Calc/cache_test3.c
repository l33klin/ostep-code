//
// Created by Klin on 2020/4/29.
// https://coolshell.cn/articles/20793.html#%E7%A4%BA%E4%BE%8B%E4%B8%89
//

#include <stdio.h>
#include <stdlib.h> /* for atoi() */
#include <time.h>  /* for clock() */ 
#include <unistd.h> /* for sleep() */


int main(int argc, char *argv[]) {
    const int row = 1024;
    const int col = 512;
    int matrix[row][col];

    //逐行遍历
    clock_t tic = clock();
    int sum_row=0;
    for(int _r=0; _r<row; _r++) {
        for(int _c=0; _c<col; _c++){
            sum_row += matrix[_r][_c];
        }
    }
    clock_t toc = clock();
    printf("Elapsed: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

    //逐列遍历
    clock_t tic1 = clock();
    int sum_col=0;
    for(int _c=0; _c<col; _c++) {
        for(int _r=0; _r<row; _r++){
            sum_col += matrix[_r][_c];
        }
    }
    clock_t toc1 = clock();
    printf("Elapsed: %f seconds\n", (double)(toc1 - tic1) / CLOCKS_PER_SEC);
    return 0;
}
