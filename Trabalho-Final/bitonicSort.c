#include<stdio.h>
#include<stdlib.h>
#include <time.h>

void ascendingSwap(int index1, int index2, int *arr) {
    if(arr[index2] < arr[index1]) {
        int temp = arr[index2];
        arr[index2] = arr[index1];
        arr[index1] = temp;
    }
}

void decendingSwap(int index1 , int index2 , int *arr)
{
  if(arr[index1] < arr[index2])
  {
      int temp = arr[index2];
      arr[index2] = arr[index1];
      arr[index1] = temp;
  }
}

void bitonicSortFromBitonicSequence( int inicio ,int fim, int dir , int *ar )    
    {
        if(dir == 1)
        {
            int counter = 0;
            int meio = fim - inicio + 1;
            for(int j = meio/2;j>0;j = j/2)
            {   counter =0;
                for(int i = inicio ; i +j <= fim ; i++)
                {
                        if(counter < j)
                        {
                            ascendingSwap(i,i+j,ar);
                            counter++;

                        }
                        else 
                        {
                            counter =0;
                            i = i+ j-1;
                            
                        }
                }
            }
        }
        else 
        {
            int counter = 0;
            int meio = fim - inicio + 1;
            for(int j = meio/2;j>0;j = j/2)
            {   counter =0;
                for(int i = inicio ; i <= (fim-j) ; i++)
                {
                        if(counter < j)
                        {
                            decendingSwap(i,i+j,ar);
                            counter++;

                        }
                        else 
                        {
                            counter =0;
                            i = i+ j-1;
                            
                        }
                }
            }
        }
    
    }
void bitonicSequenceGenerator(int inicio , int fim , int *ar)
{
    int meio = fim - inicio +1;
      for(int j = 2;j<=meio;j = j*2)
            {   
                for(int i=0;i<meio;i=i+j)
                {
                 if(((i/j)%2) ==0) 
                 {
                     bitonicSortFromBitonicSequence(i,i+j-1,1,ar);
                 }   
                 else
                 {
                     bitonicSortFromBitonicSequence(i,i+j-1,0,ar);
                 }
                }
            }
}



//Gera números aleatórios preenchendo o array
void GeraAleatorios(int numero[], int quantNumeros, int Limite) {
    srand(time(NULL))   ;
    int valor;

    for (int i = 0; i < quantNumeros; i++){
        valor = rand() % Limite;
        numero[i] = valor;
    }
}

void printArray(int *A, int size) 
{ 
    int i; 
    for (i=0; i < size; i++) 
        printf("%d ", A[i]); 
    printf("\n"); 
} 

// Define Tamanho do Array a ser ordenado
#define SIZE 1024

int main()
{   
    clock_t start = clock();

    int *ar = malloc(sizeof(int)*SIZE);
    GeraAleatorios(ar,SIZE,SIZE);

    bitonicSequenceGenerator(0,SIZE-1,ar);

    clock_t end = clock();
    float seconds = (float)(end - start)/CLOCKS_PER_SEC;
    printf("%f\n", seconds);

}