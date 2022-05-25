#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(144, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(10 ); //normally 5 for filming
}

void loop() {
  // put your main code here, to run repeatedly:
  
  strip.setPixelColor(1, 255, 0, 0);
  strip.setPixelColor(25, 255, 0, 0);
  strip.setPixelColor(29, 255, 0, 0);
  strip.setPixelColor(30, 255, 0, 0);
  strip.setPixelColor(31, 255, 0, 0);
  strip.setPixelColor(36, 255, 0, 0);
  strip.setPixelColor(50, 255, 0, 0);
  strip.setPixelColor(65, 255, 0, 0);
  strip.show();
  
}
