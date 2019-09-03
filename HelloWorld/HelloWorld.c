/*
 * How to compile:
 *
 * gcc -o HelloWorld HelloWorld.c -fopenmp
 *
 */

#include <stdio.h>
#include <omp.h>

void main(){
	#pragma omp parallel
	{
		int np = omp_get_num_threads();
		int id = omp_get_thread_num();
		printf("Hello from thread(%d) from (total of %d)\n",id,np);
	}
}
