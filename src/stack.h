#pragma once
#include "vector.h"

typedef struct stack_t stack_t;

stack_t *create_stack(size_t initial_size, size_t element_size,
                      destructor_f destructor);

void stack_push(stack_t *stack, void *data);
void *stack_peek(stack_t *stack);
void *stack_pop(stack_t *stack);

void destroy_stack(stack_t **stack);
