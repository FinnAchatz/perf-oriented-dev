#!/bin/bash

# Execute job in the partition "lva" unless you have special requirements.
#SBATCH --partition=lva
# Name your job to be able to identify it later
#SBATCH --job-name 07fa[vers]
# Redirect output stream to this file
#SBATCH --output=output[vers].log
# Maximum number of tasks (=processes) to start in total
#SBATCH --ntasks=1
# Maximum number of tasks (=processes) to start per node
#SBATCH --ntasks-per-node=1
# Enforce exclusive node allocation, do not share with other jobs
#SBATCH --exclusive

# Set what should be benchmarked.
# 0: default, 1: RPMalloc, 2: MiMalloc
VERS=[vers]

# Path to libraries
MIMALLOC=/home/cb76/cb761225/perf-oriented-dev/external_libs/mimalloc/out/release/libmimalloc.so
RPMALLOC=/home/cb76/cb761225/perf-oriented-dev/external_libs/rpmalloc/bin/linux/release/x86-64/librpmalloc.so
LOGPATH=/home/cb76/cb761225/perf-oriented-dev/exercises/07/tmp/time_${VERS}.csv
WORKDIR=/scratch/cb761225/allscale_api/build
LOCK=/home/cb76/cb761225/perf-oriented-dev/exercises/07/lock

# Command to meassure (time)
MEASSURE="/usr/bin/time -o ${LOGPATH} -a -f %e,%S,%U,%M,%t"

# create csv if not there yet and write header
if [ ! -f ${LOGPATH} ]; then
	touch ${LOGPATH}
	echo "real,kernel,user,max,avg" > ${LOGPATH}
fi

while [ -e $LOCK ]; do 
	sleep 1;
done
touch $LOCK

cd $WORKDIR
module load llvm/15.0.4-python-3.10.8-gcc-8.5.0-bq44zh7

ninja clean

if [ $VERS -eq 1 ]; then
	LD_PRELOAD=$RPMALLOC $MEASSURE ninja
elif [ $VERS -eq 2 ]; then
	LD_PRELOAD=$MIMALLOC $MEASSURE ninja
else
	$MEASSURE ninja
fi

rm $LOCK
