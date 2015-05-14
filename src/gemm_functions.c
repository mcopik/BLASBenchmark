/*
 * gemm_functions.c
 *
 *  Created on: May 13, 2015
 *      Author: mcopik
 */
#include <stdio.h>
#include <time.h>

#include "cblas.h"
#include "gemm_functions.h"


#define get_ticks(var) { \
  unsigned int __a, __d; \
  __asm volatile("rdtsc" : "=a" (__a), "=d" (__d)); \
  var = ((unsigned long) __a) | (((unsigned long) __d) << 32); \
  } while(0)

typedef void (*blas_function)(CMDOptions *, double *, double *, double *);

static inline void compute_gemm_blas3(CMDOptions * options,  double * C, double * A, double * B)
{
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, options->m, options->n, options->k,
			1.0, A, options->k, B, options->n, 0.0, C, options->n);
}


void compute_gemm(CMDOptions * options, double * C, double * A, double * B, uint8_t level, uint8_t combination)
{
	blas_function func;
	switch(level) {
		case 3:
			func = &compute_gemm_blas3;
			break;
		default:
			printf("Not implemented!\n");
	}

	uint64_t ticks_before, ticks_after;
	clock_t timer_before, timer_after;
	double time = 0.0;

	for(int i = 0; i < options->iterations; ++i) {

	    timer_before = clock();

	    get_ticks(ticks_before);
		(*func)(options, C, A, B);
		get_ticks(ticks_after);
		timer_after = clock() - timer_before;
		time =  ( (double) timer_after) / CLOCKS_PER_SEC;
		printf("TIME %d : %f\n", i, time);
		printf("#ops/cycles %d : %f\n", i, ((double) 2*options->m*options->n*options->k) / (ticks_after - ticks_before) );
		printf("#ops/time %d : %f\n", i, 2*options->m*options->n*options->k / time);
	}

}


void print_matrix(double * A, uint32_t rows, uint32_t cols)
{
	for(uint32_t i = 0; i < rows; ++i) {
		for(uint32_t j = 0;j < cols; ++j) {
			printf("%f ", A[i*cols + j]);
		}
		printf(";\n");
	}
	printf("\n");
}
