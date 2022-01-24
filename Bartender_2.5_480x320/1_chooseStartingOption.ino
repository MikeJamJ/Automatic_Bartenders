/*
   Creator:
      Michael Jamieson
   Date of last Update:
      14/11/2019
   Description:
      gives the user the ability to choose which pump values to start the program with

      choseOption() is the main loop where setIngs() is used for if the user wants to
      alter the current pump values or set brand new ones
*/

void chooseOption() {
  Serial.println(F("\n===================================\nENTERING CHOOSE OPTIONS\n===================================\n"));

  bool b_chooseOption = 1;
  bool b_useNewIngs = 0;

  drawChooseStartingOption();
  resetPosValue();

  /*
     Choose to:
     1. use previous values
     2. alter previous values
     3. use new values
  */
  while (b_chooseOption) {
    if (pos != lastPos) {
      noInterrupts(); //Turn off interrupts
      if (pos < 0) pos = 2;
      else if (pos > 2) pos = 0;
      Serial.print(F("position: "));
      Serial.println(pos);
      updateChooseStartingOptionButtons();
      lastPos = pos;
      interrupts();   //Turn on interrupts
    }

    if (!digitalRead(butSelect)) {
      curButtonTime = millis();
      if ((curButtonTime - prevButtonTime) >= 20) {
        prevButtonTime = millis();
        b_chooseOption = 0;
        switch (pos) {
          case 0:
            b_chooseOption = 0;
            break;
          case 1:
            b_useNewIngs = 1;
            setIngs();
            break;
          case 2:
            b_useNewIngs = 1;
            resetPumpValues();
            setIngs();
            break;
        }
      }
    }
  }
  Serial.println(F("END OF CHOOSE OPTIONS"));
  Serial.println(F("\n===================================\nVALUES INPUT\n===================================\n"));
}

void setIngs() {
  bool b_setIngs = 1;
  uint8_t lastButton = 0;

  drawSetIngs();
  printCurrentIngInfo();
  resetPosValue();

  while (b_setIngs) {
    if (pos != lastPos) {
      //Turns off interrupt to allow the code to finish before another value can be checked
      noInterrupts();
      if (pos < 0) pos = numOfPumps - 1 ;
      else if (pos > (numOfPumps - 1)) pos = 0;
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
        setTextSize(2);
        tft.setTextColor(TEXT_COLOR, BACKGROUND_COLOR);
        if ((curButtonTime - prevButtonTime) == 500) {
          printCenterH(F("3"), 300);
        }
        else if ((curButtonTime - prevButtonTime) == 1500) {
          printCenterH(F("2"), 300);
        }
        else if ((curButtonTime - prevButtonTime) == 2500) {
          printCenterH(F("1"), 300);
        }
        else if ((curButtonTime - prevButtonTime) >= 3500) {
          b_setIngs = 0;
          setPumpValuesToMemory();
          //setPumpValuesToSD();
          //printFileContents(pumpFileName);
          break;
        }
      }
      if (b_setIngs) {
        if ((curButtonTime - prevButtonTime) > 500) {
          tft.fillRect( ((tft.width() / 2) - (TEXT_WIDTH / 2)), 300, TEXT_WIDTH, TEXT_HEIGHT, BACKGROUND_COLOR);
        }
        swapIngredient(pos);
        Serial.println(F("Back in setIngs();"));

      }
    }
  }
}


void resetPumpValues() {
  for (uint8_t i = 0; i < numOfPumps; i++) {
    pumps[i].value = "NULL";
  }
}
