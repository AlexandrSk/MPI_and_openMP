#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
int fact(int c);
double taylor(double x, int n);

int main(int argc, char *argv[]) {
	double x = 0;
	int n = 0;
	int n_max = 100000;
	omp_set_num_threads(4);
	if (argc != 3) {
		printf("Input three parametrs!\n");
		return 1;
	}
	sscanf_s(argv[1], "%lf", &x);
	sscanf_s(argv[2], "%d", &n);

	if ((n > n_max) || (n < 0)) {
		printf("Invalid parameter n, enter n from 0..100\n");
		return 1;
	}

	int i;
	double sum = 0;
	double t = omp_get_wtime();

#pragma omp parallel for private(i) reduction(+: sum)
	for (i = 1; i <= n; i++) {
		double taylor = pow(x, i) / fact(i);
		sum += taylor;
	}

	double diff = omp_get_wtime() - t;
	printf("Time: %lf\n", diff);
	return 0;
}

    int fact(int c) {
	int fact = 1;
	int i;
	for (i = 1; i <= c; i++) {
		fact *= i;
	}
	return fact;
}