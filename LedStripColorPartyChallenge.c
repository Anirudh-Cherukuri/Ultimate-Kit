
/*
 * Display random ever changing colors on the LED strip, button 
 * changes the mode between full strip and individual pixels
 */

//Include the LEDStrip library to use the commands
#include "LEDStrip.h"

const byte numPixels = 15; //number of pixels on a strip

int color = 0; //color values on the strip range from -1 to 300.

//0 is individual pixel mode, 1 is whole strip mode
int stripMode = 0; //Which display mode the strip is in

int pixel = 7; //Current pixel if in individual pixel color mode

/*
 * Make the LED strip object LEDStrip strip
 *  = LEDStrip(numPixels, dataPin (DI), clockPin(CI));
 */
LEDStrip strip = LEDStrip(numPixels, 13, 12);

void setup() {

  //Button
  pinMode(A5,INPUT_PULLUP);
  
}

void loop() {

  //If the button is pressed
  if (digitalRead(A5) == LOW){
    delay(100); //Delay 10 ms to debounce
    //Wait until the button is released to register a press
    while( digitalRead(A5) == LOW){
      delay(1); //Wait while button is held
    }
    stripMode = 1 - stripMode; //Change the mode
  }

  //If in single pixel mode
  if (stripMode == 0){
    //Change the current pixel to a random location
    pixel = random(0,numPixels);

    //Change the color by 50x a random amount
    //Color values will be 0-250 and be divisible by fifty
    color = 50*random(0,6);

    //Write the new pixel to the new color
    strip.setPixel(pixel,color);
  }

  //In whole strip mode
  if (stripMode == 1){

    //Change the color by 50x a random amount
    //Color values will be 0-250 and be divisible by fifty
    
    // Changed 6 to 10
    color = 50*random(0,10);
    
    //Write the strip to the new color
    strip.setPixel(strip.ALL,color);
    
    delay(100); //Visibility delay
  }

  strip.draw(); //Draw what was written to the strip
}

//Change the limits of the random function to change the color
//  range you draw

// (c) 2017 Let's Start Coding. License: www.letsstartcoding.com/bsdlicense

