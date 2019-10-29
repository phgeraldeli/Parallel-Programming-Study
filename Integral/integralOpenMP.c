main(int argc, char** argv) {
    int my_rank;
    int p; // número de processos
    float a=0.0, b=1.0; // intervalo a calcular
    int n=1024; // número de trapezóides
    float h; // base do trapezóide
    float local_a, local_b; // intervalo local
    int local_n; // número de trapezóides local
    float integral; // integral no meu intervalo
    float total; // integral total
    int source; // remetente da integral
    int dest=0; // destino das integrais (nó 0)
    int tag=200; // tipo de mensagem (único)
    int i;

    float calcula(float local_a, float local_b,int local_n, float h);
    float f(float x);
    omp_set_num_threads(4);

      h = (b-a) / n;
//    local_n = n / p;
//    local_a = a + my_rank * local_n * h;
//    local_b = local_a + local_n * h;
    integral = 0.0;
    //integral = ( f(a) + f(b) ) /2.0;
    
    int x=a;
    #pragma omp parallel for reduction(+:integral)
    for(i=1;i<=n;i++){
        integral += (i/(double)n)*(i/(double)n);
    }
    integral = integral * h;
    //integral = integral * h;    
    printf("Resultado: %f\n", integral);

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
