#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

// Define Tamanho do Array a ser ordenado
#define SIZE 1024
int arr[SIZE];

//Gera números aleatórios preenchendo o array
void GeraAleatorios(int numero[], int quantNumeros, int Limite) {
    srand(time(NULL));
    int valor;

    for (int i = 0; i < quantNumeros; i++){
        valor = rand() % quantNumeros/2;
        numero[i] = valor;
        // printf("%d ", valor);
    }
}

void printArray(int A[], int size) 
{ 
    int i; 
    for (i=0; i < size; i++) 
        printf("%d ", A[i]); 
    printf("\n"); 
} 


void merge(int arr_local[], int inicio, int meio, int fim) {
    // Define o tamanho do array da esquerda e da direita
    int tamEsquerda = meio - inicio + 1;
    int tamDireita = fim - meio;
    int esquerda[tamEsquerda], direita[tamDireita];
    //Percorre o array recebido colocando nos auxiliares
    for(int i = 0; i < tamEsquerda; i++) esquerda[i] = arr_local[inicio + i];   
    for(int i = 0; i < tamDireita; i++) direita[i] = arr_local[meio + 1+ i];   

    /*
    * Enquanto os 2 arrays tiverem numeros a serem contabilizados
    * percorra os mesmos.
    */
    int i = 0,j = 0,atual = inicio;
    while(i < tamEsquerda && j < tamDireita) {
        if(esquerda[i] <= direita[j]){
            arr_local[atual] = esquerda[i];
            i++;
        }else {
            arr_local[atual] = direita[j];
            j++;
        }
        atual++;
    }
    // No caso de 1 dos arrays forem totalmente percorridos
    // Todos os números do arary que sobrou são maiores
    while(i < tamEsquerda) {
        arr_local[atual] = esquerda[i];
        i++;
        atual++;
    }
    while(j < tamDireita) {
        arr_local[atual] = direita[j];
        j++;
        atual++;
    }
}

// Ordena o array
void mergeSort(int sub_arr[], int inicio, int fim, int max) 
{ 
    if (inicio < fim) 
    { 
        // Define o meio do array
        int meio = (inicio+fim)/2; 
        if(max!=0){
            //Divide o array na metade anterior
            mergeSort(sub_arr, inicio, meio,max-1); 
            //Divide o array na metade posterior
            mergeSort(sub_arr, meio+1, fim,max-1); 
        }
        //Faz o merge dos arrays
        // printf("Chamou Com inicio=%d, meio=%d e fim=%d",inicio,meio,fim); 
        merge(sub_arr, inicio, meio, fim); 
    } 
} 
  
  
int main(int argc, char** argv) 
{ 
    int rank;
	int np;	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
    clock_t start = clock();
    GeraAleatorios(arr, SIZE, SIZE);

    int arr_size = sizeof(arr)/sizeof(arr[0]);  
    int local_size = SIZE/np;
	
    int *sub_array = malloc(local_size * sizeof(int));
	MPI_Scatter(arr, local_size, MPI_INT, sub_array, local_size, MPI_INT, 0, MPI_COMM_WORLD);
    
    mergeSort(sub_array, 0, local_size - 1,-1); 

    int *sorted = NULL;
	if(rank == 0) {
		
		sorted = malloc(SIZE * sizeof(int));
		
		}
	
	MPI_Gather(sub_array, local_size, MPI_INT, sorted, local_size, MPI_INT, 0, MPI_COMM_WORLD);


  
    if(rank == 0) {

        // printf("\nArray antes final merge: \n");

        // printArray(sorted, SIZE);
			
		// printf("\n");
		// printf("\n");
        
        mergeSort(sorted, 0, SIZE - 1,2); 

        printf("\nArray ordenado: \n");

        printArray(sorted, SIZE);
			
		printf("\n");
		printf("\n");

	    clock_t end = clock();
	    float seconds = (float)(end - start)/CLOCKS_PER_SEC;
    	printf("\nO Algoritmo Levou %f segundos\n", seconds);

    }



	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();


  
    // printf("\nArray ordenado: \n"); 
    // printArray(arr, arr_size); 

    return 0; 
} 