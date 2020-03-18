/* Use a sound trigger to make a single LED shine brighter when 
 *  a loud noise occurs.
 */  

void setup() {

pinMode(A4,INPUT); //middle pin of the sound trigger
pinMode(9,OUTPUT); //LED

}

void loop() {
  //Set the sound minimum and maximum threshold
  //The sensor can read 0-1023, but likely range is 250-450
  const int soundMin = 250;
  const int soundMax = 450;

  //The brightness variable will be between 0-255
  //soundMin becomes 0 brightness, soundMax becomes 255 brightness
  int brightness= map(analogRead(A4),soundMin,soundMax,0,255);

  //The constrain method keeps brightness variable between 0 and 255
  brightness = constrain(brightness,0,255);
  
  analogWrite(9,brightness);//write the value of brightness to the LED
}

//Reverse the way the map is working so the light 
// turns off near loud noises

//(c) 2017 Let's Start Coding. License: www.letsstartcoding.com/bsdlicense
