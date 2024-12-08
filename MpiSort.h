#ifndef MpiSort
#define MpiSort

#include <mpi.h>

int mpi_bitonic_sort(int Array[], int world_rank, int world_size);

int mpi_bitonic_sort(int Array[], int world_rank, int world_size){

    printf("Hello from rank %d out of %d processors\n", world_rank, world_size);
    MPI_Finalize();
    return 0;
}

#endif