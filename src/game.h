#pragma once

#include "deck.h"
#include "pokedex.h"
#include <stdint.h>

typedef struct game_t game_t;

game_t *create_game(const char *db_path, uint8_t player_amount,
                    uint8_t hand_size, size_t iter);

bool game_runing(game_t *game);
void game_loop(game_t *game);

void destroy_game(game_t **game);
