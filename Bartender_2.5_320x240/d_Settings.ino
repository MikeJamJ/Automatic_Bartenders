/*
   Settings menu that allow the user to choose between cleaning and priming individual pumps:
   settings();
   printSettingsInfo(int pos);
*/

//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------

void settings() {
  Serial.println("\n===================================\nENTERING SETTINGS\n===================================\n");

  int numOfSettingOptions = 1;
  resetPosValue();

  while (!digitalRead(butSelect)) {}

  while (SET == true) {
    if (pos != lastPos) {
      //Turns off interrupt to allow the code to finish before another value can be checked
      noInterrupts();  
      if (pos < 0) pos = numOfSettingOptions;
      else if (pos > numOfSettingOptions) pos = 0;
      Serial.print("position: ");
      Serial.println(pos);
      updateSettingsButtons();
      lastPos = pos;
      interrupts();
    }

    if (!digitalRead(butSelect)) {
      curButtonTime = millis();
      prevButtonTime = curButtonTime;
      while (!digitalRead(butSelect)) {
        curButtonTime = millis();
        if ((curButtonTime - prevButtonTime) >= 2000) {
          SET = false;
          MM = true;
          break;
        }
      }
      if (!MM) {
        SUBSET = true;
        if (pos == 0) {
          SS_SwapScreen();
          subSetSwap();
        }
        else if (pos == 1) {
          SS_PrimeScreen();
          subSetPrime();
        }
      }      
    }
  }
  Serial.print("END OF SETTINGS\nSET: ");
  Serial.println(SET);
}


//For subSet menus
void printCurrentIngInfo() {
  myGLCD.setColor(OFF_BLACK);
  myGLCD.fillRect(160, 84, 319, 96);
  myGLCD.setColor(OFF_WHITE);
  myGLCD.setBackColor(OFF_BLACK);
  myGLCD.print(pumps[pos], 160, 84);
}
