#include "deck.h"
#include "card.h"
#include "destructor.h"
#include "queue.h"

#include <stdlib.h>

typedef struct deck_t {
  queue_t *c;
} deck_t;

deck_t *create_deck(void) {
  deck_t *d = malloc(sizeof(deck_t));
  if (!d)
    return NULL;

  d->c = create_queue(40, sizeof(card_t *), (destructor_f)destroy_card);
  if (!d->c) {
    destroy_deck(&d);
    return NULL;
  }

  return d;
}

void deck_shuffle(deck_t *deck, size_t iter) {
  size_t orig = 0, dest = 0;

  for (size_t i = 0; i < iter; i++) {
    do {
      orig = rand() % queue_size(deck->c);
      dest = rand() % queue_size(deck->c);

      card_t *card = queue_at(deck->c, orig);
      queue_assign(deck->c, dest, card);
    } while (orig == dest);
  }
}

void deck_push(deck_t *deck, card_t *card) { queue_push(deck->c, card); }
card_t *deck_pop(deck_t *deck) { return queue_pop(deck->c); }
const card_t *deck_peek(deck_t *deck) { return queue_peek(deck->c); }

void destroy_deck(deck_t **deck) {
  if (!deck)
    return;
  deck_t *d = *deck;
  *deck = NULL;

  if (d) {
    if (d->c)
      destroy_queue(&d->c);
    free(d);
  }
}
