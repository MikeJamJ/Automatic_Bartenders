/*
   Creator:
      Michael Jamieson
   Date of last Update:
      07/09/2019
   Description:
      Function for changing the Ingredient currently associated with a pump to a new one from
      the list of Ingredients
*/

//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------

void SubSet_Swap() {
#if PRINT_TO_SERIAL
  Serial.println(F("\n===================================\nENTERING SWAP\n===================================\n"));
#endif

  uint8_t lastButton = 0;
  drawSubSet_Swap();
  resetPosValue();
  while (!digitalRead(butSelect)) {} // wait until button not held

  while (b_SUBSET == true) {
    if (pos != lastPos) {
      noInterrupts();
      if (pos < 0) pos = numOfPumps - 1;
      else if (pos > numOfPumps - 1) pos = 0;
      serialPrintPosValue();
      updatePumpSelectionButton(1);
      updateIngredientSelection(0);
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
        drawPumpSelectionButton(0);
        updatePumpSelectionButton(0);
        drawIngredientSelection(1);
        swapIngredient(pos);
        pos = lastButton;
        lastPos = pos;
        drawPumpSelectionButton(1);
        updatePumpSelectionButton(1);
        drawIngredientSelection(0);
        updateIngredientSelection(0);
      }
    }
  }

  drawSettingsMenu();
  resetPosValue();
  while (!digitalRead(butSelect)) {}
}

/*
   Allows the current ingredient associated with a pump to be changed

   @param curPump   pump to be changed
*/
void swapIngredient (int curPump) {
#if PRINT_TO_SERIAL
  Serial.println(F("\n===================================\nENTERING SUBSWAP\n===================================\n"));
#endif

  bool SWAP = true;

  // find the Ingredient in the list that matches the one associated with the passed pump 'curPump'
  for (byte i = 0; i < sizeOfIngList; i++) {
    if (IngredientList[i].getIngName() == pumps[curPump].value) {
      pos = i;
      lastPos = pos;
      break;
    }
  }
  updateIngredientSelection(1);

  while (!digitalRead(butSelect)) {}  // wait until button not held

  while (SWAP == true) {
    if (pos != lastPos) {
      noInterrupts();
      if (pos < 0) pos = sizeOfIngList - 1;
      else if (pos > sizeOfIngList - 1) pos = 0;
      serialPrintPosValue();
      updateIngredientSelection(1);
      lastPos = pos;
      interrupts();
    }

    if (!digitalRead(butSelect)) {
      curButtonTime = millis();
      prevButtonTime = curButtonTime;
      while (!digitalRead(butSelect)) {
        curButtonTime = millis();
        if ((curButtonTime - prevButtonTime) >= 2000) {
          SWAP = false;
          break;
        }
      }
      if (SWAP) {
        pumps[curPump].value = IngredientList[pos].getIngName();
        SWAP = false;
      }
    }
  }
}
