/*
   Creator:
      Michael Jamieson
   Date of last Update:
      14/11/2019
   Description:
      Main Menu of the system where drinks can be selected to be made.

      mainMenu() is the main loop while updateMainMenu() is used as an updater for
      updating the screen with the relevant information for the selected drink.
*/

//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------

void mainMenu() {
  Serial.println(F("\n===================================\nENTERING MENU\n===================================\n"));

  uint8_t possibleDrinksSize = masterDrinkList.findPossibleDrinksSize(pumps, numOfPumps);
  Drink possibleDrinksArray[possibleDrinksSize] = {};
  masterDrinkList.findPossibleDrinks(pumps, numOfPumps, possibleDrinksArray, possibleDrinksSize);
  DrinkList possible_drinks(possibleDrinksArray, possibleDrinksSize);
  possible_drinks.alphabetize();
#if PRINT_TO_SERIAL
  possible_drinks.serialPrintDrinks();
#endif

  resetPosValue();
  updateMainMenu(possible_drinks);

  while (!digitalRead(butSelect)) {}

  while (b_MM == true) {
    if (pos != lastPos) {
      noInterrupts(); //Turns off interrupt to allow the code to finish before another value can be checked
      if (pos < 0) pos = possibleDrinksSize - 1;
      else if (pos > (possibleDrinksSize - 1)) pos = 0;
      Serial.print(F("position: "));
      Serial.println(pos);
      updateMainMenu(possible_drinks);
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
        updateMainMenu(possible_drinks);
      }
    }
  }
  Serial.print(F("END OF MENU\nb_MM: "));
  Serial.println(b_MM);
}
