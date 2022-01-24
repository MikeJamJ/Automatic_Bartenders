/*
   SS_Prime functions. Will run the selected pump while the button is held down
   and times out after 3 seconds.
*/

//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------

void SubSet_Run() {
  Serial.println(F("\n===================================\nENTERING RUN\n===================================\n"));

  int numOfPumps = 5;
  pos = 0;
  Serial.print(F("position: "));
  Serial.println(pos);
  int lastButton = 0;
  //drawPumpButtonsArray();
  printCurrentIngInfo();

  while (b_SUBSET == true) {
    if (pos != lastPos) {
      //Turns off interrupt to allow the code to finish before another value can be checked
      noInterrupts();  
      if (pos < 0) pos = numOfPumps - 1;
      else if (pos > numOfPumps - 1) pos = 0;
      Serial.print(F("position: "));
      Serial.println(pos);
      //updatePumpButtonsArray(lastButton);
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
          b_SET = true;
          b_SUBSET = false;
          break;
        }
      }
      if (b_SUBSET) {
        prime(pos);
      }
    }
  }
  Serial.print(F("END OF PRIME\nb_SUBSET: "));
  Serial.println(b_SUBSET);
  Serial.println(F("\n===================================\nREENTERING b_SETTINGS\n===================================\n"));
  resetPosValue();
  drawSettingsMenu();
  while (!digitalRead(butSelect)) {}
}


void prime(byte pumpNum) {
  Serial.println(F("\n===================================\nENTERING SUBPRIME\n===================================\n"));
  bool PRIME = true;
  setTextSize(1);
  tft.setCursor(163, 144);
  tft.setTextColor(TEXT_COLOR, BACKGROUND_COLOR);
  tft.print(F("Hold to run pump"));
  
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
  Serial.print(F("END OF PRIME\nPRIME: "));
  Serial.println(PRIME);
  Serial.println(F("\n===================================\nREENTERING PRIME\n===================================\n"));
  resetPrime(pumpNum);
  while (!digitalRead(butSelect)) {}
}


void resetPrime(byte n){
  pos = n;
  tft.fillRect(163, 144, 319, 176, BACKGROUND_COLOR);
}
