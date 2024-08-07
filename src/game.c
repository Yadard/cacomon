#include "game.h"
#include "deck.h"
#include "pokedex.h"
#include <stddef.h>
#include <stdlib.h>

typedef struct game_t {
  pokedex_t *pokedex;
  deck_t *deck;
} game_t;

static void load_deck(game_t *game, size_t iter) {
  hashmap_iter_t *it = create_hashmap_iter();
  hashmap_iter_t *end = create_hashmap_iter();
  pokedex_begin(game->pokedex, it);
  pokedex_end(game->pokedex, end);
  for (; !hashmap_iter_equal(it, end); hashmap_iter_next(it)) {
    card_t *card = hashmap_iter_get(it);
    deck_push(game->deck, card);
  }

  deck_shuffle(game->deck, iter);
}

game_t *create_game(const char *db_path, uint8_t player_amount,
                    uint8_t hand_size, size_t iter) {
  game_t *game = malloc(sizeof(game_t));
  if (!game)
    return NULL;

  game->pokedex = load_pokedex(db_path);
  if (!game->pokedex) {
    destroy_game(&game);
    return NULL;
  }
  game->deck = create_deck();
  if (!game->deck) {
    destroy_game(&game);
    return NULL;
  }

  return game;
}

bool game_running(game_t *game);

void game_loop(game_t *game);

void destroy_game(game_t **game) {
  if (!game)
    return;

  game_t *g = *game;
  *game = NULL;

  if (g) {
    if (g->deck)
      destroy_deck(&g->deck);
    if (g->pokedex)
      deload_pokedex(&g->pokedex);
    free(g);
  }
}
