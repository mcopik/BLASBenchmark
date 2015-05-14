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

static inline void compute_gemm_blas0(CMDOptions * options,  double * C, double * A, double * B)
{
	for(int i = 0;i < options->m; ++i) {
		for(int j = 0;j < options->n;++j) {

			double temp = 0.0;
			for(int k = 0; k < options->k;++k) {
				 temp += A[i*options->k + k] * B[k*options->n + j];
			}
			C[i*options->n + j] += temp;
		}
	}
}

static inline void compute_gemm_blas1(CMDOptions * options,  double * C, double * A, double * B)
{

	for(int i = 0;i < options->m; ++i) {
		for(int j = 0;j < options->n;++j) {
			C[i*options->n + j] += cblas_ddot(options->k, &A[i*options->k], 1, &B[j], options->n);
		}
	}
}

static inline void compute_gemm_blas2(CMDOptions * options,  double * C, double * A, double * B)
{
	for(int i = 0;i < options->k; ++i) {
		cblas_dger(CblasRowMajor, options->m, options->n, 1.0, &A[i], options->k, &B[i*options->n],
					1, C, options->n);
	}
}

static inline void compute_gemm_blas3(CMDOptions * options,  double * C, double * A, double * B)
{
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, options->m, options->n, options->k,
			1.0, A, options->k, B, options->n, 0.0, C, options->n);
}


void compute_gemm(CMDOptions * options, double * C, double * A, double * B)
{
	blas_function func;
	switch(options->blasLevel) {
		case 3:
			func = &compute_gemm_blas3;
			break;
		case 2:
			func = &compute_gemm_blas2;
			break;
		case 1:
			func = &compute_gemm_blas1;
			break;
		case 0:
			func = &compute_gemm_blas0;
			break;
		default:
			printf("Not implemented!\n");
			return;
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
		uint64_t ops = ((uint64_t)2*options->m)*options->n*options->k;
		printf("#ops/cycles %d : %f\n", i, ((double) ops) / (ticks_after - ticks_before) );
		double gflops = ops / time;
		printf("GFlops (#ops/time) %d : %e\n", i, gflops);
		printf("Efficiency (#gflops/(clock*8)) %d : %f\n", i, gflops/(3.4e9*8));
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
