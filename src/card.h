#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef struct card_t {
  uint16_t hp;
  uint16_t attack;
  uint16_t speed;
  struct {
    uint16_t defence;
    uint16_t attack;
  } special;
  bool legendary;
} card_t;
