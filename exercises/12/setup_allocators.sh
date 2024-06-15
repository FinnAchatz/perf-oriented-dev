#!/usr/bin/env bash

GREEN='\033[0;32m'
NC='\033[0m' # No Color

mkdir allocators && cd allocators

echo -e "${GREEN}Cloning rpmalloc...${NC}"
git clone https://github.com/mjansson/rpmalloc.git

# Build rpmalloc
echo -e "${GREEN}Building rpmalloc...${NC}"
cd rpmalloc \
    && ./configure.py \
    && ninja
