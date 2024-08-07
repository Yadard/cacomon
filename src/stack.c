#include "stack.h"
#include <stdlib.h>

typedef struct stack_t {
  vector_t *vec;
} stack_t;

stack_t *create_stack(size_t initial_size, size_t element_size,
                      destructor_f destructor) {
  stack_t *stack = malloc(sizeof(stack_t));
  if (!stack)
    return NULL;

  stack->vec = create_vector(initial_size, element_size, destructor);
  if (!stack->vec) {
    destroy_stack(&stack);
    return NULL;
  }

  return stack;
}

void stack_push(stack_t *stack, void *data) {
  if (!stack)
    return;

  vector_push(stack->vec, data);
}

void *stack_peek(stack_t *stack) {
  if (!stack)
    return NULL;
  return vector_at(stack->vec, vector_size(stack->vec) - 1);
}

void *stack_pop(stack_t *stack) {
  if (!stack)
    return NULL;

  vector_pop(stack->vec);
  return vector_at(stack->vec, vector_size(stack->vec));
}

void destroy_stack(stack_t **stack) {
  if (!stack)
    return;
  stack_t *st = *stack;
  if (st) {
    destroy_vector(&st->vec);
    free(st);
  }

  *stack = NULL;
}
