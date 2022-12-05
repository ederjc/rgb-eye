#include <Adafruit_NeoPixel.h>
#include <rgb_eye.h>
//#include "C:\Users\ederjuli\Documents\Projects\2210-XXL-Chatbot\arduino_lib\include\rgb_eye.h"

#define PIN 52
#define NUMPIXELS 101*2
#define BRIGHTNESS 255

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Eye eye;

void setup() {
  // put your setup code here, to run once:
eye.init(BRIGHTNESS);
}

void loop() {
/*eye.dead();
delay(4000);
eye.blink();
delay(500);*/
eye.friendly();
delay(5000);
//eye.small();
//delay(5000);
eye.open();
delay(4000);
eye.line();
delay(70);
}
