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
Adafruit_NeoPixel strip = Adafruit_NeoPixel(120, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

int redLeft = 255;
int greenLeft = 00;
int blueLeft = 0;

int redRight = 0;
int greenRight = 0;
int blueRight = 255;

int delayBetweenFlashes = 20;
int delayTime = 130;

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(255);
}

void loop() {
  
  for(int x = 0; x < 5; x++){
      flashLeft(7);
      flashRight(7);
  }
  doubleLightMovement(5);  
}

void flashLeft(int repetition){
  setAllOff();
  for(int z = 0; z < repetition; z++){
    for(int x = 0; x < 60; x++){
    strip.setPixelColor(x, redLeft, greenLeft, blueLeft);
    }
    strip.show();
    delay(delayBetweenFlashes);
    for(int x = 0; x < 60; x++){
      strip.setPixelColor(x, 0, 0, 0);
    }
    strip.show();
    delay(delayBetweenFlashes);
  }
}

void flashRight(int repetition){
  setAllOff();
  for(int z = 0; z < repetition; z++){
    for(int x = 60; x < 120; x++){
    strip.setPixelColor(x, redRight, greenRight, blueRight);
    }
    strip.show();
    delay(delayBetweenFlashes);
    for(int x = 60; x < 120; x++){
      strip.setPixelColor(x, 0, 0, 0);
    }
    strip.show();
    delay(delayBetweenFlashes);
  }
}

void doubleLightMovement(int repeatNumber){       
  for(int y = 0; y < repeatNumber; y++){
      for(int x = 0; x < 60; x++){
        strip.setPixelColor(x, redLeft, greenLeft, blueLeft);
        strip.setPixelColor(x+60, 0, 0, 0);
      }
      strip.show();
      delay(delayTime);
      for(int x = 0; x < 60; x++){
        strip.setPixelColor(x, 0, 0, 0);
        strip.setPixelColor(x+60, redRight, greenRight, blueRight);
      }
      strip.show();
      delay(delayTime);
  }
}


void setAllOff(){
  for(int x = 0; x < 120; x++){
    strip.setPixelColor(x, 0, 0, 0);  
  }
  strip.show();
}
