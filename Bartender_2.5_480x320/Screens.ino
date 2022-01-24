/*
   Creator:
      Michael Jamieson
   Date of last Update:
      07/09/2019
   Description:
      Functions for drawing the various information to the
      480x320 TFT display.

      Classic GFX font is;
      setTextSize(1) = 6x8 pixels
      setTextSize(2) = 12x16 pixels
      setTextSize(3) = 18x24 pixels
*/

//================================================================================
// TEXT FUNCTIONS
//================================================================================

/*
   Sets the text size for displaying
   updates global TEXT_WIDTH and TEXT_HEIGHT variables

   @param s   desired size of text
*/
void setTextSize(uint8_t s) {
  uint8_t defaultWidth = 6;
  uint8_t defaultHeight = 8;
  tft.setTextSize(s);
  TEXT_HEIGHT = defaultHeight * s;
  TEXT_WIDTH = defaultWidth * s;
}

/*
   Prints a string centered vertically given an x coordinate

   @param str   desired string to print
   @param x     coordinate of center of text to print at
*/
void printCenterV(String str, int x) {
  tft.setCursor(x, ((tft.height() / 2) - (TEXT_HEIGHT / 2)));
  tft.print(str);
}

/*
   Prints a string centered horizontally given an y coordinate

   @param str   desired string to print
   @param x     coordinate of center of text to print at
*/
void printCenterH(String str, int y) {
  tft.setCursor((tft.width() / 2) - ((str.length() * TEXT_WIDTH) / 2), y);
  tft.print(str);
}


//================================================================================
// SCREEN DRAW FUNCTIONS
//================================================================================

void drawLogo() {
  tft.fillScreen(BACKGROUND_COLOR);

  setTextSize(3);
  tft.setTextColor(TEXT_COLOR);
  printCenterH(F("PROFESSOR"), ((tft.height() / 2) - 24));
  printCenterH(F("SMIRNOFF"), ((tft.height() / 2) + 2));
  delay(2000);
}

void drawChooseStartingOption() {
  tft.fillScreen(BACKGROUND_COLOR);

  //Top banner
  setTextSize(2);
  tft.setCursor(27, 14);
  tft.print(F("Setup"));
  tft.drawFastHLine(3, 41, 473, TEXT_COLOR);

  //Buttons
  drawButton(UseCurrent, 1, 0);
  drawButton(AlterCurrent, 0, 0);
  drawButton(SetNew, 0, 0);

  //Current values
  tft.setCursor(237, 65);
  tft.setTextColor(TEXT_COLOR, BACKGROUND_COLOR);
  tft.print(F("Pump:"));
  printPumpValues(237, 90, 28, 10, TEXT_COLOR, BACKGROUND_COLOR);
}

void drawSetIngs() {
  tft.fillRect(0, 42, tft.width(), tft.height() - 42, BACKGROUND_COLOR);
  setTextSize(2);
  tft.setTextColor(TEXT_COLOR, BACKGROUND_COLOR);
  printCenterH(F("SELECT PUMP VALUES"), 55);
  printCenterH(F("Hold button to confirm selection"), 300);
  drawPumpSelectionButton(1);
  drawIngredientSelection(0);
}

void drawMainMenu() {
  tft.fillScreen(BACKGROUND_COLOR);

  //Top banner
  setTextSize(2);
  tft.setTextColor(TEXT_COLOR, BACKGROUND_COLOR);
  tft.setCursor(27, 14);
  tft.print(F("Main Menu"));
  tft.drawFastHLine(3, 41, 473, TEXT_COLOR);

  tft.fillRect(239, 83, 2, 20, TEXT_COLOR);
  printCenterH(F("Select to make drink"), 295);

  //Scroll buttons
  drawButton(MainMenuLeft, 0);
  drawButton(MainMenuRight, 0);

  //Ingredient section
  setTextSize(2);
  tft.setCursor(221, 118);
  tft.print(F("Ingredients:"));
}

void drawSettingsMenu() {
  tft.fillScreen(BACKGROUND_COLOR);

  //Top banner
  tft.fillRect((27 + 96), 14, 200, 16, BACKGROUND_COLOR);
  setTextSize(2);
  tft.setCursor(27, 14);
  tft.setTextColor(TEXT_COLOR, BACKGROUND_COLOR);
  tft.print(F("Settings"));
  tft.drawFastHLine(3, 41, 473, TEXT_COLOR);

  //Setting buttons
  drawButton(Swap, 1, 0);
  drawButton(Run, 0, 0);
}

void drawSubSet_Swap() {
  //Top banner
  setTextSize(2);
  tft.setCursor((27 + 96), 14);
  tft.setTextColor(TEXT_COLOR, BACKGROUND_COLOR);
  tft.print(F(" > Swap Ingredients"));

  //Overwrite data
  tft.fillRect(71, 70, 338, 200, BACKGROUND_COLOR);

  tft.setTextColor(0xF800, BACKGROUND_COLOR);
  printCenterH(F("Select pump and ingredient"), 60);
  drawPumpSelectionButton(1);
  updatePumpSelectionButton(1);
  drawIngredientSelection(0);
  updateIngredientSelection(0);
}

void drawSubSet_Run() {
  //Top banner
  setTextSize(2);
  tft.setCursor((27 + 96), 14);
  tft.setTextColor(TEXT_COLOR, BACKGROUND_COLOR);
  tft.print(F(" > Run Pump"));

  //Overwrite data
  tft.fillRect(71, 70, 338, 200, BACKGROUND_COLOR);

  tft.setTextColor(0xF800, BACKGROUND_COLOR);
  printCenterH(F("Select pump to run"), 60);
  drawPumpSelectionButton(1);
  updatePumpSelectionButton(1);
}

void drawRunPump() {
  tft.fillRect( ((tft.width() / 2) - (TEXT_WIDTH * 18 / 2)), 60, TEXT_WIDTH * 18, TEXT_HEIGHT, BACKGROUND_COLOR);
  setTextSize(2);
  tft.setCursor(163, 144);
  tft.setTextColor(0xF800, BACKGROUND_COLOR);
  printCenterH(F("Hold to run pump"), 60);
  printCenterH(F("Exiting in  "), 300);
}

void reset_Run() {
  tft.fillRect( ((tft.width() / 2) - (TEXT_WIDTH * 16 / 2)), 60, TEXT_WIDTH * 16, TEXT_HEIGHT, BACKGROUND_COLOR);
  tft.fillRect( ((tft.width() / 2) - (TEXT_WIDTH * 12 / 2)), 300, TEXT_WIDTH * 12, TEXT_HEIGHT, BACKGROUND_COLOR);
  tft.setTextColor(0xF800, BACKGROUND_COLOR);
  printCenterH(F("Select pump to run"), 60);
}

void drawDrinkInProgress() {
  //Cover ingredients and bottom prompt
  tft.fillRect(221, 118, 200, 150, BACKGROUND_COLOR);
  tft.fillRect(0, 293, 480, 16, BACKGROUND_COLOR);

  //Print progress info
  setTextSize(2);
  tft.setTextColor(TEXT_COLOR, BACKGROUND_COLOR);
  tft.setCursor(237, 155);
  tft.print(F("Preparing Drink"));

  //Draw prorgess bar
  tft.fillRect(235, 183, 183, 28, TEXT_COLOR);
  tft.fillRect(237, 185, 179, 24, BACKGROUND_COLOR);
}

void drawDrinkComplete() {
  setTextSize(2);
  tft.setCursor(281, 233);
  tft.setTextColor(0x1CC5, BACKGROUND_COLOR);
  tft.print(F("ENJOY!"));
  delay(2000);

  //Cover ingredients and bottom prompt
  tft.fillRect(221, 118, 200, 150, BACKGROUND_COLOR);
  tft.fillRect(0, 293, 480, 16, BACKGROUND_COLOR);

  //Ingredient section
  setTextSize(2);
  tft.setTextColor(TEXT_COLOR, BACKGROUND_COLOR);
  tft.setCursor(221, 118);
  tft.print(F("Ingredients:"));
}

void drawErrorScreen() {
  setTextSize(3);
  tft.setTextColor(TEXT_COLOR, BACKGROUND_COLOR);
  printCenterH(F("NO POSSIBLE DRINKS"), tft.height() / 4);
  setTextSize(2);
  printCenterH(F("Bringing you back to"), tft.height() / 2);
  printCenterH(F("choosing Ingredients"), (tft.height() / 2) + 20);
}

//================================================================================
// BUTTON DRAWING FUNCTIONS
//================================================================================

/*
   Draws a 'ButtonRect' struct to the screen

   @param button    desired button struct to draw
   @param selected  boolean of whether the button is currently selected
   @param updated   boolean of whether the button has been updated
*/
void drawButton(ButtonRect button, boolean selected, boolean updated) {
  setTextSize(button.textSize);
  if (!updated) tft.fillRect(button.x, button.y, button.width, button.height, button.borderColor);
  switch (selected) {
    case 0:
      tft.fillRect(button.x + button.border, button.y + button.border, button.width - (2 * button.border), button.height - (2 * button.border), button.baseColor);
      tft.setTextColor(button.textColor, button.baseColor);
      break;
    case 1:
      tft.fillRect(button.x + button.border, button.y + button.border, button.width - (2 * button.border), button.height - (2 * button.border), button.selectColor);
      tft.setTextColor(button.textColor, button.selectColor);
      break;
  }
  tft.setCursor(((button.x + (button.width / 2)) - ((TEXT_WIDTH * button.string.length()) / 2)) , ((button.y + (button.height / 2)) - (TEXT_HEIGHT / 2)));
  tft.print(button.string);
}

/*
   Draws a 'ButtonTri' struct to the screen

   @param button    desired button struct to draw
   @param selected  boolean of whether the button is currently selected
*/
void drawButton(ButtonTri button, boolean selected) {
  switch (selected) {
    case 0:
      tft.fillTriangle(button.x1, button.y1, button.x2, button.y2, button.x3, button.y3, button.baseColor);
      break;
    case 1:
      tft.fillTriangle(button.x1, button.y1, button.x2, button.y2, button.x3, button.y3, button.selectColor);
      break;
  }
}

/*
   Prints list of the values associated with all pumps

   @param x, y        coordinates of top left of the start of the list
   @param xSpace      spacing from number pump value
   @param ySpace      spacing between list items
   @param textColor   color of text
   @param backColor   background color of text
*/
void printPumpValues(int x, int y, int xSpace, int ySpace, uint16_t textColor, uint16_t backColor) {
  setTextSize(2);
  tft.setTextColor(textColor, backColor);
  for (uint8_t i = 0; i < numOfPumps; i++) {
    tft.setCursor(x, y + ((TEXT_HEIGHT + ySpace) * i));
    tft.print(String(i + 1) + ".");
    tft.setCursor(x + xSpace, y + ((TEXT_HEIGHT + ySpace) * i));
    tft.print(pumps[i].value);
  }
}

void drawPumpSelectionButton(bool selected) {
  // draw Pump label regardless
  setTextSize(2);
  tft.setCursor(55, 94);
  tft.setTextColor(TEXT_COLOR, BACKGROUND_COLOR);
  tft.print(F("Pump:"));

  switch (selected) {
    case 0:
      tft.fillRect(55, 122, 370, 53, BACKGROUND_COLOR);
      setTextSize(3);
      tft.setCursor(186, 137);
      tft.setTextColor(TEXT_COLOR, BACKGROUND_COLOR);
      tft.print(F("Pump"));
      break;
    case 1:
      tft.fillRect(55, 122, 370, 53, BORDER_COLOR);
      tft.fillRect(58, 125, 364, 47, SECOND_COLOR);
      setTextSize(3);
      tft.setCursor(186, 137);
      tft.setTextColor(TEXT_COLOR, SECOND_COLOR);
      tft.print(F("Pump"));

      drawButton(PumpScrollLeft, 0);
      drawButton(PumpScrollRight, 0);
      break;
  }
}

void drawIngredientSelection(bool selected) {
  // draw ingredient label regardless
  setTextSize(2);
  tft.setCursor(55, 194);
  tft.setTextColor(TEXT_COLOR, BACKGROUND_COLOR);
  tft.print(F("Current Ingredient:"));

  switch (selected) {
    case 0:
      tft.fillRect(55, 218, 370, 53, BACKGROUND_COLOR);
      break;
    case 1:
      tft.fillRect(55, 218, 370, 53, BORDER_COLOR);
      tft.fillRect(58, 221, 364, 47, SECOND_COLOR);

      drawButton(IngredientScrollLeft, 0);
      drawButton(IngredientScrollRight, 0);
      break;
  }
}


//================================================================================
// SCREEN UPDATE FUNCTIONS
//================================================================================

void updateChooseStartingOptionButtons() {
  if (pos == 0) {
    drawButton(UseCurrent, 1, 1);                           //Use Current button selected
    if (lastPos == 1) drawButton(AlterCurrent, 0, 1);       //Alter Current button deselected
    else if (lastPos == 2) drawButton(SetNew, 0, 1);        //Set New button deselected
  }
  else if (pos == 1) {
    drawButton(AlterCurrent, 1, 1);                         //Alter Current button selected
    if (lastPos == 0) drawButton(UseCurrent, 0, 1);         //Use Current button deselected
    else if (lastPos == 2) drawButton(SetNew, 0, 1);        //Set New button deselected
  }
  else if (pos == 2) {
    drawButton(SetNew, 1, 1);                               //Set New button selected
    if (lastPos == 0) drawButton(UseCurrent, 0, 1);         //Use Current button deselected
    else if (lastPos == 1) drawButton(AlterCurrent, 0, 1);  //Alter Current button deselected
  }
}

void updateMainMenu(uint8_t drinks[], uint8_t arraySize) {
  Serial.print(F("freeMemory at update = "));
  Serial.println(freeMemory());
  Serial.print(F("\n"));

  int volPosX = 257;
  uint8_t volPosY = 84;
  uint8_t perPosX = 223;
  uint8_t perPosY = 84;
  uint8_t ingPosX = 235;
  uint8_t ingPosY = 143;
  uint8_t ingSpace = 2;

  String tempVol = String(choice.getTotalVol()) + F(" ml");
  String tempPercent = String(int(choice.getTotalPercentAlc())) + F("% alc");

  //Overwrite previous drink info
  setTextSize(3);
  tft.fillRect( ((tft.width() / 2) - ((TEXT_WIDTH * choice.getDrinkName().length()) / 2)), 53, (TEXT_WIDTH * choice.getDrinkName().length()), TEXT_HEIGHT, BACKGROUND_COLOR); //Overwrites area where information will be added
  setTextSize(2);
  tft.fillRect((perPosX - (tempPercent.length() * TEXT_WIDTH)), perPosY, (tempPercent.length() * TEXT_WIDTH), TEXT_HEIGHT, BACKGROUND_COLOR);
  tft.fillRect(volPosX, volPosY, (tempVol.length() * TEXT_WIDTH), TEXT_HEIGHT, BACKGROUND_COLOR);
  tft.fillRect(ingPosX, ingPosY, (TEXT_WIDTH * 30), (choice.getSize() * (TEXT_HEIGHT + ingSpace)), BACKGROUND_COLOR);

  //Color the arrows according to which direction you turned
  if (lastPos > pos) {
    if (lastPos == (arraySize - 1) && pos == 0) {
      drawButton(MainMenuRight, 1);
    } else {
      drawButton(MainMenuLeft, 1);
    }
  }
  else if (lastPos < pos) {
    if (pos == (arraySize - 1) && lastPos == 0) {
      drawButton(MainMenuLeft, 1);
    } else {
      drawButton(MainMenuRight, 1);
    }
  }

  //Change choice to next drink
  choice = masterDrinkList[drinks[pos]];

  //Print new drink info
  setTextSize(3);
  tft.setTextColor(TEXT_COLOR, BACKGROUND_COLOR);
  printCenterH(choice.getDrinkName(), 53);
  setTextSize(2);
  tempVol = String(choice.getTotalVol()) + F(" ml");
  tft.setCursor(volPosX, volPosY);
  tft.print(tempVol);
  tempPercent = String(int(choice.getTotalPercentAlc())) + F("% alc");
  tft.setCursor((perPosX - (tempPercent.length() * TEXT_WIDTH)), perPosY);
  tft.print(tempPercent);

  //Print ingredients
  tft.setTextColor(SECOND_COLOR, BACKGROUND_COLOR);
  for (int i = 0; i < choice.getSize(); i++) {
    tft.setCursor(ingPosX, (ingPosY + ((TEXT_HEIGHT + ingSpace) * i)));
    tft.print(choice.getIngredient(i).getIngName());
  }

  // Draw drink image
  if (!b_SD_CONNECTED) {
    tft.drawLine(73, 120, 73 + IMAGE_W, 120 + IMAGE_H, 0xF800);
    tft.drawLine(73, 120 + IMAGE_H, 73 + IMAGE_W, 120 , 0xF800);
  } else {
    if (choice.image == "default" && masterDrinkList[drinks[lastPos]].image == "default") {
      //do nothing
    } else {
      uint8_t ret = showBMP((choice.image + ".bmp"), 73, 120);
      if (ret != 0) {
        tft.drawLine(73, 120, 73 + IMAGE_W, 120 + IMAGE_H, 0xF800);
        tft.drawLine(73, 120 + IMAGE_H, 73 + IMAGE_W, 120, 0xF800);
        serialPrintSDImageError(ret);
      }
    }
  }

  //Reset scroll arrows
  drawButton(MainMenuLeft, 0);
  drawButton(MainMenuRight, 0);
}

int updateDrinkProgressBar(int timeSegments, unsigned long startTime, int lastBarDrawn) {
  if ((millis() - startTime) / timeSegments != lastBarDrawn) {
    lastBarDrawn = (millis() - startTime) / timeSegments;
    tft.fillRect((240 + (22 * (lastBarDrawn - 1))), 188, 19, 18, SECOND_COLOR);
  }
}

void updateSettingsButtons() {
  switch (pos) {
    case 0:
      drawButton(Swap, 1, 1); //Swap button selected
      drawButton(Run, 0, 1);  //Prime button deselected
      break;
    case 1:
      drawButton(Swap, 0, 1); //Swap button deselected
      drawButton(Run, 1, 1);  //Prime button selected
      break;
    default:
#if PRINT_TO_SERIAL
      Serial.println(F("Invalid pos variable"));
#endif
      pos = 0;
      break;
  }
}

void updatePumpSelectionButton(boolean selected) {
  setTextSize(3);
  switch (selected) {
    case 0:
      tft.setTextColor(TEXT_COLOR, BACKGROUND_COLOR);
      tft.setCursor(286, 137);
      tft.print(pos + 1);
      break;
    case 1:
      if (lastPos > pos) {
        if (lastPos == (numOfPumps - 1) && pos == 0) {
          drawButton(PumpScrollRight, 1);
        } else {
          drawButton(PumpScrollLeft, 1);
        }
      }
      else if (lastPos < pos) {
        if (pos == (numOfPumps - 1) && lastPos == 0) {
          drawButton(PumpScrollLeft, 1);
        } else {
          drawButton(PumpScrollRight, 1);
        }
      }

      tft.setTextColor(TEXT_COLOR, SECOND_COLOR);
      tft.setCursor(286, 137);
      tft.print(pos + 1);
      drawButton(PumpScrollLeft, 0);
      drawButton(PumpScrollRight, 0);
      break;
  }
}

void updateIngredientSelection(boolean selected) {
  setTextSize(3);
  switch (selected) {
    case 0:
      tft.setTextColor(TEXT_COLOR, BACKGROUND_COLOR);
      tft.fillRect(((tft.width() / 2) - ((pumps[lastPos].value.length() * TEXT_WIDTH) / 2)), 232, (pumps[lastPos].value.length() * TEXT_WIDTH), TEXT_HEIGHT, BACKGROUND_COLOR);
      printCenterH(pumps[pos].value, 232);
      break;
    case 1:
      if (lastPos > pos) {
        if (lastPos == (sizeOfIngList - 1) && pos == 0) {
          drawButton(IngredientScrollRight, 1);
        } else {
          drawButton(IngredientScrollLeft, 1);
        }
      }
      else if (lastPos < pos) {
        if (pos == (sizeOfIngList - 1) && lastPos == 0) {
          drawButton(IngredientScrollLeft, 1);
        } else {
          drawButton(IngredientScrollRight, 1);
        }
      }
      tft.setTextColor(TEXT_COLOR, SECOND_COLOR);
      tft.fillRect(((tft.width() / 2) - ((IngredientList[lastPos].getIngName().length() * TEXT_WIDTH) / 2)), 232, (IngredientList[lastPos].getIngName().length() * TEXT_WIDTH), TEXT_HEIGHT, SECOND_COLOR);
      printCenterH(IngredientList[pos].getIngName(), 232);
      drawButton(IngredientScrollLeft, 0);
      drawButton(IngredientScrollRight, 0);
      break;
  }
}
