#include "data_structure.h"
#include <stdio.h>

void* init_data_structure(size_t size){
  printf("inti data structure\n");
  return malloc(1);
}

void destroy_data_structue(void* data_structure){
  printf("destroy_data_structue\n");
  free(data_structure);
}

void write_element(void* data_structure, size_t index, element elem){
  printf("write %d at %ld\n", elem.value, index);
}

void insert_element(void* data_structure, size_t index, element elem){
    printf("insert %d at %ld\n", elem.value, index);
}

element read_element(void* data_structure, size_t index){
    printf("read at %ld\n", index);
    return (element)1;
}

element delete_element(void* data_structure, size_t index){
  printf("delete at %ld\n", index);
  return (element)2;
}
