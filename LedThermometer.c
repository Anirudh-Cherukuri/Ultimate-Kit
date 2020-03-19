
/*
 * Display the temperature in LED blinks by counting out the
 *  tens and ones place to LEDs.
 */

void setup() {
  //Configure the LED pins
  pinMode(5,OUTPUT);//Tens place of the temperature
  pinMode(6,OUTPUT);//Ones place of the temperature

  //Check the temp sensor pinout, getting it backwards ruins it
  pinMode(A3,INPUT); //Center pin of temp sensor to A3
  
  /*
   * Conversion constants 0.88 and -58 turn the analog reading 
   *  to Farenheit. Cast analogRead(A3) to a float
   */
  const int tempF = int(0.88*float(analogRead(A3) - 58.0));

  //Use modulo to remove the ones place from tempF.
  //Divide difference by 10 for the tens place of tempF
  //e.g. tempF = 35 gives (35 - 5)/10 = 3
  const int tempTens = (tempF-(tempF%10))/10;

  //Blink the 10s place digit on pin 5
  for (int i = 0;i < tempTens;i++){
    digitalWrite(5,HIGH);
    delay(300);
    digitalWrite(5,LOW);
    delay(300);
  }
  
  //Blink the 1s place digit on pin 6
  //tempF%10 will equal the remainder of tempF / 10
  for (int i = 0;i < tempF%10;i++){
    digitalWrite(6,HIGH);
    delay(300);
    digitalWrite(6,LOW);
    delay(300);
  }

}

void loop() {
  //Nothing in the loop. It will check the temperature once when
  //powered on
  }

//Try to bring the calculations and blinking into loop, so that it
//  measures repeatedly

// (c) 2017 Let's Start Coding. License: www.letsstartcoding.com/bsdlicense


