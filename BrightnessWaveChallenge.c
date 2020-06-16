
/*
 * Make the LED strip fade up and down along its length
 */

//Include the LEDStrip library to use the commands
#include "LEDStrip.h"

const byte numPixels = 15;
/*
 * Make the LED strip object LEDStrip strip
 *  = LEDStrip(numPixels, dataPin (DI), clockPin (CI));
 */
LEDStrip strip = LEDStrip(numPixels, 13, 12);

//A list of the brightnesses, values picked for aesthetics
int brightnesses[] = {2,9,16,23,31,37,44,51,44,37,31,23,16,9,2};

int pixel = 7; //Initial pixel value is 7

void setup() {
}

void loop() {

  //Loop for all 15 pixels
  for (int i = 0;i<15;i++){
    //Set the ith pixel past the head to 200 (green) at the
    //  brightness from the array above. 
    strip.setPixel((pixel + i)%numPixels,100,brightnesses[i]);
    //(pixel + i)%15 wraps pixel+i around the strip in a loop
  }
  
  strip.draw(); //Draw what was written to the strip

  pixel++; //Increase pixel 

  delay(200); //A delay for visibility

}

//Put the brightness[i] element in set pixel into the color spot 
//  (replace 200) and set the brightness instead to 100.

// (c) 2017 Let's Start Coding. License: www.letsstartcoding.com/bsdlicense

