
/*
 * Morse Code - LED blinks text messages as Morse code dots and dashes 
 */

// create constant array of the messages you want Morse'd out
// Change the "SOS" to any message you like... 
const char message[ ] = "SOS"; 

// In ASCII code, 'space' is 32, '0'-'9' is 48-57, and 'A'-'Z' is 65-90
const String morse[] = { ".----", "..---", "...--", "....-", ".....", 
  "-....", "--...", "---..", "----.", "-----", ".-", "-...", "-.-.", "-..", 
  ".","..-.","--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", 
  ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", 
  "--.."};

const byte speaker = A5; // speaker
const int dotLen = 200; //delay in milliseconds
const int dashLen = 3*dotLen; // 3X longer than the dot
const int wordLen = 7*dotLen; // space between words.

void setup() {         
  pinMode(speaker, OUTPUT);
}

// blink out one morse code character.
void signalMorse(String c) {
  int i = 0; 
  while (c[i]) { // for each dot or dash in the letter...
    tone(speaker, 450); // speaker plays a tone of 450 hertz
    if (c[i] == '.') { 
       delay(dotLen); // if dot, short delay
    } else if (c[i] == '-') {
       delay(dashLen); // if dash, longer delay
    }
    noTone(speaker); // speaker off
    delay(dotLen);  // off blink. 
    i++;    //bring in the next dot or dash from the morse letter!]'
  };
  // We already delayed one dot length in the loop. A Word break = dashLen..
  delay(dashLen-dotLen); 
}

void loop() {
  int i = 0; //counter variable to move through the array
  char C; //holds each letter as it gets converted to blinks
  while (message[i]) { // fails when reaches the end of the string ("0")
    C = toupper(message[i]);
        
    if (C == ' ') {
      delay(wordLen); // space between words  
    } 
    else if (C>47 && C<58) {  // 0-9. ASCII 48-57
      signalMorse(morse[C-48]);
    } 
    else if (C>64 && C<91) {  // A-Z, ASCII 65-90, 10-34 in morse[]
      signalMorse(morse[C-55]);
    }
    else {
      delay(wordLen);
    }
    i++; // move to the next character in your message
  }
  delay(2 * wordLen);
}

// Try to add a low tone after the message is complete. Where should it go?

// (c) 2017 Let's Start Coding. License: www.letsstartcoding.com/bsdlicense

