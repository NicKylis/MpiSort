#include <stdio.h>
#include <stdlib.h>
#include "simpleSort.h"
#include <time.h>

#define MAX_NUM 1000

void generate_random_array(int *arr, int size, int rank) {
    srand(time(NULL) + rank);
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % MAX_NUM;
    }
}

int main(){
    int N = 1048576; // Define the number of integers in the list
    int p = 1; // Define the number of processes
    int data = N / p; // Define each processes' data to sort
    int Array[N];

    generate_random_array(Array, N, 0);

    // Prints the initial array
    // printf("[");
    // for (int i = 0; i < N; i++) {
    //     printf("%d ", Array[i]);
    // }
    // printf("]\n");

    serial_sorting(Array, N);

    // Prints the array after serial sorting
    printf("[");
    for (int i = 0; i < N; i++) {
        printf("%d ", Array[i]);
    }
    printf("]\n");
    return 0;
}