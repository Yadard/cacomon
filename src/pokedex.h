#pragma once

#include "card.h"
#include "hashmap.h"
typedef struct pokedex_t pokedex_t;

pokedex_t *load_pokedex(const char *file_path);

card_t *pokedex_get_by_name(pokedex_t *pkd, const char *str);

void pokedex_begin(pokedex_t *pkd, hashmap_iter_t *it);
void pokedex_end(pokedex_t *pkd, hashmap_iter_t *it);

void deload_pokedex(pokedex_t **pokedex);
