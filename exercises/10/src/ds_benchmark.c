#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#include "data_structure.h"

#define READ                                                                   \
    do {                                                                       \
        x.value = read_element(ds, get_next_index(&index, ds_size))->value;    \
    } while (0)
#define WRITE                                                                  \
    do {                                                                       \
        x.value *= 3;                                                          \
        write_element(ds, get_next_index(&index, ds_size), x);                 \
    } while (0)
#define INSERT                                                                 \
    do {                                                                       \
        x.value *= 3;                                                          \
        insert_element(ds, get_next_index(&index, ds_size), x);                \
    } while (0)
#define DELETE                                                                 \
    do {                                                                       \
        delete_element(ds, get_next_index(&index, ds_size));                   \
    } while (0)

#define DIFF_SEC(START, CURR)                                                  \
    ((CURR.tv_sec - START.tv_sec) +                                            \
     ((CURR.tv_nsec - START.tv_nsec) / 1000000000.0))

#ifndef CONF
#define CONF
#endif

/*  Written in 2019 by David Blackman and Sebastiano Vigna (vigna@acm.org)

To the extent possible under law, the author has dedicated all copyright
and related and neighboring rights to this software to the public domain
worldwide. This software is distributed without any warranty.

See <http://creativecommons.org/publicdomain/zero/1.0/>. */

#include <stdint.h>

/* This is xoshiro128++ 1.0, one of our 32-bit all-purpose, rock-solid
   generators. It has excellent speed, a state size (128 bits) that is
   large enough for mild parallelism, and it passes all tests we are aware
   of.

   For generating just single-precision (i.e., 32-bit) floating-point
   numbers, xoshiro128+ is even faster.

   The state must be seeded so that it is not everywhere zero. */

static uint32_t s[4];

static inline uint32_t rotl(const uint32_t x, int k) {
    return (x << k) | (x >> (32 - k));
}

uint32_t next_random(void) {
    const uint32_t result = rotl(s[0] + s[3], 7) + s[0];

    const uint32_t t = s[1] << 9;

    s[2] ^= s[0];
    s[3] ^= s[1];
    s[1] ^= s[2];
    s[0] ^= s[3];

    s[2] ^= t;

    s[3] = rotl(s[3], 11);

    return result;
}

size_t get_next_index(size_t *index, int mod) {
#ifdef RANDOM
    *index = next_random() % mod;
#else
    *index = ((*index) + 1) % mod;
#endif
    return *index;
}
void fill_data_structure_linear(void *ds, size_t size) {
    for (size_t i = 0; i < size; i++) {
        insert_element(ds, i, (element){.value = i});
    }
}

void fill_data_structure_random(void *ds, size_t size) {
    insert_element(ds, 0, (element){.value = 0});
    for (size_t i = 1; i < size; i++) {
        size_t index = ((size_t)next_random()) % i;
        insert_element(ds, index, (element){.value = i});
    }
    for (size_t i = 0; i < size; i++) {
        write_element(ds, i, (element){.value = i});
    }
}

void benchmark(double min_time_sec, int instruction_mix, int ds_size,
               bool fill_random) {
    size_t index = -1;
    element x;
    x.value = 1;

    void *ds = init_data_structure(ds_size + 1);
    if (fill_random) {
        fill_data_structure_random(ds, ds_size);
    } else {
        fill_data_structure_linear(ds, ds_size);
    }

    struct timespec start_ts, curr_ts;
    timespec_get(&start_ts, TIME_UTC);
    timespec_get(&curr_ts, TIME_UTC);
    size_t counter = 0;

    while (DIFF_SEC(start_ts, curr_ts) < min_time_sec) {
        if (instruction_mix == 0) { // 100% read/write
            for (int i = 0; i < 50; i++) {
                READ;
                WRITE;
            }
        } else if (instruction_mix == 1) { // 99% read/write
            for (int i = 0; i < 24; i++) {
                READ;
                WRITE;
            }
            READ;
            INSERT;
            WRITE;
            for (int i = 0; i < 24; i++) {
                READ;
                WRITE;
            }
            DELETE;
        } else if (instruction_mix == 10) { // 90% read/write
            for (int i = 0; i < 10; i++) {
                READ;
                WRITE;
                READ;
                WRITE;
                INSERT;
                READ;
                WRITE;
                READ;
                WRITE;
                DELETE;
            }
        } else { // 50% read/write
            for (int i = 0; i < 25; i++) {
                READ;
                INSERT;
                WRITE;
                DELETE;
            }
        }
        timespec_get(&curr_ts, TIME_UTC);
        counter++;
    }

    destroy_data_structure(ds);

    int rand_sum = 0;
    char buff_cpy[ELEM_SIZE];
    memcpy(&buff_cpy, &(x.buff), ELEM_SIZE);
    for (size_t i = 0; i < ELEM_SIZE; i++) {
        rand_sum += buff_cpy[i];
    }

    // "CONF {name,random_access,elem_size}, ins_mix,
    // num_elems,fill_random,repetitions
    printf(CONF "%d,%d,%d,%zu\n", instruction_mix, ds_size, fill_random,
           counter);
}

int main(int argc, char *argv[]) {
    if (argc <= 3) {
        printf("usage: %s <desired execution time (s)> <instruction "
               "mix> <data_structure size> [-r random init]\n",
               argv[0]);
        return EXIT_FAILURE;
    }
    double exec_time = atof(argv[1]);
    int instruction_mix = atoi(argv[2]);
    int ds_size = atoi(argv[3]);
    bool random_init = false;
    if (argc == 5 && argv[4][1] == 'r') {
        random_init = true;
    }

    printf("\r");

    benchmark(exec_time, instruction_mix, ds_size, random_init);

    return EXIT_SUCCESS;
}
