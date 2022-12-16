#include <Adafruit_NeoPixel.h>
#include <rgb_eye.h>

#define PIN 52
#define NUMPIXELS 101 * 2
#define BRIGHTNESS 255

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Eye eye;

void setup() {
  eye.init(BRIGHTNESS);
}

void loop() {
  /*eye.dead();
  delay(4000);
  eye.blink();
  delay(500);*/

  //delay(2000);
  //eye.small();
  //delay(5000);
  //eye.open();

  eye.friendly();
  delay(5000);
  eye.line();
  delay(200);
}