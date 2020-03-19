
/*
 * Scrolling color changing bar on the LED strip
 */

//Include the LEDStrip library to use the commands
#include "LEDStrip.h"

const byte numPixels = 15; //number of pixels on a strip

int color = 100; //Color of the illuminated pixel. Colors range 0-300

int pixel = 7; //Initial pixel location

int barLength = 7; //Number of pixels in the bar

/*
 * Make the LED strip object LEDStrip strip
 *  = LEDStrip(numPixels, dataPin (DI), clockPin(CI));
 */
LEDStrip strip = LEDStrip(numPixels, 13, 12);



void setup() {

}

void loop() {

  //Wipe the strip blank
  strip.clear();

  //Draw 'barLength' many consecutive pixels, starting at 'pixel'
  for (int i = 0; i < barLength; i++){
    //(pixel+i)%(numPixels+barLength) moves bar off strip before color change
    strip.setPixel((pixel+i)%(numPixels+barLength),color);
  }

  pixel++; //Increase the pixel location

  //When the 'tail' pixel goes off strip
  if (pixel == numPixels){
    color = (color + 50)%300; //Change the color of the bar
  }

  //When the 'tail' pixel hits the end of the off-strip space
  if (pixel == numPixels+barLength){
    pixel = 0; //Reset head position to 0
  }

  strip.draw(); //Display what we wrote to the strip

  delay(200); //Timing delay 200 ms between movements
}

//Change barLength and the delay to modfiy the effect

// (c) 2017 Let's Start Coding. License: www.letsstartcoding.com/bsdlicense
