#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
/*
 * How to compile:
 *
 * gcc -o HelloWorld4Threads HelloWorldSettingNumbersofThreads.c -fopenmp
 *
 */
int main() 
{
	// ou #pragma omp parallel num_threads(4)
	omp_set_num_threads(4);
	#pragma omp parallel
	{
		int np = omp_get_num_threads();
		int iam = omp_get_thread_num();
		printf("Hello from thread %d (total %d)\n",iam,np);
	}
}
