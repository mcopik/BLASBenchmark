#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * GNU C library.
 */
#include <getopt.h>


typedef struct _CMDOptions {
	bool test;
	const char * matrix_source_A;
	const char * matrix_source_B;
	const char * test_dest;
	unsigned int m;
	unsigned int n;
	unsigned int k;
	unsigned int iterations;
	unsigned int blasLevel;
	unsigned int configurationNumber;
} CMDOptions;

int process_options(CMDOptions * opts, int argc, char ** argv)
{


    struct option long_options[] =
      {
        /* These options set a flag. */
        {"test", required_argument, &opts->test, 1},
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

	if( !process_options(&options, argc, argv) ) {
		return 1;
	}

	printf("%s %s %s \n", options.matrix_source_A, options.matrix_source_B, options.test_dest);

	double * C, * B, * A;

	C = malloc( sizeof(double) * options.m * options.n);
	B = malloc( sizeof(double) * options.k * options.n );
	A = malloc( sizeof(double) * options.m * options.k );
	memset(C, sizeof(double) * options.m * options.n, 0 );

	if( options.test ) {
		//load data
	} else {
		//generate randomly

	}

	free(C);
	free(B);
	free(A);

	return 0;
}
