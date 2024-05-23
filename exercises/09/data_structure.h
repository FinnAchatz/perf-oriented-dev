#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

#include <stdlib.h>
#include <stdio.h>

#ifndef ELEM_SIZE
#define ELEM_SIZE 8
#endif // !ELEM_SIZE

union custom_elem {
  int value;
  char buff[ELEM_SIZE];
};

typedef union custom_elem element;

void* init_data_structure(size_t size);
void destroy_data_structue(void* data_structure);

void write_element(void* data_structure, size_t index, element elem);
void insert_element(void* data_structure, size_t index, element elem);
element read_element(void* data_structure, size_t index);
element delete_element(void* data_structure, size_t index);

#endif
