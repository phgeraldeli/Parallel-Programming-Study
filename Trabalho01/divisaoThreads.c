/*
 * 
 *  gcc divisaoThreads.c -o divisaoThreads -fopenmp
 * ./divisaoThreads
 *	
 */




#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#include <time.h>

#define SIZE 100
int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];

int main()
{
	int i,j,k,N;
	N = SIZE;
	omp_set_num_threads(4);


	clock_t start = clock();


	// Inicializa Matriz com 1
	#pragma omp parallel private(i,j)
	#pragma omp for
	for(i = 0 ; i < SIZE; i++){
		for(j = 0; j < SIZE; j++) {
			A[i][j] = 2;
			B[i][j] = 2;
			C[i][j] = 0;
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
		printf("\nNumero de threads!! %d\n",omp_get_num_threads() );
	}
	 printf("-------------- Multiplicacao de matriz --------------\n");
	// Printa a matriz
	for(i = 0; i < SIZE; i++) {
		for(j = 0; j < SIZE; j++) {
			printf("%d ", C[i][j]);
		}
		printf("\n");
	}
	clock_t end = clock();
	float seconds = (float)(end - start)/CLOCKS_PER_SEC;
    printf("Durou %f segundos\n", seconds);
	printf("%d",omp_get_num_threads() );

}




