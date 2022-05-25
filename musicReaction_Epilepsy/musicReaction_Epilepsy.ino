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

//variables that are important for the code pls do not touch
float value;
float value2; //can remove
float microphoneValue;
int counter = 0;


//variables that can be changed to the users desire
int whileLoopValue = 1;
int colorIncrease = 15; //MUST BE A MULTIPLE OF 255
int redColor = 255;
int greenColor = 0;
int blueColor = 0;
int delayTime = 1;



void setup() {
  pinMode(A0, INPUT);
  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(255);
}

void loop() { 
  counter  = 0;
  while(counter < whileLoopValue){
      lightUpInwards(getValue()); 
      counter++;
      delay(delayTime);
  }
  
  counter  = 0;  
  while(counter < whileLoopValue){ 
      lightUpOutwards(getValue());
      counter++;
      delay(delayTime);
  } 
}

void lightUpInwards(int value){
  setAllOff();
  setColors();
  for(int x = 0; x < value; x++){
    strip.setPixelColor(x, redColor, greenColor, blueColor);
  }
  for(int x = 119; x > (119-value); x--){
    strip.setPixelColor(x, redColor, greenColor, blueColor);
  }
  strip.show();
}


void lightUpOutwards(int value){
  setAllOff();
  setColors();
  //setBlueColor();
  //setGreenColor():
  for(int x = 59; (59-x) < value; x--){
    strip.setPixelColor(x, redColor, greenColor, blueColor);
  }
  for(int x = 60; x < (60+value); x++){
    strip.setPixelColor(x, redColor, greenColor, blueColor);
  }
  strip.show();
}


int getValue(){
    microphoneValue = analogRead(A0);
    //value2 = microphoneValue;
    Serial.print(microphoneValue);  
    //value = microphoneValue/1.7; // linear
    value = (microphoneValue*microphoneValue)*0.1; //normally 0.0144 for playing music from phone speaker QUADRATIC
    //value = (microphoneValue*microphoneValue*microphoneValue)/4000; //CUBIC
    value = constrain(value, 0, 30);
    Serial.print("  Mapped Value: ");
    Serial.println(value);
    return value;  //old code: return microphoneValue;
}


void setColors(){  
  if(redColor == 255 && greenColor == 0 && blueColor != 255){
    blueColor += colorIncrease;
  }else if(blueColor == 255 && greenColor == 0 && redColor != 0){
    redColor -= colorIncrease;
  }else if(redColor == 0 && blueColor == 255 && greenColor != 255){
    greenColor += colorIncrease;
  }else if(greenColor == 255 && redColor == 0 && blueColor != 0){
    blueColor -= colorIncrease;
  }else if(blueColor == 0 && greenColor == 255 && redColor != 255){
    redColor += colorIncrease;
  }else if(redColor == 255 && blueColor == 0 && greenColor != 0){
    greenColor -= colorIncrease;
  }  
}

void setAllOff(){
  for(int x = 0; x < 120; x++){
    strip.setPixelColor(x, 0, 0, 0);  
  }
  strip.show();
}
