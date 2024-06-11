#!/bin/bash

# Execute job in the partition "lva" unless you have special requirements.
#SBATCH --partition=lva
# Name your job to be able to identify it later
#SBATCH --job-name test
# Redirect output stream to this file
#SBATCH --output=output.log
# Maximum number of tasks (=processes) to start in total
#SBATCH --ntasks=1
# Maximum number of tasks (=processes) to start per node
#SBATCH --ntasks-per-node=1
# Enforce exclusive node allocation, do not share with other jobs
#SBATCH --exclusive

LUA=/home/cb76/cb761225/lua-5.4.6/src/lua
FIB=/home/cb76/cb761225/perf-oriented-dev/lua/fib.lua

echo "%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%"
echo "%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%"
echo "%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%"
echo "%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%"
echo "                       GPROF"
echo "%#%#%#%#%#%#%#%#%#%#%#%#|||#%#%#%#%#%#%#%#%#%#%#%#%#%#%"
echo "%#%#%#%#%#%#%#%#%#%#%#%#|||#%#%#%#%#%#%#%#%#%#%#%#%#%#%"
echo "%#%#%#%#%#%#%#%#%#%#%#%\\\\V//#%#%#%#%#%#%#%#%#%#%#%#%#%"
echo "%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%#%"
$LUA $FIB


