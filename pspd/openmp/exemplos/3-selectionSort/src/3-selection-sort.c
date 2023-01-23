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