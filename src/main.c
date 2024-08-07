#include <stdint.h>
#include <stdlib.h>

#define DEFAULT_PLAYER_AMOUNT 2
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

  game_t *game = create_game(player_amount, deck);

  return EXIT_SUCCESS;
}
