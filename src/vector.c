#include "vector.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct vector_t {
  struct {
    uint8_t *mem;
    size_t size;
  } data;
  size_t size;
  size_t used;
  size_t init_size;

  destructor_f dest;
} vector_t;

vector_t *create_vector(size_t initial_size, size_t element_size,
                        destructor_f destructor) {
  vector_t *vec = malloc(sizeof(vector_t));
  if (!vec)
    return NULL;

  vec->used = 0;
  vec->size = initial_size;
  vec->init_size = initial_size;
  vec->dest = destructor;

  vec->data.size = element_size;
  vec->data.mem = malloc(element_size * initial_size);
  if (!vec->data.mem) {
    destroy_vector(&vec);
    return NULL;
  }

  return vec;
}

void vector_pop(vector_t *vector) { --vector->used; }

void vector_push(vector_t *vector, void *data) {
  if (!vector)
    return;

  if (vector->used == vector->size) {
    vector->size += 2 * vector->init_size;
    vector->data.mem =
        realloc(vector->data.mem, vector->data.size * vector->size);
  }

  memcpy(vector->data.mem + vector->used * vector->data.size, data,
         vector->data.size);
}

void *vector_at(vector_t *vector, size_t index) {
  if (!vector || index >= vector->used)
    return NULL;

  return vector->data.mem + index * vector->data.size;
}

void vector_assign(vector_t *vector, size_t index, void *data) {
  if (!vector || index >= vector->used)
    return;

  memcpy(vector->data.mem + index * vector->data.size, data, vector->data.size);
}

size_t vector_size(vector_t *vector) { return vector->used; }

void destroy_vector(vector_t **vector) {
  if (!vector)
    return;

  vector_t *vec = *vector;

  if (vec) {
    if (vec->dest) {
      for (size_t i = 0; i < vec->used; i++)
        vec->dest(vector_at(vec, i));
    }
    if (vec->data.mem)
      free(vec->data.mem);
    free(vec);
  }

  *vector = NULL;
}
