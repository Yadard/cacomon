#pragma once

#include "destructor.h"
#include <stdbool.h>
#include <stddef.h>

typedef struct hashmap_t hashmap_t;
typedef struct hashmap_entry_t hashmap_entry_t;
typedef size_t (*hash_func)(const char *str);

typedef struct hashmap_iter_t hashmap_iter_t;

hashmap_t *create_hashmap(size_t buckets_amount, size_t bucket_init_size,
                          size_t element_size, destructor_f element_destructor,
                          hash_func hash_f);

void *hashmap_at(hashmap_t *hashmap, const char *str);
void hashmap_assign(hashmap_t *hashmap, const char *str, void *data);

hashmap_iter_t *create_hashmap_iter(void);
void hashmap_begin(hashmap_t *hashmap, hashmap_iter_t *it);
void *hashmap_iter_get(hashmap_iter_t *it);
void hashmap_iter_next(hashmap_iter_t *it);
bool hashmap_iter_equal(hashmap_iter_t *a, hashmap_iter_t *b);
void hashmap_end(hashmap_t *hashmap, hashmap_iter_t *it);
void destroy_hashmap_iter(hashmap_iter_t **it);

void destroy_hashmap(hashmap_t **hashmap);
