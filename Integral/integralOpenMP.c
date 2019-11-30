#include <stdio.h>
#include <stdlib.h>
<<<<<<< HEAD
#include <string.h>
#include <omp.h>
#include <time.h>

main(int argc, char** argv) {
=======
#include <omp.h>
#include <string.h>
#include <time.h>

void main(int argc, char** argv) {
>>>>>>> b69439c44b713859ea71686bef957c4aa1e77a46
    int my_rank;
    int p; // número de processos
    float a=0.0, b=1.0; // intervalo a calcular

    //int n=256; // número de trapezóides
    //int n=512; // número de trapezóides
    //int n=1024; // número de trapezóides
    int n=1024*1024; // número de trapezóides
   //int n=1024*1024*1024; // número de trapezóides

    float h; // base do trapezóide
    float local_a, local_b; // intervalo local
    int local_n; // número de trapezóides local
    double integral; // integral no meu intervalo
    float total; // integral total
    int source; // remetente da integral
    int dest=0; // destino das integrais (nó 0)
    int tag=200; // tipo de mensagem (único)
    int i;

    float calcula(float local_a, float local_b,int local_n, float h);
    float f(float x);
    clock_t start = clock();
    omp_set_num_threads(4);

    h = (b-a) / n;
    
    integral = 0.0;
    
    int x=a;
    #pragma omp parallel for reduction(+:integral)
<<<<<<< HEAD
    for(i=1; i<n;i++){
        integral += (i/(double)n)*(i/(double)n);
    }
    integral = integral * h;  
    integral += 1.0/(2*n);
    total=integral;
    printf("Resultado: %f\n", total);
    clock_t end = clock();
    float seconds = (float)(end - start)/CLOCKS_PER_SEC;
    printf("Durou %f segundos\n", seconds);
=======
    for(i=1;i < n;i++){
        integral += (i/(double)n)*(i/(double)n);
    }
    integral = integral * h;
    integral += 1.0/(2.0*n);
    printf("Resultado: %f\n", integral);
>>>>>>> b69439c44b713859ea71686bef957c4aa1e77a46

    clock_t end = clock();
	float seconds = (float)(end - start)/CLOCKS_PER_SEC;
    printf("Durou %f segundos\n", seconds);
}

float calcula(float local_a, float local_b,int local_n, float h) {
    float integral;
    float x, i;
    float f(float x); // função a integrar
    integral = ( f(local_a) + f(local_b) ) /2.0;
    x = local_a;
    for( i=1; i<=local_n; i++) {
        x += h;
        integral += f(x);
    }
    integral *= h;

    return integral;
}


float f(float x) {

    float fx; // valor de retorno

    // esta é a função a integrar
    // exemplo: função quadrática
    fx = x * x;

    return fx;
}
