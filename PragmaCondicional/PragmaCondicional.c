#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#define N 10000

int main() 
{
	float a[N], b[N];
	int i,n;
	float temp,csum;
	n = 10;
	csum = 0.0;

	for(i = 0; i< n ; i++) {
		a[i] = 1;
		b[i] = 1;
	}

	#pragma omp parallel shared(a,b,n) private(temp,i) reduction(+:csum)
	{
		for(i=0; i<n ; i++){
			temp = a[i] / b[i];
		        csum += temp + 1;	
		}
	}

	printf("csum = %f\n", csum);
}
