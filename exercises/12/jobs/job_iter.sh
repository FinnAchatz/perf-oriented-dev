#!/bin/bash

# Execute job in the partition "lva" unless you have special requirements.
#SBATCH --partition=lva
# Name your job to be able to identify it later
#SBATCH --job-name fib_iter.lua
# Redirect output stream to this file
#SBATCH --output=fib_iter.log
# Maximum number of tasks (=processes) to start in total
#SBATCH --ntasks=1
# Maximum number of tasks (=processes) to start per node
#SBATCH --ntasks-per-node=1
# Enforce exclusive node allocation, do not share with other jobs
#SBATCH --exclusive

ORIGINAL_LUA=../lua-5.4.6/src/lua
OPTIMIZED_LUA=../lua-5.4.6-optimized/src/lua

echo "running original lua interpreter:"
${ORIGINAL_LUA} ../lua/fib_iter.lua

echo "running optimized lua interpreter:"
${OPTIMIZED_LUA} ../lua/fib_iter.lua

