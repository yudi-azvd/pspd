#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>

void selection_sort(int *v, int n){
	int i, j, min, tmp;

	for(i = 0; i < n - 1; i++){
		min = i;

		for(j = i + 1; j < n; j++)
			if(v[j] < v[min])
				min = j;

		tmp = v[i];
		v[i] = v[min];
		v[min] = tmp;
	}
}

int compare (const void * a, const void * b){
  return (* (int*) a - * (int*) b);
}

int main(int argc, char **argv){
	char *resposta[] = { "errada", "ok" };
	int *vector, *test;
	int i, n, is_ok;
	double elapsed_q, start_q, end_q;
	double elapsed_s, start_s, end_s;

	if(argc < 2){
		fprintf(stderr, "Uso: %s <número de elementos>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	n = atoi(argv[1]);
	n *= 10e3;

	printf("Número de elementos: %d * 10E3\n", (int) (n / 10e3));

	vector = (int *) malloc(n * sizeof(int));
	if(vector == NULL){
		fprintf(stderr, "Out of memory!\n");
		exit(EXIT_FAILURE);
	}

	test = (int *) malloc(n * sizeof(int));
	if(test == NULL){
		fprintf(stderr, "Out of memory!\n");
		exit(EXIT_FAILURE);
	}

	srand(time(NULL));

	for(i = 0; i < n; i++){
		vector[i] = rand();
		test[i] = vector[i];
	}

	start_q = omp_get_wtime();
	qsort(test, n, sizeof(int), compare);
	end_q = omp_get_wtime();

	elapsed_q = end_q - start_q;

	start_s = omp_get_wtime();
	selection_sort(vector, n);
	end_s = omp_get_wtime();

	elapsed_s = end_s - start_s;

	is_ok = (memcmp(vector, test, n * sizeof(int)) == 0);

	printf("A ordenação de valores está %s\nq_time: %.3f seconds\ns_time: %.3f seconds\n", resposta[is_ok], elapsed_q, elapsed_s);

	free(vector);
	free(test);

	return 0;
}
