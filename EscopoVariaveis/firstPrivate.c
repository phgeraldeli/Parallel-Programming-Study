#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

int main()
{
	int a = 1,b = 2;
	int c = 3;
	
	/* firstprivate passa a variavel de fora para dentro das paralelizacoes 
	 * de forma que todas as replicacoes vao somar o a de fora com o 1, deixando
	 * o codigo consistente
	 *
	 * reduction(op:var)
	 * Reduction faz a operação passada como parametro em todas as threads, ou seja
	 * se eu tenho 2 threads e uma soma com pragma omp parallel no final temos:
	 * reduction(op:somaTotal) => (somaTotal op somaTotal)
	 * 
	 * ps: reduction é um fistprivate!
       	*/

	#pragma omp parallel firstprivate(a)
	{
		a += 1;
		c += 7;
		printf("A becomes %d, b is %d \n",a,b);
	}

}

