
/*
 * Turn an LED on with two claps, and off with two more
 */

//A toggling variable for the LED state to use with digitalWrite
int clapCount = 0; //Will equal 0, 1, 2 or 3

void setup() {

  pinMode(A4,INPUT);//Center pin of sound trigger

  pinMode(6,OUTPUT); //LED
}

void loop() {  
  const int soundThreshold = 600; //Experiment with your threshold

   //Change clapCount if noise detected. 
  if (analogRead(A4) > soundThreshold){
    clapCount++; //Increase the value of clapCount by 1
    //clapCount is changed to the remainder of clapCount/4
    clapCount = clapCount%6;
    delay(300); //prevent the noise from registering more than once
  }

  //clapCount%4 restricts clapCount to 0-3
  if (clapCount == 3){ //Turn LED on after 2 claps
    digitalWrite(6,HIGH);
  }
  if (clapCount == 0){//Turn LED off after 2 more
    digitalWrite(6,LOW);
  }
  
}

//Change the clapCount%4 to clapCount%6, and the (clapCount == 2) to
//  clapCount == 3. How many claps does it take to turn on and off 
//  now? 3 claps

// (c) 2017 Let's Start Coding. License: www.letsstartcoding.com/bsdlicense
