#include <stdio.h>
#include <stdlib.h>

#include "data_structure.h"

#define DS_SIZE 101

#ifndef INSTRUCTION_MIX
  #define INSTRUCTION_MIX 50 // 0 1 10 50% ins/del 
#endif

#ifdef DEBUG
#define READ x = read_element(ds, increase_mod(&index, DS_SIZE)); printf("read   : ");print_ds(ds);
#define WRITE write_element(ds, increase_mod(&index, DS_SIZE), 9);printf("write  : ");print_ds(ds);
#define INSERT insert_element(ds, increase_mod(&index, DS_SIZE), 8);printf("insert : ");print_ds(ds);
#define DELETE x = delete_element(ds, increase_mod(&index, DS_SIZE));printf("delete : ");print_ds(ds);
#else
#define READ x = read_element(ds, increase_mod(&index, DS_SIZE));
#define WRITE write_element(ds, increase_mod(&index, DS_SIZE), x*3);
#define INSERT insert_element(ds, increase_mod(&index, DS_SIZE), x*5);
#define DELETE x = delete_element(ds, increase_mod(&index, DS_SIZE));
#endif /* ifdef DEBUG */


#if INSTRUCTION_MIX == 0

#define INSTRUCTIONS \
for (int i = 0; i < 50; i++) {\
  READ\
  WRITE\
}

#elif INSTRUCTION_MIX == 1

#define INSTRUCTIONS \
for (int i = 0; i < 24; i++) {\
  READ\
  WRITE\
}\
 READ\
 INSERT\
 WRITE\
 for (int i = 0; i < 24; i++) {\
  READ\
}\
DELETE

#elif INSTRUCTION_MIX == 10 

#define INSTRUCTIONS \
for (int i = 0; i < 10; i++) {\
  READ\
  WRITE\
  READ\
  WRITE\
  INSERT\
  READ\
  WRITE\
  READ\
  WRITE\
  DELETE\
}

#elif INSTRUCTION_MIX == 50

#define INSTRUCTIONS \
for (int i = 0; i < 25; i++) {\
  READ\
  INSERT\
  WRITE\
  DELETE\
}

#endif

size_t increase_mod(size_t *index, int mod) {
  *index = ((*index) + 1) % mod;
  return *index;
}

void print_ds(void* ds){
  for (size_t i = 0; i < DS_SIZE; i++) {
    printf("%d ", read_element(ds, i));
  }   
  printf("\n");
}

int main(int argc, char *argv[]) {
  int repetitions = 1;
  if (argc <= 1) {
    printf("usage: %s <number of operations (in hundreds)>\nusing 1\n", argv[0]);
  } else {
    repetitions = atoi(argv[1]);
  }

  void *ds = init_data_structure(DS_SIZE);
  size_t index = -1;
  int x = 1;

  for (int rep = 0; rep < repetitions; rep++){
    INSTRUCTIONS
  }

    #ifdef DEBUG
  print_ds(ds);
    #endif /* ifdef DEBUG */

  destroy_data_structue(ds);
  printf("%d\n", x);
  return EXIT_SUCCESS;
}
