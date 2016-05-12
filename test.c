#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main(){
	omp_set_num_threads(7);
	#pragma omp parallel
    printf("Hello, world.\n");
    return 0;
}