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
MIN_TIME=1
CSV_PATH="../../values_local.csv"

# set stack size
ulimit -s 131072 

cd ./src/build

echo "name, elem_size, ins_mix, num_elems, repetitions, time, control, control2, control3" >> ${CSV_PATH}

# run programs 
for ins_mix in 0 1 10 50; do 
  for elem_size in 8 512 8M; do 
    for num_elems in 10 1000; do
      for prog in ds_benchmark_array_ ds_benchmark_linked_list_ ds_benchmark_linked_list_AA_; do 
        ./${prog}${elem_size} ${MIN_TIME} ${ins_mix} ${num_elems} >> $CSV_PATH
      done
    done
  done
done

for ins_mix in 0 1 10 50; do 
  for elem_size in 8 512; do 
    for num_elems in 100000 10000000; do
      for prog in ds_benchmark_array_ ds_benchmark_linked_list_ ds_benchmark_linked_list_AA_; do 
        ./${prog}${elem_size} ${MIN_TIME} ${ins_mix} ${num_elems} >> $CSV_PATH
      done
    done
  done
done

