#include "input.h"

void input_handle(input_t* input) {
    scanKeys();
    input->keys = keysDown();

    if (input->keys & KEY_TOUCH) {
        touchPosition touch;
        touchRead(&touch);
        input->touch_x = touch.px;
        input->touch_y = touch.py;
    }
}