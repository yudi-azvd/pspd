#include <locale.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CMP_PIXEL_BUFFER 128
#define BMP_HEADER_OFFSET 54

// Header Bitmap em stuct sem padding
// https://stackoverflow.com/questions/4306186/structure-padding-and-packing
typedef struct __attribute__((__packed__)) BmpHeader {
    char id[2];
    unsigned int filesize;
    short reserved[2];
    unsigned int offset;
    unsigned int size;
    unsigned int width;
    unsigned int height;
    unsigned short planes;
    unsigned short bits;
    unsigned int compression;
    unsigned int image_size;
    int x_res;
    int y_res;
    unsigned int ncolors;
    unsigned int importantcolors;
} BmpHeader;

typedef struct Pixel {
    uint8_t b;
    uint8_t g;
    uint8_t r;
} Pixel;

void print_bmp_header(BmpHeader* h) {
    fprintf(stdout, "BMP headers\n");
    fprintf(stdout, "id [%c%c]\n", h->id[0], h->id[1]);
    fprintf(stdout, "filesize [%u]\n", h->filesize);
    fprintf(stdout, "reserved [%d %d]\n", h->reserved[0], h->reserved[1]);
    fprintf(stdout, "offset [%u]\n", h->offset);
    fprintf(stdout, "size [%u]\n", h->size);
    fprintf(stdout, "width [%u]\n", h->width);
    fprintf(stdout, "height [%u]\n", h->height);
    fprintf(stdout, "planes [%hu]\n", h->planes);
    fprintf(stdout, "bits [%hu]\n", h->bits);
    fprintf(stdout, "compression [%u]\n", h->compression);
    fprintf(stdout, "image_size [%u]\n", h->image_size);
    fprintf(stdout, "x_res [%d]\n", h->x_res);
    fprintf(stdout, "y_res [%d]\n", h->y_res);
    fprintf(stdout, "ncolors [%hu]\n", h->ncolors);
    fprintf(stdout, "importantcolors [%hu]\n", h->importantcolors);
}

int cmp_bmp_header(BmpHeader* h1, BmpHeader* h2) {
    int ret = 0;

    if (0 != strncmp(h1->id, h2->id, 2)) {
        fprintf(stdout, "BMP Headers differ: id [%s] - [%s]\n", h1->id, h2->id);
        ret += 1;
    }
    if (h1->filesize != h2->filesize) {
        fprintf(stdout, "BMP Headers differ: filesize [%u] - [%u]\n", h1->filesize, h2->filesize);
        ret += 1;
    }
    if (0 != memcmp(h1->reserved, h2->reserved, 2)) {
        fprintf(stdout, "BMP Headers differ: reserved [%d %d] - [%d %d]\n", h1->reserved[0], h1->reserved[1], h2->reserved[0], h2->reserved[1]);
        ret += 1;
    }
    if (h1->offset != h2->offset) {
        fprintf(stdout, "BMP Headers differ: offset [%u] - [%u]\n", h1->offset, h2->offset);
        ret += 1;
    }
    if (h1->size != h2->size) {
        fprintf(stdout, "BMP Headers differ: size [%u] - [%u]\n", h1->size, h2->size);
        ret += 1;
    }
    if (h1->planes != h2->planes) {
        fprintf(stdout, "BMP Headers differ: planes [%hu] - [%hu]\n", h1->planes, h2->planes);
        ret += 1;
    }
    if (h1->bits != h2->bits) {
        fprintf(stdout, "BMP Headers differ: bits [%hu] - [%hu]\n", h1->bits, h2->bits);
        ret += 1;
    }
    if (h1->compression != h2->compression) {
        fprintf(stdout, "BMP Headers differ: compression [%u] - [%u]\n", h1->compression, h2->compression);
        ret += 1;
    }
    if (h1->image_size != h2->image_size) {
        fprintf(stdout, "BMP Headers differ: image_size [%u] - [%u]\n", h1->image_size, h2->image_size);
        ret += 1;
    }
    if (h1->x_res != h2->x_res) {
        fprintf(stdout, "BMP Headers differ: x_res [%d] - [%d]\n", h1->x_res, h2->x_res);
        ret += 1;
    }
    if (h1->y_res != h2->y_res) {
        fprintf(stdout, "BMP Headers differ: y_res [%d] - [%d]\n", h1->y_res, h2->y_res);
        ret += 1;
    }
    if (h1->ncolors != h2->ncolors) {
        fprintf(stdout, "BMP Headers differ: ncolors [%hu] - [%hu]\n", h1->ncolors, h2->ncolors);
        ret += 1;
    }
    if (h1->importantcolors != h2->importantcolors) {
        fprintf(stdout, "BMP Headers differ: importantcolors [%hu] - [%hu]\n", h1->importantcolors, h2->importantcolors);
        ret += 1;
    }

    return ret;
}

int cmp_pixel(Pixel p1, Pixel p2) {
    int result = 0;
    if (p1.r != p2.r)
        result += 1;
    if (p1.g != p2.g)
        result += 1;
    if (p1.b != p2.b)
        result += 1;
    return result;
}

void print_pixel(Pixel* p) {
    printf("rgb(%3d, %3d, %3d)\n", p->r, p->g, p->b);
}

int main(int argc, char** argv) {
    setlocale(LC_NUMERIC, "");
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <file1.bmp> <file2.bmp>\n", argv[0]);
        return 1;
    }

    FILE *f1, *f2;
    char* filename1 = argv[1];
    char* filename2 = argv[2];

    f1 = fopen(filename1, "r");
    if (!f1) {
        fprintf(stderr, "Not able to open file: %s\n", filename1);
        return 2;
    }

    f2 = fopen(filename2, "r");
    if (!f2) {
        fprintf(stderr, "Not able to open file: %s\n", filename2);
        return 3;
    }

    BmpHeader header1, header2;
    fread(&header1, sizeof(BmpHeader), 1, f1);
    fread(&header2, sizeof(BmpHeader), 1, f2);

    int headers_differ = cmp_bmp_header(&header1, &header2);
    if (headers_differ) {
        fprintf(stderr, "BMP Headers are different!\n");
        return headers_differ;
    }

    int rows = header1.height;
    int cols = header1.width;

    Pixel* pixel_row_1 = calloc(cols, sizeof(Pixel));
    Pixel* pixel_row_2 = calloc(cols, sizeof(Pixel));
    Pixel *p1, *p2;

    char cmp_pixel_buffer[CMP_PIXEL_BUFFER];
    int pixel_counter = 0, row_counter = 0;
    int byte_counter = 0;
    int bytes_read = 0;
    int read_count = 0;
    int different_pixels = 0, i, j;
    for (i = 0; i < rows; i++) {
        read_count = fread(pixel_row_1, sizeof(Pixel), cols, f1);
        bytes_read += read_count * sizeof(Pixel);
        read_count = fread(pixel_row_2, sizeof(Pixel), cols, f2);
        row_counter++;

        for (j = 0; j < cols; j++) {
            pixel_counter++;
            byte_counter += 3;
            p1 = &pixel_row_1[j];
            p2 = &pixel_row_2[j];
            if (0 != cmp_pixel(*p1, *p2)) {
                snprintf(cmp_pixel_buffer, CMP_PIXEL_BUFFER,
                         "x:%d y:%d\n"
                         "  file1 (%3d, %3d, %3d)\n"
                         "  file2 (%3d, %3d, %3d)\n",
                         i, j,
                         p1->r, p1->g, p1->b,
                         p2->r, p2->g, p2->b);
                fprintf(stderr, "%s\n", cmp_pixel_buffer);
                different_pixels++;
            }
        }
    }

    if (different_pixels) {
        fprintf(stderr, "Total different pixels: %d\n", different_pixels);
        // fprintf(stderr, "f1 at: %ld\n", ftell(f1));
        // fprintf(stderr, "f2 at: %ld\n", ftell(f2));
        // print_bmp_header(&header1);
    }

    free(pixel_row_1);
    free(pixel_row_2);
    fclose(f1);
    fclose(f2);
    return different_pixels;
}