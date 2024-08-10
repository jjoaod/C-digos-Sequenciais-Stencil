#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 256
#define MAX_ITER 1000
#define DT 0.1
#define D 0.1

void heat_diffusion_3d(double *grid, double *new_grid) {
    int i, j, k, iter;
    int index;

    for (iter = 0; iter < MAX_ITER; iter++) {
        // Atualiza new_grid com a difusão de calor
        for (i = 1; i < N-1; i++) {
            for (j = 1; j < N-1; j++) {
                for (k = 1; k < N-1; k++) {
                    index = i * (N * N) + j * N + k;
                    new_grid[index] = grid[index] + D * DT * (
                        (grid[(i-1) * (N * N) + j * N + k] - 2 * grid[index] + grid[(i+1) * (N * N) + j * N + k]) / (DT * DT) +
                        (grid[i * (N * N) + (j-1) * N + k] - 2 * grid[index] + grid[i * (N * N) + (j+1) * N + k]) / (DT * DT) +
                        (grid[i * (N * N) + j * N + (k-1)] - 2 * grid[index] + grid[i * (N * N) + j * N + (k+1)]) / (DT * DT));
                }
            }
        }

        // Atualiza grid com o novo valor
        for (i = 1; i < N-1; i++) {
            for (j = 1; j < N-1; j++) {
                for (k = 1; k < N-1; k++) {
                    index = i * (N * N) + j * N + k;
                    grid[index] = new_grid[index];
                }
            }
        }
    }
}

int main() {
    double *grid, *new_grid;
    int size = N * N * N;
    int i, j, k, index;

    // Alocação dinâmica para grid e new_grid
    grid = (double *)malloc(size * sizeof(double));
    new_grid = (double *)malloc(size * sizeof(double));

    // Inicialização da matriz grid
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < N; k++) {
                index = i * (N * N) + j * N + k;
                grid[index] = i;
            }
        }
    }

    double t1 = omp_get_wtime();
    // Chamada à função de difusão de calor
    heat_diffusion_3d(grid, new_grid);

    printf("Time = %.5f\n", omp_get_wtime() - t1);
    // Liberação da memória alocada para grid e new_grid
    free(grid);
    free(new_grid);

    return 0;
}
