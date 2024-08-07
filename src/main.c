#include "deck.h"
#include "hashmap.h"
#include <stdint.h>
#include <stdlib.h>

#define DEFAULT_PLAYER_AMOUNT 2
#define ITERATIONS_SHUFFLE 50
#define DEFAULT_HAND_SIZE 5

#include "game.h"
#include "pokedex.h"

int main(int argc, const char **argv) {
  uint8_t player_amount = DEFAULT_PLAYER_AMOUNT;
  uint8_t hand_size = DEFAULT_HAND_SIZE;

  if (argc > 1) {
    hand_size = atoi(argv[1]);
    if (hand_size == 0 && argv[1][0] != '0')
      hand_size = DEFAULT_HAND_SIZE;
  }

  pokedex_t *pokedex = load_pokedex("./pokemon.csv");
  deck_t *deck = create_deck();

  hashmap_iter_t *it = create_hashmap_iter();
  hashmap_iter_t *end = create_hashmap_iter();
  pokedex_begin(pokedex, it);
  pokedex_end(pokedex, end);
  for (; !hashmap_iter_equal(it, end); hashmap_iter_next(it)) {
    card_t *card = hashmap_iter_get(it);
    deck_push(deck, card);
  }

  deck_shuffle(deck, ITERATIONS_SHUFFLE);

  game_t *game = create_game(player_amount, hand_size, pokedex, deck);
  while (game_runing(game))
    game_loop(game);

  destroy_game(&game);

  return EXIT_SUCCESS;
}
