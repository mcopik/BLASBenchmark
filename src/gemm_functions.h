/*
 * gemm_functions.h
 *
 *  Created on: May 13, 2015
 *      Author: mcopik
 */

#ifndef SRC_GEMM_FUNCTIONS_H_
#define SRC_GEMM_FUNCTIONS_H_
#include <stdint.h>
#include <stdbool.h>

/**
 * L3 cache size is 8 MB - 2000x2000 doubles will give over 30 MB
 */
#define CACHE_TRASHING_SIZE 2000

struct _CMDOptions;
typedef struct _CMDOptions CMDOptions;

struct _CMDOptions {
	bool test;
	bool verbose;
	bool trashing;
	const char * matrix_source_A;
	const char * matrix_source_B;
	const char * test_dest;
	uint32_t m;
	uint32_t n;
	uint32_t k;
	uint8_t iterations;
	uint8_t blasLevel;
	uint8_t configurationNumber;
};

void compute_gemm(CMDOptions * options, double * C, double * A, double * B);

void print_matrix(double * A, uint32_t rows, uint32_t cols);

#endif /* SRC_GEMM_FUNCTIONS_H_ */
