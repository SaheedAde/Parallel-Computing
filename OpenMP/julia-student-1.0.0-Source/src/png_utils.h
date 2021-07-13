

/*
 * (C) 2021 Sascha Hunold
 * I based these functions on the libpng example, see below.
*/

/*
 * A simple libpng example program
 * http://zarb.org/~gc/html/libpng.html
 *
 * Modified by Yoshimasa Niwa to make it much simpler
 * and support all defined color_type.
 *
 * To build, use the next instruction on OS X.
 * $ brew install libpng
 * $ clang -lz -lpng16 libpng_test.c
 *
 * Copyright 2002-2010 Guillaume Cottenceau.
 *
 * This software may be freely redistributed under the terms
 * of the X11 license.
 *
 */

#ifndef PNG_UTILS_H
#define PNG_UTILS_H

#include <png.h>

void read_png_file(char *filename, png_bytep **row_pointers, int *width, int *height);
void write_png_file(char *filename, png_bytep *row_pointers, int width, int height);

#endif
