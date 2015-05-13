/*
 * gemm_functions.c
 *
 *  Created on: May 13, 2015
 *      Author: mcopik
 */
#include <stdio.h>

#include "cblas.h"
#include "gemm_functions.h"

static void compute_gemm_blas3(CMDOptions * options, double * C, double * A, double * B)
{
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, options->m, options->n, options->k,
			1.0, A, options->k, B, options->n, 1.0, C, options->n);
}


void compute_gemm(CMDOptions * options, double * C, double * A, double * B, uint8_t level, uint8_t combination)
{
	switch(level) {
		case 3:
			compute_gemm_blas3(options, C, A, B);
			break;
		default:
			printf("Not implemented!\n");
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
