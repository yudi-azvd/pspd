#include <stdio.h>
#include <omp.h>

int main(){
	int myid, nthreads;

	nthreads = omp_get_num_threads();
	#pragma omp parallel private(myid) shared(nthreads)
	{
		myid = omp_get_thread_num();
		printf("%d of %d - hello world!\n", myid, nthreads);
	}

	return 0;
}