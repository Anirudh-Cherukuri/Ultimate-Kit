
/*
 * Press a button to 'flip a coin' between two LED lights on pins 2 and 3
 */
 
void setup() {
  pinMode(2,OUTPUT);//LEDs
  pinMode(3,OUTPUT);
  
  pinMode(A5,INPUT_PULLUP);//button
}

void loop() {
     //When button pressed, create a flashing effect 30 times
  if(digitalRead(A5) == LOW){
     for(int i = 0; i< 30; i++){
         digitalWrite(2,HIGH);
         digitalWrite(3,LOW);
         delay(50);
         digitalWrite(3,HIGH);
         digitalWrite(2,LOW);
         delay(50);
         digitalWrite(3,LOW);
     }
        //Randomly decide a winner between 2 and 4 (2 or 3) and light it.
     digitalWrite(random(2,4),HIGH);
     delay(1500);
     digitalWrite(2,LOW);
     digitalWrite(3,LOW);
  }
}

// Make the number of times the 'for' loop runs a random value so you have
// different lengths of time the coin is flipping.

// (c) 2017 Let's Start Coding. License: www.letsstartcoding.com/bsdlicense

