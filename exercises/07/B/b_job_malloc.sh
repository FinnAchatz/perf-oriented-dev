#!/bin/bash

# Execute job in the partition "lva" unless you have special requirements.
#SBATCH --partition=lva
# Name your job to be able to identify it later
#SBATCH --job-name 07fa
# Redirect output stream to this file
#SBATCH --output=output.log
# Maximum number of tasks (=processes) to start in total
#SBATCH --ntasks=1
# Maximum number of tasks (=processes) to start per node
#SBATCH --ntasks-per-node=1
# Enforce exclusive node allocation, do not share with other jobs
#SBATCH --exclusive

PROGS='malloc'
LOGPATH=/home/cb76/cb761225/perf-oriented-dev/exercises/07/B/time_

for p in $PROGS; do 
  echo $p
  /usr/bin/time -o ${LOGPATH}${p}.time -a -f %e ./malloctest_$p 1 500 1000000 10 1000
done
