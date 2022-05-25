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

int counter;
float value;
int newValue;
int previousValue;
float microphoneValue;
int delayTime = 1;
int whileLoopValue = 1;

int redColor = 255;
int greenColor = 255;
int blueColor = 255;

void setup() {
  pinMode(A0, INPUT);
  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(255);
}

void loop() {
      counter = 0;
        while(counter < whileLoopValue){                       
            newValue = getValue();
            lightUpInwards(newValue, previousValue); 
            previousValue = newValue;
            counter++;
            delay(delayTime);        
        }
      
        /*
        counter  = 0;  
        while(counter < whileLoopValue){ 
            microphoneValue = analogRead(A0);
            Serial.print(microphoneValue);  
            value = map(microphoneValue, 0, 100, 0, 73); //was 73
            Serial.print("  Mapped Value: ");
            Serial.println(value);
            
            
            lightUpOutwards(value, previousValue);
            counter++;
            delay(delayTime);
            previousValue = value;
        }*/
}

void lightUpInwards(int value, int previousValue){  
  
 
  if(value > previousValue){
     for(int x = 0; x < value; x++){
        strip.setPixelColor(x, redColor, greenColor, blueColor);
        strip.show();
     }
     for(int x = 119; x > (119-value); x--){
        strip.setPixelColor(x, redColor, greenColor, blueColor);
        strip.show();
     }    
  }else if(value < previousValue){
     for(int x = previousValue; x > value; x--){
        strip.setPixelColor(x, 0, 0, 0);
        strip.show();
     }
     for(int x = 119 - previousValue; x < (119 - value); x++){
        strip.setPixelColor(x, 0, 0, 0); 
        strip.show();
     }    
  }else{
    //do nothing
  }
  
}

void lightUpOutwards(int value, int previousValue){
  if(value > previousValue){
     for(int x = 59; (59 - x) < value; x--){
        strip.setPixelColor(x, redColor, greenColor, blueColor);
     }
     for(int x = 60; x < (60 + value); x++){
        strip.setPixelColor(x, redColor, greenColor, blueColor);
     }    
  }else if(value < previousValue){  
     //NEED TO CHECK FOR BUGS IN THE FOR LOOP CODE BELOW
     for(int x = (59 - value-1); (59 - x) > (59 - previousValue); x--){
        strip.setPixelColor(x, 0, 0, 0);
     }
     for(int x = 60 + previousValue; x > (60 + value); x++){
        strip.setPixelColor(x, 0, 0, 0); 
     }    
  }else{
    //do nothing
  }
  strip.show();
}


int getValue(){
    microphoneValue = analogRead(A0);
    Serial.print("Microphone Value   ");
    Serial.print(microphoneValue);  
    //value = map(microphoneValue, 0, 100, 0, 73); //was 73
    //value = (microphoneValue*microphoneValue)/50;
    value = (microphoneValue*microphoneValue*microphoneValue)/3000;
    Serial.print("  Mapped Value: ");
    Serial.println(value);
    return value;  //old code: return microphoneValue;
}
