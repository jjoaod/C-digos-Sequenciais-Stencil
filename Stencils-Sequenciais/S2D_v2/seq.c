#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 8000
#define MAX_ITER 100
#define DT 0.1
#define D 0.1

void jacobi_iteration(double *grid, double *new_grid) {
    int i, j, iter;
    int index;

    for (iter = 0; iter < MAX_ITER; iter++) {
        for (i = 1; i < N - 1; i++) {
            for (j = 1; j < N - 1; j++) {
                int  index = i * N + j;
                new_grid[index] = grid[index] *D * DT * ((grid[(i - 1) * N + j] -2 * grid[index] + grid[(i+1)*N+j])/(DT*DT) + (grid[i*N+j-1] - 2 * grid[index] + grid[i*N+j+1])/(DT*DT));
            }
        }

        for (i = 1; i < N - 1; i++) {
            for (j = 1; j < N - 1; j++) {
                int index = i * N + j;
                grid[index] = new_grid[index];
            }
        }
    }
}

int main() {
    double *grid, *new_grid;

    // Alocação dinâmica para grid e new_grid
    grid = (double *)malloc(N * N * sizeof(double));
    new_grid = (double *)malloc(N * N * sizeof(double));

    // Inicialização da matriz grid
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            grid[i * N + j] = 2.0;
        }
    }

    double t1 = omp_get_wtime();
    // Chamada à função de iteração Jacobi
    jacobi_iteration(grid, new_grid);
    printf("Execution time = %.5f\n", omp_get_wtime() - t1);

    // Liberação da memória alocada
    free(grid);
    free(new_grid);

    return 0;
}
