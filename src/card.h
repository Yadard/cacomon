#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define TYPES_AMOUNT 2

typedef struct card_t {
  char *name;
  char *types[TYPES_AMOUNT];
  uint16_t hp;
  uint16_t attack;
  uint16_t defence;
  uint16_t speed;
  struct {
    uint16_t defence;
    uint16_t attack;
  } special;
  bool legendary;
} card_t;

void destroy_card(card_t **card);
