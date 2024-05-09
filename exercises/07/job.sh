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

# Set what should be benchmarked.
# 0: default, 1: RPMalloc, 2: MiMalloc
VERS=0

# Path to libraries
MIMALLOC=/home/cb76/cb761225/perf-oriented-dev/external_libs/mimalloc/out/release/libmimalloc.so
RPMALLOC=/home/cb76/cb761225/perf-oriented-dev/external_libs/rpmalloc/out/release
LOGPATH=/home/cb76/cb761225/perf-oriented-dev/exercises/07/tmp/time_${VERS}.csv
WORKDIR=/scratch/cb761225/allscale_api/build

# Command to meassure (time)
MEASSURE="/usr/bin/time -o ${LOGPATH} -a -f %e,%S,%U,%M,%t"

# create csv if not there yet and write header
if [ ! -f ${LOGPATH} ]; then
	touch ${LOGPATH}
	echo "real,kernel,user,max,avg" > ${LOGPATH}
fi

cd $WORKDIR
module load llvm/15.0.4-python-3.10.8-gcc-8.5.0-bq44zh7
ninja clean

if [ $VERS -eq 1 ]; then
	$MEASSURE LD_PRELOAD=$RPMALLOC ninja
elif [ $VERS -eq 2 ]; then
	$MEASSURE LD_PRELOAD=$MIMALLOC ninja
else
	$MEASSURE ninja
fi


