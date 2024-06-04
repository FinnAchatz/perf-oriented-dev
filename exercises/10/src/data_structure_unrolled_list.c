
// -------------------------------------------------------------------------- //
// --- Explanation ---------------------------------------------------------- //
// -------------------------------------------------------------------------- //

// ---------------------    ---------------------    ---------------------
// |c1|c2|c3|...|cx|*ci| -> |c1|c2|c3|...|cx|*ci| -> |c1|c2|c3|...|cx|*ci|
// ---------------------    ---------------------    ---------------------
// cx  = Data Cell
// *ci = Chunk Pointer Cell => Stores a Pointer to the next Chunk in
//                             it's CHUNK_POINTER_FIELD.
//                             This is why the Chunk Pointer Index is one
//                             less than the CHUNK_SIZE.
//                             The last Chunk Pointer will be a NULL
//                             Pointer to indicate that no more chunks
//                             are allocated after it.
//
// NOTE: I think I have too many safeguards/redundant safeguards implemented,
//       but since this is not Rust, I thought better safe than sorry.
//
// Usage Manual:
//
// Your Code needs to define a few Values for this Code to work:
//
//      => (Optional) CHUNK_SIZE = Number of Elements per Chunk (default = 4096)
//      => CHUNK_POINTER_FIELD   = The Field of the Struct which holds the
//                                 Chunk Pointers
//                                 BEWARE: This Field needs to be able to
//                                 store a Pointer in it (size_t)

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define DIV_CEIL(x, y) (((x)/(y)) + (((x) % (y)) != 0))

typedef struct {
    char * chunks;
    size_t num_elem;
    size_t element_size;
    size_t chunk_size;
} unrolled_linked_list_t;

// -------------------------------------------------------------------------- //

// Helper Struct for iterating through Chunks in a MemoryManager
// Built according to the Rust-Iterator:
// https://doc.rust-lang.org/stable/std/iter/index.html
typedef struct {
    char * curr_chunk;
    size_t curr_elem_idx;
    unrolled_linked_list_t * manager;
} unrolled_linked_list_i;

// -------------------------------------------------------------------------- //

static void to_iter(unrolled_linked_list_t * m, unrolled_linked_list_i * i) {
    if (m == NULL) {
        i == NULL;
    } else {
        *i = (unrolled_linked_list_i) {
            .curr_chunk= m->chunks,
            .curr_elem_idx = 0,
            .manager = m
        };
    }
}

// -------------------------------------------------------------------------- //

static char ** get_chunk_pointer(unrolled_linked_list_i * i) {
    return ((char **) i->curr_chunk + i->manager->chunk_size * i->manager->element_size);
}

static bool in_last_chunk(unrolled_linked_list_i * i) {
    char ** chunk_pointer = get_chunk_pointer(i);
    return *chunk_pointer == NULL;
}

static bool is_current_chunk_pointer(unrolled_linked_list_i * i) {
    return ((i->curr_elem_idx % i->manager->chunk_size) == 0) && (i->curr_elem_idx != 0);
}

// Return the next Element as a Pointer.
// Returns NULL if all Elements where already returned.
// Does not advance the Iterator.
static void * peek (unrolled_linked_list_i * i) {
    if (i == NULL) 
        return NULL;

    // Check if the Index of the element is valid.
    if (i->curr_elem_idx >= i->manager->num_elem) 
        return NULL;

    // Check if the current Element is not the Chunk Pointer.
    if (!is_current_chunk_pointer(i)) 
        return i->curr_chunk + (i->curr_elem_idx % i->manager->chunk_size);

    char * chunk_pointer = *((char **) (i->curr_chunk + (i->manager->chunk_size * i->manager->element_size)));
    // Return NULL if the chunk_pointer is NULL, otherwise return a reference to the first element in the next chunk.
    return chunk_pointer;
}

// Return the next Element as a Pointer.
// Returns NULL if all Elements where already returned.
// Advances the Iterator.
static void * next (unrolled_linked_list_i * i) {
    if (i == NULL) 
        return NULL;

    // Check if the Index of the element is valid.
    if (i->curr_elem_idx >= i->manager->num_elem) 
        return NULL;

    // Check if the current Element is not the Chunk Pointer.
    if (!is_current_chunk_pointer(i)) 
        return i->curr_chunk + (i->curr_elem_idx++ % i->manager->chunk_size) * i->manager->element_size;

    // Check that more chunks are allocated.
    char ** chunk_pointer = get_chunk_pointer(i);
    if (*chunk_pointer == NULL) 
        // Return NULL if no more chunks are allocated.
        return NULL;

    // Redirect to the next Chunk
    i->curr_chunk = *chunk_pointer;
    i->curr_elem_idx++;

    // Return reference to the start of the next chunk which equals the first element.
    return i->curr_chunk;
}

static void write_to_next(unrolled_linked_list_i * i, void * value) {
    void * elem = next(i);
    if (elem == NULL) 
        return;

    memcpy(elem, value, i->manager->element_size);
}

static void copy_next(unrolled_linked_list_i * i, void * value) {
    void * elem = next(i);
    if (elem == NULL) 
        return;

    memcpy(value, elem, i->manager->element_size);
}

static void insert_before_inner(char * curr_chunk, size_t element_size, size_t num_elem, size_t chunk_size) {
    char ** chunk_pointer = (char **) curr_chunk + element_size * chunk_size;
    if (*chunk_pointer == NULL) {
        // Check if the current chunk is full.
        if (num_elem % chunk_size == 1) {
            *chunk_pointer = (char *) malloc(chunk_size * element_size * sizeof(char) + sizeof(void *));
            if (*chunk_pointer == NULL) 
                return;

            char ** next_chunk_pointer = (char**) *chunk_pointer + element_size * chunk_size;
            *next_chunk_pointer = NULL;
            // Copy the last element of current chunk into the first element of the next chunk.
            memcpy(*chunk_pointer, curr_chunk + (chunk_size - 1) * element_size, element_size);
            // Move all elements in the current chunk forward one.
            memmove(curr_chunk + element_size, curr_chunk, (chunk_size - 1) * element_size);
        } else {
            // Move all elements in the current chunk forward one.
            memmove(curr_chunk + element_size, curr_chunk, ((num_elem - 1) % chunk_size) * element_size);
        }
    } else {
        // Move all elements in following chunks forward one.
        insert_before_inner(*chunk_pointer, element_size, num_elem, chunk_size);
        // Copy the last element of current chunk into the first element of the next chunk.
        memcpy(*chunk_pointer, curr_chunk + element_size * (chunk_size - 1), element_size);
        // Move all elements in the current chunk forward one.
        memmove(curr_chunk + element_size, curr_chunk, (chunk_size - 1) * element_size);
    }
}

static void insert_before(unrolled_linked_list_i * i, void * value) {
    if (i == NULL) 
        return;

    i->manager->num_elem ++; 

    char ** chunk_pointer = get_chunk_pointer(i);
    if (is_current_chunk_pointer(i)) {
        // If there are no more chunks, create a new one and copy the desired value into the first element.
        if (*chunk_pointer == NULL) {
            *chunk_pointer = (char *) malloc(i->manager->chunk_size * i->manager->element_size * sizeof(char) + sizeof(void *));
            if (*chunk_pointer == NULL) 
                return;

            char ** next_chunk_pointer = (char **) *chunk_pointer + i->manager->chunk_size * i->manager->element_size;
            *next_chunk_pointer = NULL;
        } else {
            // Move all elements in all following chunks forward one.
            insert_before_inner(*chunk_pointer, i->manager->element_size, i->manager->num_elem, i->manager->chunk_size);
        }
        // Copy the desired value into the first element of the next chunk.
        memcpy(*chunk_pointer, value, i->manager->element_size);
    } else if (*chunk_pointer == NULL) {
        char * curr_elem = i->curr_chunk + (i->curr_elem_idx % i->manager->chunk_size) * i->manager->element_size;
        // Check if the current chunk is full.
        if ((i->manager->num_elem % i->manager->chunk_size) == 1 && i->manager->num_elem != 1) {
            *chunk_pointer = (char *) malloc(i->manager->chunk_size * i->manager->element_size * sizeof(char) + sizeof(void *));
            if (*chunk_pointer == NULL) 
                return;

            char ** next_chunk_pointer = (char **) *chunk_pointer + i->manager->chunk_size * i->manager->element_size;
            *next_chunk_pointer = NULL;

            // Copy the last element of current chunk into the first element of the next chunk.
            memcpy(*chunk_pointer, i->curr_chunk + (i->manager->chunk_size - 1) * i->manager->element_size, i->manager->element_size);
            memmove(curr_elem + i->manager->element_size, curr_elem, (i->manager->chunk_size - 1) * i->manager->element_size);
        } else {
            // Calculate how many elements are still in this chunk after the current element.
            size_t elems_in_chunk = (i->manager->num_elem - 1) % i->manager->chunk_size;
            // Since the chunk pointer is NULL, all elements are in the current chunk.
            memmove(curr_elem + i->manager->element_size, curr_elem, elems_in_chunk * i->manager->element_size);
        }
        memcpy(curr_elem, value, i->manager->element_size);
    } else {
        insert_before_inner(*chunk_pointer, i->manager->element_size, i->manager->num_elem, i->manager->chunk_size);
        memcpy(*chunk_pointer, i->curr_chunk + (i->manager->chunk_size - 1) * i->manager->element_size, i->manager->element_size);

        char * curr_elem = i->curr_chunk + (i->curr_elem_idx % i->manager->chunk_size) * i->manager->element_size;
        // Calculate how many elements are still in this chunk after the current element.
        // We know that the chunk must be full since the chunk pointer is not NULL.
        size_t elems_in_chunk = i->manager->chunk_size - (i->curr_elem_idx % i->manager->chunk_size) - 1;
        memmove(curr_elem + i->manager->element_size, curr_elem, elems_in_chunk * i->manager->element_size);
        memcpy(curr_elem, value, i->manager->element_size);
    }
}

static void remove_inner(char * curr_chunk, size_t element_size, size_t num_elem, size_t chunk_size) {
    char ** chunk_pointer = ((char **) curr_chunk + element_size * chunk_size);
    // Check if the iterator is in the last allocated chunk.
    if (*chunk_pointer == NULL) {
        // Recursion ends here after all elements are moved back one.
        // The previos recursive call already copied the first element from this chunk.
        memmove(curr_chunk, &curr_chunk[element_size], (num_elem % chunk_size) * element_size);
    } else {
        // Move all elements in the current chunk back one.
        memmove(curr_chunk, &curr_chunk[element_size], (chunk_size - 1) * element_size);
        // Copy first element of next chunk into the last element of the current chunk.
        memcpy(&curr_chunk[element_size * (chunk_size - 1)], *chunk_pointer, element_size);

        char ** next_chunk_pointer = ((char **) *chunk_pointer + element_size * chunk_size);
        // Check if the next chunk is the last chunk and will now be empty.
        if ((*next_chunk_pointer == NULL) && ((num_elem % chunk_size) == 0)) {
            free(*chunk_pointer);
            *chunk_pointer = NULL;
        } else {
            // Repeat with the next chunk.
            remove_inner(*chunk_pointer, element_size, num_elem, chunk_size);
        }
    }
}

static void * remove_elem(unrolled_linked_list_i * i) {
    if (i == NULL) 
        return NULL;

    // Check if the Index of the element is valid.
    if (i->curr_elem_idx >= i->manager->num_elem) 
        return NULL;

    i->manager->num_elem --;

    // NOTE: peek cannot return NULL here as all of it's Guards are satisfied.
    // TODO: This returns a reference to the element that will be overridden by the memmove. This would probably have to be malloc'd.
    char * curr_elem = (char *) peek(i);
    if (is_current_chunk_pointer(i)) {
        // NOTE: chunk_pointer cannot be null here, since the index of the current element is less than the total amount of elements.
        //       This implies that there are elements after this, implying that another chunk has to exist.
        char ** chunk_pointer = get_chunk_pointer(i);
        char ** next_chunk_pointer = (char **) (*chunk_pointer + i->manager->chunk_size * i->manager->element_size);

        // Check if the next chunk is the last chunk and will now be empty.
        if ((*next_chunk_pointer == NULL) && ((i->manager->num_elem % i->manager->chunk_size) == 0)) {
            free(*chunk_pointer);
            *chunk_pointer = NULL;
        } else {
            remove_inner(*chunk_pointer, i->manager->element_size, i->manager->num_elem, i->manager->chunk_size);
        }
    }
    // Check if the iterator is in the last allocated chunk.
    else if (in_last_chunk(i)) {
        memmove(curr_elem, curr_elem + i->manager->element_size, (i->manager->num_elem - i->curr_elem_idx) * i->manager->element_size);
    } else {
        char ** chunk_pointer = get_chunk_pointer(i);
        char ** next_chunk_pointer = (char **) (*chunk_pointer + i->manager->chunk_size * i->manager->element_size);

        // Calculate how many elements are still in this chunk after the current element.
        size_t elems_in_chunk = i->manager->chunk_size - (i->curr_elem_idx % i->manager->chunk_size) - 1;
        memmove(curr_elem, &curr_elem[i->manager->element_size], elems_in_chunk * i->manager->element_size);
        // Copy first element of next chunk into the last element of the current chunk.
        memcpy(&i->curr_chunk[i->manager->element_size * (i->manager->chunk_size - 1)], chunk_pointer, i->manager->element_size);

        // Check if the next chunk is the last chunk and will now be empty.
        if ((*next_chunk_pointer == NULL) && ((i->manager->num_elem % i->manager->chunk_size) == 0)) {
            free(*chunk_pointer);
            *chunk_pointer = NULL;
        } else {
            // Move all elements back one in all following chunks.
            remove_inner(i->curr_chunk, i->manager->element_size, i->manager->num_elem, i->manager->chunk_size);
        }
    }

    return curr_elem;
}

// -------------------------------------------------------------------------- //

struct {
    void  (*to_iter)(unrolled_linked_list_t *, unrolled_linked_list_i *);
    void* (*next) (unrolled_linked_list_i *);
    void  (*insert_before) (unrolled_linked_list_i *, void *);
    void* (*remove) (unrolled_linked_list_i *);
    void  (*write_to_next) (unrolled_linked_list_i *, void *);
    void  (*copy_next) (unrolled_linked_list_i *, void *);
} Iter = {
    .to_iter        = to_iter,
    .next           = next,
    .insert_before  = insert_before,
    .remove         = remove_elem,
    .write_to_next  = write_to_next,
    .copy_next      = copy_next,
};

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

int init_chunks (unrolled_linked_list_t *, size_t, size_t);
void print_chunk_pointers(unrolled_linked_list_t);

// -------------------------------------------------------------------------- //

int init_chunks (unrolled_linked_list_t * m, size_t element_size, size_t chunk_size) {
    if (m == NULL) 
        return -1;

    char * chunk = (char *) malloc(chunk_size * element_size * sizeof(char) + sizeof(void *));
    if (chunk == NULL) 
        return -1;

    m->chunks = chunk;
    *((char **) m->chunks + m->chunk_size * m->element_size) = NULL;
    m->element_size = element_size;
    m->chunk_size = chunk_size;
    m->num_elem = 0;

    return 0;
}

// -------------------------------------------------------------------------- //

void print_chunk_pointers(unrolled_linked_list_t l) {
    char ** c = (char **) l.chunks;

    printf("Chunk Pointers: [");

    while (c[l.chunk_size * l.element_size] != NULL) {
        printf("%p -> ", c);
        c = (char **) c[l.chunk_size * l.element_size];
    }

    printf("%p]\n", c);
}

// -------------------------------------------------------------------------- //

