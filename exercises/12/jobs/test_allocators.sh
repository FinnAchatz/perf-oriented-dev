#!/usr/bin/env bash

# Execute job in the partition "lva" unless you have special requirements.
#SBATCH --partition=lva
# Name your job to be able to identify it later
#SBATCH --job-name allocators_test
# Redirect output stream to this file
#SBATCH --output=allocators_test.log
# Maximum number of tasks (=processes) to start in total
#SBATCH --ntasks=1
# Maximum number of tasks (=processes) to start per node
#SBATCH --ntasks-per-node=1
# Enforce exclusive node allocation, do not share with other jobs
#SBATCH --exclusive
#
ORIGINAL_LUA=../lua-5.4.6/src/lua
OPTIMIZED_LUA=../lua-5.4.6-optimized/src/lua

echo "testing default"
echo "running original lua interpreter:"
${ORIGINAL_LUA} ../../lua/fib.lua

echo "running optimized lua interpreter:"
${OPTIMIZED_LUA} ../../lua/fib.lua

echo "testing rpmalloc"
echo "running original lua interpreter:"
LDD_PRELOAD=./allocators/rpmalloc/bin/linux/release/x86-64/librpmalloc.so ${ORIGINAL_LUA} ../../lua/fib.lua

echo "running optimized lua interpreter:"
LDD_PRELOAD=./allocators/rpmalloc/bin/linux/release/x86-64/librpmalloc.so ${OPTIMIZED_LUA} ../../lua/fib.lua

echo "testing mimalloc"
echo "running original lua interpreter:"
LDD_PRELOAD=./allocators/mimalloc/out/release/libmimalloc.so ${ORIGINAL_LUA} ../../lua/fib.lua

echo "running optimized lua interpreter:"
LDD_PRELOAD=./allocators/mimalloc/out/release/libmimalloc.so ${OPTIMIZED_LUA} ../../lua/fib.lua
