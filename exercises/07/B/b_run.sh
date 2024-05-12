#!/bin/bash

for r in {1..10} ; do
	sbatch b_job_fast.sh
done
for r in {1..4} ; do
	sbatch b_job_malloc.sh
done
