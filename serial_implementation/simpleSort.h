#ifndef simpleSort
#define simpleSort

#include <stdio.h>
#include <stdlib.h>

int compare_int(const void *a, const void *b); // Helper function
void serial_sorting(int Array[], int N); // The serial sorting method for testing

// Requirement for qsort, comparison between ints
int compare_int(const void *a, const void *b){
    return (*(int*)a - *(int*)b);
}

// Serial sorting of a 1d array of N elements with qsort()
void serial_sorting(int Array[], int N){
    qsort(Array, N, sizeof(int), compare_int);
}

#endif