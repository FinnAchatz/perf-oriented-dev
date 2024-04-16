#!/bin/bash

# Execute job in the partition "lva" unless you have special requirements.
#SBATCH --partition=lva
# Name your job to be able to identify it later
#SBATCH --job-name 04fa
# Redirect output stream to this file
#SBATCH --output=output_perf_3.log
# Maximum number of tasks (=processes) to start in total
#SBATCH --ntasks=1
# Maximum number of tasks (=processes) to start per node
#SBATCH --ntasks-per-node=1
# Enforce exclusive node allocation, do not share with other jobs
#SBATCH --exclusive

EVENTS1=L1-dcache-load-misses,\
L1-dcache-loads,\
L1-dcache-prefetch-misses,\
L1-dcache-prefetches,\
L1-dcache-store-misses,\
L1-dcache-stores,\
L1-icache-load-misses
EVENTS2=L1-icache-loads,\
LLC-load-misses,\
LLC-loads,\
LLC-prefetch-misses,\
LLC-prefetches,\
LLC-store-misses,\
LLC-stores
EVENTS3=branch-load-misses,\
branch-loads,\
dTLB-load-misses,\
dTLB-loads,\
dTLB-store-misses,\
dTLB-stores,\
iTLB-load-misses
EVENTS4=iTLB-loads,\
node-load-misses,\
node-loads,\
node-prefetch-misses,\
node-prefetches,\
node-store-misses,\
node-stores

EVENTS=$EVENTS3

echo "#########################################"
echo "################ ssca2 ##################"
echo "#########################################"
perf stat -e $EVENTS ./ssca2 17

echo
echo
echo
echo "#########################################"
echo "############### npb_bt_a #################"
echo "#########################################"
perf stat -e $EVENTS ./npb_bt_a

