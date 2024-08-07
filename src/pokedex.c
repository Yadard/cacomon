#pragma once

#include "pokedex.h"
typedef struct pokedex_t {

} pokedex_t;

pokedex_t *load_pokedex(const char *file_path);

card_t *pokedex_get_by_id(size_t id);
card_t *pokedex_get_by_name(const char *str);

void deload_pokedex(pokedex_t **pokedex);
