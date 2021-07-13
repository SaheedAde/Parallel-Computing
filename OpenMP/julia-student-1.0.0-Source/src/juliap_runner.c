
#include <ctype.h>
#include <libgen.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <omp.h>

#include "juliap.h"

void usage(const char *prog_name) {
  fprintf(
      stderr,
      "usage: %s -n <int> -p <int> [-o <fname>] [-h]\n"
      "-n number elements per dimension (nxn)\n"
      "-p number threads\n"
      "-o output file\n"
      "-h print this help message\n",
      prog_name);
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {

  int tok;
  long i, j;
  long n = 1, nset = 0;
  int p = 1, pset = 0;
  int outfileset = 0;
  char outfile[200];

  double time_start, time_end;
  int help = 0;

  double xmin = -1.5,
         xmax = 1.5,
         ymin = -1.5,
         ymax = 1.5;

  int im_width = 500,
      im_height = 500;
  
  double **image;

  opterr = 0;

  while ((tok = getopt(argc, argv, "n:p:o:h")) != -1) {
    switch (tok) {
    case 'n':
      n = atol(optarg);
      im_width  = n;
      im_height = n;
      nset = 1;
      break;
    case 'p':
      p = atoi(optarg);
      pset = 1;
      break;
    case 'h':
      help = 1;
      break;
    case 'o':
      strcpy(outfile, optarg);
      outfileset = 1;
      break;    
    default:
      fprintf(stderr, "unknown parameter\n");
      exit(1);
    }
  }

  if ((nset + pset < 2) || help == 1) {
    usage(basename(argv[0]));
  }

  if( outfileset == 0 ) {
    strcpy(outfile, "julia.out");
  }

  omp_set_dynamic(0);
  omp_set_num_threads(p);

  image = (double**)calloc(im_height, sizeof(double*));
  for(i=0; i<im_height; i++) {
    image[i] = (double*)calloc(im_width, sizeof(double));
  }

  time_start = omp_get_wtime();
  //mmm_impl(a, b, c, n);
  compute_julia_set(xmin, xmax, ymin, ymax, image, im_width, im_height);
  time_end = omp_get_wtime();

  printf("elements per dimensions (n)=%ld; Thread number (p)=%d; runtime=%.6f\n", n, p, time_end - time_start);

  if( outfileset ) {
    FILE *fh = fopen(outfile, "w");
    for(i=0; i<im_width; i++) {
      for(j=0; j<im_height; j++) {
        fprintf(fh, "%.8f ", image[i][j]);
      }
      fprintf(fh,"\n");
    }
    fclose(fh);
  }

  for(i=0; i<im_height; i++) {
    free(image[i]);
  }
  free(image);

  return 0;
}
