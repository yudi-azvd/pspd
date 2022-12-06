#include <mpi/mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

  const int ARR_SIZE = 16;
  int arr_a[ARR_SIZE];
  int arr_b[ARR_SIZE];
  int arr_c[ARR_SIZE];
  int arr_tmp[ARR_SIZE];

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

  if (rank == 0) {
    int nworkers = nprocs - 1;
    int slice_size = ARR_SIZE / nworkers;
    int rest_size = ARR_SIZE % nworkers;
    int whole_workers = nworkers;
    if (rest_size != 0) {
      whole_workers--;
    }

    // printf("whole workers  %d\n", whole_workers);
    // printf("    n workers  %d\n", nworkers);
    // printf("   slice size  %d\n", slice_size);
    // printf("    rest size  %d\n", rest_size);
    // printf("TOTAL ITEMS    %d\n", ARR_SIZE);
    master_init_arr(arr_a, ARR_SIZE, 0, 1);
    master_init_arr(arr_b, ARR_SIZE, 0, 1);
    printf("Master array A\n");
    print_arr(arr_a, ARR_SIZE);
    printf("Master array B\n");
    print_arr(arr_b, ARR_SIZE);

    int offset = 0, i;
    int limit = rest_size != 0 ? nworkers - 1 : nworkers;
    int final_rest_size = slice_size + rest_size;
    for (i = 1; i <= limit; i++) {
      offset = slice_size * (i - 1);
      MPI_Send(&slice_size, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
      MPI_Send(arr_a + offset, slice_size, MPI_INT, i, 0, MPI_COMM_WORLD);
      MPI_Send(arr_b + offset, slice_size, MPI_INT, i, 0, MPI_COMM_WORLD);
      // printf("Master arr A slice(%d, %d) to worker %d\n", offset, slice_size, i);
      // print_arr(arr_a + offset, slice_size);
      // printf("Master arr B slice(%d, %d) to worker %d\n", offset, slice_size, i);
      // print_arr(arr_b + offset, slice_size);
    }
    if (rest_size != 0) {
      offset = slice_size * (i-1);
      MPI_Send(&final_rest_size, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
      MPI_Send(arr_a + offset, final_rest_size, MPI_INT, i, 0, MPI_COMM_WORLD);
      MPI_Send(arr_b + offset, final_rest_size, MPI_INT, i, 0, MPI_COMM_WORLD);
      // printf("Master arr A rest(%d, %d) to worker %d\n", offset, final_rest_size, i);
      // print_arr(arr_a + offset, final_rest_size);
      // printf("Master arr B rest(%d, %d) to worker %d\n", offset, final_rest_size, i);
      // print_arr(arr_b + offset, final_rest_size);
    }

    int worker_id = 0;
    for (int i = 1; i <= whole_workers; i++) {
      MPI_Recv(arr_tmp, slice_size, MPI_INT, i, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
      worker_id = status.MPI_SOURCE;
      offset = slice_size * (worker_id - 1);
      copy_arr(arr_tmp, 0, arr_c, offset, slice_size);
      // printf("Master recv slice arr from worker %d\n", i);
      // print_arr(arr_tmp, slice_size);
    }
    if (rest_size != 0) {
      MPI_Recv(arr_tmp, final_rest_size, MPI_INT, i, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
      offset = slice_size * (i-1);
      copy_arr(arr_tmp, 0, arr_c, offset, final_rest_size);
      // printf("Master recv rest arr from worker %d\n", i);
      // print_arr(arr_tmp, final_rest_size);
    }

    printf("\nMaster final sum C\n");
    print_arr(arr_c, ARR_SIZE);
  } else {
    int MASTER_RANK = 0, slice_size = 0;
    MPI_Recv(&slice_size, 1, MPI_INT, MASTER_RANK, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(arr_a, slice_size, MPI_INT, MASTER_RANK, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(arr_b, slice_size, MPI_INT, MASTER_RANK, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

      for (int i = 0; i < slice_size; i++)
      arr_c[i] = arr_a[i] + arr_b[i];
    // printf("Worker %d A\n", rank);
    // print_arr(arr_a, slice_size);
    // printf("Worker %d B\n", rank);
    // print_arr(arr_b, slice_size);
    // fflush(stdout);

    MPI_Send(arr_c, slice_size, MPI_INT, MASTER_RANK, 0, MPI_COMM_WORLD);
  }

  MPI_Finalize();
}