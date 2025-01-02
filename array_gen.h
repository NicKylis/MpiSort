#ifndef ARRAY_GEN_H
#define ARRAY_GEN_H

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_NUM 1000

void generate_random_array(int *arr, int size, int rank) {
    srand(time(NULL) + rank);
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % MAX_NUM;
    }
}

#endif