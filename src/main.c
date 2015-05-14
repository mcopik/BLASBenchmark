//enable drand48 in C99 - declarations of functions are in a conditional preprocessor directive
#define _XOPEN_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

/**
 * GNU C library.
 */
#include <getopt.h>

#include "gemm_functions.h"

int process_options(CMDOptions * opts, int argc, char ** argv)
{


    struct option long_options[] =
      {
        /* These options set a flag. */
        {"test", required_argument, (int*) &opts->test, 1},
        /* These options don’t set a flag.
           We distinguish them by their indices. */
        {"matrix_a",	required_argument,  0, 'a'},
		{"matrix_b",  	required_argument, 0, 'b'},
        {"m", 			required_argument, 0, 'm'},
        {"n",  			required_argument, 0, 'n'},
        {"k",    		required_argument, 0, 'k'},
        {"iters",    	required_argument, 0, 'u'},
        {"blas_level",  required_argument, 0, 'l'},
        {"blas_conf", 	required_argument, 0, 'c'},
        {0, 0, 0, 0}
      };

	/**
	 * Example of getopt usage:
	 * http://www.gnu.org/software/libc/manual/html_node/Example-of-Getopt.html
	 */
	int c;
    int option_index = 0;
	while ( (c = getopt_long (argc, argv, "a:b:m:n:k:i:l:c", long_options, &option_index) ) != -1) {
		switch (c)
		{
        	case 0:
        		opts->test_dest = optarg;
			break;
			case 'a':
				opts->matrix_source_A = optarg;
			break;
			case 'b':
				opts->matrix_source_B = optarg;
			break;
			case 'l':
				opts->blasLevel = atoi(optarg);
			break;
			case 'i':
				opts->iterations = atoi(optarg);
			break;
			case 'c':
				opts->configurationNumber = atoi(optarg);
			break;
			case 'm':
				opts->m = atoi(optarg);
			break;
			case 'k':
				opts->k = atoi(optarg);
			break;
			case 'n':
				opts->n = atoi(optarg);
			break;

			default:
				printf("%c\n", c);
				return 1;
		}
	}
	return 0;
}

int main(int argc, char ** argv)
{
	CMDOptions options = {
			.blasLevel = 0,
			.configurationNumber = 0,
			.iterations = 10,
			.m = 1000,
			.n = 1000,
			.k = 1000,
			.matrix_source_A = "",
			.matrix_source_B = "",
			.test_dest = "",
			.test = false
	};

	if( process_options(&options, argc, argv) ) {
		abort();
		return 1;
	}

	printf("%s %s %s \n", options.matrix_source_A, options.matrix_source_B, options.test_dest);

	double * C, * B, * A;

	C = malloc( sizeof(double) * options.m * options.n);
	B = malloc( sizeof(double) * options.k * options.n );
	A = malloc( sizeof(double) * options.m * options.k );
	memset(C, 0, sizeof(double) * options.m * options.n);

	if( options.test ) {
		//load data
		printf("ok\n");
	} else {

		srand48( time(NULL) );
		for(int i = 0;i < options.m; ++i) {
			for(int j = 0;j < options.k; ++j) {
				A[i*options.k + j] = drand48();
			}
		}

		for(int i = 0;i < options.k; ++i) {
			for(int j = 0;j < options.n; ++j) {
				B[i*options.n + j] = drand48();
			}
		}

	}
	//print_matrix(A, options.m, options.k);
	//print_matrix(B, options.k, options.n);

	compute_gemm(&options, C, A, B, 3, 0);

	//print_matrix(C, options.m, options.n);


	free(C);
	free(B);
	free(A);

	return 0;
}
