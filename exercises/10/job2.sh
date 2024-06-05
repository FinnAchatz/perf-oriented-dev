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

# set parameters 
MIN_TIME=0.1
CSV_PATH="../../values_2.csv"

# set stack size
ulimit -s unlimited

cd ./src/build

echo "name,random_access,elem_size,ins_mix,num_elems,fill_random,repetitions" >> ${CSV_PATH}


for ins_mix in 0 1 10 50; do 
  for elem_size in 8; do 
    for num_elems in 100000; do
      for prog in ds_benchmark_array_ ds_benchmark_linked_list_ ds_benchmark_tiered_list_; do 
        ./${prog}${elem_size} ${MIN_TIME} ${ins_mix} ${num_elems} >> $CSV_PATH
        ./${prog}${elem_size}_random ${MIN_TIME} ${ins_mix} ${num_elems} >> $CSV_PATH
      done
    done
  done
done
