#!/usr/bin/env bash

cd ./lua-5.4.6/ && make clean &&  make all test && cd ..

cd ./lua-5.4.6-optimized/ && make clean && make all test && cd ..

./setup_allocators.sh
