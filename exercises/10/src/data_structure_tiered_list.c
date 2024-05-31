#include "data_structure.h"
#include <stdio.h>

#ifndef SUBARRAY_COUNT
#define SUBARRAY_COUNT 3
#endif /* ifndef SUBARRAY_COUNT */


typedef struct {
    size_t curr_length;
    element *array;
} sub_array_t;

typedef struct {
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
                printf("%s % 4d", j != 0 ? "|" : "", ds->subarrays[i].array[j].value);
            } else {
                printf("%s     ", j != 0 ? "|" : "");
            }
        }
        printf("]\n");
    }
}

void *init_data_structure(size_t size) {
    data_structure_t *ds = malloc(sizeof(data_structure_t));
    ds->subarray_count = SUBARRAY_COUNT;
    ds->subarray_length = size/SUBARRAY_COUNT + 1;

    for (size_t i = 0; i < ds->subarray_count; i++) {
        ds->subarrays[i].array =
            malloc((ds->subarray_length) * sizeof(element));
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
  #ifdef DEBUG
    printf("\ndestroy()\n");
    debug_print_data_structure((data_structure_t*)data_structure);
  #endif /* ifdef DEBUG */
    for (size_t i = 0; i < SUBARRAY_COUNT; i++) {
        free(((data_structure_t *)data_structure)->subarrays[i].array);
    }
    free(data_structure);
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

void write_element(void *data_structure, size_t index, element elem) {
    data_structure_t *ds = data_structure;

    sub_array_t *sub_array;
    size_t sub_index;
    get_subarray_index(ds, index, &sub_array, &sub_index, NULL);
    // write element at index
    sub_array->array[sub_index] = elem;
  #ifdef DEBUG
    printf("\nwrite(idx: %lu, elem: %d)\n", index, elem.value);
    debug_print_data_structure(ds);
  #endif /* ifdef DEBUG */
}

void insert_element(void *data_structure, size_t index, element elem) {
    data_structure_t *ds = data_structure;

    // first get position to insert element
    sub_array_t *sub_array;
    size_t sub_index;
    size_t sub_array_num;
    get_subarray_index(ds, index, &sub_array, &sub_index, &sub_array_num);

    // two cases: either there is still space in that subarray -> insert and
    // shift in subarray
    //            subarray is full -> shift in subarray, insert last element
    //            into next subarray
    element overflow_elem = sub_array->array[sub_array->curr_length - 1];
    // shift elements
    for (size_t i = sub_array->curr_length; i > sub_index; i--) {
        sub_array->array[i] = sub_array->array[i - 1];
    }
    // insert
    sub_array->array[sub_index] = elem;
    sub_array->curr_length++;
    if (sub_array->curr_length > ds->subarray_length) {
        // second case, insert last element into next subarray
        // could probably be optimized using tail recursion to don't overload
        // the stack
        sub_array->curr_length--;
        insert_element(ds, index - sub_index + sub_array->curr_length,
                       overflow_elem);
        
    }
  #ifdef DEBUG
    printf("\ninsert(idx: %lu, elem: %d)\n", index, elem.value);
    debug_print_data_structure(ds);
  #endif /* ifdef DEBUG */
}

element *read_element(void *data_structure, size_t index) {
    data_structure_t *ds = data_structure;

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
    data_structure_t *ds = data_structure;

    // first get position to insert element
    sub_array_t *sub_array;
    size_t sub_index;
    size_t sub_array_num;
    get_subarray_index(ds, index, &sub_array, &sub_index, &sub_array_num);

    // shift elements
    for (size_t i = sub_index + 1; i < sub_array->curr_length; i++) {
        sub_array->array[i - 1] = sub_array->array[i];
    }
    sub_array->curr_length--;

    // compensate underflow if sub_array is emmpty and not last
    if (sub_array->curr_length == 0 && sub_array_num != ds->subarray_count){
      element* underflow_elem = read_element(ds, index);
      insert_element(ds, index, *underflow_elem);
      delete_element(ds, index + 1);
    }
  #ifdef DEBUG
    printf("\ndelete(idx: %lu)\n", index);
    debug_print_data_structure((data_structure_t*)data_structure);
  #endif /* ifdef DEBUG */
}
