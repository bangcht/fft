#ifndef FFT_H
#define FFT_H
#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

unsigned long SIZE;

int nThreads = 1;
// 1048576
#define PI 3.14159265359
#define DEBUG 0
void calW(double complex *w);
unsigned long bit_reverse(unsigned long a,unsigned long n);
void fft(double complex *data, double complex *res, unsigned long N);
#endif


