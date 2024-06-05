CC = gcc
# CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c11 -O3
# CFLAGS = -Wall -Wextra  -Wpedantic -std=c11 -O0 -DTEST
CFLAGS = -Wall -Wextra  -Wpedantic -std=c11 -O3 -g


all: ds_benchmark_linked_list ds_benchmark_array ds_benchmark_tiered_list ds_benchmark_unrolled_list
test: test_array test_linked_list test_tiered_list test_unrolled_list

%.o: %.c
	$(CC) $(CFLAGS) -c $@ $<

ds_benchmark_array: ds_benchmark.c data_structure_array.o data_structure.h
	$(CC) $(CFLAGS) -o build/ds_benchmark_array_8 data_structure_array.o ds_benchmark.c -DELEM_SIZE=8 -DCONF="\"array,0,8,"\"
	$(CC) $(CFLAGS) -o build/ds_benchmark_array_512 data_structure_array.o ds_benchmark.c -DELEM_SIZE=512 -DCONF="\"array,0,512,"\"
	$(CC) $(CFLAGS) -o build/ds_benchmark_array_8M data_structure_array.o ds_benchmark.c -DELEM_SIZE=8388608 -DCONF="\"array,0,8M,"\"

	$(CC) $(CFLAGS) -o build/ds_benchmark_array_8_random data_structure_array.o ds_benchmark.c -DRANDOM -DELEM_SIZE=8 -DCONF="\"array,1,8,"\"
	$(CC) $(CFLAGS) -o build/ds_benchmark_array_512_random data_structure_array.o ds_benchmark.c -DRANDOM -DELEM_SIZE=512 -DCONF="\"array,1,512,"\"
	$(CC) $(CFLAGS) -o build/ds_benchmark_array_8M_random data_structure_array.o ds_benchmark.c -DRANDOM -DELEM_SIZE=8388608 -DCONF="\"array,1,8M,"\"

ds_benchmark_linked_list: ds_benchmark.c data_structure_linked_list.o data_structure.h
	$(CC) $(CFLAGS) -o build/ds_benchmark_linked_list_8 data_structure_linked_list.o ds_benchmark.c -DELEM_SIZE=8 -DCONF="\"linked list,0,8,"\"
	$(CC) $(CFLAGS) -o build/ds_benchmark_linked_list_512 data_structure_linked_list.o ds_benchmark.c -DELEM_SIZE=512 -DCONF="\"linked list,0,512,"\"
	$(CC) $(CFLAGS) -o build/ds_benchmark_linked_list_8M data_structure_linked_list.o ds_benchmark.c -DELEM_SIZE=8388608 -DCONF="\"linked list,0,8M,"\"

	$(CC) $(CFLAGS) -o build/ds_benchmark_linked_list_8_random data_structure_linked_list.o ds_benchmark.c -DRANDOM -DELEM_SIZE=8 -DCONF="\"linked list,1,8,"\"
	$(CC) $(CFLAGS) -o build/ds_benchmark_linked_list_512_random data_structure_linked_list.o ds_benchmark.c -DRANDOM -DELEM_SIZE=512 -DCONF="\"linked list,1,512,"\"
	$(CC) $(CFLAGS) -o build/ds_benchmark_linked_list_8M_random data_structure_linked_list.o ds_benchmark.c -DRANDOM -DELEM_SIZE=8388608 -DCONF="\"linked list,1,8M,"\"

ds_benchmark_tiered_list: ds_benchmark.c data_structure_tiered_list.o data_structure.h
	$(CC) $(CFLAGS) -o build/ds_benchmark_tiered_list_8 data_structure_tiered_list.o ds_benchmark.c -DELEM_SIZE=8 -DCONF="\"tiered list,0,8,"\"
	$(CC) $(CFLAGS) -o build/ds_benchmark_tiered_list_512 data_structure_tiered_list.o ds_benchmark.c -DELEM_SIZE=512 -DCONF="\"tiered list,0,512,"\"
	$(CC) $(CFLAGS) -o build/ds_benchmark_tiered_list_8M data_structure_tiered_list.o ds_benchmark.c -DELEM_SIZE=8388608 -DCONF="\"tiered list,0,8M,"\"

	$(CC) $(CFLAGS) -o build/ds_benchmark_tiered_list_8_random data_structure_tiered_list.o ds_benchmark.c -DRANDOM -DELEM_SIZE=8 -DCONF="\"tiered list,1,8,"\"
	$(CC) $(CFLAGS) -o build/ds_benchmark_tiered_list_512_random data_structure_tiered_list.o ds_benchmark.c -DRANDOM -DELEM_SIZE=512 -DCONF="\"tiered list,1,512,"\"
	$(CC) $(CFLAGS) -o build/ds_benchmark_tiered_list_8M_random data_structure_tiered_list.o ds_benchmark.c -DRANDOM -DELEM_SIZE=8388608 -DCONF="\"tiered list,1,8M,"\"
ds_benchmark_unrolled_list: ds_benchmark.c data_structure_unrolled_list.o data_structure.h
	$(CC) $(CFLAGS) -o build/ds_benchmark_unrolled_list_8 data_structure_unrolled_list.o ds_benchmark.c -DELEM_SIZE=8 -DCONF="\"unrolled list,0,8,"\"
	$(CC) $(CFLAGS) -o build/ds_benchmark_unrolled_list_512 data_structure_unrolled_list.o ds_benchmark.c -DELEM_SIZE=512 -DCONF="\"unrolled list,0,512,"\"
	$(CC) $(CFLAGS) -o build/ds_benchmark_unrolled_list_8M data_structure_unrolled_list.o ds_benchmark.c -DELEM_SIZE=8388608 -DCONF="\"unrolled list,0,8M,"\"

	$(CC) $(CFLAGS) -o build/ds_benchmark_unrolled_list_8_random data_structure_unrolled_list.o ds_benchmark.c -DRANDOM -DELEM_SIZE=8 -DCONF="\"unrolled list,1,8,"\"
	$(CC) $(CFLAGS) -o build/ds_benchmark_unrolled_list_512_random data_structure_unrolled_list.o ds_benchmark.c -DRANDOM -DELEM_SIZE=512 -DCONF="\"unrolled list,1,512,"\"
	$(CC) $(CFLAGS) -o build/ds_benchmark_unrolled_list_8M_random data_structure_unrolled_list.o ds_benchmark.c -DRANDOM -DELEM_SIZE=8388608 -DCONF="\"unrolled list,1,8M,"\"

test_array: test_data_structure.c data_structure_array.o data_structure.h 
	$(CC) $(CFLAGS) -o test/test_array data_structure_array.o test_data_structure.c -DELEM_SIZE=8

test_linked_list: test_data_structure.c data_structure_linked_list.o data_structure.h 
	$(CC) $(CFLAGS) -o test/test_linked_list data_structure_linked_list.o test_data_structure.c -DELEM_SIZE=8

test_tiered_list: test_data_structure.c data_structure_tiered_list.o data_structure.h 
	$(CC) $(CFLAGS) -o test/test_tiered_list data_structure_tiered_list.o test_data_structure.c -DELEM_SIZE=8

test_unrolled_list: test_data_structure.c data_structure_unrolled_list.o data_structure.h 
	$(CC) $(CFLAGS) -o test/test_unrolled_list data_structure_unrolled_list.o test_data_structure.c -DELEM_SIZE=8

clean:
	rm build/* *.o
