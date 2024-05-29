#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "data_structure.h"

#define READ x.value = read_element(ds, get_next_index(&index, ds_size))->value;
#define WRITE                                                                  \
    x.value *= 3;                                                              \
    write_element(ds, get_next_index(&index, ds_size), x);
#define INSERT                                                                 \
    x.value *= 3;                                                              \
    insert_element(ds, get_next_index(&index, ds_size), x);
#define DELETE delete_element(ds, get_next_index(&index, ds_size));

#define DIFF_SEC(START, CURR)                                                  \
    ((CURR.tv_sec - START.tv_sec) + ((CURR.tv_nsec - START.tv_nsec) / 1000000000.0))
#ifndef CONF
#define CONF
#endif /* ifndef CONF
 */

size_t get_next_index(size_t *index, int mod) {
    *index = ((*index) + 1) % mod;
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
                READ WRITE
            }
        } else if (instruction_mix == 1) { // 99% read/write
            for (int i = 0; i < 24; i++) {
                READ WRITE
            }
            READ INSERT WRITE for (int i = 0; i < 24; i++){READ WRITE} DELETE
        } else if (instruction_mix == 10) { // 90% read/write
            for (int i = 0; i < 10; i++) {
                READ WRITE READ WRITE INSERT READ WRITE READ WRITE DELETE
            }
        } else { // 50% read/write
            for (int i = 0; i < 25; i++) {
                READ INSERT WRITE DELETE
            }
        }
        timespec_get(&curr_ts, TIME_UTC);
        counter++;
    }

    destroy_data_structue(ds);

    int rand_sum = 0;
    char buff_cpy[ELEM_SIZE];
    memcpy(&buff_cpy, &(x.buff), ELEM_SIZE);
    for (size_t i = 0; i < ELEM_SIZE; i++) {
        rand_sum += buff_cpy[i];
    }

    printf(CONF"%d, %d, %lu, %lf, %d, %d, %lu\n", instruction_mix, ds_size, counter, DIFF_SEC(start_ts, curr_ts), x.value, rand_sum, sizeof(element));
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

    benchmark(exec_time, instruction_mix, ds_size);

    return EXIT_SUCCESS;
}
