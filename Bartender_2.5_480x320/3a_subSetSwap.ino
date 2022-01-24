/*
   SS_Swap functions. Will go through the ingredient array and swap
   the current drink with the selected ingredient
*/

//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------

void SubSet_Swap() {
  Serial.println(F("\n===================================\nENTERING SWAP\n===================================\n"));

  uint8_t lastButton = 0;
  //drawPumpButtonsArray();
  //printCurrentIngInfo();

  while (b_SUBSET == true) {
    if (pos != lastPos) {
      //Turns off interrupt to allow the code to finish before another value can be checked
      noInterrupts();  
      if (pos < 0) pos = numOfPumps - 1;
      else if (pos > numOfPumps - 1) pos = 0;
      Serial.print(F("position: "));
      Serial.println(pos);
      updatePumpSelectionButton();
      //updatePumpButtonsArray(lastButton);
      //printCurrentIngInfo();
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
        swapIngredient(pos);
        Serial.println(F("Back in subset swap"));
      }
    }
  }
  Serial.print(F("END OF SWAP\nSUBSET: "));
  Serial.println(b_SUBSET);
  Serial.println(F("\n===================================\nREENTERING SETTINGS\n===================================\n"));
  resetPosValue();
  drawSettingsMenu();
  while (!digitalRead(butSelect)) {}
}


void swapIngredient (int pumpNum) {
  Serial.println(F("\n===================================\nENTERING SUBSWAP\n===================================\n"));
  bool SWAP = true;
  resetPosValue();
  tft.setCursor(150, 144);
  tft.setTextColor(TEXT_COLOR, BACKGROUND_COLOR);
  tft.print(F("New Ingredient:"));

  String ings[] = {
    "Apple Juice",
    "Bourbon",
    "Brandy",
    "Champagne",
    "Club Soda",
    "Cointreau",
    "Coke",
    "Cranberry Juice",
    "Curacao Blue",
    "Curacao Orange",
    "Gin",
    "Green Chartreuse",
    "Grenadine",
    "Kahlua",
    "Lemon Juice",
    "Lime Juice",
    "Margarita Mix",
    "Martini Mix",
    "Milk",
    "Orange Juice",
    "Pineapple Juice",
    "Rum",
    "Scotch",
    "Simple Syrup",
    "Sprite",
    "SP Apple",
    "SP Blue",
    "SP Raspberry",
    "SP Watermelon",
    "S&S Mix",
    "Tequila",
    "Vermouth (Dry)",
    "Vermouth (Sweet)",
    "Vex",
    "Vodka",
    "null"
  };
  byte sizeOfIngArray = sizeof(ings)/sizeof(ings[0]);

  printSwapInfo(ings);

  while (SWAP == true) {
    if (pos != lastPos) {
      if (pos < 0) pos = sizeOfIngArray - 1;
      else if (pos > sizeOfIngArray - 1) pos = 0;
      Serial.print(F("position: "));
      Serial.println(pos);
      printSwapInfo(ings);
      lastPos = pos;
      delay(20);
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
        pumps[pumpNum].value = ings[pos];
        SWAP = false;
      }
    }
  }
  Serial.print(F("END OF SUBSWAP\nSWAP: "));
  Serial.println(SWAP);
  Serial.println(F("\n===================================\nREENTERING SWAP\n===================================\n"));
  resetPosValue();
  resetSwap(pumpNum);
  while (!digitalRead(butSelect)) {}
}


void printSwapInfo(String ings[]) {
  tft.fillRect(160, 164, 319, 176, BACKGROUND_COLOR);
  tft.setCursor(160, 164);
  tft.setTextColor(TEXT_COLOR, BACKGROUND_COLOR);
  tft.print(ings[pos]);
}


void resetSwap(byte n){
  pos = n;
  tft.fillRect(150, 144, 319, 176, BACKGROUND_COLOR);
  printCurrentIngInfo();
}
