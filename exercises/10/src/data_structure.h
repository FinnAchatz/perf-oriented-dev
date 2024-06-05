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

// initilize data structure to be able to handle at least size elements
void* init_data_structure(size_t size);

void destroy_data_structure(void* data_structure);

// write element elem at position index
void write_element(void* data_structure, size_t index, element elem);
// insert element elem between index and index-1
void insert_element(void* data_structure, size_t index, element elem);
// read element at position index
element* read_element(void* data_structure, size_t index);
// delete element at position index and move remaining elements to fill gap
void delete_element(void* data_structure, size_t index);

#endif
