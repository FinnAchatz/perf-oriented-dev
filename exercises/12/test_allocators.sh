#!/usr/bin/env bash

echo "testing rpmalloc"
LDD_PRELOAD=./allocators/rpmalloc/bin/linux/release/x86-64/librpmalloc.so lua ../../lua/fib.lua

echo "testing mimalloc"
LDD_PRELOAD=./allocators/mimalloc/out/release/libmimalloc.so lua ../../lua/fib.lua
