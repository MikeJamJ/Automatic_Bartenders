/*
   SS_Prime functions. Will run the selected pump while the button is held down
   and times out after 3 seconds.
*/

//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------

void subSetPrime() {
  Serial.println("\n===================================\nENTERING PRIME\n===================================\n");

  int numOfPumps = 5;
  pos = 0;
  Serial.print("position: ");
  Serial.println(pos);
  int lastButton = 0;
  printPumpButtons();
  printCurrentIngInfo();

  while (SUBSET == true) {
    if (pos != lastPos) {
      //Turns off interrupt to allow the code to finish before another value can be checked
      noInterrupts();  
      if (pos < 0) pos = numOfPumps;
      else if (pos > numOfPumps) pos = 0;
      Serial.print("position: ");
      Serial.println(pos);
      updatePumpButtons(lastButton);
      printCurrentIngInfo();
      lastPos = pos;
      lastButton = pos;
      interrupts();
    }

    if (!digitalRead(butSelect)) {
      curButtonTime = millis();
      prevButtonTime = curButtonTime;
      while (!digitalRead(butSelect)) {
        curButtonTime = millis();
        if ((curButtonTime - prevButtonTime) >= 2000) {
          SET = true;
          SUBSET = false;
          break;
        }
      }
      if (SUBSET) {
        prime(pos);
      }
    }
  }
  Serial.print("END OF PRIME\nSUBSET: ");
  Serial.println(SUBSET);
  Serial.println("\n===================================\nREENTERING SETTINGS\n===================================\n");
  resetPosValue();
  settingsScreen();
  while (!digitalRead(butSelect)) {}
}


void prime(byte pumpNum) {
  Serial.println("\n===================================\nENTERING SUBPRIME\n===================================\n");
  bool PRIME = true;
  myGLCD.setFont(SmallFont);
  myGLCD.setColor(OFF_WHITE);
  myGLCD.setBackColor(OFF_BLACK);
  myGLCD.print("Hold to run pump", 163, 144);
  
  prevButtonTime = millis();
  while (PRIME == true) {
    curButtonTime = millis();
    if ((curButtonTime - prevButtonTime) >= 3000){
      PRIME = false;
    }
    
    if (!digitalRead(butSelect)) {
      startPump(pumpNum);
      while (!digitalRead(butSelect)) {
      }
      digitalWrite(Relay_1, RELAY_OFF);
      digitalWrite(Relay_2, RELAY_OFF);
      digitalWrite(Relay_3, RELAY_OFF);
      digitalWrite(Relay_4, RELAY_OFF);
      digitalWrite(Relay_5, RELAY_OFF);
      digitalWrite(Relay_6, RELAY_OFF);
      prevButtonTime = millis();
    }
  }
  Serial.print("END OF PRIME\nPRIME: ");
  Serial.println(PRIME);
  Serial.println("\n===================================\nREENTERING PRIME\n===================================\n");
  resetPrime(pumpNum);
  while (!digitalRead(butSelect)) {}
}


void resetPrime(byte n){
  pos = n;
  myGLCD.setColor(OFF_BLACK);
  myGLCD.fillRect(163, 144, 319, 176);
}


