#include <stdio.h>
#include <stdlib.h>

#include "data_structure.h"

#define DS_SIZE 101

#ifndef INSTRUCTION_MIX
#define INSTRUCTION_MIX 50 // 0 1 10 50% ins/del
#endif

#define READ x = read_element(ds, get_next_index(&index, DS_SIZE));
#define WRITE write_element(ds, get_next_index(&index, DS_SIZE), (element)(x.value * 3));
#define INSERT insert_element(ds, get_next_index(&index, DS_SIZE), (element)(x.value * 5));
#define DELETE x = delete_element(ds, get_next_index(&index, DS_SIZE));

#if INSTRUCTION_MIX == 0

#define INSTRUCTIONS                                                           \
    for (int i = 0; i < 50; i++) {                                             \
        READ WRITE                                                             \
    }

#elif INSTRUCTION_MIX == 1

#define INSTRUCTIONS                                                           \
    for (int i = 0; i < 24; i++) {                                             \
        READ WRITE                                                             \
    }                                                                          \
    READ INSERT WRITE for (int i = 0; i < 24; i++){READ WRITE} DELETE

#elif INSTRUCTION_MIX == 10

#define INSTRUCTIONS                                                           \
    for (int i = 0; i < 10; i++) {                                             \
        READ WRITE READ WRITE INSERT READ WRITE READ WRITE DELETE              \
    }

#elif INSTRUCTION_MIX == 50

#define INSTRUCTIONS                                                           \
    for (int i = 0; i < 25; i++) {                                             \
        READ INSERT WRITE DELETE                                               \
    }

#endif

size_t get_next_index(size_t *index, int mod) {
    *index = ((*index) + 1) % mod;
    return *index;
}

void benchmark(int repetitions) {
    size_t index = -1;
    element x;
    x.value = 1;

    void *ds = init_data_structure(DS_SIZE);
    for (int rep = 0; rep < repetitions; rep++) {
        INSTRUCTIONS
    }
    destroy_data_structue(ds);

    printf("control number: %d\n", x.value);
}

int main(int argc, char *argv[]) {
    int repetitions = 1;

    if (argc <= 1) {
        printf("usage: %s <number of operations (in hundreds)>\nusing 1\n",
               argv[0]);
    } else {
        repetitions = atoi(argv[1]);
    }

    benchmark(repetitions);

    printf("size of element: %ld", sizeof(element));

    return EXIT_SUCCESS;
}
