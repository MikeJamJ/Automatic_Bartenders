/*
   Creator:
      Michael Jamieson
   Date of last Update:
      07/09/2019
   Description:
      Main Menu of the system where drinks can be selected to be made.
*/

//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------

void mainMenu() {
#if PRINT_TO_SERIAL
  Serial.println(F("\n===================================\nENTERING MENU\n===================================\n"));
#endif

  // Check for drinks to can be made. If none can be made, return to the ChooseOptions screen
  tft.fillScreen(BACKGROUND_COLOR);
  uint8_t possibleDrinksSize = findPossibleDrinksSize(pumps, numOfPumps);
  if (possibleDrinksSize == 0) {
    while (possibleDrinksSize == 0) {
      drawErrorScreen();
      delay(2000);
      chooseOption();
      possibleDrinksSize = findPossibleDrinksSize(pumps, numOfPumps);
    }
  }
  uint8_t possible_drinks[possibleDrinksSize] = {};
  findPossibleDrinks(pumps, numOfPumps, possible_drinks, possibleDrinksSize);
  alphabetize(possible_drinks, possibleDrinksSize);

#if PRINT_TO_SERIAL
  serialPrintDrinkArray(possible_drinks, possibleDrinksSize);
#endif

  drawMainMenu();
  resetPosValue();
  updateMainMenu(possible_drinks, possibleDrinksSize);
  while (!digitalRead(butSelect)) {}

  while (b_MM == true) {
    if (pos != lastPos) {
      noInterrupts();
      if (pos < 0)                              pos = possibleDrinksSize - 1;
      else if (pos > (possibleDrinksSize - 1))  pos = 0;
      serialPrintPosValue();
      updateMainMenu(possible_drinks, possibleDrinksSize);
      lastPos = pos;
      interrupts();
    }
    if (!digitalRead(butSelect)) {  //Check for button press
      curButtonTime = millis();
      prevButtonTime = curButtonTime;
      while (!digitalRead(butSelect)) {
        curButtonTime = millis();
        if ((curButtonTime - prevButtonTime) >= 2000) //If button is held for more than 2 seconds, exit to settings
        {
          b_MM = false;
          b_SET = true;
          break;
        }
      }
      if (!b_SET) {   //If button is held less than 2 seconds, make the drink
        drawDrinkInProgress();
        makeDrink();
        drawDrinkComplete();
        updateMainMenu(possible_drinks, possibleDrinksSize);
        tft.setTextColor(TEXT_COLOR, BACKGROUND_COLOR);
        printCenterH(F("Select to make drink"), 295);
      }
    }
  }
}
