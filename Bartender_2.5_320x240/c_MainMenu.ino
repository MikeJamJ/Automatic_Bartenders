/*
   Main Menu of the system where drinks can be selected:
   mainMenu();
   printDrinkInfo();
*/

//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------

void mainMenu() {
  Serial.println("\n===================================\nENTERING MENU\n===================================\n");

  //Empty drink array for the ones that are displayed on the screen
  Drink possibleDrinks[] = {
    defaultDrink, //1
    defaultDrink, //2
    defaultDrink, //3
    defaultDrink, //4
    defaultDrink, //5
    defaultDrink, //6
    defaultDrink, //7
    defaultDrink, //8
    defaultDrink, //9
    defaultDrink, //10
    defaultDrink, //11
    defaultDrink, //12
    defaultDrink  //13
  };
  DrinkList possible_drinks(possibleDrinks, (sizeof(possibleDrinks) / sizeof(possibleDrinks[0])));
  mainMenuSetup(possible_drinks);

  resetPosValue();
  printDrinkInfo(possible_drinks);

  while (!digitalRead(butSelect)) {}

  while (MM == true) {
    //Serial.println(digitalRead(butSelect));
    if (pos != lastPos) {
      //Turns off interrupt to allow the code to finish before another value can be checked
      noInterrupts();   
      if (pos < 0) pos = endOfDrinkList;
      else if (pos > endOfDrinkList) pos = 0;
      Serial.print("position: ");
      Serial.println(pos);
      printDrinkInfo(possible_drinks);
      lastPos = pos;
      interrupts();
    }
    //If the user presses the select button, the drink that is currently being displayed will be made
    if (!digitalRead(butSelect)) {
      curButtonTime = millis();
      /*
        This checks for a long or short button press. If the button is released
        under 2 seconds, a drink is made. If the button is held for more than 2
        seconds, the system goes to the Settings menu
      */
      prevButtonTime = curButtonTime;
      while (!digitalRead(butSelect)) {
        curButtonTime = millis();
        if ((curButtonTime - prevButtonTime) >= 2000)
        {
          MM = false;
          SET = true;
          break;
        }
      }
      if (!SET) {
        Serial.println("===================================\nMAKING DRINK\n===================================\n");
        printMakingDrink();
        makeDrink();
        printDrinkInfo(possible_drinks);
      }
    }
  }
  Serial.print("END OF MENU\nMM: ");
  Serial.println(MM);
}


//Prints out drink name, total volume, ingredients, and type onto the screen
void printDrinkInfo(DrinkList possible_drinks) {
  int ingPosY = 106;
  choice = possible_drinks.getDrink(pos);

  //Overwrites area where information will be added
  myGLCD.setColor(OFF_BLACK);
  myGLCD.fillRect(0, 30, 319, 239);
  myGLCD.drawBitmap(15, 63, 90, 160, margarita_img);

  //Print Drink Name and Total Volume
  myGLCD.setColor(OFF_WHITE);
  myGLCD.setBackColor(OFF_BLACK);

  myGLCD.setFont(BigFont);
  myGLCD.print(choice.getDrinkName(), CENTER, 30);

  myGLCD.setFont(SmallFont);
  myGLCD.printNumI(choice.calcTotalVol(), 264, 217, 3, " ");
  myGLCD.print(" ml", 290, 217);

  myGLCD.print("Ingredients:", 123, 84);
  myGLCD.drawLine(123, 97, 214, 97);

  //Print ingredients in a list
  for (int i = 0; i < choice.getSize(); i++) {
    myGLCD.print(choice.getIngredient(i).getIngName(), 123, (ingPosY + (12 * i)));
  }

  if (choice.getType() == 'N') {
    myGLCD.print("Non-Alcoholic", 195, 51);
  }
}
