#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <inttypes.h>

#include <string.h>

#define INIT_SIZE_FACTOR_DYN 1

typedef struct {
	int64_t repeats;
	int64_t iterations;
	int64_t lower, upper;
} thread_args;

typedef struct {
  int64_t size;
  int64_t size_used;
  void* arena_ptr;
  void* head_ptr;
} arena_data;

arena_data* init_arena(int64_t size);
void free_arena(arena_data* arena);
void* alloc_arena(arena_data* arena, int64_t size);

#ifdef ARENA
void* benchmark_thread(void *args) {
	thread_args *t_args = (thread_args*)args;
	for(int64_t r = 0; r < t_args->repeats; ++r) {
		unsigned seed = 0;
		void **allocations = (void**)calloc(t_args->iterations, sizeof(void*));
#ifdef DYNAMIC
    arena_data* arena = init_arena(t_args->iterations * t_args->upper * INIT_SIZE_FACTOR_DYN);
#else  
    arena_data* arena = init_arena(t_args->iterations * t_args->upper);
#endif /* ifdef DYNAMIC */
		for(int64_t i = 0; i < t_args->iterations; ++i) {
			int64_t to_alloc = rand_r(&seed) % (t_args->upper - t_args->lower) + t_args->lower;
			allocations[i] = alloc_arena(arena, to_alloc);
		}
    free_arena(arena);
		free(allocations);
	}
	return NULL;
}
#else
void* benchmark_thread(void *args) {
	thread_args *t_args = (thread_args*)args;
	for(int64_t r = 0; r < t_args->repeats; ++r) {
		unsigned seed = 0;
		void **allocations = (void**)calloc(t_args->iterations, sizeof(void*));
		for(int64_t i = 0; i < t_args->iterations; ++i) {
			int64_t to_alloc = rand_r(&seed) % (t_args->upper - t_args->lower) + t_args->lower;
			allocations[i] = malloc(to_alloc);
		}
		for(int64_t i = 0; i < t_args->iterations; ++i) {
			free(allocations[i]);
		}
		free(allocations);
	}
	return NULL;
}
#endif /* ifdef ARENA */

int main(int argc, char** argv) {
	int64_t num_threads = 100;
	if(argc != 6) {
		printf("USAGE: ./malloctest [num_threads] [num_repeats] [num_iterations] [lower] [upper]\n");
		return -1;
	}
	num_threads = atol(argv[1]);
	thread_args t_args;
	t_args.repeats = atol(argv[2]);
	t_args.iterations = atol(argv[3]);
	t_args.lower = atol(argv[4]);
	t_args.upper = atol(argv[5]);

	pthread_t* threads = (pthread_t*)calloc(num_threads, sizeof(pthread_t));
	
	for(int64_t i = 0; i < num_threads; ++i) {
		pthread_create(&threads[i], NULL, benchmark_thread, &t_args);
	}

	for(int64_t i = 0; i < num_threads; ++i) {
		pthread_join(threads[i], NULL);
	}
  free(threads);
}

#ifndef DYNAMIC

arena_data* init_arena(int64_t size){
  arena_data* arena = malloc(sizeof(arena_data) + size);
  arena->size = size;
  arena->size_used = 0;
  arena->arena_ptr = arena + sizeof(arena_data);
  arena->head_ptr = arena->arena_ptr;
  return arena;
}

void free_arena(arena_data* arena){
  free(arena);
}

// unsafe! can return addresses out of allocated memory
void* alloc_arena(arena_data* arena, int64_t size){
  void* data_ptr = arena->head_ptr;
  arena->head_ptr = (void*) ((int64_t)data_ptr + size);
  arena->size_used += size;
  return data_ptr;
}

#else

arena_data* init_arena(int64_t size){
  arena_data* arena = malloc(sizeof(arena_data));
  arena->size = size;
  arena->size_used = 0;
  arena->arena_ptr = malloc(size);
  arena->head_ptr = arena->arena_ptr;
  return arena;
}

void free_arena(arena_data* arena){
  free(arena->arena_ptr);
  free(arena);
}

void* alloc_arena(arena_data* arena, int64_t size){
  // check if arena is too small
  if (arena->size_used+size > arena->size) {
    void* new_arena_ptr = malloc(arena->size * 2);
    arena->size *= 2;
    memcpy(new_arena_ptr, arena->arena_ptr, arena->size_used);
    free(arena->arena_ptr);
    arena->arena_ptr = new_arena_ptr;
    arena->head_ptr = (void*)((int64_t)(arena->arena_ptr) + arena->size_used);
  }
  void* data_ptr = arena->head_ptr;
  arena->head_ptr = (void*) ((int64_t)data_ptr + size);
  arena->size_used += size;
  return data_ptr;
}

#endif

