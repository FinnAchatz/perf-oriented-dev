CC = gcc
#CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c11 -O3
CFLAGS = -Wall -Wextra  -Wpedantic -std=c11 -O0 -g

all: ds_benchmark_dummy ds_benchmark_linked_list ds_benchmark_array


ds_benchmark_dummy: ds_benchmark.c data_structure_dummy.o data_structure.h
	$(CC) $(CFLAGS) -o build/ds_benchmark_dummy data_structure_dummy.o ds_benchmark.c

# data_structure_array.o: data_structure_array.c  data_structure.h
# 	$(CC) $(CFLAGS) -c data_structure_array.o data_structure_array.c

ds_benchmark_array: ds_benchmark.c data_structure_array.o data_structure.h
	$(CC) $(CFLAGS) -o build/ds_benchmark_array_8 data_structure_array.o ds_benchmark.c -DELEM_SIZE=8
	$(CC) $(CFLAGS) -o build/ds_benchmark_array_512 data_structure_array.o ds_benchmark.c -DELEM_SIZE=512
	$(CC) $(CFLAGS) -o build/ds_benchmark_array_8M data_structure_array.o ds_benchmark.c -DELEM_SIZE=8388608

ds_benchmark_linked_list: ds_benchmark.c data_structure_linked_list.o data_structure.h
	$(CC) $(CFLAGS) -o build/ds_benchmark_linked_list_8 data_structure_linked_list.o ds_benchmark.c -DELEM_SIZE=8
	$(CC) $(CFLAGS) -o build/ds_benchmark_linked_list_512 data_structure_linked_list.o ds_benchmark.c -DELEM_SIZE=512
	$(CC) $(CFLAGS) -o build/ds_benchmark_linked_list_8M data_structure_linked_list.o ds_benchmark.c -DELEM_SIZE=8388608
	$(CC) $(CFLAGS) -o build/ds_benchmark_linked_list_AA_8 data_structure_linked_list.o ds_benchmark.c -DELEM_SIZE=8 -DALTERNATIVE_ALLOC_LL
	$(CC) $(CFLAGS) -o build/ds_benchmark_linked_list_AA_512 data_structure_linked_list.o ds_benchmark.c -DELEM_SIZE=512 -DALTERNATIVE_ALLOC_LL
	$(CC) $(CFLAGS) -o build/ds_benchmark_linked_list_AA_8M data_structure_linked_list.o ds_benchmark.c -DELEM_SIZE=8388608 -DALTERNATIVE_ALLOC_LL

clean:
	rm build/* *.o
