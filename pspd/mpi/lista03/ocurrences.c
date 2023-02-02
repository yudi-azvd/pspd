
#include "util.h"
#include <mpi/mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int rank, nprocs;
    char* filename = argv[1];
    int ocurrences = 0;
    int n = 3;

    MPI_File file;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    if (argc < 2) {
        if (rank == 0) {
            fprintf(stderr, "Usage: mpirun -n <nprocs> %s <filename>", argv[0]);
            MPI_Finalize();
        }
        return 1;
    }

    int ierr = MPI_File_open(MPI_COMM_WORLD, filename, MPI_MODE_RDONLY, MPI_INFO_NULL, &file);
    if (ierr) {
        if (rank == 0) {
            fprintf(stderr, "Could not open file %s", filename);
            MPI_Finalize();
        }
        return 2;
    }

    int workers = nprocs - 1;

    if (rank == 0) {
        // printf("Parent process pid=%d\n", rank);

        int file_size_bytes = get_file_size(filename);
        int jobs = file_size_bytes / BYTES_PER_LINE;
        divide_jobs_and_offsets(jobs, workers);

        print_job_division(workers);
        print_job_offsets(workers);

        for (int child_proc = 1; child_proc < nprocs; child_proc++) {
            int displc = job_division[child_proc] * BYTES_PER_LINE;
            int offset = job_offsets[child_proc];
            MPI_Send(&displc, 1, MPI_INT, child_proc, 0, MPI_COMM_WORLD);
            MPI_Send(&offset, 1, MPI_INT, child_proc, 0, MPI_COMM_WORLD);
        }

    } else {
        int local_ocurrences = 0;
        int displc = 0, offset = 0;
        int read_number = 0;
        char buffer[BYTES_PER_LINE];
        MPI_Offset moffset;

        MPI_Recv(&displc, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&offset, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Child pid=%d | displc %d, offset %d\n", rank, displc, offset);

        for (int i = 0; i < displc; i += BYTES_PER_LINE) {
            moffset = offset + i;
            MPI_File_read_at(file, moffset, buffer, BYTES_PER_LINE, MPI_CHAR, MPI_STATUS_IGNORE);
            buffer[BYTES_PER_LINE - 1] = '\0';
            printf("Child %d at %lld read [%s]\n", rank, moffset, buffer);
        }
    }

    MPI_File_close(&file);
    MPI_Finalize();
}