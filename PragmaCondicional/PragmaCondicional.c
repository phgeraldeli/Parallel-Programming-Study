#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#define N 10

int main() 
{
	float a[N], b[N];
	int i,n;
	float temp,csum;
	n = N;
	csum = 0.0;

	for(i = 0; i< n ; i++) {
		a[i] = 1;
		b[i] = 1;
	}
	omp_set_num_threads(4);
	#pragma omp parallel shared(a,b,n) private(temp,i) reduction(+:csum)
	{
		#pragma omp for
		for(i=0; i<n ; i++){
			temp = a[i] + b[i];
		        csum += temp + 1;	
		}
	}

	printf("csum = %f\n", csum);
}
