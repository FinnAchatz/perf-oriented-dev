#!/usr/bin/env bash

GREEN='\033[0;32m'
NC='\033[0m' # No Color

mkdir allocators && cd allocators

echo -e "${GREEN}Building rpmalloc...${NC}"
git clone https://github.com/mjansson/rpmalloc.git
cd rpmalloc
./configure.py && \
# HACK: To fix a compile error on lcc `-Weverything` needs to be removed.
sed -i "s/ -Weverything//g" "./build.ninja" && \
ninja
cd .. # Go back to `allocators` directory.

echo -e "${GREEN}Building mimalloc...${NC}"
git clone https://github.com/microsoft/mimalloc.git
cd mimalloc
mkdir -p out/release && \
cd out/release && \
cmake ../.. && \
make
cd ../../../ # Go back to `allocators` directory.
