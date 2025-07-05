#include "cursor.h"

cursor_t* init_cursor() {
    cursor_t* cursor = (cursor_t*)calloc(1,sizeof(cursor_t));
    if (cursor == NULL) {
        exit(EXIT_FAILURE);
    }
    return cursor;
}

void enable_cursor(cursor_t* cursor, bool active) {
    if (cursor == NULL) {
        return;
    }
    cursor->active = active ? 1 : 0;
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