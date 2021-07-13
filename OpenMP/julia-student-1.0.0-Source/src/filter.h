
#ifndef JULIAF_H_
#define JULIAF_H_

#include "png_utils.h"

#ifndef max
    #define max(a,b) ((a) > (b) ? (a) : (b))
#endif

#ifndef min
    #define min(a,b) ((a) < (b) ? (a) : (b))
#endif

void apply_filter(png_bytep *row_pointers, int width, int height, double filter[3][3], int rounds);

void filter_on_pixel(png_bytep *row_pointers, int x, int y, double filter[3][3]);

#endif