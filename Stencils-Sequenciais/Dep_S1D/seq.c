#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 20000000  // Example size; change as needed
#define MAX_ITER 1000

void gauss_seidel_iteration_1d(double* array, int size) {
    int i, iter;

    for (iter = 0; iter < MAX_ITER; iter++) {
        for (i = 1; i < size; i++) {
            array[i] += (array[i - 1] / 2.0);
    	}
    }
}

int main() {
    int size = N;
    double* array = (double*)malloc(size * sizeof(double));

    // Initialize array with some values, for example:
    for (int i = 0; i < size; i++) {
        array[i] = i * 1.0;  // Example initialization
    }

    double t1 = omp_get_wtime();
    gauss_seidel_iteration_1d(array, size);
    printf("Execution time = %.5f\n", omp_get_wtime() - t1);
   
    free(array);

    return 0;
}
