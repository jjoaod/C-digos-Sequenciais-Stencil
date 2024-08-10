#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define WIDTH 40000
#define HEIGHT 40000

void apply_edge_detection(int *image) {
    int i, j, k, l;
    int *temp_image = (int *)malloc(WIDTH * HEIGHT * sizeof(int));
    int kernel[3][3] = {{-1, -1, -1},
                        {-1,  8, -1},
                        {-1, -1, -1}};

    for (i = 1; i < WIDTH-1; i++) {
        for (j = 1; j < HEIGHT-1; j++) {
            int sum = 0;
            for (k = -1; k <= 1; k++) {
                for (l = -1; l <= 1; l++) {
                    sum += kernel[k+1][l+1] * image[(i+k)*HEIGHT + (j+l)];
                }
            }
            temp_image[i*HEIGHT + j] = sum;
        }
    }

    for (i = 1; i < WIDTH-1; i++) {
        for (j = 1; j < HEIGHT-1; j++) {
            image[i*HEIGHT + j] = temp_image[i*HEIGHT + j];
        }
    }

    free(temp_image);
}

int main() {
    int *image = (int *)malloc(WIDTH * HEIGHT * sizeof(int));
    
    // Inicialização da imagem (exemplo)
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            image[i*HEIGHT + j] = i + j;  // Apenas um exemplo para preencher a imagem
        }
    }

  double t1 = omp_get_wtime();
    apply_edge_detection(image);
    printf("Execution time = %.5f\n", omp_get_wtime() - t1);

    // Limpeza da memória alocada
    free(image);

    return 0;
}
