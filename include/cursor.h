#include "square.h"

typedef struct {
    uint8_t index:7;
    uint8_t active:1; // 0 for inactive, 1 for active
} cursor_t;

cursor_t* init_cursor();
void enable_cursor(cursor_t*,bool);
void cursor_move(cursor_t*,uint8_t);
int8_t cursor_get_index(cursor_t*);