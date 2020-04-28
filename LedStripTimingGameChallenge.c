
/*
 * Reaction game-  press the button when the moving pixel overlaps 
 * the center one. Speed increases each time you succeed
 */

//Include the LEDStrip library to use the commands
#include "LEDStrip.h"

const byte numPixels = 15; //Number of pixels on a strip
const byte middlePixel = numPixels/2; //The pixel at the middle of your strip

int pixel = 0; //Position of the pixel on the strip

const int hitColor = 50; //The color of the strip when you hit the mark
const int missColor = 100; //The color of the strip when you miss the mark

int Direction = 1; //Direction of travel of the pixel

int delayTime = 300; //Starting time (in ms) between pixel movements

long timer = millis(); //Timer to control movement of pixel

/*
 * Make the LED strip object LEDStrip strip
 *  = LEDStrip(numPixels, dataPin (DI), clockPin (CI));
 */
LEDStrip strip = LEDStrip(numPixels, 13, 12);


void setup() {

  //Button
  pinMode(A5,INPUT_PULLUP);
}

void loop() {

  //If at the center pixel
  if (pixel == middlePixel){
    strip.setPixel(pixel,(hitColor+missColor)); //overlap the colors
    
    //If the button is pressed while on the center pixel
    if (digitalRead(A5) == LOW){
       delayTime= delayTime*.75; //delayTime reduced by 25%
      
      //Blink the hitColor to indicate success
      strip.setPixel(strip.ALL,hitColor);
      strip.draw();
      delay(1000);
      strip.clear();
    }
  }

  //When not on the center pixel
  if (pixel != middlePixel){
    strip.setPixel(pixel,missColor); //Set the moving pixel
    strip.setPixel(middlePixel,hitColor); //Set the center pixel

    //If button pressed when not at center
    if (digitalRead(A5) == LOW){
      
      //Blink all pixels the missColor for a second
      strip.setPixel(strip.ALL,missColor);
      strip.draw();
      delay(1000);
      strip.clear();
    
    //changed 100 to 50
      delayTime = delayTime + 50; //Slow down the ball
    }
   }

  //Every delayTime many ms, update pixel position
  if (millis()-timer > delayTime){
    timer = millis(); //Reset the timer 
    strip.setPixel(pixel,-1); //Clear previous pixel
    pixel = pixel + Direction; //Move the pixel
    
    //If at either end of the strip, change direction of travel
    if ((pixel == 0)||(pixel == numPixels-1)){
      Direction = Direction*-1;
    }
  }

  strip.draw(); //Draw what was written to the strip this loop
}

//Change the reduction to delayTime time to make the game move more
//  quickly

//(c) 2017 Let's Start Coding. License: www.letsstartcoding.com/bsdlicense
