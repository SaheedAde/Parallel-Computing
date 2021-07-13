
#include <stdio.h>
#include <omp.h>

#include "juliap.h"

void compute_julia_set(double xmin, double xmax, double ymin, double ymax, 
    double **image, int im_width, int im_height)
{

    double zabs_max = 10;
    double complex c = -0.1 + 0.65 * I;
    int nit_max = 1000;

    double xwidth  = xmax - xmin;
    double yheight = ymax - ymin;
    int i, j;
    int nit;
    double complex z;

    #pragma omp parallel for collapse(2) schedule(runtime)
    for(i=0; i<im_width; i++) {
        for(j=0; j<im_height; j++) {
            nit = 0;

            // Map pixel position to a point in the complex plane
            z = (double)i / (double)im_width * xwidth + xmin 
              + ((double)j / (double)im_height * yheight + ymin) * I;

            // Do the iterations
            while( cabs(z) <= zabs_max && nit < nit_max ) {
                z = cpow(z,2) + c;
                nit += 1;
            }
            image[i][j] = (double)nit / (double)nit_max;
        }
    }
}
