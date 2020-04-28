/*
 * Play a memory game with three LEDs and three buttons. 
 * The game will blink out a pattern of lights. Each light corresponds
 * to a button in the game. Try to 'play back' the pattern to the game.
 * Get it right and you'll hear a beep and move on to the next (harder)
 * level. Get it wrong and you'll hear a deep tone and start over. 
 */

byte computer[10]; //array to hold the computer's moves up to 10 moves
byte player[10]; //array to hold player's (your) moves up to 10 moves


byte computersTurn = true;
byte numGuess = 0; //count guesses and hold them to compare to the computer's
byte level = 3; //how many lights in the sequence player has to copy
const int wait = 500;//pause between each play. Change for faster/slower play

const byte speaker = A5; //speaker pin A5

//When player presses button, put it in the array in order
void setPlayer(byte _guess) {
  player[numGuess] = _guess;
  digitalWrite(_guess,HIGH);
  delay(300);
  digitalWrite(_guess,LOW);
  numGuess++; //move to the next position in array of player's guesses
}

void setup() {
  
  pinMode(4, OUTPUT); //LEDs to display moves
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

  pinMode(speaker, OUTPUT);

  //Buttons
  pinMode(0, INPUT_PULLUP); //corresponds to pin 4 LED
  pinMode(2, INPUT_PULLUP); //corresponds to pin 5 LED
  pinMode(A0, INPUT_PULLUP); //corresponds to pin 6 LED
}

void loop() {

  //Assign random numbers 4, 5, or 6 to computer's array
  if (computersTurn == true) {
    for (int i = 0; i < level; i++) {
      computer[i] = random(4, 7);
    }
  }
  //Write moves from the computer[] array to LEDs
  for (int i = 0; i < level; i++) {
    digitalWrite(computer[i], HIGH);
    delay(wait);
    digitalWrite(computer[i], LOW);
    delay(wait);
  }

  computersTurn = false; //Swap to player's turn

  //Put player's guesses into player's array via setPlayer() function
  //Keep accepting guesses until number of guesses = the level player is on
  while (numGuess < level) {
    if (digitalRead(0) == LOW) {
      setPlayer(4);
    }
    if (digitalRead(2) == LOW) {
      setPlayer(5);
    }
    if (digitalRead(A0) == LOW) {
      setPlayer(6);
    }
  }

  //Check if player array matches computer's array
  for (int i = 0; i < level; i++) {
    if (player[i] == computer[i]) {
      tone(speaker, 950);
      delay(50);
      noTone(speaker);

    } else {   //if the arrays don't match, play the low tone and restart
      tone(speaker, 150, 1000);
      level = 2;
    }
  }

  //changed 2000 to 500
  delay(500); //wait after player's placement before the computer's turn
  computersTurn = true;
  numGuess = 0; //reset the number of player guesses to 0
  level++; //increase the number of lights the computer will show by 1

  //If the player beats 10 levels, victory display and reset game!
  if (level > 10) {
    for (int i = 0; i < 80; i++) {
      tone(speaker, 950);
      digitalWrite(5, HIGH);
      digitalWrite(6, LOW);
      delay(20);
      tone(speaker, 550);
      digitalWrite(6, HIGH);
      digitalWrite(5, LOW);
      delay(20);
      noTone(speaker);
    }
    level = 3;//now reset back to level 3 after victory
  }
}

// Try to adjust the value of 'wait' after each level in order to make 
// the computer place its values faster each time

// Feeling ambitious? Try to add in a timer so that the player has only a
// limited window to put in their answers before they automatically lose!

// (c) 2017 Let's Start Coding. License: www.letsstartcoding.com/bsdlicense