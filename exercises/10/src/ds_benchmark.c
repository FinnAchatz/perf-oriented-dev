#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "data_structure.h"
#include "test_data_structure.h"

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

void benchmark(double min_time_sec, int instruction_mix, int ds_size) {
    size_t index = -1;
    element x;
    x.value = 1;

    struct timespec start_ts, curr_ts;
    timespec_get(&start_ts, TIME_UTC);
    timespec_get(&curr_ts, TIME_UTC);
    size_t counter = 0;

    void *ds = init_data_structure(ds_size);

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

    printf(CONF "%d, %d, %lu, %lf, %d, %d, %lu\n", instruction_mix, ds_size,
           counter, DIFF_SEC(start_ts, curr_ts), x.value, rand_sum,
           sizeof(element));
}

void random_benchmark(double min_time_sec, int instruction_mix, int ds_size) {
    size_t index = -1;
    element x;
    x.value = 1;

    struct timespec start_ts, curr_ts;
    timespec_get(&start_ts, TIME_UTC);
    timespec_get(&curr_ts, TIME_UTC);
    size_t counter = 0;

    void *ds = init_data_structure(ds_size);

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

    printf(CONF "%d, %d, %lu, %lf, %d, %d, %lu\n", instruction_mix, ds_size,
           counter, DIFF_SEC(start_ts, curr_ts), x.value, rand_sum,
           sizeof(element));
}
int main(int argc, char *argv[]) {
    if (argc <= 3) {
        printf("usage: %s <desired execution time (s)> <instruction "
               "mix> <data_structure size>\n",
               argv[0]);
        return EXIT_FAILURE;
    }
    double exec_time = atof(argv[1]);
    int instruction_mix = atoi(argv[2]);
    int ds_size = atoi(argv[3]);
#ifdef TEST
    run_all_tests();
#endif /* ifdef TEST  */

#ifndef DEBUG
    benchmark(exec_time, instruction_mix, ds_size);
#else
    // void* ds = init_data_structure(ds_size);
    // insert_element(ds, 1, (element){.value=-11});
    // insert_element(ds, 4, (element){.value=-33});
    // delete_element(ds, 4);
    // read_element(ds, 5);
    // write_element(ds, 4, (element){.value=-99});
    // delete_element(ds, 4);
    // read_element(ds, 5);
    // delete_element(ds, 4);
    // insert_element(ds, 4, (element){.value=-22});
    // delete_element(ds, 4);
    // read_element(ds, 5);
    //
    // destroy_data_structure(ds);
#endif

    return EXIT_SUCCESS;
}
