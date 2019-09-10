/*
 * #pragma omp for (paralelismo de dados)
 * #pragma omp sections (paralelismo funcional)
 * #pragma omp single (unica thread)
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <string.h>

#define SIZE 10
int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];

int main(int argc, char** argv)
{
	int meu_rank, np, origem, destino, tag = 0;
	int i,j,k,N;
	N = SIZE;
	MPI_Status status;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&meu_rank);
	MPI_Comm_size(MPI_COMM_WORLD,&np);

	for(i = 0 ; i < SIZE; i++){
		for(j = 0; j < SIZE; j++) {
			A[i][j] = 1;
			B[i][j] = 1;
			C[i][j] = 1;
		}
	}

	printf("-------------- Matriz inicializada --------------\n");
	
	for(j = 0; j< N; j++) {
		C[meu_rank][j] = 0.0;
		for(k = 0; k < N ; k++){
			C[meu_rank][j] = C[meu_rank][j] + A[meu_rank][j] * B[k][j];
		}
	}
	
	if(meu_rank != origem) {
		MPI_Send(C[meu_rank], SIZE, MPI_INT, origem, tag, MPI_COMM_WORLD);
	}else {
		for(origem = 1; origem<np; origem++) {
			MPI_Recv(C[meu_rank], SIZE, MPI_INT, origem, tag, MPI_COMM_WORLD, &status);
		}
	}


	for(i = 0; i < SIZE; i++) {
		for(j = 0; j < SIZE; j++){
			printf("%d ", C[i][j]);
		}
		printf("\n");
	}
		
	MPI_Finalize();
}




