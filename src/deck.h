#pragma once

#include "card.h"

typedef struct deck_t deck_t;

deck_t *create_deck(void);

void deck_shuffle(deck_t *deck, size_t iter);
void deck_push(deck_t *deck, card_t *card);
card_t *deck_pop(deck_t *deck);
const card_t *deck_peek(deck_t *deck);

void destroy_deck(deck_t **deck);
