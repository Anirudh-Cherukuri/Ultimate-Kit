/*
 * A pixel bouncing back and forth on the strip
 */

//Include the LEDStrip library to use the commands
#include "LEDStrip.h"

const byte numPixels = 15; //number of pixels on a strip

/*
 * Make the LED strip object LEDStrip strip
 *  = LEDStrip(numPixels, dataPin (DI), clockPin(CI));
 */
LEDStrip strip = LEDStrip(numPixels, 13, 12);

int pixel = 0; //Position of the pixel on the strip

//Direction will be 1 or -1
int Direction = 1; //Direction of travel of the pixel

void setup() {

}

void loop() {

  strip.setPixel(pixel,-1); //Clear the old pixel (-1 is off)

  pixel = pixel + Direction; //Move the pixel

  //Color range is 0 - 300, 200 is green
  strip.setPixel(pixel,200); //Write the pixel

  strip.draw(); //Draw what we wrote to the strip
  delay(500);
  
  if (pixel % 2 != 0) {
      strip.setPixel(pixel,-1);
      strip.draw();
      delay(500);
      
      strip.setPixel(pixel,200);
      strip.draw();
      delay(500);
  }

  //If at either end of the strip
  if ((pixel == 0)||(pixel == numPixels-1)){
      Direction = -1*Direction; //Change direction
  }

  delay(500); //Timing delay controls pixel speed
}

//Change the if statement to make the pixel bounce between different
//  limits

// (c) 2017 Let's Start Coding. License: www.letsstartcoding.com/bsdlicense
