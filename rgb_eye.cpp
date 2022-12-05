#include <Arduino.h>
#include "rgb_eye.h"

// Inner dot + first circle
uint8_t Eye::_mask_circle_1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
// second circle
uint8_t Eye::_mask_circle_2[] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};
// Upper part
uint8_t Eye::_mask_top[] = {
    71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
    45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56,
    25, 26, 27, 28, 29, 30, 31, 32, 33,
    11, 12, 13, 14, 15, 16,
    3, 4, 5
};
// Middle line
uint8_t Eye::_mask_middle_line[] = {86, 57, 34, 17, 6, 1, 2, 10, 24, 44, 70};
uint8_t Eye::_mask_middle_line_horizontal[] = {78, 29, 4, 1, 8, 39, 94};
uint8_t Eye::_mask_friendly_r[] = {
    87, 88, 89, 101,
    58, 59, 69,
    35, 36,
    18, 13,
    7
};
// "Dead" mask
uint8_t Eye::_mask_x[] = {
    20, 21, 38, 39, 40, 63, 64, 93, 94, 95,
    23, 10, 11, 43, 24, 25, 69, 44, 45, 101, 70, 71,
    13, 14, 28, 29, 30, 50, 51, 77, 78, 79,
    16, 17, 18, 33, 34, 35, 56, 57, 58, 85, 86, 87
};

Eye::Eye() {
    this->_state = STATE_OFF;
}

void Eye::init(uint8_t brightness) {
  pixels.begin();
  pixels.setBrightness(brightness);
  pixels.clear();
  pixels.show();
}

void Eye::small() {
    pixels.clear();
    this->_selectMask(this->_mask_circle_1, sizeof(this->_mask_circle_1));
    pixels.show();
}

void Eye::close() {
    uint8_t segments[3][6] = {
        {78, 29, 4, 8, 39, 94},
        {29, 4, 8, 39},
        {4, 8}
    };
    for (uint8_t i = 0; i < 3; i++) {
        pixels.clear();
        this->_selectMask(this->_mask_middle_line, sizeof(_mask_middle_line));
        this->_selectMask(segments[i], sizeof(segments[i]));
        pixels.show();
        delay(40);
    }
    this->line();
}

void Eye::open() {
    //pixels.fill((uint32_t)(this->_r >> 16 || this->_g >> 8 || this->_b));
    for (uint8_t i = 0; i < pixels.numPixels(); i++) pixels.setPixelColor(i, pixels.Color(this->_r, this->_g, this->_b));
    pixels.show();
}

void Eye::openToDead() {
    uint8_t segments[3][6] = {
        {78, 29, 4, 8, 39, 94},
        {29, 4, 8, 39},
        {4, 8}
    };
    for (uint8_t i = 3; i > 0; i--) {
        pixels.clear();
        this->_selectMask(this->_mask_middle_line, sizeof(_mask_middle_line));
        this->_selectMask(segments[i-1], sizeof(segments[i-1]));
        pixels.show();
        delay(40);
    }
    this->dead();
}

void Eye::dead() {
    pixels.clear();
    this->_selectMask(this->_mask_middle_line, sizeof(this->_mask_middle_line));
    this->_selectMask(this->_mask_middle_line_horizontal, sizeof(this->_mask_middle_line_horizontal));
    pixels.show();
}

void Eye::friendly() {
    pixels.clear();
    this->_selectMask(this->_mask_top, sizeof(_mask_top));
    this->_selectMask(this->_mask_middle_line, sizeof(_mask_middle_line));
    this->_selectMask(this->_mask_friendly_r, sizeof(_mask_friendly_r));
    pixels.show();
}

void Eye::line() {
    pixels.clear();
    //this->_selectMask(this->_mask_top, sizeof(_mask_top));
    this->_selectMask(this->_mask_middle_line, sizeof(this->_mask_middle_line));
    //this->_selectMask(this->_mask_friendly_r, sizeof(_mask_friendly_r));
    pixels.show();
}

void Eye::blink() {
    this->close();
    delay(50);
    this->openToDead();
}

void Eye::_selectMask(uint8_t mask[], uint8_t size) {
    uint8_t length = size/sizeof(uint8_t);
    // Eye 0
    for (uint8_t i = 0; i < length; i++) pixels.setPixelColor(mask[i]-1, pixels.Color(this->_r, this->_g, this->_b));
    // Eye 1
    for (uint8_t i = 0; i < length; i++) pixels.setPixelColor(mask[i]+100, pixels.Color(this->_r, this->_g, this->_b));
}