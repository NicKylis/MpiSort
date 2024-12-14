#ifndef MpiSort
#define MpiSort

#include <mpi.h>

void mpi_bitonic_sort(int Array[], int low, int count, int dir); // The main bitonic sort algorithm
void swap(int *a, int *b); // Helper swap function
void compare_and_swap(int Arrayay[], int i, int j, int dir); // Helper function for elbow sort
void elbow_sort(int Array[], int low, int count, int dir); // Merger function

void mpi_bitonic_sort(int Array[], int low, int count, int dir){
    if (count > 1) {
       int mid = count / 2;

       mpi_bitonic_sort(Array, low, mid, 1);  // Sort first half in ascending order
       mpi_bitonic_sort(Array, low + mid, mid, 0);  // Sort second half in descending order
       elbow_sort(Array, low, count, dir);  // Merge the two halves
     }
}

// Swaps two integers
void swap(int *a, int *b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

// Comparison and swap based on the direction (1 for ascending, 0 for descending)
void compare_and_swap(int Array[], int i, int j, int dir){
    if ((dir == 1 && Array[i] > Array[j]) || (dir == 0 && Array[i] < Array[j])) {
        swap(&Array[i], &Array[j]);
    }
}

void elbow_sort(int Array[], int low, int count, int dir){

    if (count > 1) {
        int mid = count / 2;

        for (int i = low; i < low + mid; i++) {
            compare_and_swap(Array, i, i + mid, dir);
        }

        elbow_sort(Array, low, mid, dir);
        elbow_sort(Array, low + mid, mid, dir);
    }
}
#endif