CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=gnu11 -O3

all: malloctest_arena malloctest_malloc malloctest_dyn_arena

malloctest_arena: malloctest.c
	$(CC) $(CFLAGS) -DARENA -o $@ $<

malloctest_dyn_arena: malloctest.c
	$(CC) $(CFLAGS) -DARENA -DDYNAMIC -o $@ $<

malloctest_malloc: malloctest.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm malloctest_arena malloctest_malloc malloctest_dyn_arena

