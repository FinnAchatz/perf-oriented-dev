#!/bin/bash

# Execute job in the partition "lva" unless you have special requirements.
#SBATCH --partition=lva
# Name your job to be able to identify it later
#SBATCH --job-name 04fa
# Redirect output stream to this file
#SBATCH --output=output.log
# Maximum number of tasks (=processes) to start in total
#SBATCH --ntasks=1
# Maximum number of tasks (=processes) to start per node
#SBATCH --ntasks-per-node=1
# Enforce exclusive node allocation, do not share with other jobs
#SBATCH --exclusive

echo "#########################################"
echo "################ ssca2 ##################"
echo "#########################################"
valgrind --tool=massif --massif-out-file="massif-ssca2.out" ./ssca2 17

echo
echo
echo
echo "#########################################"
echo "############### npb_bt_a #################"
echo "#########################################"
valgrind --tool=massif --massif-out-file="massif-npb_bt_a.out" ./npb_bt_a

