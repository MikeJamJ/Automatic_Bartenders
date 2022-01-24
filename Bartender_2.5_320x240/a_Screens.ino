/*
   Functions for drawing the various screens for the 320x240 UTFT display:
   displayLogo();
   menuScreen();
   settingsScreen();
   sorryScreen();
*/

//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------


//Dislpays logo
void displayLogo() {
  myGLCD.fillScr(OFF_BLACK);

  //Product Name
  myGLCD.setColor(OFF_WHITE);
  myGLCD.setBackColor(OFF_BLACK);
  myGLCD.setFont(BigFont);
  myGLCD.print("PROFESSOR", CENTER, 99);
  myGLCD.print("SMIRNOFF", CENTER, 123);
}


//Draws Home screen of the bartender which displays the drink name, ingredients, and total volume
void menuScreen() {
  myGLCD.fillScr(OFF_BLACK);

  //Top Banner
  myGLCD.setColor(OFF_WHITE);
  myGLCD.fillRect(0, 0, 319, 15);
  myGLCD.setColor(OFF_BLACK);
  myGLCD.setBackColor(OFF_WHITE);
  myGLCD.setFont(SmallFont);
  myGLCD.print("PROFESSOR SMIRNOFF", CENTER, 3);
}


//Displays the settings screen
void settingsScreen() {
  myGLCD.clrScr();
  myGLCD.fillScr(OFF_BLACK);
  myGLCD.setFont(SmallFont);

  //Top Banner
  myGLCD.setColor(OFF_WHITE);
  myGLCD.fillRect(0, 0, 319, 15);
  myGLCD.setColor(OFF_BLACK);
  myGLCD.setBackColor(OFF_WHITE);
  myGLCD.print("SETTINGS", CENTER, 3);

  //Button outlines
  myGLCD.setColor(SM_LIGHT_GREY);
  myGLCD.fillRect(0, 26, 299, 27);
  myGLCD.fillRect(0, 59, 299, 62);
  myGLCD.fillRect(0, 94, 299, 95);
  myGLCD.fillRect(300, 26, 301, 95);

  //Swap button
  myGLCD.setColor(OFF_WHITE);
  myGLCD.fillRect(0, 28, 299, 58);
  myGLCD.setColor(OFF_BLACK);
  myGLCD.setBackColor(OFF_WHITE);
  myGLCD.print("Swap Ingredients", 7, 38);
  myGLCD.drawLine(271, 34, 287, 43);
  myGLCD.drawLine(271, 52, 287, 43);

  //Prime Button
  myGLCD.setColor(SM_DARK_GREY);
  myGLCD.fillRect(0, 63, 299, 93);
  myGLCD.setColor(OFF_WHITE);
  myGLCD.setBackColor(SM_DARK_GREY);
  myGLCD.print("Prime / Run Pump", 7, 73);
  myGLCD.drawLine(271, 69, 287, 78);
  myGLCD.drawLine(271, 87, 287, 78);
}


void updateSettingsButtons() {
  myGLCD.setFont(SmallFont);
  switch (pos) {
    case 0:
      //Swap button turns white
      myGLCD.setColor(OFF_WHITE);
      myGLCD.fillRect(0, 28, 299, 58);
      myGLCD.setColor(OFF_BLACK);
      myGLCD.setBackColor(OFF_WHITE);
      myGLCD.print("Swap Ingredients", 7, 38);
      myGLCD.drawLine(271, 34, 287, 43);
      myGLCD.drawLine(271, 52, 287, 43);

      //Prime Button turns black
      myGLCD.setColor(SM_DARK_GREY);
      myGLCD.fillRect(0, 63, 299, 93);
      myGLCD.setColor(OFF_WHITE);
      myGLCD.setBackColor(SM_DARK_GREY);
      myGLCD.print("Prime / Run Pump", 7, 73);
      myGLCD.drawLine(271, 69, 287, 78);
      myGLCD.drawLine(271, 87, 287, 78);
      break;
    case 1:
      //Swap button turns Grey
      myGLCD.setColor(SM_DARK_GREY);
      myGLCD.fillRect(0, 28, 299, 58);
      myGLCD.setColor(OFF_WHITE);
      myGLCD.setBackColor(SM_DARK_GREY);
      myGLCD.print("Swap Ingredients", 7, 38);
      myGLCD.drawLine(271, 34, 287, 43);
      myGLCD.drawLine(271, 52, 287, 43);

      //Prime Button turns White
      myGLCD.setColor(OFF_WHITE);
      myGLCD.fillRect(0, 63, 299, 93);
      myGLCD.setColor(OFF_BLACK);
      myGLCD.setBackColor(OFF_WHITE);
      myGLCD.print("Prime / Run Pump", 7, 73);
      myGLCD.drawLine(271, 69, 287, 78);
      myGLCD.drawLine(271, 87, 287, 78);
      break;
    default:
      Serial.println("Invalid pos variable");
      break;
  }
}


void SS_SwapScreen() {
  myGLCD.setColor(OFF_BLACK);
  myGLCD.fillRect(0, 16, 319, 239);

  myGLCD.setColor(OFF_WHITE);
  myGLCD.fillRect(0, 28, 49, 58);
  myGLCD.setColor(SM_LIGHT_GREY);
  myGLCD.fillRect(0, 26, 49, 27);
  myGLCD.fillRect(0, 59, 49, 60);
  myGLCD.fillRect(50, 26, 51, 60);
  myGLCD.setColor(OFF_BLACK);
  myGLCD.setBackColor(OFF_WHITE);
  myGLCD.print("Swap", 7, 38);

  myGLCD.setColor(OFF_WHITE);
  myGLCD.setBackColor(OFF_BLACK);
  myGLCD.print("Current Ingredient:", 150, 64);
}


void SS_PrimeScreen() {
  myGLCD.setColor(OFF_BLACK);
  myGLCD.fillRect(0, 16, 319, 239);

  myGLCD.setColor(OFF_WHITE);
  myGLCD.fillRect(0, 63, 49, 93);
  myGLCD.setColor(SM_LIGHT_GREY);
  myGLCD.fillRect(0, 61, 49, 62);
  myGLCD.fillRect(0, 94, 49, 95);
  myGLCD.fillRect(50, 61, 51, 95);
  myGLCD.setColor(OFF_BLACK);
  myGLCD.setBackColor(OFF_WHITE);
  myGLCD.print("Prime", 7, 73);

  myGLCD.setColor(OFF_WHITE);
  myGLCD.setBackColor(OFF_BLACK);
  myGLCD.print("Current Ingredient:", 150, 64);
}


void printPumpButtons() {
  int x = 62;
  int y = 26;
  myGLCD.setFont(SmallFont);
  for (int i = 0; i < 6; i++) {
    myGLCD.setColor(SM_LIGHT_GREY);
    myGLCD.fillRect(x, (y + (i * 27)), 128, (y + ((i + 1) * 27) - 1));
    myGLCD.setColor(SM_DARK_GREY);
    if (i == 0) {
      myGLCD.setColor(OFF_WHITE);
    }
    myGLCD.fillRect(x + 2, y + 2 + (i * 27), x + 64, (y + 24 + (i * 27)));
    myGLCD.setBackColor(SM_DARK_GREY);
    myGLCD.setColor(OFF_WHITE);
    if (i == 0) {
      myGLCD.setBackColor(OFF_WHITE);
      myGLCD.setColor(OFF_BLACK);
    }
    myGLCD.print("Pump ", (x + 10), (y + 8 + (i * 27)));
    myGLCD.printNumI(i + 1, (x + 55), (y + 8 + (i * 27)));
  }
}


void updatePumpButtons(int lastButton) {
  int x = 62;
  int y = 26;
  myGLCD.setFont(SmallFont);

  //Change previous Button
  myGLCD.setColor(SM_DARK_GREY);
  myGLCD.fillRect(x + 2, y + 2 + (lastButton* 27), x + 64, (y + 24 + (lastButton* 27)));
  myGLCD.setBackColor(SM_DARK_GREY);
  myGLCD.setColor(OFF_WHITE);
  myGLCD.print("Pump ", (x + 10), (y + 8 + (lastButton* 27)));
  myGLCD.printNumI(lastButton+ 1, (x + 55), (y + 8 + (lastButton* 27)));

  //Change to selected button
  myGLCD.setColor(OFF_WHITE);
  myGLCD.fillRect(x + 2, y + 2 + (pos* 27), x + 64, (y + 24 + (pos* 27)));
  myGLCD.setBackColor(OFF_WHITE);
  myGLCD.setColor(OFF_BLACK);
  myGLCD.print("Pump ", (x + 10), (y + 8 + (pos* 27)));
  myGLCD.printNumI(pos+ 1, (x + 55), (y + 8 + (pos* 27)));
}


void printMakingDrink(){
  myGLCD.setColor(OFF_BLACK);
  myGLCD.fillRect(123, 84, 319, 239);
  myGLCD.setColor(OFF_WHITE);
  myGLCD.setBackColor(OFF_BLACK);
  myGLCD.setFont(BigFont);
  myGLCD.print("Drink in", 150, 112);
  myGLCD.print("Progress", 150, 130); 
}


//Displays if no drinks of the selected type are available with the current ingredients
void sorryScreen() {
  myGLCD.setColor(OFF_BLACK);
  myGLCD.fillRect(0, 16, 319, 187);
  myGLCD.setColor(OFF_WHITE);
  myGLCD.setBackColor(OFF_BLACK);
  myGLCD.print("None of this Drink Type are available", CENTER, 50);
}





