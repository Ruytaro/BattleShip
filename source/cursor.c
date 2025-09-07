#include "cursor.h"

void toggle_cursor(cursor_t* cursor, bool active) {
    if (cursor == NULL) {
        return;
    }
    cursor->vertical = active ? 1 : 0;
}

void cursor_move(cursor_t* cursor,uint8_t index) {
    if (cursor == NULL) {
        return;
    }
    cursor->index = (index + cursor->index) % 100;
}

int8_t cursor_get_index(cursor_t* cursor) {
    if (cursor == NULL) {
        return -1;
    }
    return cursor->index;
}