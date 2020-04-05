//
// Created by Klin on 2020/4/5.
//
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int *x = (int *) malloc(sizeof(int));
    x = NULL;
    free(x);
    return 0;
}



