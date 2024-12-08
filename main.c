#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include "simpleSort.h"
#include "MpiSort.h"

int world_size;
int world_rank;

void main(int argc, char** argv){
    int N = 0; // Define the number of integers in the list
    int p = 6; // Define the number of processes
    int data = N / p; // Define each processes' data to sort
    int Array[5] = {1, 2, 3, 4, 5};
    
    MPI_Init(&argc, &argv);
    // MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    serial_sorting(Array);
    mpi_bitonic_sort(Array, world_rank, world_size);

}

//mpicc -o main main.c
//mpirun -np {num_of_proccesses} ./main
//mpirun -np 4 ./main