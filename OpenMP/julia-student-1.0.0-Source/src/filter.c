/*
 * (C) 2021 Sascha Hunold
 */

#include <math.h>
#include <omp.h>
#include "filter.h"

const int fwidth2  = 1;
const int fheight2 = 1;

void apply_filter(png_bytep *row_pointers, int width, int height, double filter[3][3], int rounds) {    
    int i, j;
    #pragma omp parallel
    #pragma omp single
    {
        for(int r=0; r<rounds; r++) {
	    #pragma omp task shared (i)    
	    for(i=fwidth2; i<width - fwidth2; i++) {
	        #pragma omp task shared (j)     
	        for(j=fheight2; j<height - fheight2; j++) {
		    filter_on_pixel(row_pointers, i, j, filter);
	        }
	    }
        }
    }
}

