#include "complex.h"


void init(complex *c, double real, double imaginary){
	c->re = real;
	c->im = imaginary;
}

void show(complex c){
	printf("c = %lf + j * %lf\n", c.re, c.im);
}

complex add(complex a, complex b){
	complex c;
	c.re = a.re + b.re;
	c.im = a.im + b.im;
	return c;
}

complex sub(complex a, complex b){
	complex c;
	c.re = a.re - b.re;
	c.im = a.im - b.im;
	return c;
}

complex mul(complex a, complex b){
	complex c;
	c.re = a.re * b.re - a.im * b.im;
	c.im = a.re * b.im + a.im * b.re;
	return c;
}

complex div(complex a, complex b){
	complex c;
	double d = b.re * b.re + b.im * b.im;
	init(&c, (a.re * b.re + a.im * b.im) / d, (a.im * b.re - a.re * b.im) / d);
	return c;
}
