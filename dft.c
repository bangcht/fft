#include "dft.h"

void dft(double *in, double complex *res){
	int k, n;
	for (k = 0; k < SIZE; k++) {
        for (n = 0; n < SIZE; n++) {
            res[k] += in[n] * cexp(-I * 2 * PI * k * n / SIZE);
        }
    }
}

int main(){
	int i;
	FILE *fin, *fout;
	fin = fopen("input.txt", "r");
	fscanf(fin, "%lu", &SIZE);
	double data[SIZE];
	double complex res[SIZE];
	for (i = 0; i < SIZE; i++){
		fscanf(fin, "%lf", &data[i]);
		//printf("%lf\n", data[i]);
	}
	dft(data, res);
	fout = fopen("dft_output.txt", "w");
	for (i = 0; i < SIZE; i++){
		fprintf(fout, "%.12lf + j * %.12lf\n", creal(res[i]), cimag(res[i]));
	}
	return 0;
}	