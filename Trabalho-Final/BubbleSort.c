#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 1024
#define true 1
#define false 0

int A[SIZE];

void GeraAleatorios(int numero[], int quantNumeros, int Limite) {
    srand(time(NULL));
    int valor;

    for (int i = 0; i < quantNumeros; i++){
        valor = rand() % Limite;
        numero[i] = valor;
    }
}

void printa_vetor(int vetor[], int length) {
    printf("[%d, ", vetor[0]);
    for (int i = 1; i < length - 1; i++)
    {       
        printf("%d, ", vetor[i]);
    }
    printf("%d]\n", vetor[length]);
} 

int main(int argc, char** argv) {

    int aux;

    GeraAleatorios(A, SIZE, SIZE);
    clock_t start = clock();
    
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (A[j] > A[j + 1])
            {
                aux = A[j];
                A[j] = A[j+1];
                A[j+1] = aux;
            }
            
        }
        
    }
    clock_t end = clock();
    float seconds = (float)(end - start)/CLOCKS_PER_SEC;
    printa_vetor(A, SIZE);
    printf("Durou %f segundos\n", seconds);
}