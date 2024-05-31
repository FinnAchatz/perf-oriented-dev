/*
*
* Some tests for generic lists. 
* Generated by Chat-GPT
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "data_structure.h"

void small_test_init_and_destroy() {
    void* data_structure = init_data_structure(10);
    assert(data_structure != NULL);
    destroy_data_structure(data_structure);
    printf("small_test_init_and_destroy passed.\n");
}

void small_test_insert_and_read() {
    void* data_structure = init_data_structure(10);
    element elem;
    elem.value = 42;

    insert_element(data_structure, 0, elem);
    element* read_elem = read_element(data_structure, 0);
    assert(read_elem != NULL);
    assert(read_elem->value == 42);

    destroy_data_structure(data_structure);
    printf("small_test_insert_and_read passed.\n");
}

void small_test_write_and_read() {
    void* data_structure = init_data_structure(10);
    element elem;
    elem.value = 42;

    insert_element(data_structure, 0, elem);
    elem.value = 84;
    write_element(data_structure, 0, elem);
    element* read_elem = read_element(data_structure, 0);
    assert(read_elem != NULL);
    assert(read_elem->value == 84);

    destroy_data_structure(data_structure);
    printf("small_test_write_and_read passed.\n");
}

void small_test_delete_element() {
    size_t size = 10;
    void* data_structure = init_data_structure(size);

    element elems[5];
    for (int i = 0; i < 5; i++) {
        elems[i].value = i * 3;
        insert_element(data_structure, i, elems[i]);
    }

    delete_element(data_structure, 2);

    // Verify elements before the deleted index
    for (int i = 0; i < 2; i++) {
        element* read_elem = read_element(data_structure, i);
        assert(read_elem != NULL);
        assert(read_elem->value == i * 3);
    }

    // Verify elements after the deleted index are shifted left
    for (int i = 2; i < 4; i++) {
        element* read_elem = read_element(data_structure, i);
        assert(read_elem != NULL);
        assert(read_elem->value == (i + 1) * 3);
    }

    // // Verify the last element is now out of bounds
    // element* read_elem = read_element(data_structure, 4);
    // assert(read_elem == NULL);

    destroy_data_structure(data_structure);
    printf("test_delete_element passed.\n");
}

void small_test_insert_multiple_and_read() {
    void* data_structure = init_data_structure(10);
    element elem1, elem2, elem3;
    elem1.value = 1;
    elem2.value = 2;
    elem3.value = 3;

    insert_element(data_structure, 0, elem1);
    insert_element(data_structure, 1, elem2);
    insert_element(data_structure, 2, elem3);

    element* read_elem1 = read_element(data_structure, 0);
    element* read_elem2 = read_element(data_structure, 1);
    element* read_elem3 = read_element(data_structure, 2);

    assert(read_elem1 != NULL && read_elem1->value == 1);
    assert(read_elem2 != NULL && read_elem2->value == 2);
    assert(read_elem3 != NULL && read_elem3->value == 3);

    destroy_data_structure(data_structure);
    printf("small_test_insert_multiple_and_read passed.\n");
}

void test_init_and_destroy() {
    size_t size = 1000;
    void* data_structure = init_data_structure(size);
    assert(data_structure != NULL);
    destroy_data_structure(data_structure);
    printf("test_init_and_destroy passed.\n");
}

void test_insert_and_read() {
    size_t size = 1000;
    void* data_structure = init_data_structure(size);

    element elems[10];
    for (int i = 0; i < 10; i++) {
        elems[i].value = i * 3;
        insert_element(data_structure, i, elems[i]);
    }

    for (int i = 0; i < 10; i++) {
        element* read_elem = read_element(data_structure, i);
        assert(read_elem != NULL);
        assert(read_elem->value == i * 3);
    }

    destroy_data_structure(data_structure);
    printf("test_insert_and_read passed.\n");
}

void test_write_and_read() {
    size_t size = 1000;
    void* data_structure = init_data_structure(size);

    element elems[10];
    for (int i = 0; i < 10; i++) {
        elems[i].value = i * 3;
        insert_element(data_structure, i, elems[i]);
    }

    for (int i = 0; i < 10; i++) {
        elems[i].value = i * 30;
        write_element(data_structure, i, elems[i]);
    }

    for (int i = 0; i < 10; i++) {
        element* read_elem = read_element(data_structure, i);
        assert(read_elem != NULL);
        assert(read_elem->value == i * 30);
    }

    destroy_data_structure(data_structure);
    printf("test_write_and_read passed.\n");
}

void test_delete_element() {
    size_t size = 1000;
    void* data_structure = init_data_structure(size);

    element elems[10];
    for (int i = 0; i < 10; i++) {
        elems[i].value = i * 3;
        insert_element(data_structure, i, elems[i]);
    }

    delete_element(data_structure, 2);

    // Verify elements before the deleted index
    for (int i = 0; i < 2; i++) {
        element* read_elem = read_element(data_structure, i);
        assert(read_elem != NULL);
        assert(read_elem->value == i * 3);
    }

    // // Verify elements after the deleted index are shifted left
    // for (int i = 2; i < 9; i++) {
    //     element* read_elem = read_element(data_structure, i);
    //     assert(read_elem != NULL);
    //     assert(read_elem->value == (i + 1) * 3);
    // }
    //

    destroy_data_structure(data_structure);
    printf("test_delete_element passed.\n");
}

void test_insert_multiple_and_read() {
    size_t size = 1000;
    void* data_structure = init_data_structure(size);

    element elems[100];
    for (int i = 0; i < 100; i++) {
        elems[i].value = i;
        insert_element(data_structure, i, elems[i]);
    }

    for (int i = 0; i < 100; i++) {
        element* read_elem = read_element(data_structure, i);
        assert(read_elem != NULL);
        assert(read_elem->value == i);
    }

    destroy_data_structure(data_structure);
    printf("test_insert_multiple_and_read passed.\n");
}

void test_edge_cases() {
    size_t size = 1000;
    void* data_structure = init_data_structure(size);

    // Test insertion at the beginning
    element elem1 = {.value = 100};
    insert_element(data_structure, 0, elem1);
    element* read_elem = read_element(data_structure, 0);
    assert(read_elem != NULL);
    assert(read_elem->value == 100);

    // // Test insertion at the end
    // element elem2 = {.value = 200};
    // insert_element(data_structure, size - 1, elem2);
    // read_elem = read_element(data_structure, size - 1);
    // assert(read_elem != NULL);
    // assert(read_elem->value == 200);

    // // Test out of bounds
    // element elem3 = {.value = 300};
    // insert_element(data_structure, size, elem3); // Assuming this should be handled gracefully
    // read_elem = read_element(data_structure, size);
    // assert(read_elem == NULL);

    destroy_data_structure(data_structure);
    printf("test_edge_cases passed.\n");
}

void run_bigger_tests() {
    test_init_and_destroy();
    test_insert_and_read();
    test_write_and_read();
    test_delete_element();
    test_insert_multiple_and_read();
    test_edge_cases();

    printf("All bigger tests passed.\n");
}


void run_small_tests() {
    small_test_init_and_destroy();
    small_test_insert_and_read();
    small_test_write_and_read();
    small_test_delete_element();
    small_test_insert_multiple_and_read();

    printf("All small tests passed.\n");
}

void run_all_tests() {
  run_small_tests();
  run_bigger_tests();
}

