#include "data_structure.h"

typedef struct {
    size_t length;
    element *array;
} data_structure_t;

void *init_data_structure(size_t size) {
    data_structure_t *ds = malloc(sizeof(data_structure_t));
    ds->length = size;
    ds->array = malloc(sizeof(element) * size);
    return ds;
}

void destroy_data_structure(void *data_structure) {
    free(((data_structure_t *)data_structure)->array);
    free(data_structure);
}

void write_element(void *data_structure, size_t index, element elem) {
    ((data_structure_t *)data_structure)->array[index] = elem;
}

void insert_element(void *data_structure, size_t index, element elem) {
    data_structure_t *ds = data_structure;
    for (size_t i = ds->length; i > index; i--) {
        ds->array[i] = ds->array[i - 1];
    }
    ds->array[index] = elem;
}

element *read_element(void *data_structure, size_t index) {
    return &((data_structure_t *)data_structure)->array[index];
}

void delete_element(void *data_structure, size_t index) {
    data_structure_t *ds = data_structure;
    for (size_t i = index; i < ds->length; i++) {
        ds->array[i] = ds->array[i + 1];
    }
}
