#include "data_structure.h"
#include <stdio.h>

struct data_structure {
  size_t length;
  element* array;
};

void *init_data_structure(size_t size) {
  struct data_structure* ds = malloc(sizeof(struct data_structure));
  ds->length = size;
  ds->array = malloc(sizeof(element)*(size * 1));
  for (size_t i = 0; i < size; i++) {
    ds->array[i].value = i;
  }
  return ds;
}

void destroy_data_structue(void *data_structure) { free(data_structure); }

void write_element(void *data_structure, size_t index, element elem) {
  ((struct data_structure*)data_structure)->array[index] = elem;
}

void insert_element(void *data_structure, size_t index, element elem) {
  struct data_structure* ds = data_structure;
  for (size_t i = ds->length; i > index; i--) {
    ds->array[i] = ds->array[i-1] ;
  }
  ds->array[index] = elem;
}

element read_element(void *data_structure, size_t index) {
  struct data_structure* ds = data_structure;
  element* elems = ds->array;
  element elem = elems[index];
  return elem;
  return ((struct data_structure*)data_structure)->array[index];
}

element delete_element(void *data_structure, size_t index) {
  struct data_structure* ds = data_structure;
  element elem = ds->array[index];
  for (size_t i = index; i < ds->length; i++) {
    ds->array[i] = ds->array[i+1];
  }
  return elem;
}
