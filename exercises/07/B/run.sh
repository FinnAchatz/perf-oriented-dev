#!/bin/bash

# number of repetitions for each version
LOCK=/home/cb76/cb761225/perf-oriented-dev/exercises/07/lock

for r in {1..10} ; do
	for v in {0..2} ; do
		# sleep until lock is free (process is finished)
		while [ -e $LOCK ]; do 
			sleep 2
	       	done

		sbatch job${v}.sh
		sleep 20
	done
done


