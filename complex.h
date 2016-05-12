#ifndef COMPLEX_H
#define COMPLEX_H

#include <stdio.h>

typedef struct {
	double re; 
	double im;
} complex;

void init(complex *c, double real, double imaginary);
void show(complex c);
complex add(complex a, complex b);
complex sub(complex a, complex b);
complex mul(complex a, complex b);
complex div(complex a, complex b);

#endif

