/*
   Creator:
      Michael Jamieson
   Date of last Update:
      07/09/2019
   Description:
      gives the user the ability to choose which pump values to start the program with

      choseOption() is the main loop where setIngs() is used for if the user wants to
      alter the current pump values or set new ones
*/

void chooseOption() {
#if PRINT_TO_SERIAL
  Serial.println(F("\n===================================\nENTERING CHOOSE OPTIONS\n===================================\n"));
#endif

  bool b_chooseOption = 1;
  bool b_useNewIngs = 0;

  drawChooseStartingOption();
  resetPosValue();

  /*
     Choose to:
     1. use current values
     2. alter current values
     3. use new values
  */
  while (b_chooseOption) {
    if (pos != lastPos) {
      noInterrupts(); //Turn off interrupts
      if (pos < 0)      pos = 2;
      else if (pos > 2) pos = 0;
      serialPrintPosValue();
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
#if PRINT_TO_SERIAL
  Serial.println(F("\n===================================\nEND OF CHOOSE OPTIONS\n===================================\n"));
#endif
}

void setIngs() {
#if PRINT_TO_SERIAL
  Serial.println(F("\n===================================\nENTERING SET INGS\n===================================\n"));
#endif

  bool b_setIngs = 1;
  bool b_countdown = 0;
  uint8_t lastPump = 0;

  drawSetIngs();
  resetPosValue();
  updatePumpSelectionButton(1);
  updateIngredientSelection(0);

  while (b_setIngs) {
    if (pos != lastPos) {
      //Turns off interrupt to allow the code to finish before another value can be checked
      noInterrupts();
      if (pos < 0) pos = numOfPumps - 1 ;
      else if (pos > (numOfPumps - 1)) pos = 0;
      serialPrintPosValue();
      updatePumpSelectionButton(1);
      updateIngredientSelection(0);
      lastPos = pos;
      lastPump = pos;
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
          b_countdown = 1;
          tft.fillRect(0, 300, tft.width(), tft.height() - 300, BACKGROUND_COLOR);
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
          if (b_SD_CONNECTED) setPumpValuesToSD();
          else      setPumpValuesToMemory();
          break;
        }
      }
      if (b_countdown) {
        printCenterH(F("Hold button to confirm selection"), 300);
        b_countdown = 0;
      }
      else if (b_setIngs) {
        if ((curButtonTime - prevButtonTime) > 500) {
          tft.fillRect( ((tft.width() / 2) - (TEXT_WIDTH / 2)), 300, TEXT_WIDTH, TEXT_HEIGHT, BACKGROUND_COLOR);
        }
        drawPumpSelectionButton(0);
        updatePumpSelectionButton(0);
        drawIngredientSelection(1);
        swapIngredient(pos);
        pos = lastPump;
        lastPos = pos;
        drawPumpSelectionButton(1);
        updatePumpSelectionButton(1);
        drawIngredientSelection(0);
        updateIngredientSelection(0);
      }
    }
  }
}

void resetPumpValues() {
  for (uint8_t i = 0; i < numOfPumps; i++) {
    pumps[i].value = "NULL";
  }
}
