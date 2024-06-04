#include "data_structure.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

#ifndef SUBARRAY_COUNT
#define SUBARRAY_COUNT 10
#endif /* ifndef SUBARRAY_COUNT */

typedef struct {
    size_t curr_length;
    element *array;
} sub_array_t;

typedef struct {
    void* mem_block;
    size_t subarray_length;
    size_t subarray_count;
    sub_array_t subarrays[SUBARRAY_COUNT];
} data_structure_t;

void debug_print_data_structure(data_structure_t *ds) {
    printf("subarray_length:%lu  subarray_count:%lu\n", ds->subarray_length,
           ds->subarray_count);
    for (size_t i = 0; i < SUBARRAY_COUNT; i++) {

        printf("[%lu *] -> [", ds->subarrays[i].curr_length);
        for (size_t j = 0; j < ds->subarray_length; j++) {

            if (j < ds->subarrays[i].curr_length) {
                printf("%s % 4d", j != 0 ? "|" : "",
                       ds->subarrays[i].array[j].value);
            } else {
                printf("%s     ", j != 0 ? "|" : "");
            }
        }
        printf("]\n");
    }
    fflush(stdout);
}

void *init_data_structure(size_t size) {
    assert(size > 0);

    data_structure_t *ds = malloc(sizeof(data_structure_t));
    // set to at least 1 x 2
    ds->subarray_count = SUBARRAY_COUNT > 0 ? SUBARRAY_COUNT : 1;
    ds->subarray_length = size / SUBARRAY_COUNT > 1 ? size / SUBARRAY_COUNT + 1 : 2;

    ds->mem_block = malloc(sizeof(element) * ds->subarray_length * ds->subarray_count);

    for (size_t i = 0; i < ds->subarray_count; i++) {
        ds->subarrays[i].array = ds->mem_block+ sizeof(element) * ds->subarray_length * i;
        ds->subarrays[i].curr_length = 0;
    }
    ds->subarrays[0].curr_length = 1;

#ifdef DEBUG
    printf("\ninit(size:%lu)\n", size);
    debug_print_data_structure(ds);
#endif /* ifdef DEBUG */

    return ds;
}

void destroy_data_structure(void *data_structure) {
    assert(data_structure != NULL);

    data_structure_t* ds = data_structure;

#ifdef DEBUG
    printf("\ndestroy()\n");
    debug_print_data_structure((data_structure_t *)data_structure);
#endif /* ifdef DEBUG */
    free(ds->mem_block);
    free(ds);
}

// sets subarray pointer to subarray containing index at position sub_index
void get_subarray_index(data_structure_t *ds, size_t index,
                        sub_array_t **sub_array, size_t *sub_index,
                        size_t *sub_array_num) {

    size_t idx_sum = 0;
    for (size_t i = 0; i < SUBARRAY_COUNT; i++) {
        idx_sum += ds->subarrays[i].curr_length;
        if (idx_sum > index || (ds->subarrays[i].curr_length == 0)) {
            *sub_array = &(ds->subarrays[i]);
            *sub_index = index - (idx_sum - (*sub_array)->curr_length);
            if (sub_array_num) *sub_array_num = i;
            break;
        }
    }
}

// helper to overflow if last sublist is full
void overflow_super(data_structure_t *ds, element overflow_elem) {
#ifdef DEBUG
    printf("\before noverflow_super()\n");
    debug_print_data_structure(ds);
#endif /* ifdef DEBUG */
    // Idea: if last subarray is full a normal overslow is no longer possible.
    // To work with that, shift all subarrays to the left and insert elements
    // from lost array again in the beginning. this should again fill the
    // subarrays from the left as wanted.
    sub_array_t drop_array = ds->subarrays[0];

    element drop_elems[drop_array.curr_length];
    size_t drop_elems_count = drop_array.curr_length;
    memcpy(drop_elems, drop_array.array, drop_array.curr_length * sizeof(element));

    // shift subarrays
    for (size_t i = 1; i < ds->subarray_count; i++) {
        ds->subarrays[i - 1] = ds->subarrays[i];
    }

    // maybe it's possible to reuse the drop array instead of mallocing a new
    // one
    ds->subarrays[ds->subarray_count - 1] = drop_array;
    ds->subarrays[ds->subarray_count - 1].array[0] = overflow_elem;
    ds->subarrays[ds->subarray_count - 1].curr_length = 1;

    // insert dropped elements
    for (int i = drop_elems_count - 1; i >= 0; i--) {
        insert_element(ds, 0, drop_elems[i]);
    }
    // free(drop_array.array);
#ifdef DEBUG
    printf("\noverflow_super()\n");
    debug_print_data_structure(ds);
#endif /* ifdef DEBUG */
}

void write_element(void *data_structure, size_t index, element elem) {
    assert(data_structure != NULL);

    data_structure_t *ds = data_structure;

    assert(index < ds->subarray_count * ds->subarray_length);

#ifdef DEBUG
    printf("\nbefore write(idx: %lu, elem: %d)\n", index, elem.value);
    debug_print_data_structure(ds);
#endif /* ifdef DEBUG */

    sub_array_t *sub_array;
    size_t sub_index;
    get_subarray_index(ds, index, &sub_array, &sub_index, NULL);
    // write element at index
    assert(sub_index < sub_array->curr_length);
    sub_array->array[sub_index] = elem;
#ifdef DEBUG
    printf("\nwrite(idx: %lu, elem: %d)\n", index, elem.value);
    debug_print_data_structure(ds);
#endif /* ifdef DEBUG */
}

void insert_element(void *data_structure, size_t index, element elem) {
    assert(data_structure != NULL);

    data_structure_t *ds = data_structure;

    assert(index < ds->subarray_count * ds->subarray_length);

#ifdef DEBUG
    printf("\nbefore insert(idx: %lu, elem: %d)\n", index, elem.value);
    debug_print_data_structure(ds);
#endif /* ifdef DEBUG */

    // first get position to insert element
    sub_array_t *sub_array;
    size_t sub_index;
    size_t sub_array_num;
    get_subarray_index(ds, index, &sub_array, &sub_index, &sub_array_num);

    // two cases:
    //    1. there is still space in that subarray -> insert and
    //       shift in subarray
    //    2. subarray is full ->
    //        if not last subarray: insert last element into next
    //           subarray goto 1.
    //        if last subarray: call overflow_super()

    element overflow_elem = sub_array->array[sub_array->curr_length - 1];
    // shift elements
    for (size_t i = sub_array->curr_length; i > sub_index; i--) {
        sub_array->array[i] = sub_array->array[i - 1];
    }
    // insert
    sub_array->array[sub_index] = elem;
    sub_array->curr_length++;

    // second case, overflow
    if (sub_array->curr_length > ds->subarray_length) {

        // last subarray
        if (sub_array_num + 1 == ds->subarray_count) {
            sub_array->curr_length--;
            overflow_super(ds, overflow_elem);
        } else {
            sub_array->curr_length--;
            insert_element(ds, index - sub_index + sub_array->curr_length,
                           overflow_elem);
        }
    }
#ifdef DEBUG
    printf("\ninsert(idx: %lu, elem: %d)\n", index, elem.value);
    debug_print_data_structure(ds);
#endif /* ifdef DEBUG */
}

element *read_element(void *data_structure, size_t index) {
    data_structure_t *ds = data_structure;
#ifdef DEBUG
    printf("\nbefore read(idx: %lu)\n", index);
    debug_print_data_structure(ds);
#endif /* ifdef DEBUG */

    // first traverse superarray to get to subarray which contains index
    sub_array_t *sub_array;
    size_t sub_index;
    get_subarray_index(ds, index, &sub_array, &sub_index, NULL);

    // read element at index
    element *elem = &(sub_array->array[sub_index]);
#ifdef DEBUG
    printf("\nread(idx: %lu) = %d\n", index, elem->value);
    debug_print_data_structure(ds);
#endif /* ifdef DEBUG */
    return elem;
}

void delete_element(void *data_structure, size_t index) {
#ifdef DEBUG
    printf("\nbefore delete(idx: %lu)\n", index);
    debug_print_data_structure((data_structure_t *)data_structure);
#endif /* ifdef DEBUG */
    data_structure_t *ds = data_structure;

    // first get position to insert element
    sub_array_t *sub_array;
    size_t sub_index;
    size_t sub_array_idx;
    get_subarray_index(ds, index, &sub_array, &sub_index, &sub_array_idx);

    // underflow if sub_array will be empty and next sub_array has elements
    if (sub_array->curr_length == 1 && ds->subarrays[sub_array_idx+1].curr_length > 0){
        // duplicate next element into current sub_array
        element underflow_elem = ds->subarrays[sub_array_idx+1].array[0];
        sub_array->array[1] = underflow_elem;
        sub_array->curr_length++;
        // remove duplicated element
        delete_element(ds, index + 2);
    }

    // shift elements
    for (size_t i = sub_index + 1; i < sub_array->curr_length; i++) {
        sub_array->array[i - 1] = sub_array->array[i];
    }
    sub_array->curr_length--;

#ifdef DEBUG
    printf("\ndelete(idx: %lu)\n", index);
    debug_print_data_structure((data_structure_t *)data_structure);
#endif /* ifdef DEBUG */
}
