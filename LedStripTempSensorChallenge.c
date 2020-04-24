
/*
 *An LED strip that changes color depending on the temperature
 */

#include "LEDStrip.h"

const byte numPixels = 15; //number of pixels on a strip

/*
 *Make the LED strip object LEDStrip strip 
 * = LEDStrip(numPixels, dataPin, clockPin);
 */
LEDStrip strip = LEDStrip(numPixels, 13, 12);

void setup() {
  pinMode(A4,INPUT); //Temperature sensor pin
}

void loop() {
  const int minTemp= 60; //set the minimum expected temp as a variable
  const int maxTemp= 80;
  
  //Use an equation to convert the analogRead of the temp sensor to a
  //value in degrees Fahrenheit
  float tempF = int(0.88*float(analogRead(A4)) - 58.0); 

  //limit the possible values of tempF to minTemp and maxTemp 
  tempF = constrain(tempF,minTemp,maxTemp);

  //Set the pixels to the color corresponding to temperature
                                            //changed from 0,100
  strip.setPixel(strip.ALL,map(tempF,minTemp,maxTemp,25,75));

  strip.draw(); //Draw the pixels that you set in .setPixel
  delay(250);
}

//Change the color range in the map (0,100) for a different range based on temp

//(c) 2017 Let's Start Coding. License: www.letsstartcoding.com/bsdlicense


