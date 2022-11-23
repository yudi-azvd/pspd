#include <mpi/mpi.h>
#include <stdio.h>
#include <stdlib.h>

void print_arr(int *arr, int size) {
  for (int i = 0; i < size; i++)
    printf("%d ", arr[i]);
  printf("\n");
}

void master_init_arr(int *arr, int size, int offset, int multiplier) {
  for (int i = 0; i < size; i++)
    arr[i] = i + offset;
}

void copy_arr(int *src, int src_start, int *dst, int dst_start, int size) {
  int j = 0;
  for (int i = 0; i < size; i++) {
    dst[dst_start + j] = src[src_start + i];
    j++;
  }
}

int main(int argc, char **argv) {
  int rank, nprocs;
  MPI_Status status;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

  const int ARR_SIZE = 16;
  int arr_a[ARR_SIZE];
  int arr_b[ARR_SIZE];
  int arr_t[ARR_SIZE];
  int arr_c[ARR_SIZE];

  if (rank == 0) {
    master_init_arr(arr_a, ARR_SIZE, 0, 1);
    master_init_arr(arr_b, ARR_SIZE, 2, 1);
    printf("Master array A\n");
    print_arr(arr_a, ARR_SIZE);
    printf("Master array B\n");
    print_arr(arr_b, ARR_SIZE);
    fflush(stdout);

    int nworkers = nprocs - 1;
    int slice_size = ARR_SIZE / nworkers;
    int rest_size = ARR_SIZE % nworkers;
    printf("n workers  %d\n", nworkers);
    printf("slice size %d\n", slice_size);
    printf("rest size  %d\n", rest_size);
    fflush(stdout);
    exit(0);
    int offset = 0;
    for (int i = 1; i <= nworkers; i++) {
      offset = slice_size * (i - 1);
      MPI_Send(&slice_size, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
      MPI_Send(arr_a + offset, slice_size, MPI_INT, i, 0, MPI_COMM_WORLD);
      MPI_Send(arr_b + offset, slice_size, MPI_INT, i, 0, MPI_COMM_WORLD);
    }

    for (int i = 0; i < nworkers; i++) {
      MPI_Recv(arr_t, slice_size, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
      int worker_id = status.MPI_SOURCE;
      int offset = slice_size * (worker_id - 1);
      copy_arr(arr_t, 0, arr_c, offset, slice_size);
    }

    printf("Master final sum C\n");
    print_arr(arr_c, ARR_SIZE);
  } else {
    exit(0);
    int MASTER_RANK = 0, slice_size = 0;
    MPI_Recv(&slice_size, 1, MPI_INT, MASTER_RANK, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(arr_a, slice_size, MPI_INT, MASTER_RANK, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(arr_b, slice_size, MPI_INT, MASTER_RANK, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    for (int i = 0; i < slice_size; i++)
      arr_c[i] = arr_a[i] + arr_b[i];
    // printf("WORKER(%d) A\n", rank);
    // print_arr(arr_a, slice_size);
    // printf("WORKER(%d) B\n", rank);
    // print_arr(arr_b, slice_size);
    // fflush(stdout);

    MPI_Send(arr_c, slice_size, MPI_INT, MASTER_RANK, 0, MPI_COMM_WORLD);
  }

  MPI_Finalize();
}