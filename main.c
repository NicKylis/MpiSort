#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "sortnmerge.h"
#include "bitonicMPI.h"
#include "array_gen.h"
#include "serial_qsort.h"

int main(int argc, char *argv[]) {

    int rank, p;
    int q, n;
    int *local_data;
    int local_size;
    int *sorted_data = NULL;
    double start_time, end_time, elapsed_time, max_time;

    q = atoi(argv[1]);
    p = atoi(argv[2]);
    n = (1 << (q + p));

    // Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    if (argc != 3) {
        if (rank == 0) {
            printf("Usage: %s <q> <p>\n", argv[0]);
        }
        MPI_Finalize();
        return 0;
    }

    local_size = (1 << q);
    local_data = (int *)malloc(local_size * sizeof(int));

    // Generate random numbers for each process
    srand(time(NULL));
    generate_random_array(local_data, local_size, rank);

    // Uncomment to print the unsorted array (only in each process):
    // printf("Process %d unsorted array: ", rank);
    // for (int i = 0; i < local_size; i++) {
    //     printf("%d ", local_data[i]);
    // }
    // printf("\n");

    // Sort locally in ascending or descending order based on rank
    qsort(local_data, local_size, sizeof(int), (rank % 2 == 0) ? (int (*)(const void *, const void *))&cmp_asc : (int (*)(const void *, const void *))&cmp_desc);

    start_time = MPI_Wtime();
    // Perform Bitonic Sort in parallel using MPI
    mpi_bitonic_sort(local_data, local_size, rank, p);

    // Gather all sorted data from each process to the root process
    if (rank == 0) {
        sorted_data = (int *)malloc(n * sizeof(int));
    }

    MPI_Gather(local_data, local_size, MPI_INT, sorted_data, local_size, MPI_INT, 0, MPI_COMM_WORLD);
    
    // End the timer once the sorting is over and calculate the maximun latency
    end_time = MPI_Wtime();
    elapsed_time = end_time - start_time;
    MPI_Reduce(&elapsed_time, &max_time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    // If root process, validate the final sorted result and print the final sorted array
    if (rank == 0) {
        bitonic_sort(sorted_data, 0, n, 1);
        // Uncomment to print the final sorted array (before validation):
        printf("Final sorted array (from MPI): ");
        for (int i = 0; i < n; i++) {
            if(sorted_data[i] != 0 && sorted_data[i] <= MAX_NUM){
                printf("%d ", sorted_data[i]);
            }
        }
        printf("\n");
        printf("Time for completion: %f seconds\n", max_time);

        // Check correctness: Use qsort() to verify the result
        int *validation_data = (int *)malloc(n * sizeof(int));
        memcpy(validation_data, sorted_data, n * sizeof(int));

        // Sort the gathered data using qsort for validation
        qsort(validation_data, n, sizeof(int), cmp_asc);

        // Compare the two sorted arrays to validate correctness
        int mistakes = 0;
        for (int i = 0; i < n; i++) {
            if (sorted_data[i] == validation_data[i]) {
                mistakes =+ 1;
            }
        }

        printf("Validation : The array has %d mistakes.\n", mistakes);

        free(validation_data);
        free(sorted_data);
    }

    free(local_data);
    MPI_Finalize();

    return 0;
}
