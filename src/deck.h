#pragma once

#include "card.h"

typedef struct deck_t deck_t;

deck_t *create_deck(void);

void deck_push(card_t card);
card_t *deck_pop(void);
const card_t *deck_peek(void);

void destroy_deck(deck_t **deck);
