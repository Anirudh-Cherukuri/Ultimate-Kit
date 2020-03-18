/*
 * Press a button to 'roll a die' and get the outcome in blinks
 */

void setup() {
  pinMode(11,OUTPUT);//LED
  pinMode(A5,INPUT_PULLUP);//button
}

void loop() {
     //When button pressed, create a flashing effect 10 times on pin 1
  if(digitalRead(A5) == LOW){
     for(byte i = 0; i<30; i++){
         digitalWrite(11,HIGH);
         delay(50);
         digitalWrite(11,LOW);
         delay(50);
     }
     delay(500); //pause after 'roll' has completed
     
      //choose a random number 1-6 and blink the LED that number of times
     for(byte i = 0; i<= random(1,7); i++){
         digitalWrite(11,HIGH);
         delay(300);
         digitalWrite(11,LOW);
         delay(300);
    }
  }
}

// Try to add a speaker and that plays a rising tone while the dice rolls

// (c) 2017 Let's Start Coding. License: www.letsstartcoding.com/bsdlicense
