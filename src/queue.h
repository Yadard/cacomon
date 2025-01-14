#pragma once
#include "vector.h"

typedef struct queue_t queue_t;

queue_t *create_queue(size_t initial_size, size_t element_size,
                      destructor_f destructor);

void queue_push(queue_t *queue, void *data);
void *queue_peek(queue_t *queue);
void *queue_pop(queue_t *queue);
void *queue_at(queue_t *queue, size_t index);
void queue_assign(queue_t *queue, size_t index, void *data);
size_t queue_size(queue_t *queue);

void destroy_queue(queue_t **queue);
