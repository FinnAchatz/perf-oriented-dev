#include <stdio.h>
#include <stdlib.h>

#include "data_structure.h"

#define DS_SIZE 10

#ifndef INSTRUCTION_MIX
#define INSTRUCTION_MIX 50 // 0 1 10 50% ins/del
#endif

#define READ x = read_element(ds, get_next_index(&index, DS_SIZE));
#define WRITE                                                                  \
    x.value *= 3;                                                              \
    write_element(ds, get_next_index(&index, DS_SIZE), x);
#define INSERT                                                                 \
    x.value *= 3;                                                              \
    insert_element(ds, get_next_index(&index, DS_SIZE), x);
#define DELETE x = delete_element(ds, get_next_index(&index, DS_SIZE));

size_t get_next_index(size_t *index, int mod) {
    *index = ((*index) + 1) % mod;
    return *index;
}

void benchmark(int repetitions, int instruction_mix) {
    size_t index = -1;
    element x;
    x.value = 1;

    void *ds = init_data_structure(DS_SIZE);

    write_element(ds, 0, x);
    read_element(ds, 0);

    // if (instruction_mix == 0) { // 100% read/write
    //     for (int rep = 0; rep < repetitions; rep++) {
    //         for (int i = 0; i < 50; i++) {
    //             READ WRITE
    //         }
    //     }
    // } else if (instruction_mix == 1) { // 99% read/write
    //     for (int rep = 0; rep < repetitions; rep++) {
    //         for (int i = 0; i < 24; i++) {
    //             READ WRITE
    //         }
    //         READ INSERT WRITE for (int i = 0; i < 24; i++){READ WRITE} DELETE
    //     }
    // } else if (instruction_mix == 10) { // 90% read/write
    //     for (int rep = 0; rep < repetitions; rep++) {
    //         for (int i = 0; i < 10; i++) {
    //             READ WRITE READ WRITE INSERT READ WRITE READ WRITE DELETE
    //         }
    //     }
    // } else { // 50% read/write
    //     for (int rep = 0; rep < repetitions; rep++) {
    //         for (int i = 0; i < 25; i++) {
    //             READ INSERT WRITE DELETE
    //         }
    //     }
    // }

    destroy_data_structue(ds);

    printf("control number: %d\n", x.value);
}

int main(int argc, char *argv[]) {
    if (argc <= 2) {
        printf("usage: %s <number of operations (in hundreds)> <instruction "
               "mix [0, 1, 10, 50]>\n",
               argv[0]);
        return EXIT_FAILURE;
    }
    int repetitions = atoi(argv[1]);
    int instruction_mix = atoi(argv[2]);

    benchmark(repetitions, instruction_mix);

    printf("size of element: %ld", sizeof(element));

    return EXIT_SUCCESS;
}
