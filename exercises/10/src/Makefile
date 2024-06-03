CC = gcc
# CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c11 -O3
CFLAGS = -Wall -Wextra  -Wpedantic -std=c11 -O0 -DTEST
# CFLAGS = -Wall -Wextra  -Wpedantic -std=c11 -O0 -g -DDEBUG -DTEST


all: ds_benchmark_dummy ds_benchmark_linked_list ds_benchmark_array
test: test_array test_linked_list test_tiered_list


ds_benchmark_dummy: ds_benchmark.c data_structure_dummy.o data_structure.h test_data_structure.h
	$(CC) $(CFLAGS) -o build/ds_benchmark_dummy data_structure_dummy.o ds_benchmark.c

ds_benchmark_array: ds_benchmark.c data_structure_array.o data_structure.h test_data_structure.h
	$(CC) $(CFLAGS) -o build/ds_benchmark_array_8 data_structure_array.o ds_benchmark.c -DELEM_SIZE=8 -DCONF="\"array, 8, "\"
	$(CC) $(CFLAGS) -o build/ds_benchmark_array_512 data_structure_array.o ds_benchmark.c -DELEM_SIZE=512 -DCONF="\"array, 512, "\"
	$(CC) $(CFLAGS) -o build/ds_benchmark_array_8M data_structure_array.o ds_benchmark.c -DELEM_SIZE=8388608 -DCONF="\"array, 8M, "\"

ds_benchmark_linked_list: ds_benchmark.c data_structure_linked_list.o data_structure.h test_data_structure.h
	$(CC) $(CFLAGS) -o build/ds_benchmark_linked_list_8 data_structure_linked_list.o ds_benchmark.c -DELEM_SIZE=8 -DCONF="\"linked list, 8, "\"
	$(CC) $(CFLAGS) -o build/ds_benchmark_linked_list_512 data_structure_linked_list.o ds_benchmark.c -DELEM_SIZE=512 -DCONF="\"linked list, 512, "\"
	$(CC) $(CFLAGS) -o build/ds_benchmark_linked_list_8M data_structure_linked_list.o ds_benchmark.c -DELEM_SIZE=8388608 -DCONF="\"linked list, 8M, "\"
	$(CC) $(CFLAGS) -o build/ds_benchmark_linked_list_AA_8 data_structure_linked_list.o ds_benchmark.c -DELEM_SIZE=8 -DALTERNATIVE_ALLOC_LL -DCONF="\"linked list (alt.), 8, "\"
	$(CC) $(CFLAGS) -o build/ds_benchmark_linked_list_AA_512 data_structure_linked_list.o ds_benchmark.c -DELEM_SIZE=512 -DALTERNATIVE_ALLOC_LL -DCONF="\"linked list (alt.), 512, "\"
	$(CC) $(CFLAGS) -o build/ds_benchmark_linked_list_AA_8M data_structure_linked_list.o ds_benchmark.c -DELEM_SIZE=8388608 -DALTERNATIVE_ALLOC_LL -DCONF="\"linked list (alt.), 8M, "\"

ds_benchmark_tiered_list: ds_benchmark.c data_structure_tiered_list.o data_structure.h test_data_structure.o
	$(CC) $(CFLAGS) -o build/ds_benchmark_tiered_8 data_structure_tiered_list.o test_data_structure.o ds_benchmark.c -DELEM_SIZE=8

test_array: test_data_structure.c data_structure_array.o data_structure.h 
	$(CC) $(CFLAGS) -o test/test_array data_structure_array.o test_data_structure.c

test_linked_list: test_data_structure.c data_structure_linked_list.o data_structure.h 
	$(CC) $(CFLAGS) -o test/test_linked_list data_structure_linked_list.o test_data_structure.c

test_tiered_list: test_data_structure.c data_structure_tiered_list.o data_structure.h 
	$(CC) $(CFLAGS) -o test/test_tiered_list data_structure_tiered_list.o test_data_structure.c

clean:
	rm build/* *.o
