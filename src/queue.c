#include "queue.h"
#include <stdlib.h>

typedef struct queue_t {
  vector_t *vec;
  size_t offset;
} queue_t;

queue_t *create_queue(size_t initial_size, size_t element_size,
                      destructor_f destructor) {
  queue_t *queue = malloc(sizeof(queue_t));
  if (!queue)
    return NULL;

  queue->offset = 0;
  queue->vec = create_vector(initial_size, element_size, destructor);
  if (!queue->vec) {
    destroy_queue(&queue);
    return NULL;
  }

  return queue;
}

void queue_push(queue_t *queue, void *data) {
  if (!queue)
    return;

  ++queue->offset;
  vector_push(queue->vec, data);
}

void *queue_peek(queue_t *queue) {
  if (!queue)
    return NULL;

  size_t i = vector_size(queue->vec) - queue->offset;
  return vector_at(queue->vec, i);
}

void *queue_pop(queue_t *queue) {
  if (!queue)
    return NULL;

  size_t i = vector_size(queue->vec) - queue->offset--;
  vector_pop(queue->vec);
  return vector_at(queue->vec, i);
}

void destroy_queue(queue_t **queue) {
  if (!queue)
    return;

  queue_t *q = *queue;

  if (q) {
    if (q->vec)
      destroy_vector(&q->vec);
    free(q);
  }

  *queue = NULL;
}
