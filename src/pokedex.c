#include "pokedex.h"
#include "card.h"
#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static size_t hash_pokedex(const char *str) { return str[0] - str[1]; }

typedef struct pokedex_t {
  hashmap_t *hashmap;
} pokedex_t;

pokedex_t *load_pokedex(const char *file_path) {
  pokedex_t *pkd = malloc(sizeof(pokedex_t));
  if (!pkd)
    return NULL;

  pkd->hashmap = create_hashmap(10, 5, sizeof(card_t), free, hash_pokedex);

  char buff[BUFSIZ];
  FILE *f = fopen(file_path, "r");

  while (fgets(buff, BUFSIZ, f) != NULL) {
    card_t *card = malloc(sizeof(card_t));
    if (!card) {
      deload_pokedex(&pkd);
      return NULL;
    }

    char *field = strtok(buff, ",");
    card->name = strdup(field);
    field = strtok(NULL, ",");
    if (!field) {
      deload_pokedex(&pkd);
      return NULL;
    }
    card->types[0] = strdup(field);
    field = strtok(NULL, ",");
    if (!field) {
      deload_pokedex(&pkd);
      return NULL;
    }
    card->types[1] = strdup(field);
    field = strtok(NULL, ",");
    if (!field) {
      deload_pokedex(&pkd);
      return NULL;
    }
    card->hp = atoll(field);
    field = strtok(NULL, ",");
    if (!field) {
      deload_pokedex(&pkd);
      return NULL;
    }
    card->attack = atoll(field);
    field = strtok(NULL, ",");
    if (!field) {
      deload_pokedex(&pkd);
      return NULL;
    }
    card->special.attack = atoll(field);
    field = strtok(NULL, ",");
    if (!field) {
      deload_pokedex(&pkd);
      return NULL;
    }
    card->special.defence = atoll(field);
    field = strtok(NULL, ";");
    if (!field) {
      deload_pokedex(&pkd);
      return NULL;
    }
    card->legendary = atoll(field);

    hashmap_assign(pkd->hashmap, card->name, card);
  }

  fclose(f);
  return pkd;
}

card_t *pokedex_get_by_name(pokedex_t *pkd, const char *str) {
  return hashmap_at(pkd->hashmap, str);
}

void pokedex_begin(pokedex_t *pkd, hashmap_iter_t *it) {
  hashmap_begin(pkd->hashmap, it);
}

void pokedex_end(pokedex_t *pkd, hashmap_iter_t *it) {
  hashmap_end(pkd->hashmap, it);
}

void deload_pokedex(pokedex_t **pokedex) {
  if (!pokedex)
    return;
  pokedex_t *pkd = *pokedex;
  *pokedex = NULL;

  if (pkd->hashmap)
    destroy_hashmap(&pkd->hashmap);
}
