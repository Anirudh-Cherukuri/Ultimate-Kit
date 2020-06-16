
/*
 * Fade random colors from bright to dim by changing the flicker rate
 */

void setup() {
  pinMode(4, OUTPUT); //LED pins to fade
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
}

//create a function that takes in 4 values from loop and digitalWrites them
void fade(int _on4, int _on5, int _on6, int _offTime) {
  for (int repeat =0; repeat <(20 /_offTime); repeat++) {
    digitalWrite(4,_on4);
    digitalWrite(5,_on5);
    digitalWrite(6,_on6);
    delay(1);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW); 
    delay(_offTime);
  }
}

void loop() {
  // Set each LED on or off at random
  byte on4 = random(2);//will return either a 1 or a 0
  byte on5 = random(2); 
  byte on6 = random(2);
  
  // if all 3 randoms are zero, all lights are off. Default to one on.
  if ( (on4 + on5 + on6) == 0) { 
  	on4 = 1; 
  } 
  
  for (byte offTime =20; offTime >0; offTime--) { // fade from dim to bright
       fade(on4,on5,on6, offTime);
  }
  
  for (byte offTime =0; offTime <20; offTime++) { //fade from bright to dim
       fade(on4,on5,on6, offTime);
  }
}


//Try changing the "40/ _offTime" to "20/ _offTime" to change fade speed


// (c) 2017 Let's Start Coding. License: www.letsstartcoding.com/bsdlicense

