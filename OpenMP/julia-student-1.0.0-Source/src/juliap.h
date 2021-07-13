
#ifndef JULIAP_H_
#define JULIAP_H_

#include <complex.h> 

void compute_julia_set(double xmin, double xmax, double ymin, double ymax, 
    double **image, int im_width, int im_height);

#endif