#include <stdlib.h>
#include <time.h>
#include <stdio.h>

// Define Tamanho do Array a ser ordenado
#define SIZE 1024
int arr[SIZE];

//Gera números aleatórios preenchendo o array
void GeraAleatorios(int numero[], int quantNumeros, int Limite) {
    srand(time(NULL));
    int valor;

    for (int i = 0; i < quantNumeros; i++){
        valor = rand() % Limite;
        numero[i] = valor;
    }
}

// void merge(int arr[], int inicio, int meio, int fim) {
//     // Define o tamanho do array da esquerda e da direita
//     int n1 = meio - inicio + 1;
//     int n2 = fim - meio;
//     int esquerda[n1], direita[n2];

    
// }

void merge(int arr[], int inicio, int meio, int fim) 
{ 
    int i, j, k; 
    // Define o tamanho do array da esquerda e da direita
    int n1 = meio - inicio + 1; 
    int n2 =  fim - meio; 
    int L[n1], R[n2]; 
  
    /* Percorre o array recebido colocando no auxiliar esquerda
    *  todos os numeros a serem ordenados da parte anterior
    */    
    for (i = 0; i < n1; i++) 
        L[i] = arr[inicio + i]; 
        
    /* Percorre o array recebido colocando no auxiliar esquerda
    *  todos os numeros a serem ordenados da parte posterior
    */    
    for (j = 0; j < n2; j++) 
        R[j] = arr[meio + 1+ j]; 
  
    i = 0;
    j = 0;
    k = inicio;
    /*
    * Enquanto os 2 arrays tiverem numeros a serem contabilizados
    * percorra os mesmos.
    */
    while (i < n1 && j < n2) 
    { 
        // Se o primeiro de L for menor que o primeiro de R coloca 
        // o numero de L no array
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else // Caso contrário coloca o numero de R
        { 
            arr[k] = R[j]; 
            j++; 
        }
        k++; 
    } 
    // No caso de 1 dos arrays forem totalmente percorridos
    // Todos os números do arary que sobrou são maiores
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
}   


// Ordena o array
void mergeSort(int arr[], int inicio, int fim) 
{ 
    if (inicio < fim) 
    { 
        // Define o meio do array
        int meio = inicio+(fim-inicio)/2; 
  
        //Divide o array na metade anterior
        mergeSort(arr, inicio, meio); 
        //Divide o array na metade posterior
        mergeSort(arr, meio+1, fim); 

        //Faz o merge dos arrays
        merge(arr, inicio, meio, fim); 
    } 
} 
  
/* UTILITY FUNCTIONS */
/* Function to print an array */
void printArray(int A[], int size) 
{ 
    int i; 
    for (i=0; i < size; i++) 
        printf("%d ", A[i]); 
    printf("\n"); 
} 
  
int main() 
{ 
    clock_t start = clock();
    GeraAleatorios(arr, SIZE, SIZE);
    int arr_size = sizeof(arr)/sizeof(arr[0]); 
    
  
    mergeSort(arr, 0, arr_size - 1); 
  
    clock_t end = clock();
    float seconds = (float)(end - start)/CLOCKS_PER_SEC;
    printf("\nArray ordenado: \n"); 
    printArray(arr, arr_size); 
    printf("\nO Algoritmo Levou %f segundos\n", seconds);
    return 0; 
} 
