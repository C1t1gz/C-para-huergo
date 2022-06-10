#ifndef FILTERS_H
#define FILTERS_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include "ppm.h"
#include <atomic>


// SINGLE-THREAD FILTERS

void blackWhite(ppm& img);
void contraste(ppm& img, float contrast);
void brightness(ppm& img, float b);
void shades(ppm& img, unsigned char shades);
void merge(ppm& img1, ppm& img2, float alpha);
void sharpen(ppm & img);
void frame(ppm& img, pixel color, int x);
void boxBlur(ppm &img);
void zoom(ppm& img, int n);
void edgeDetection(ppm &img);
void crop(ppm& img, int k, int t);
void plain(ppm &img, unsigned char c);

// MULTI-THREAD FILTERS

void blackWhiteThreaded(ppm& img, int nthreads);
void brightnessThreaded(ppm& img, float b, int n);
void constrastThreaded(ppm& img, float contrast, int n);
void threadedconvolution(ppm& img, short int ker[], int start, int end);
void threadedsharpen(ppm& img,int nthreads);
#endif