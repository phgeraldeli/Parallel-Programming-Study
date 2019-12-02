#include<stdio.h>
#include<stdlib.h>
#include <time.h>

#define UP 0
#define DOWN 1
#define SIZE 1024

int tamSubparte;

void printfArray(int* seq, int size) {
    printf("[ %d,", seq[0]);
    for (int i = 1; i < size; i++)
    {
        printf("%d, ", seq[i]);
    }
    printf("%d]\n", seq[size-1]);
}

void GeraAleatorios(int numero[], int quantNumeros, int Limite) {
    srand(time(NULL))   ;
    int valor;

    for (int i = 0; i < quantNumeros; i++){
        valor = rand() % Limite;
        numero[i] = valor;
    }
}

main() {
    int i, j, n, numThreads, id;
    int *seq;

    n = SIZE;
    seq = (int *) malloc (n * sizeof(int));
    numThreads =  2;
    tamSubparte = n / numThreads;

    clock_t start = clock();
    GeraAleatorios(seq,n,n);

    /*
        Do menor pro maior
        9 6 7 4 4 8 7 6
        --> <-- --> <--  1 rodada
        6 9 7 4 4 8 7 6
        ---->     <----  2 Rodada
          ----> <----
        6 4 7 9 7 8 4 6
        --> --> <-- <-- 3 Rodada
        Temos:
        4 6 7 9 8 7 4 6
             -> <-
           -       -
        -            -
        Geramos duas bitonic sequence com posições:
        pos 0 1 2 3 ascendente
        pos 4 5 6 7 descendente
    */
    for (i = 2; i <= tamSubparte; i = 2 * i)
    {
        #pragma omp parallel for shared(i, seq) private(j)
        for (j = 0; j < n; j += i)
        {
            if ((j / i) % 2 == 0)
                bitonic_sort_seq(j, i, seq, UP);
            else
                bitonic_sort_seq(j, i, seq, DOWN);
        }
    }

    for (i = 2; i <= numThreads; i = 2 * i)
    {
        for (j = 0; j < numThreads; j += i)
        {
            if ((j / i) % 2 == 0)
                bitonic_sort_par(j*tamSubparte, i*tamSubparte, seq, UP);
            else
                bitonic_sort_par(j*tamSubparte, i*tamSubparte, seq, DOWN);
        }
#pragma omp parallel for shared(j)
        for (j = 0; j < numThreads; j++)
        {
            if (j < i)
                bitonic_sort_seq(j*tamSubparte, tamSubparte, seq, UP);
            else
                bitonic_sort_seq(j*tamSubparte, tamSubparte, seq, DOWN);
        }
    }

    clock_t end = clock();

    printfArray(seq, n);
    float seconds = (float)(end - start)/CLOCKS_PER_SEC;
    printf("%f\n", seconds);
    free(seq);
}


void bitonic_sort_seq(int start, int length, int *seq, int flag)
{

    if (length == 1)
        return;

    int i;
    int split_length;

    split_length = length / 2;

    // bitonic split
    for (i = start; i < start + split_length; i++)
    {
        if (flag == UP)
        {
            if (seq[i] > seq[i + split_length])
                swap(&seq[i], &seq[i + split_length]);
        }
        else
        {
            if (seq[i] < seq[i + split_length])
                swap(&seq[i], &seq[i + split_length]);
        }
    }

    bitonic_sort_seq(start, split_length, seq, flag);
    bitonic_sort_seq(start + split_length, split_length, seq, flag);
}

void bitonic_sort_par(int start, int length, int *seq, int flag)
{
    int i;
    int split_length;

    if (length == 1)
        return;

    if (length % 2 !=0 )
    {
        printf("The length of a (sub)sequence is not divided by 2.\n");
        exit(0);
    }

    split_length = length / 2;

    // bitonic split
#pragma omp parallel for shared(seq, flag, start, split_length) private(i)
    for (i = start; i < start + split_length; i++)
    {
        if (flag == UP)
        {
            if (seq[i] > seq[i + split_length])
                swap(&seq[i], &seq[i + split_length]);
        }
        else
        {
            if (seq[i] < seq[i + split_length])
                swap(&seq[i], &seq[i + split_length]);
        }
    }

    if (split_length > tamSubparte)
    {
        // tamSubparte -> n/numThreads
        bitonic_sort_par(start, split_length, seq, flag);
        bitonic_sort_par(start + split_length, split_length, seq, flag);
    }

    return;
}

void swap(int *a, int *b)
{
    int t;
    t = *a;
    *a = *b;
    *b = t;
}