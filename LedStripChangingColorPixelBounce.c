
/*
 * Bouncing a pixel up and down the LED Strip, changing color along the way
 */

#include "LEDStrip.h"

const byte numPixels = 15; //number of pixels on a strip

int color = 200; //the initial color value (ranges from 0-300)

/*
 * Make the LED strip object LEDStrip strip
 *  = LEDStrip(numPixels, dataPin, clockPin);
 */
LEDStrip strip = LEDStrip(numPixels, 13, 12);

int pixel = 0; //Position of the pixel on the strip

int Direction = 1; //Direction of travel of the pixel

void setup() {

}

void loop() {

  strip.setPixel(pixel,-1); //Clear the old pixel
  
  pixel = pixel + Direction; //Move the pixel

  strip.setPixel(pixel,color); //Set the new position and color

  strip.draw(); //Draw what you set up with .setPixel


  //If at either end of the strip
  if ((pixel == 0)||(pixel == numPixels)){
    Direction = -1*Direction; //Direction will be 1 or -1
    //Change color by 77, %300 to keep within 0-299 range
    color = (color + 77)%300;
  }

  delay(100); //controls the speed at which the pixel moves
}

//Change the if statement to make the pixel bounce between different
//  limits

// (c) 2017 Let's Start Coding. License: www.letsstartcoding.com/bsdlicense

