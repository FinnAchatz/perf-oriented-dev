#!/bin/bash

# Execute job in the partition "lva" unless you have special requirements.
#SBATCH --partition=lva
# Name your job to be able to identify it later
#SBATCH --job-name 04fa
# Redirect output stream to this file
#SBATCH --output=output_time3.log
# Maximum number of tasks (=processes) to start in total
#SBATCH --ntasks=1
# Maximum number of tasks (=processes) to start per node
#SBATCH --ntasks-per-node=1
# Enforce exclusive node allocation, do not share with other jobs
#SBATCH --exclusive

EVENTS=L1-dcache-load-misses,\
L1-dcache-loads,\
L1-dcache-prefetch-misses,\
L1-dcache-prefetches,\
L1-dcache-store-misses,\
L1-dcache-stores,\
L1-icache-load-misses

echo "#########################################"
echo "################ ssca2 ##################"
echo "#########################################"
#/bin/time valgrind --tool=massif --massif-out-file="massif-ssca2.out" ./ssca2 17
#/bin/time perf stat -e $EVENTS ./ssca2 17
/bin/time ./ssca2 17

echo
echo
echo
echo "#########################################"
echo "############### npb_bt_a #################"
echo "#########################################"
#/bin/time valgrind --tool=massif --massif-out-file="massif-npb_bt_a2.out" ./npb_bt_a
#/bin/time perf stat -e $EVENTS ./npb_bt_a 17
/bin/time ./npb_bt_a 17

