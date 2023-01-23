#include <omp.h>

long long int sum(int *v, long long int N){
	long long int i = 0, sum = 0, sum_local = 0;
	
	#pragma omp parallel private(i, sum_local)
	{
	sum_local = 0;
	#pragma omp for
	for(i = 0; i < N; i++)
		sum_local += v[i];

	#pragma omp atomic
	sum += sum_local;
	}

	return sum;
}