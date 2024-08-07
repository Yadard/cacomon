#pragma once

#include "destructor.h"
typedef struct vector_t vector_t;

vector_t *create_vector(size_t initial_size, size_t element_size,
                        destructor_f destructor);

void vector_push(vector_t *vector, void *data);
void vector_pop(vector_t *vector);
void *vector_at(vector_t *vectdor, size_t index);
void vector_assign(vector_t *vector, size_t index, void *data);

size_t vector_size(vector_t *vector);

void destroy_vector(vector_t **vector);
