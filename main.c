#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include "simpleSort.h"
#include "MpiSort.h"

int world_size;
int world_rank;

void main(int argc, char** argv){
    int N = 10; // Define the number of integers in the list
    int p = 6; // Define the number of processes
    int data = N / p; // Define each processes' data to sort
    int Array[N];

    for(int i = 0; i < N; i++){
        Array[i] = N - i*2 + 2;
    }

    // Prints the initial array
    printf("[");
    for (int i = 0; i < N; i++) {
        printf("%d ", Array[i]);
    }
    printf("]\n");

    serial_sorting(Array, N);

    // Prints the array after serial sorting
    printf("[");
    for (int i = 0; i < N; i++) {
        printf("%d ", Array[i]);
    }
    printf("]\n");

    // MPI_Init(&argc, &argv);
    // MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    // MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    mpi_bitonic_sort(Array, 0, N, 1);

    printf("[");
    for (int i = 0; i < N; i++) {
        printf("%d ", Array[i]);
    }
    printf("]\n");

    // MPI_Finalize();
}

//mpicc -o main main.c
//mpirun -np {num_of_proccesses} ./main
//mpirun -np 4 ./main

//TODO: move the MPI stuff from main to MpiSort