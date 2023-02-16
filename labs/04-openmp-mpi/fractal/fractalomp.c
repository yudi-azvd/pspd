#include "../job_division.h"
#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

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

int write_bmp_header(FILE* f, int width, int height) {

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
    size_t ret = 0;
    ret += fwrite(id, sizeof(char), 2, f);
    ret += fwrite(&filesize, sizeof(int), 1, f);
    ret += fwrite(reserved, sizeof(short), 2, f);
    ret += fwrite(&offset, sizeof(int), 1, f);
    ret += fwrite(&size, sizeof(int), 1, f);
    ret += fwrite(&width, sizeof(int), 1, f);
    ret += fwrite(&height, sizeof(int), 1, f);
    ret += fwrite(&planes, sizeof(short), 1, f);
    ret += fwrite(&bits, sizeof(short), 1, f);
    ret += fwrite(&compression, sizeof(int), 1, f);
    ret += fwrite(&image_size, sizeof(int), 1, f);
    ret += fwrite(&x_res, sizeof(int), 1, f);
    ret += fwrite(&y_res, sizeof(int), 1, f);
    ret += fwrite(&ncolors, sizeof(int), 1, f);
    ret += fwrite(&importantcolors, sizeof(int), 1, f);

    // Success means that we wrote 17 "objects" successfully
    return (ret != 17);
}

int main(int argc, char* argv[]) {
    int n, workers;
    int range[2];
    int area = 0, width = 0, height = 0;
    unsigned char *pixel_array, *rgb;
    double t1, t2;
    FILE* output_file;

    if ((argc <= 1) || (atoi(argv[1]) < 1)) {
        fprintf(stderr, "Entre 'N' como um inteiro positivo! \n");
        return 1;
    }

    if (argc >= 3) {
        workers = atoi(argv[2]);
    } else
        workers = omp_get_max_threads();

    printf("workers=%d\n", workers);

    n = atoi(argv[1]);
    height = n;
    width = 2 * n;
    area = height * width * 3;
    pixel_array = calloc(area, sizeof(unsigned char));

    output_file = fopen(OUTFILE, "w");
    if (write_bmp_header(output_file, width, height)) {
        fprintf(stderr, "Failed writing header\n");
        return 3;
    }

    divide_jobs_and_offsets(n, workers);
    // printf("Computando linhas de pixel %d até %d, para uma área total de %d bytes\n", 0, n - 1, area);
    // print_job_division(workers);
    // print_job_offsets(workers);

    t1 = omp_get_wtime();
#pragma omp parallel
    {
        unsigned char rgb[3] = {0, 0, 0};
        int local_i = 0;
        int tid = omp_get_thread_num();
        int line_start = job_offsets[tid];
        int line_jump = job_division[tid];
        int line_end = line_start + line_jump;
        int byte_count = line_jump * width * BYTES_PER_PIXEL;
        int byte_offset = line_start * width * BYTES_PER_PIXEL;

        // printf("WID %d | start: %d, end: %d, jump: %d, bytes: %d, local_i: %d, byte offs: %d\n",
        //        tid, line_start, line_end, line_jump, byte_count, local_i, byte_offset);

        local_i += byte_offset;
        for (int i = line_start; i < line_end; i++)
            for (int j = 0; j < width * 3; j += 3) {
                compute_julia_pixel(j / 3, i, width, height, 1.0, rgb);

                pixel_array[local_i++] = rgb[0];
                pixel_array[local_i++] = rgb[1];
                pixel_array[local_i++] = rgb[2];
            }

#pragma omp critical
        fseek(output_file, HEADER_OFFSET + byte_offset, SEEK_SET);

        fwrite(pixel_array + byte_offset, sizeof(unsigned char), byte_count, output_file);
    }

    t2 = omp_get_wtime();
    free(pixel_array);
    fclose(output_file);

    printf("N = %d, Time elapsed %f\n", n, t2 - t1);

    return 0;
}
