#include "square.h"
#include <stdint.h>
#include <stdlib.h>

typedef struct {
  uint8_t index : 7,
      vertical : 1; // 0 for horizontal, 1 for vertical
} cursor_t;

void toggle_cursor(cursor_t *, bool);
void cursor_move(cursor_t *, uint8_t);
int8_t get_cursor_index(cursor_t *);