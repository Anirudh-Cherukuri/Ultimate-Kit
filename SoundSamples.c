
/*
 * Press a button to activate various sound effects
 */

byte pressCount = 0; //track presses on button to change the effect

    //Function to check for button presses
void checkPress(){
   if(digitalRead(12)==LOW){
     pressCount++;
     delay(200);
  }
}
void setup() {
  pinMode(A5, OUTPUT); //speaker
  pinMode(12, INPUT_PULLUP); //button
}

void loop() { 
  checkPress(); //run the checkPress function 
  
    //rising pitch
if(pressCount == 1) { //if pressCount = 1, start the rising tone
    for (int i = 0; (i < 1200); i++) {//play tones 0-1199
      tone(A5, i);
      delay(5);
      checkPress(); //run the function to see if button was pressed
      if(pressCount!=1){ //if button pressed again, break the 'for' loop
         break;
      }
    }
  }

     //random tones 
  if(pressCount == 2){ 
      tone(A5, random(1,1201)); //Play any tone between 0 and 1201
      delay(50); //pressCount is checked every 50 milliseconds
  }

    //falling pitch
  if(pressCount == 3) {
    for (int i = 1300; i > 30; i--) {//play tones from 1300 down to 30
      tone(A5, i);
      delay(5); 
      checkPress();//run function again to check pressCount
      if(pressCount!=3){ //if button pressed again, break the for loop
         break;
      }
    }
  }
  
  int pitch = 1 ; //tone value as it rises and falls
  int scale = 10; //the speed of the change of pitch.
  
    //rising and falling pitch
  while(pressCount == 4) {
    checkPress();
    pitch = pitch + scale;
    tone(A5, pitch);
    delay(5);
    if(pitch <= 0 || pitch >= 1200){
        scale = -scale;
     }
   }
  
  int lowTone = 10; //starting place for a rising tone
  int highTone = 1800; //starting place for a sinking tone
  
     //Low pitch rises as high pitch falls
  while(pressCount == 5){
     checkPress();
     tone(A5,lowTone);
     delay(50);
     tone(A5,highTone);
     delay(50);
     highTone-=10;
     lowTone+=10;
     
        //reset the tones 
     if(highTone < 10){
        highTone = 1500;
     }
     if(lowTone > 1800){
        lowTone = 10;
     }
  }
   
    //Turn off the sounds and reset presses to 0
  if(pressCount > 5){
    noTone(A5);
    pressCount = 0;
  }
 }

// Add another button for 'off' that resets pressCount to 0 when pressed

 
// (c) 2017 Let's Start Coding. License: www.letsstartcoding.com/bsdlicense

