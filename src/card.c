#include "card.h"

void destroy_card(card_t **card) {
  if (!card)
    return;
  card_t *c = *card;
  *card = NULL;

  if (c->name)
    free(c->name);
  for (size_t i = 0; i < TYPES_AMOUNT; i++) {
    if (c->types[i])
      free(c->types[i]);
  }

  free(c);
}
