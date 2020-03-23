
/*
 * In this lesson, you will add an additional wall for an extra challenge.
 * 
 * To make this work, you will duplicate the original wall and add checks to 
 * ensure the program works correctly for both obstacles
 */
#include "MakerScreenXVI.h"

MakerScreenXVI lcd;

byte run0[8] = { //legs in partial stride
  0b00000,
  0b01100,
  0b01100,
  0b01100,
  0b01110,
  0b01100,
  0b01010,
  0b01010
};

byte run1[8] = { //legs in full stride
  0b00000,
  0b01100,
  0b01100,
  0b01111,
  0b01100,
  0b01100,
  0b01010,
  0b10001
};

/*
 * The same custom character will work for both walls
 */
byte wall[8] = { //wall obstacle
  0b11111,
  0b10101,
  0b11111,
  0b10001,
  0b11111,
  0b10101,
  0b11111,
  0b10001
};

byte crash[8] = { //crashed JumpMan
  0b00000,
  0b00011,
  0b01011,
  0b00111,
  0b00011,
  0b00011,
  0b00001,
  0b00001
};

byte jump[8] = { //mid-jump icon
  0b00110,
  0b10110,
  0b01100,
  0b01111,
  0b01110,
  0b01011,
  0b10000,
  0b00000
};

// Make an icon for the heart object, just like the others
byte heart[8] = {//heart for extra life
  0b00000,
  0b01010,
  0b10101,
  0b10001,
  0b01010,
  0b00100,
  0b00000,
  0b00000
};

int position = 0;  //holds the changing position of the cursor
bool runState = 0; //which running animation to draw (0 or 1).
int jumpState = 0; //0 ='pre-jump', 1 ='mid jump', 2='post jump'
bool buttonState = 0; //will equal 1 after press, 0 after jump completed
int wallPosition = 14; //wall can be placed from 0 to 15

/*
 * You will need another variable to hold the position of the new wall 
 */
int wall2Position = 10; //position of the second wall

bool heartState = 0;//0 = no heart available, 1 = heart available
int heartPosition; //which column is the heart in?
int lives = 3; //starting number of lives

int animationDuration = 300; //ms between animations of JumpMan's legs
int runDuration = 600; //ms between moving JumpMan's position on the screen

//Timers to update for each 'level'
long animationTimer;
long runTimer;

void setup() {

  lcd.begin();
  
  lcd.backlightOn();

  lcd.createChar(0, run0); //partial stride character
  lcd.createChar(1, run1); //full stride character
  lcd.createChar(2, wall); //wall character in 'slot' 2 of custom characters
  lcd.createChar(3, crash); //splatted character against the wall
  lcd.createChar(4, jump);  //mid-jump icon
  lcd.createChar(5, heart); //heart for extra lives

  pinMode(6,INPUT_PULLUP); //button to trigger jump

  startScreen();//run function for welcome screen

  //Start both timers equal to millis() so that the difference between
  //millis and the variables is 0.
  animationTimer = millis();
  runTimer = millis();

  randomSeed(analogRead(A0));//take a reading from A0 to get a random number

}

void loop() {
 
  lcd.setCursor(0,0);
  lcd.write(4); //Show the jump icon alongside the lives counter
  lcd.print(lives);

   //Set the cursor depending on the state of the character
  if (jumpState == 0){
    lcd.setCursor(position,1);
  }
  else if (jumpState == 1){
    lcd.setCursor(position,0);
  }
  else if (jumpState == 2){
    lcd.setCursor(position,1);
  }

  if (jumpState == 1){ //if jump has been activated..
    lcd.write(4); //draw JumpMan mid-air
  }
  else{
    lcd.write(runState); //draw the run0 or run1 animation
  }

  lcd.setCursor(wallPosition,1);
  lcd.write(2); //draw wall

  /*
   * Draw your second wall the same way you drew the other
   */
  lcd.setCursor(wall2Position,1);
  lcd.write(2);//draw wall 2

  if (heartState == 1){//if a heart is available, draw it
    lcd.setCursor(heartPosition,0);
    lcd.write(5);
  }
  if ((digitalRead(6) == LOW)&&(jumpState == 0)){
    buttonState = 1; //1 means a press is recorded
  }
  
   //Button is unpressed and a jump has been completed
  if ((digitalRead(6) == HIGH)&&(jumpState == 2)){
    jumpState = 0;
  }

  if (millis() - animationTimer > animationDuration){
    runState = 1 - runState; //draw the next JumpMan animation
    animationTimer = millis();
    lcd.clear(); //clear the LCD to draw a new character
  }

  if (millis() - runTimer > runDuration){//update position after runDuration
    position = position + 1;

   if (position == 16){
      heartState = 0; //by default there is no heart available
      
      if (random(0,10) < 3){//30% of the time...
        heartState = 1; //signal that a heart will be available
        heartPosition = random(3,16); // Place the heart randomly
      }

      wallPosition = random(3,16);//place wall 1 in column 3 through 15

      /*
       * Wall 2 should always be at least 3 spaces away from wall 1 because
       * JumpMan can only jump one wall at a time. Without the added space,
       * the walls could appear back-to-back and create an impossible level.
       * 
       * You may notice that if wallPosition is 15, then wall2Position can 
       * be a random number between 18 and 16. That means sometimes you'll have
       * only one wall. You could ensure you'll always have two walls by
       * limiting how far to the right wall 1 is allowed to be placed.
       */
      wall2Position = random((wallPosition+3),16);
      
      position = 0;//reset JumpMan to the left of the screen after a level
    }

  //if button has been pressed and a jump hasn't been initiated...
    if ((buttonState == 1)&&(jumpState == 0)){
      jumpState = 1; //signal a jump
      buttonState = 0; //reset button to 'unpressed' in the code
    }
    else if (jumpState == 1){ //true if jumpState set to one in the last loop
      jumpState = 2; //jump is marked as complete
    }

    //check for heart collision
    if ((position == heartPosition)&&(jumpState == 1)){
      // heartState gets set to 0 so the player doesn't get it
      // more than once.
      if (heartState == 1){
        lives = lives + 1; //add a life
        heartState = 0; //reset the heart variable
      }
    }
    
    /*
     * You will now use logic to check for a collision with the
     * second wall. The || operator checks if either or both of two
     * conditions is true. The check below says "Run the code if 
     * position equals wallPosition OR wall2Position AND the jumpState
     * is not equal to one.
     * To type the Boolean "OR", you will hold 'shift' and press the \ 
     * key, usually under the backspace or delete key
     */

    //Check to see if either jump has been missed
    if (((position == wallPosition)||(position == wall2Position))&&(jumpState != 1)){
      drawCrash();
      
      lives = lives - 1;//decrease lives by one with each crash

      if (lives == 0){ //if out of lives...
        // Clear the LCD and write "Game Over" to it
        lcd.clear();
        lcd.setCursor(4,0);
        lcd.print("Game Over");

        delay(2000);//wait two seconds to restart the game

        //Reset all state variables:
        lives = 3;
        position = 0;
        buttonState = 0;
        runState = 0;

        //Reset speeds to 'level one'
        runDuration = 600; 
        animationDuration = 300;

        /*
         * Show the start screen after the 'game over' is shown so that the 
         * next game won't start until the button is pressed again
         */
        startScreen();
      } 
    }

    //if either wall is cleared
    else if ((position == wallPosition)||(position == wall2Position)){
      runDuration = runDuration - 50; //speed each position up by 50 ms
      
      if (runDuration < 100){//keep runDuration at a minimum of 100
        runDuration = 100;
      }
    
      animationDuration = runDuration/2; //Move legs twice per position change
    }

    lcd.clear();
        
    runTimer = millis();
  }
}

void drawCrash(){
  lcd.clear();

  lcd.setCursor(position-1,1); //move cursor one position left of the collision
  lcd.write(3);//draw 'splatted' JumpMan

  lcd.setCursor(wallPosition,1);
  lcd.write(2); //draw the wall
  
  lcd.setCursor(wall2Position,1);
  lcd.write(2); //draw the second wall

  delay(1000);

  // Reset the variables to put the JumpMan back at the starting point
  position = 0;
  buttonState = 0;
  jumpState = 0;
}

void startScreen(){

  lcd.clear();

  lcd.setCursor(2,0);//place cursor near the middle of Maker Screen
  lcd.print("Press button 6");
  lcd.setCursor(4,1);//Move to the next line and complete the message
  lcd.print("to play!");

  while (digitalRead(6) == HIGH){//while the button isn't pressed...
    delay(10); //wait 10 ms and check the 'while' again
  }
  
  while (digitalRead(6) == LOW){ //while the button is pressed...
    delay(10); //wait 10 ms and check the 'while' again
  }
  
  //After both 'while' loops have completed, clear the screen and complete
  //the function
  
  lcd.clear();
  
}

/*
 * This is the last lesson in the JumpMan Guided Build. You've built an 
 * entire program that now stretches over 300 lines! Good work. 
 *
 * Now, the real challenge begins: What will you add to this game to make it
 * even more fun?
 * 
 * You could make JumpMan start off running faster or change how quickly the 
 * speed changes. You could add or take away lives or make extra 
 * lives more or less common.
 * 
 * You could also go on to add your own features. You could add an LED that 
 * lights up when a heart is available and a speaker that plays a sad tone 
 * as a part of the drawCrash() function. You may even be able to figure out
 * how to tally and hold a 'High Score' so that you can share the game with 
 * your friends.
 * 
 * Really, there's an endless supply of things you could do, and 
 * that's what makes programming exciting. By building up your code
 * a little bit at a time, you can make bigger and better projects,
 * even when the original idea seems really big.
 */ 
  
 //(c) 2017 Let's Start Coding. License: www.letsstartcoding.com/bsdlicense
 

