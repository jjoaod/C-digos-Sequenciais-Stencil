#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 8000
#define MAX_ITER 1000

void gauss_seidel_iteration(double *grid) {
    int i, j, iter;

    for (iter = 0; iter < MAX_ITER; iter++) {
        for (i = 1; i < N-1; i++) {
            for (j = 1; j < N-1; j++) {
                grid[i * N + j] += (grid[(i-1) * N + j]) / 4.0;
            }
        }
    }
}

int main() {
    // Aloca dinamicamente a grade em um único vetor de tamanho N * N
    double *grid = (double *)malloc(N * N * sizeof(double));
    
    // Inicializa a grade com zeros
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            grid[i * N + j] = 0.0;
        }
    }

    double t1 = omp_get_wtime();
    gauss_seidel_iteration(grid);
    printf("Execution time = %.5f\n", omp_get_wtime() - t1);

    // Libera a memória alocada
    free(grid);

    return 0;
}
