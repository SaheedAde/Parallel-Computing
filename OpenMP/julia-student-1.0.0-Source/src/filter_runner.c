/*
 * (C) 2021 Sascha Hunold
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <string.h>
#include <unistd.h>
#include "png_utils.h"
#include "filter.h"

static double gauss_filter[3][3] = {
    {1.0/16.0, 2.0/16.0, 1.0/16.0},
    {2.0/16.0, 4.0/16.0, 2.0/16.0},
    {1.0/16.0, 2.0/16.0, 1.0/16.0}
};

void filter_on_pixel(png_bytep *row_pointers, int x, int y, double filter[3][3]) {

    double r = 0;
    double g = 0;
    double b = 0;

    for(int i=-1; i<=1; i++) {
        for(int j=-1; j<=1; j++) {
            png_bytep px = &(row_pointers[x+i][(y+j)*4]);
            r += (double)px[0] * filter[i+1][j+1];
            g += (double)px[1] * filter[i+1][j+1];
            b += (double)px[2] * filter[i+1][j+1];
        }
    }

    png_bytep px = &(row_pointers[x][y * 4]);

    
    px[0] = min(255, r);
    px[1] = min(255, g);
    px[2] = min(255, b);
}


void usage(const char *prog_name) {
  fprintf(
      stderr,
      "usage: %s -i <infile> -o <outfile> [-p <int>] [-r <int>] [-h]\n"
      "-i input file (png)\n"
      "-o output file\n"
      "-p number threads\n"
      "-r number of filter applications\n"
      "-h print this help message\n",
      prog_name);
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    png_bytep *row_pointers = NULL;
    int width, height;    
    int help = 0;
    int r = 1; 
    int p = 1;

    char outfile[200];
    int outfileset = 0;
    
    char infile[200];
    int infileset = 0;

    int tok;
    opterr = 0;


    while ((tok = getopt(argc, argv, "i:p:o:r:h")) != -1) {
        switch (tok) {
        case 'i':
            strcpy(infile, optarg);
            infileset = 1;
            break;
        case 'o':
            strcpy(outfile, optarg);
            outfileset = 1;
            break;    
        case 'p':
            p = atoi(optarg);
            break;
        case 'r':
            r = atoi(optarg);
            break;
        case 'h':
            help = 1;
            break;
        default:
            fprintf(stderr, "unknown parameter\n");
            exit(1);
        }
    }

    if( help == 1  ) {
        usage(argv[0]);
    }

    if( infileset < 1 ) {
        usage(argv[0]);
    }

    read_png_file(infile, &row_pointers, &width, &height);

    //printf("width=%d height=%d\n", width, height);

    omp_set_num_threads(p);

    double stime = omp_get_wtime();
    apply_filter(row_pointers, width, height, gauss_filter, r);
    double etime = omp_get_wtime();

    printf("\n\nwidth=%d; number of threads(p)=%d; number of filter application(r)=%d; time=%g\n",width,p,r,etime-stime);

    if( outfileset == 1 ) {
        write_png_file(outfile, row_pointers, width, height);
    }

    return 0;
}
