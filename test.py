#!/usr/bin/python3
import os, sys, subprocess;

test_data = [ (10,10,10) , (500,400,300), (2000,1500,1000)   ];

for x in test_data:
	print('\nTest data m = {0}, n = {1}, k = {2}'.format(*x));
	for level in (0,1,2,3):
		print('\nTest BLAS level ' + str(level));
		args = [ 'bin/benchmark'];
		args.append('-m ' + str( x[0] ));
		args.append('-n ' + str( x[1] ));
		args.append('-k ' + str( x[2] ));

		args.append('--matrix_a');
		args.append('test/test_data_{0}_{1}_A'.format( *(x[0],x[2])) );
		args.append('--matrix_b');
		args.append('test/test_data_{0}_{1}_B'.format( *(x[2],x[1])) );
		args.append('--test');
		args.append('test/test_data_{0}_{1}_C'.format( *(x[0],x[1])) );

		args.append('--blas_level');
		args.append(str( level ));
		print(' '.join(args) );
		process = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE);
		process.wait();
		out, err = process.communicate()
		
