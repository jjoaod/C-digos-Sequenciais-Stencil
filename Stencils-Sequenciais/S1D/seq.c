#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 10000000
#define MAX_ITER 1000

void jacobi_iteration_1d(double *array) {
    double *new_array = malloc(sizeof(double)*N);

    int i, iter;
    
    for (iter = 0; iter < MAX_ITER; iter++) {
        for (i = 1; i < N-1; i++) {
            new_array[i] = (array[i-1] + array[i+1]) / 2.0;
        }
        for (i = 1; i < N-1; i++) {
            array[i] = new_array[i];
        }
    }
    free(new_array);
}

int main() {
    double *array = malloc(sizeof(double)*N); 

    for(int i=0; i<N; i++)
	    array[i]= (double) i *1.1;

    double t1  = omp_get_wtime();
    jacobi_iteration_1d(array);
    printf("Execution time = %.5f\n", omp_get_wtime() - t1);
   
    free(array);
    return 0;
}
