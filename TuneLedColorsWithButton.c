
/*
 * Tune a multicolor LED's colors with buttons
 * The analogWrite() function works on digital pins 3,5,6,9,10,11.
 */

byte brightness; //holds the brightness of the outputs. Range is 0-255

//function that takes in the pin number and changes brightness on that pin
void changeBrightness(byte _pin){
  brightness++;
  analogWrite(_pin,brightness);
  if(brightness == 255){
     brightness = 0;
  }
}

void setup(){
  //Set all LEDS to output
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  
  //one button per LED color
  pinMode(A5, INPUT_PULLUP); 
  pinMode(A1, INPUT_PULLUP); 
  pinMode(2, INPUT_PULLUP);
}
void loop(){
  //Increase each color to its max, then start the intensity back at 0
  if(digitalRead(A5) == LOW){
     changeBrightness(9); //pass the LED pin number to the function 
     }    
  if(digitalRead(A1) == LOW){ 
     changeBrightness(10);
    } 
  if(digitalRead(2) == LOW){ 
     changeBrightness(11);
    }
  delay(10); //Speed of fade while button is LOW. Longer delay = slower fade
}

// Add a 'reset' button that turns all of the LED brightnesses to 0

// (c) 2017 Let's Start Coding. License: www.letsstartcoding.com/bsdlicense

