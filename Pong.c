/*
 * Single line pong using the LEDStrip, when the pixel is at the
 * end of the strip, press your button to send it back to your 
 * opponent.
 */

//Include the LEDStrip library to use the commands
#include "LEDStrip.h"

const byte numPixels = 15; //number of pixels on a strip
const byte middlePixel = numPixels/2; //Where the ball will reset

//Color values on the strip range from 0 to 300
int color; //The color of the strip and ball depends on the player
const int p1Color = 75;//Color for p1's points
const int p2Color = 225;//Color for p2's points 

long timer = millis(); //Timer to control movement of pixel

//Flags for early presses, so you can't hold the button down
bool p1Early = false;
bool p2Early = false;

//Flags for when players press the button at the correct time
bool p1Hit = false;
bool p2Hit = false;

int pixel = 7; //Starting position of the pixel
int ballDelay = 150;//The number of milliseconds between pixel moves

int Direction = 1; //Direction of travel of the pixel. 1 or -1

/*
 * Make the LED strip object LEDStrip strip
 *  = LEDStrip(numPixels, dataPin (DI), clockPin(CI));
 */
LEDStrip strip = LEDStrip(numPixels, 13, 12);

void setup() {
  
  //Buttons
  pinMode(A5,INPUT_PULLUP); //p1Button
  pinMode(2,INPUT_PULLUP);//p2Button
  
}

void loop() {

  //Check the players' buttons
  int p1Button = digitalRead(A5);
  int p2Button = digitalRead(2);

  //If P1 button pressed while at pixel 0, P1 gets a hit
  if ((p1Button == LOW)&&(pixel == 0)){
    p1Hit = true;
  }
  
  //If P2 button pressed while at pixel 14, P2 gets a hit
  if ((p2Button == LOW)&&(pixel == numPixels-1)){
    p2Hit = true;
  }

  //If the 'ballSpeed' time has passed, this if loop is true.
  if (millis() - timer > ballDelay){

    timer = millis(); //Reset the timer

    //If P1 hits and didn't swing early when pixel is 0
    if ((pixel == 0)&&((p1Hit == true)&&(p1Early == false))){
      Direction = Direction*-1; //Change direction 
      color = p2Color; //Make the pixel P2's color
      p1Hit = false; //Reset the 'hit' flag for P1
    }
    //If P1 didn't hit, or swings early when pixel is 0
    else if ((pixel == 0)&&((p1Hit == false)||(p1Early == true))){
      pixel = middlePixel; //Reset pixel to middle of strip
      color = p2Color; //Make pixel P2's color
      Direction = Direction*-1; //Change direction
     
      //Flash P2's color to indicate a point for p2
      strip.setPixel(strip.ALL,p2Color); 
      strip.draw();
      delay(1000);
      strip.clear();
      
      p1Hit = false; //Reset P1's hit flag
    }

    //If P2 has hit, is not early, and pixel is in correct position...
    if ((p2Hit == true)&&(pixel == numPixels-1)&&(p2Early == false)){
      Direction = Direction*-1; //Change direction
      color = p1Color; //Set pixel to P1's color (225 is cyan)
      p2Hit = false; //Clear P2's hit flag
    }
    //if pixel is in correct position and P2 misses or swings early
    else if (((p2Hit == false)||(p2Early == true))&&(pixel == numPixels-1)){
      pixel = middlePixel; //Set pixel to middle of strip
      color = p1Color; //Set pixel to P1's color
      Direction = Direction*-1; //Change direction
      
      //Flash P1's color to indicate point earned
      strip.setPixel(strip.ALL,p1Color);
      strip.draw();
      delay(1000);
      strip.clear();
      
      p2Hit = false;//Clear P2's hit flag
    }

    strip.setPixel(pixel,-1); //clear the old pixel
    pixel = pixel + Direction; //Move the pixel

    //If just transitioning to pixel 0 and P1 pressing button
    if ((pixel == 0)&&(p1Button == LOW)){
      p1Early = true; //Flag that P1 swings early
    }
    //If just transitioning to last pixel and P2 pressing button
    else if ((pixel == numPixels-1)&&(p2Button == LOW)){
      p2Early = true; //Flag that P2 swings early
    }
    //If early swing flags not set when moving pixel, clear them
    else{
      p1Early = false;
      p2Early = false;
    }
    
    strip.setPixel(pixel,color); //Write the new pixel
  }
  
  strip.draw(); //Draw what we wrote to the strip
}

//Update the ballDelay variable for faster speeds. Try to lower ballDelay
//each time there is a confirmed hit by a player! 

// (c) 2017 Let's Start Coding. License: www.letsstartcoding.com/bsdlicense
