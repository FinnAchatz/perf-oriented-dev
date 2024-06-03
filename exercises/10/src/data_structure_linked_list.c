#include "data_structure.h"
#include <stdlib.h>

struct node {
    element elem;
    struct node *next;
};

struct head {
    struct node *head;
};

// #ifdef ALTERNATIVE_ALLOC_LL
// void *init_data_structure(size_t size) {
//   struct node* nodes[size];
//   for (size_t i = 0; i < size; i++) {
//     nodes[i] = malloc(sizeof(struct node));
//   }
//   for (size_t i = 0; i < size*1; i++) {
//     size_t rnd_index = rand()%size;
//     struct node* tmp = nodes[i%size];
//     nodes[i%size] = nodes[rnd_index];
//     nodes[rnd_index] = tmp;
//   }
//   struct head* ds = malloc(sizeof(struct head));
//   struct node* node = nodes[0];
//   ds->head= node;
//   node->elem.value = 0;
//   for (size_t i = 1; i < size; i++) {
//     node->next = nodes[i];
//     node->next->elem.value = i;
//     node = node->next;
//   }
//   return (void*)ds;
// }
// #else
// void *init_data_structure(size_t size) {
//   struct head* ds = malloc(sizeof(struct head));
//   struct node* node = malloc(sizeof(struct node));
//   ds->head= node;
//   node->elem.value = 0;
//   for (size_t i = 1; i < size; i++) {
//     node->next = malloc(sizeof(struct node));
//     node->next->elem.value = i;
//     node = node->next;
//   }
//   return (void*)ds;
// }
// #endif

void *init_data_structure(size_t size) {
    struct head *ds = malloc(sizeof(struct head));
    struct node *node = malloc(sizeof(struct node));
    ds->head = node;
    node->elem.value = -1;
    return (void *)ds;
}

void destroy_data_structure(void *data_structure) {
    struct node *node = ((struct head *)data_structure)->head;
    free(data_structure);
    struct node *next;
    while (node->next) {
        next = node->next;
        free(node);
        node = next;
    }
    free(node);
}

void write_element(void *data_structure, size_t index, element elem) {
    struct node *node = ((struct head *)data_structure)->head;
    for (size_t i = 0; i < index; i++) {
        node = node->next;
    }
    node->elem = elem;
}

void insert_element(void *data_structure, size_t index, element elem) {
    struct node *new = malloc(sizeof(struct node));
    new->elem = elem;
    if (index == 0) {
        new->next = ((struct head *)data_structure)->head;
        ((struct head *)data_structure)->head = new;
        return;
    }

    struct node *node = ((struct head *)data_structure)->head;
    for (size_t i = 1; i < index; i++) {
        node = node->next;
    }
    new->next = node->next;
    node->next = new;
}

element *read_element(void *data_structure, size_t index) {
    struct node *node = ((struct head *)data_structure)->head;
    for (size_t i = 0; i < index; i++) {
        node = node->next;
    }
    return &node->elem;
}

void delete_element(void *data_structure, size_t index) {
    struct node *node = ((struct head *)data_structure)->head;
    if (index == 0) {
        ((struct head *)data_structure)->head = node->next;
        free(node);
        return;
    }
    for (size_t i = 1; i < index; i++) {
        node = node->next;
    }
    struct node *to_delete = node->next;
    node->next = to_delete->next;
    free(to_delete);
}

size_t get_size(void *data_structure) {
    struct node *node = data_structure;
    struct node *next;
    size_t size = 1;
    while (node->next) {
        size++;
        next = node->next;
        free(node);
        node = next;
    }
    return size;
}
