#!/usr/bin/python3
import os, sys, subprocess,statistics;

def linspace(start, end, step):
    while start <= end:
        yield start
        start += step


for level in (3,):

	space = [];
	efficiency_min = [];
	efficiency_max = [];
	efficiency_mean = [];
	for x in linspace(30,1500,30):
		args = [ 'bin/benchmark'];
		args.append('-m ' + str( x ));
		args.append('-n ' + str( x ));
		args.append('-k ' + str( x ));
		args.append('--blas_level');
		args.append(str( level ));
		args.append('--trashing');

		process = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE);
		process.wait();
		out, err = process.communicate();
		out = out.decode("utf-8").split('\n');
		efficiency_data = []
		for i in range( len(out) ):
			index = out[i].find('Eff');
			if index != -1:
				efficiency_data.append( float(out[i].split(':')[1]) );
		efficiency_data.remove( min(efficiency_data) );
		efficiency_data.remove( max(efficiency_data) );

		efficiency_min.append( min(efficiency_data) );
		efficiency_max.append( max(efficiency_data) );
		efficiency_mean.append( statistics.mean(efficiency_data) );
		space.append(x);
	file_min =  open('efficiency_min_level_' + str(level), 'w');
	file_max =  open('efficiency_max_level_' + str(level), 'w');
	file_mean =  open('efficiency_mean_level_' + str(level), 'w');
	for i in range( len(space) ):
		file_min.write('{0} {1};\n'.format( *(space[i], efficiency_min[i]) ));
		file_max.write('{0} {1};\n'.format( *(space[i], efficiency_max[i]) ));
		file_mean.write('{0} {1};\n'.format( *(space[i], efficiency_mean[i]) ));
