#include <stdint.h>
#include <nds.h>

#ifndef INPUT_H
#define INPUT_H

typedef struct
{
    uint16_t keys;
    uint8_t touch_x;
    uint8_t touch_y;
}input_t;

void input_handle(input_t*);

#endif