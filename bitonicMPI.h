#ifndef BITONICMPI_H
#define BITONICMPI_H

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "sortnmerge.h"

void mpi_bitonic_sort(int *local_data, int local_size, int rank, int p) {
    int step, partner;
    int *recv_buf = (int *)malloc(local_size * sizeof(int));
    
    for (step = 1; step <= p; step++) {
        int dist = 1 << (step - 1);
        
        // Ensure p is a power of 2
        if ((p & (p - 1)) != 0) {
            if (rank == 0) {
                printf("Error: Number of processes p should be a power of 2.\n");
            }
            MPI_Finalize();
            exit(1);
        }

        if (rank % (2 * dist) < dist) {
            partner = rank + dist;
        } else {
            partner = rank - dist;
        }

        if (partner >= 0 && partner < p) {
            MPI_Sendrecv(local_data, local_size, MPI_INT, partner, 0, 
                         recv_buf, local_size, MPI_INT, partner, 0, 
                         MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            
            for (int i = 0; i < local_size; i++) {
                if ((local_data[i] > recv_buf[i]) == (rank < partner)) {
                    int temp = local_data[i];
                    local_data[i] = recv_buf[i];
                    recv_buf[i] = temp;
                }
            }
        }

        // Perform iterative bitonic sort
        bitonic_sort(local_data, 0, local_size, rank < partner);
    }

    free(recv_buf);
}

#endif