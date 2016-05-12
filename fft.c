#include "fft.h"
void calW(double complex *w){
	unsigned long k = 0;
	omp_set_num_threads(16);
	#pragma omp parallel for private(k)
	for (k = 0; k < SIZE / 2; k++){
		w[k] = cexp(-I * 2 * PI * k / SIZE);
	}
}

// bit-reversal permutation 
unsigned long bit_reverse(unsigned long a,unsigned long n) {
	unsigned long b;
	unsigned long size, i;
	b = 0;
	size = sizeof(unsigned long) * 8; 
	for(i = 0; i < n; i++)  
		b |= ((a << (size - 1 - i)) >> (size - 1)) << (n - 1 - i);
	return b;
}

void fft(double complex *data, double complex *res, unsigned long N){
	double complex *w;
	w = (complex*) malloc(SIZE / 2 * sizeof(complex));
	// double complex temp;
	// temp = (complex*) malloc(SIZE * sizeof(complex));

	calW(w);
	unsigned long stage, w_step, bf_len, step, id, bf_id, n_stage;
	//unsigned long *w_id;
	//w_id = (unsigned long*) malloc(SIZE * sizeof(unsigned long));
	n_stage = 0;
	bf_len = N;
	w_step = 1;
	for (stage = 1; stage < SIZE; stage *= 2){
		n_stage++;
		step = bf_len >> 1;
			omp_set_num_threads(nThreads);
			#pragma omp parallel for private(id)
			for (bf_id = 0; bf_id < SIZE; bf_id += bf_len){
				for (id = bf_id; id < bf_id + step; id++){
					double complex temp = data[id];
					unsigned long w_id = w_step * (id - bf_id);
					data[id] = temp + data[id + step];
					data[id + step] = (temp - data[id + step]) * w[w_id];
				}
			}
		w_step = w_step << 1;
		bf_len = bf_len >> 1;
	}

	// re
	if (DEBUG == 1){
		unsigned long i;
		omp_set_num_threads(nThreads);
		#pragma omp parallel for private(id)
		for (i = 0; i < SIZE; i++) 					  
		{
			// rev_id = bit_reverse(i, n_stage);
			res[bit_reverse(i, n_stage)] = data[i];
		}
	}
}

int main(){
	struct timespec start, end;
	printf("Enter number of threads: ");
	scanf("%d", &nThreads);
	unsigned long i;
	FILE *fin, *fout, *f_true_out;
	// read input
	fin = fopen("input.txt", "r");
	fscanf(fin, "%lu", &SIZE);
	// declare variable
	double temp;
	double complex *data;
	data = (complex*) malloc(SIZE * sizeof(complex));
	double complex *res;
	res = (complex*) malloc(SIZE * sizeof(complex));
	double complex *res_true;
	res_true = (complex*) malloc(SIZE * sizeof(complex));
	for (i = 0; i < SIZE; i++){
		fscanf(fin, "%lf", &temp);
		data[i] = temp;
	}
	fclose(fin);

	// read true output
	f_true_out = fopen("output.txt", "r");
	double a, b;
	for (i = 0; i < SIZE; i++){
		fscanf(f_true_out, "%lf %lf", &a, &b);
		res_true[i] = a + I * b;
	}
	fclose(f_true_out);
	// calculate

	printf("Started\n");
	clock_gettime(CLOCK_MONOTONIC, &start);
	fft(data, res, SIZE);
	printf("Done\n");
	printf("N = %ld\n", SIZE);
	clock_gettime(CLOCK_MONOTONIC, &end);
	if (DEBUG == 1){
		// cal err
		double err_re, err_im, max_err_re, max_err_im;
		err_re = 0;
		err_im = 0;
		max_err_im = 0; 
		max_err_re = 0;
		double err_temp; 
		for (i = 0; i < SIZE; i++){
			err_temp = fabs(creal(res_true[i]) - creal(res[i]));
			err_re += err_temp;
			if (err_temp > max_err_re) max_err_re = err_temp;
			err_temp = fabs(cimag(res_true[i]) - cimag(res[i]));
			err_im += err_temp;
			if (err_temp > max_err_im) max_err_im = err_temp;
		}
		// write to file
		fout = fopen("fft_output.txt", "w");
		for (i = 0; i < SIZE; i++){
			fprintf(fout, "%.12lf + j * %.12lf\n", creal(res[i]), cimag(res[i]));
		}
		fclose(fout);
		printf("Cummulative Real error: \t%.10lf\n", err_re);
		printf("Cummulative Imaginary error: \t%.10lf\n", err_im);
		printf("Max Real error: \t\t%.10lf\n", max_err_re);
		printf("Max Imaginary error: \t\t%.10lf\n", max_err_im);
	}
	unsigned long delta_time = end.tv_sec - start.tv_sec;
	delta_time *= 1000000000;
	delta_time += end.tv_nsec - start.tv_nsec;
	printf("N_THREADS = %d\n", nThreads);
	printf("Calculate time: \t\t%.9ldns (~%.3lfs)\n", delta_time, (double) delta_time / 1000000000);
	printf("Max threads = %d\n", omp_get_max_threads());
	return 0;
}