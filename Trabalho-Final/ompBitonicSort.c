#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
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

void bitonicSortFromBitonicSequence( int inicio ,int fim, int dir , int *ar )     //form a increaseing or decreasing array when a bitonic input is given to the function
    {
        if(dir == 1)
        {
            int counter = 0;                                                                    //counter to keep track of already swapped elements ,, parallelising this area results in poor performance due to overhead ,,need to fix
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
        else                                                                                    //decending sort
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
void bitonicSequenceGenerator(int inicio , int fim , int *ar)                         //generate a bitonic sequence  from a a random order
{
    int meio = fim - inicio +1;
      for(int j = 2;j<=meio;j = j*2)
            {   
                #pragma omp parallel for                                                         //parallel implementation results in most performance gains here
                for(int i=0;i<meio;i=i+j)
                {
                 if(((i/j)%2) ==0)                                                               //extra computation results in drastically lower performance ,need to fix
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
    srand(time(NULL));
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

int main()                                                                                        //main driver function
{   
    clock_t start = clock();
    omp_set_dynamic(0);                                                                          //disabled so that the os doesnt override the thread settings                                                     
    int maxNumberOfThreads = omp_get_num_procs();                                                //gives number of logical cores
    omp_set_num_threads(maxNumberOfThreads);                                                     //set the no of threads

    int *ar = malloc(sizeof(int)*SIZE);
    GeraAleatorios(ar,SIZE,SIZE);
    printArray(ar,SIZE);
    bitonicSequenceGenerator(0,SIZE-1,ar);
    printArray(ar,SIZE);
    clock_t end = clock();
    float seconds = (float)(end - start)/CLOCKS_PER_SEC;
    printf("\nO Algoritmo Levou %f segundos\n", seconds);

}