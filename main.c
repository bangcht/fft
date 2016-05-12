#include "main.h"

int main(){
	double pi = 4 * atan(1.0);
	double complex c = cexp(I * pi);
	printf("%lf + i * %lf\n", creal(c), cimag(c));
	return 0;
}