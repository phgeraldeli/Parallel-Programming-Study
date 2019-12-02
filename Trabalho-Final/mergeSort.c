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


void merge(int arr[], int inicio, int meio, int fim) {
    // Define o tamanho do array da esquerda e da direita
    int tamEsquerda = meio - inicio + 1;
    int tamDireita = fim - meio;
    int esquerda[tamEsquerda], direita[tamDireita];
    //Percorre o array recebido colocando nos auxiliares
    for(int i = 0; i < tamEsquerda; i++) esquerda[i] = arr[inicio + i];   
    for(int i = 0; i < tamDireita; i++) direita[i] = arr[meio + 1+ i];   

    /*
    * Enquanto os 2 arrays tiverem numeros a serem contabilizados
    * percorra os mesmos.
    */
    int i = 0,j = 0,atual = inicio;
    while(i < tamEsquerda && j < tamDireita) {
        if(esquerda[i] <= direita[j]){
            arr[atual] = esquerda[i];
            i++;
        }else {
            arr[atual] = direita[j];
            j++;
        }
        atual++;
    }
    // No caso de 1 dos arrays forem totalmente percorridos
    // Todos os números do arary que sobrou são maiores
    while(i < tamEsquerda) {
        arr[atual] = esquerda[i];
        i++;
        atual++;
    }
    while(j < tamDireita) {
        arr[atual] = direita[j];
        j++;
        atual++;
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
  

int main() 
{ 
    clock_t start = clock();
    GeraAleatorios(arr, SIZE, SIZE);
    int arr_size = sizeof(arr)/sizeof(arr[0]);

    mergeSort(arr, 0, arr_size - 1); 

    clock_t end = clock();
    float seconds = (float)(end - start)/CLOCKS_PER_SEC;
    printf("%f\n", seconds);
    return 0; 
} 
