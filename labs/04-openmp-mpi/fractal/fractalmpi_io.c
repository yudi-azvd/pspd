#include "../job_division.h"
#include <math.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OUTFILE "out_julia_normal.bmp"
// É o que está  em write_bmp_header
#define HEADER_OFFSET (54)

int compute_julia_pixel(int x, int y, int width, int height, float tint_bias, unsigned char* rgb) {
    if ((x < 0) || (x >= width) || (y < 0) || (y >= height)) {
        fprintf(stderr, "Invalid (%d,%d) pixel coordinates in a %d x %d image\n", x, y, width, height);
        return -1;
    }
    // "Zoom in" to a pleasing view of the Julia set
    float X_MIN = -1.6, X_MAX = 1.6, Y_MIN = -0.9, Y_MAX = +0.9;
    float float_y = (Y_MAX - Y_MIN) * (float)y / height + Y_MIN;
    float float_x = (X_MAX - X_MIN) * (float)x / width + X_MIN;
    // Point that defines the Julia set
    float julia_real = -.79;
    float julia_img = .15;
    // Maximum number of iteration
    int max_iter = 300;
    // Compute the complex series convergence
    float real = float_y, img = float_x;
    int num_iter = max_iter;
    while ((img * img + real * real < 2 * 2) && (num_iter > 0)) {
        float xtemp = img * img - real * real + julia_real;
        real = 2 * img * real + julia_img;
        img = xtemp;
        num_iter--;
    }

    // Paint pixel based on how many iterations were used, using some funky colors
    float color_bias = (float)num_iter / max_iter;
    rgb[0] = (num_iter == 0 ? 200 : -500.0 * pow(tint_bias, 1.2) * pow(color_bias, 1.6));
    rgb[1] = (num_iter == 0 ? 100 : -255.0 * pow(color_bias, 0.3));
    rgb[2] = (num_iter == 0 ? 100 : 255 - 255.0 * pow(tint_bias, 1.2) * pow(color_bias, 3.0));

    return 0;
}

int write_bmp_header(MPI_File file, int width, int height) {
    unsigned int row_size_in_bytes = width * 3 + ((width * 3) % 4 == 0 ? 0 : (4 - (width * 3) % 4));

    // Define all fields in the bmp header
    char id[2] = "BM";
    unsigned int filesize = 54 + (int)(row_size_in_bytes * height * sizeof(char));
    short reserved[2] = {0, 0};
    unsigned int offset = 54;

    unsigned int size = 40;
    unsigned short planes = 1;
    unsigned short bits = 24;
    unsigned int compression = 0;
    unsigned int image_size = width * height * 3 * sizeof(char);
    int x_res = 0;
    int y_res = 0;
    unsigned int ncolors = 0;
    unsigned int importantcolors = 0;

    // Write the bytes to the file, keeping track of the
    // number of written "objects"
    int count = 0, ret = 0;
    MPI_Status status;
    MPI_File_write(file, id, 2, MPI_CHAR, &status);
    MPI_Get_count(&status, MPI_CHAR, &count);
    ret += count;
    MPI_File_write(file, &filesize, 1, MPI_INT, &status);
    MPI_Get_count(&status, MPI_INT, &count);
    ret += count;
    MPI_File_write(file, reserved, 2, MPI_SHORT, &status);
    MPI_Get_count(&status, MPI_SHORT, &count);
    ret += count;
    MPI_File_write(file, &offset, 1, MPI_INT, &status);
    MPI_Get_count(&status, MPI_INT, &count);
    ret += count;
    MPI_File_write(file, &size, 1, MPI_INT, &status);
    MPI_Get_count(&status, MPI_INT, &count);
    ret += count;
    MPI_File_write(file, &width, 1, MPI_INT, &status);
    MPI_Get_count(&status, MPI_INT, &count);
    ret += count;
    MPI_File_write(file, &height, 1, MPI_INT, &status);
    MPI_Get_count(&status, MPI_INT, &count);
    ret += count;
    MPI_File_write(file, &planes, 1, MPI_SHORT, &status);
    MPI_Get_count(&status, MPI_SHORT, &count);
    ret += count;
    MPI_File_write(file, &bits, 1, MPI_SHORT, &status);
    MPI_Get_count(&status, MPI_SHORT, &count);
    ret += count;
    MPI_File_write(file, &compression, 1, MPI_INT, &status);
    MPI_Get_count(&status, MPI_INT, &count);
    ret += count;
    MPI_File_write(file, &image_size, 1, MPI_INT, &status);
    MPI_Get_count(&status, MPI_INT, &count);
    ret += count;
    MPI_File_write(file, &x_res, 1, MPI_INT, &status);
    MPI_Get_count(&status, MPI_INT, &count);
    ret += count;
    MPI_File_write(file, &y_res, 1, MPI_INT, &status);
    MPI_Get_count(&status, MPI_INT, &count);
    ret += count;
    MPI_File_write(file, &ncolors, 1, MPI_INT, &status);
    MPI_Get_count(&status, MPI_INT, &count);
    ret += count;
    MPI_File_write(file, &importantcolors, 1, MPI_INT, &status);
    MPI_Get_count(&status, MPI_INT, &count);
    ret += count;

    // Success means that we wrote 17 "objects" successfully
    return (ret != 17);
}

int main(int argc, char* argv[]) {
    int n, nprocs, workers, rank;
    int range[2];
    int area = 0, width = 0, height = 0, local_i = 0;
    unsigned char *pixel_array, *rgb;
    double t1, t2;
    FILE* output_file;
    char host[16];
    gethostname(host, 15);

    MPI_File file;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    if ((argc <= 1) || (atoi(argv[1]) < 1)) {
        if (rank == 0) {
            fprintf(stderr, "Entre 'N' como um inteiro positivo! \n");
        }
        MPI_Finalize();
        return 1;
    }

    int file_mode = MPI_MODE_WRONLY | MPI_MODE_CREATE;
    int ierr = MPI_File_open(MPI_COMM_WORLD, OUTFILE, file_mode, MPI_INFO_NULL, &file);
    if (ierr) {
        if (rank == 0) {
            fprintf(stderr, "Could not open file %s\n", OUTFILE);
        }
        MPI_Finalize();
        return 2;
    }

    workers = nprocs;
    n = atoi(argv[1]);
    height = n;
    width = 2 * n;
    area = height * width * 3;
    rgb = calloc(3, sizeof(unsigned char));

    if (write_bmp_header(file, width, height)) {
        if (rank == 0) {
            fprintf(stderr, "Failed writing header\n");
        }

        MPI_Finalize();
        return 3;
    }

    divide_jobs_and_offsets(n, workers);
    int line_start = job_offsets[rank];
    int line_jump = job_division[rank];
    int line_end = line_start + line_jump;
    int byte_count = line_jump * width * BYTES_PER_PIXEL;
    int byte_offset = line_start * width * BYTES_PER_PIXEL;

    pixel_array = calloc(byte_count, sizeof(unsigned char));
    // if (rank == 0) {
    //     printf("Computando linhas de pixel %d até %d, para uma área total de %d bytes\n", 0, n - 1, area);
    // print_job_division(workers);
    // print_job_offsets(workers);
    // }

    t1 = MPI_Wtime();
    for (int i = line_start; i < line_end; i++)
        for (int j = 0; j < width * 3; j += 3) {
            compute_julia_pixel(j / 3, i, width, height, 1.0, rgb);
            pixel_array[local_i++] = rgb[0];
            pixel_array[local_i++] = rgb[1];
            pixel_array[local_i++] = rgb[2];
        }

    // printf("PID %d | start: %d, end: %d, jump: %d, bytes: %d, local_i: %d, byte offs: %d\n", rank, line_start, line_end, line_jump, byte_count, local_i,
    //        byte_offset);

    // MPI_Request req;
    // MPI_File_iwrite_at(file, HEADER_OFFSET + byte_offset, pixel_array + byte_offset, byte_count, MPI_UNSIGNED_CHAR, &req);
    MPI_File_write_at(file, HEADER_OFFSET + byte_offset, pixel_array, byte_count, MPI_UNSIGNED_CHAR, MPI_STATUS_IGNORE);

    t2 = MPI_Wtime();
    free(rgb);
    free(pixel_array);

    printf("PID %d host %s | N = %d, Time elapsed %f\n", rank, host, n, t2 - t1);

    MPI_File_close(&file);
    MPI_Finalize();
    return 0;
}
