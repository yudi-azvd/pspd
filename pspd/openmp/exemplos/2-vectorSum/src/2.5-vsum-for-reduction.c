#include <omp.h>

long long int sum(int *v, long long int N){
	long long int i = 0, sum = 0;

	#pragma omp parallel for private(i) reduction(+ : sum)
	for(i = 0; i < N; i++)
		sum += v[i];	
	
	return sum;
}