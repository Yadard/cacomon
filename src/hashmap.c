#include "hashmap.h"
#include "destructor.h"
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct hashmap_t {
  vector_t **vectors;
  size_t size;
  hash_func hash;
  destructor_f elem_dest;
} hashmap_t;

typedef struct hashmap_entry_t {
  void *data;
  char *key;
  destructor_f dest;
} hashmap_entry_t;

typedef size_t (*hash_func)(const char *str);

typedef struct hashmap_iter_t {
  size_t bucket_index;
  size_t elem_index;
  hashmap_t *hashmap;
} hashmap_iter_t;

hashmap_entry_t *create_hashmap_entry(void *data, const char *key,
                                      destructor_f dest) {
  hashmap_entry_t *he = malloc(sizeof(hashmap_entry_t));
  if (!he)
    return NULL;

  he->key = strdup(key);
  he->data = data;
  he->dest = dest;

  return he;
}

void destroy_hashmap_entry(hashmap_entry_t **entry) {
  if (!entry)
    return;
  hashmap_entry_t *e = *entry;
  *entry = NULL;

  if (e->key)
    free(e->key);
  if (e->data)
    if (e->dest)
      e->dest(e->data);
}

hashmap_t *create_hashmap(size_t buckets_amount, size_t bucket_init_size,
                          size_t element_size, destructor_f element_destructor,
                          hash_func hash_f) {
  hashmap_t *hashmap = malloc(sizeof(hashmap_t));
  if (!hashmap)
    return NULL;

  hashmap->size = buckets_amount;
  hashmap->elem_dest = element_destructor;
  hashmap->hash = hash_f;
  if (!hash_f) {
    destroy_hashmap(&hashmap);
    return NULL;
  }

  for (size_t i = 0; i < buckets_amount; i++) {
    hashmap->vectors[i] =
        create_vector(bucket_init_size, sizeof(hashmap_entry_t *),
                      (destructor_f)destroy_hashmap_entry);
    if (!hashmap->vectors[i]) {
      destroy_hashmap(&hashmap);
      return NULL;
    }
  }

  return hashmap;
}

void *hashmap_at(hashmap_t *hashmap, const char *str) {
  size_t bi = hashmap->hash(str) % hashmap->size;

  for (size_t i = 0; i < vector_size(hashmap->vectors[bi]); i++) {
    hashmap_entry_t *e = vector_at(hashmap->vectors[bi], i);
    if (strcmp(str, e->key))
      return e;
  }

  return NULL;
}

void hashmap_assign(hashmap_t *hashmap, const char *str, void *data) {
  size_t bi = hashmap->hash(str) % hashmap->size;

  for (size_t i = 0; i < vector_size(hashmap->vectors[bi]); i++) {
    hashmap_entry_t *e = vector_at(hashmap->vectors[bi], i);
    if (strcmp(str, e->key)) {
      vector_assign(hashmap->vectors[bi], i,
                    create_hashmap_entry(data, str, hashmap->elem_dest));
      return;
    }
  }
  vector_push(hashmap->vectors[bi],
              create_hashmap_entry(data, str, hashmap->elem_dest));
}

hashmap_iter_t *create_hashmap_iter(void) {
  hashmap_iter_t *it = malloc(sizeof(hashmap_iter_t));
  if (!it)
    return NULL;

  it->elem_index = 0;
  it->bucket_index = 0;
  it->hashmap = NULL;

  return it;
}

void hashmap_begin(hashmap_t *hashmap, hashmap_iter_t *it) {
  it->bucket_index = 0;
  it->elem_index = 0;
  it->hashmap = hashmap;
}

void *hashmap_iter_get(hashmap_iter_t *it) {
  return vector_at(it->hashmap->vectors[it->bucket_index], it->elem_index);
}

void hashmap_iter_next(hashmap_iter_t *it) {
  if (vector_size(it->hashmap->vectors[it->bucket_index]) == it->elem_index)
    ++it->bucket_index;
  else
    ++it->elem_index;
}

bool hashmap_iter_equal(hashmap_iter_t *a, hashmap_iter_t *b) {
  return a->hashmap == b->hashmap && a->bucket_index == b->bucket_index &&
         a->elem_index == b->elem_index;
}

void hashmap_end(hashmap_t *hashmap, hashmap_iter_t *it) {
  it->bucket_index = hashmap->size;
  it->elem_index = vector_size(it->hashmap->vectors[it->bucket_index]);
  it->hashmap = hashmap;
}
void destroy_hashmap_iter(hashmap_iter_t **it) {
  if (!it)
    return;
  hashmap_iter_t *i = *it;
  *it = NULL;

  if (i)
    free(i);
}

void destroy_hashmap(hashmap_t **hashmap) {
  if (!hashmap)
    return;
  hashmap_t *h = *hashmap;
  *hashmap = NULL;

  if (h) {
    for (size_t i = 0; i < h->size; i++)
      destroy_vector(h->vectors + i);
    free(h);
  }
}
