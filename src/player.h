#pragma once

#include "card.h"

typedef struct player_t player_t;

player_t *create_player(void);

void player_draw(card_t *card);

void destroy_player(player_t **player);
