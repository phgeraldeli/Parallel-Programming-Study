/*
 * #pragma omp for (paralelismo de dados)
 * #pragma omp sections (paralelismo funcional)
 * #pragma omp single (unica thread)
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>

#define SIZE 10
int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];

int main()
{
	int i,j,k,N;
	N = SIZE;
	// Inicializa Matriz com 1
	#pragma omp parallel private(i,j)
	#pragma omp for
	for(i = 0 ; i < SIZE; i++){
		for(j = 0; j < SIZE; j++) {
			A[i][j] = 1;
			B[i][j] = 1;
			C[i][j] = 1;
		}
	}

	printf("-------------- Matriz inicializada --------------\n");

	// Printa a matriz
        for(i = 0; i < SIZE; i++) {
                for(j = 0; j < SIZE; j++) {
                        printf("%d ", C[i][j]);
                }
                printf("\n");
        }

	//Paralelizando Multiplicacao de matrizes
	#pragma omp parallel shared(A,B,C,N) private(i,j,k)
	#pragma omp for 
	for(i = 0; i < N; i++){
		for( j = 0; j < N; j++) {
			C[i][j] = 0.0;
			for (k = 0; k < N ; k++) {
				C[i][j] = C[i][j] + A[i][k] * B[k][j];
			}
		}
	}
	 printf("-------------- Multiplicacao de matriz --------------\n");
	// Printa a matriz
	for(i = 0; i < SIZE; i++) {
		for(j = 0; j < SIZE; j++) {
			printf("%d ", C[i][j]);
		}
		printf("\n");
	}

}




