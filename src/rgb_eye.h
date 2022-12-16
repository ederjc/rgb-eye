#ifndef Eye_h
#define Eye_h

#include <Adafruit_NeoPixel.h>

#define STATE_OFF 0
#define STATE_ON  1

class Eye {
  public:
    Eye             ();
    void init       (uint8_t brightness);
    void dead       ();
    void friendly   ();
    void close      ();
    void open       ();
    void openToDead ();
    void line       ();
    void blink      ();
    void small      ();

    static uint8_t _mask_circle_1[]; // Inner dot + first circle
    static uint8_t _mask_circle_2[]; // Second circle
    static uint8_t _mask_top[]; // Upper part
    static uint8_t _mask_middle_line[]; // Middle line
    static uint8_t _mask_middle_line_horizontal[]; // Middle line horizontal
    static uint8_t _mask_friendly_r[];
    static uint8_t _mask_x[]; // "Dead" mask

  private:
    uint8_t _r = 0;
    uint8_t _g = 135;
    uint8_t _b = 255;
    uint8_t _state = STATE_OFF;

    //void _animate(uint8_t animationIndex);
    void _selectMask(uint8_t mask[], uint8_t size);
};

extern Adafruit_NeoPixel pixels;

#endif