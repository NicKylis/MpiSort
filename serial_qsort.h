#ifndef SERIAL_QSORT_H
#define SERIAL_QSORT_H

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int cmp_asc(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int cmp_desc(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);  // Reverse the order for descending
}

#endif