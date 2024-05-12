CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=gnu11 -O3 -pthread

all: malloctest_arena malloctest_malloc malloctest_dyn_arena

malloctest_arena: malloctest.c
	$(CC) $(CFLAGS) -DARENA -o $@ $<

malloctest_dyn_arena: malloctest.c
	$(CC) $(CFLAGS) -DARENA -DDYNAMIC -DINIT_SIZE_FACTOR_DYN=1 -o $@1 $<
	$(CC) $(CFLAGS) -DARENA -DDYNAMIC -DINIT_SIZE_FACTOR_DYN=0.8 -o $@08 $<
	$(CC) $(CFLAGS) -DARENA -DDYNAMIC -DINIT_SIZE_FACTOR_DYN=0.6 -o $@06 $<
	$(CC) $(CFLAGS) -DARENA -DDYNAMIC -DINIT_SIZE_FACTOR_DYN=0.5 -o $@05 $<
	$(CC) $(CFLAGS) -DARENA -DDYNAMIC -DINIT_SIZE_FACTOR_DYN=0.4 -o $@04 $<
	$(CC) $(CFLAGS) -DARENA -DDYNAMIC -DINIT_SIZE_FACTOR_DYN=0.3 -o $@03 $<
	$(CC) $(CFLAGS) -DARENA -DDYNAMIC -DINIT_SIZE_FACTOR_DYN=0.2 -o $@02 $<

malloctest_malloc: malloctest.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm malloctest_*
	#rm malloctest_arena malloctest_malloc malloctest_dyn_arena1 malloctest_dyn_arena08 malloctest_dyn_arena06 malloctest_dyn_arena05 malloctest_dyn_arena04 malloctest_dyn_arena03 malloctest_dyn_arena02
