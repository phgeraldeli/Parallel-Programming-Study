//mpicc Trab01.c -o Trab01
//mpirun -np 4 Trab01


#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <string.h>
#include <time.h>

#define SIZE 100
int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];

int main(int argc, char** argv)
{
	int meu_rank, np, origem, destino, tag = 0, master=0;
	int i,j,k,N;
	N = SIZE;
	MPI_Status status;
    clock_t start = clock();
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&meu_rank);
	MPI_Comm_size(MPI_COMM_WORLD,&np);

    
 

	for(i = 0 ; i < SIZE; i++){
		for(j = 0; j < SIZE; j++) {
			A[i][j] = 2;
			B[i][j] = 2;
			C[i][j] = 0;
		}
	}

	printf("-------------- Matriz inicializada --------------\n");


		for(i = meu_rank; i < N; i+=np){
			for(j = 0; j < N; j++){
				for(k = 0; k < N; k++){
				C[i][j] = C[i][j] + A[i][k] * A[k][j];
			}
		}
	}
	
	if(meu_rank != master) {
		for(i=meu_rank;i<N;i+=np){
            //Data, Count, Datatype, destination, tag, comunicador
			MPI_Send(C[i], SIZE, MPI_INT, master, tag, MPI_COMM_WORLD);
		}
	}else {
		for(origem = 1; origem<np; origem++) {
			for(j = origem;j < N;j += np){
                //Data, Count, Datatype, origem, tag, comunicador, status
				MPI_Recv(C[j], SIZE, MPI_INT, origem, tag, MPI_COMM_WORLD, &status);
			}
		}
	

        printf("\n");
	    for(i = 0; i < N; i++){
		    for(j = 0; j < N; j++){
			    printf("%d ", C[i][j]);
		    }
		    printf("\n");
	    }
	    printf("\n");
	    
	    clock_t end = clock(); 
        float seconds = (float)(end - start)/CLOCKS_PER_SEC;
        printf("Durou %f segundos\n", seconds);
	}	
	MPI_Finalize();
	return 0;
}



