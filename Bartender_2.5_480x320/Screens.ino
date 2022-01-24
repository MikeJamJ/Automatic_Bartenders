/*
   Functions for drawing the various information to the 
   480x320 TFT display:

   ****Classic GFX font is;
   setTextSize(1) = 6x8 pixels
   setTextSize(2) = 12x16 pixels
   setTextSize(3) = 18x24 pixels
*/


/*
 * 
 * Functions for printing text
 * 
 */
void setTextSize(uint8_t s) {
  uint8_t defaultWidth = 6;
  uint8_t defaultHeight = 8;
  tft.setTextSize(s);
  TEXT_HEIGHT = defaultHeight * s;
  TEXT_WIDTH = defaultWidth * s;
}

void printCenterV(String str, int x) {
  tft.setCursor(x, ((tft.height() / 2) - (TEXT_HEIGHT / 2)));
  tft.print(str);
}

void printCenterH(String str, int y) {
  tft.setCursor((tft.width() / 2) - ((str.length() * TEXT_WIDTH) / 2), y);
  tft.print(str);
}


/*
 * 
 * Functions for drawing main screens
 * 
 */
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
  drawButton(UseCurrent, 1);
  drawButton(AlterCurrent, 0);
  drawButton(SetNew, 0);

  //Current values
  tft.setCursor(237, 65);
  tft.setTextColor(TEXT_COLOR, BACKGROUND_COLOR);
  tft.print(F("Pump:"));
  printPumpValues(237, 90, 28, 10, TEXT_COLOR, BACKGROUND_COLOR);
}

void drawSetIngs() {
  tft.fillScreen(BACKGROUND_COLOR);
  setTextSize(2);
  tft.setTextColor(TEXT_COLOR, BACKGROUND_COLOR);
  printCenterH(F("SELECT PUMP VALUES"), 15);
  //drawPumpButtonsArray();  
}

void drawMainMenu() {
  tft.fillScreen(BACKGROUND_COLOR);

  //Top banner
  setTextSize(2); 
  tft.setCursor(27, 14);
  tft.print(F("Main Menu"));
  tft.drawFastHLine(3, 41, 473, TEXT_COLOR);
  
  tft.drawFastVLine(240, 103, 20, TEXT_COLOR);
  printCenterH(F("Press to select drink"), 295);
  
  //Scroll buttons
  tft.fillTriangle(10, (tft.height() / 2), 30, ((tft.height() / 2) + 15), 30, ((tft.height() / 2) - 15), SECOND_COLOR);
  tft.fillTriangle(469, (tft.height() / 2), 449, ((tft.height() / 2) + 15), 449, ((tft.height() / 2) - 15), SECOND_COLOR);

  //Ingredient section
  setTextSize(2);
  tft.setTextColor(TEXT_COLOR, BACKGROUND_COLOR);
  tft.setCursor(221, 118);
  tft.print(F("Ingredients:"));
}

void drawSettingsMenu() {
  tft.fillScreen(BACKGROUND_COLOR);

  //Top banner
  tft.fillRect((27+96), 14, 200, 16, BACKGROUND_COLOR);
  setTextSize(2); 
  tft.setCursor(27, 14);
  tft.setTextColor(TEXT_COLOR, BACKGROUND_COLOR);
  tft.print(F("Settings"));
  tft.drawFastHLine(3, 41, 473, TEXT_COLOR);

  //Setting buttons
  drawButton(Swap, 1);
  drawButton(Run, 0);
}

void drawSubSet_Swap() {
  //Top banner
  setTextSize(2); 
  tft.setCursor((27+96), 14);
  tft.print(F(" > Swap Ingredients"));

  //Overwrite data
  tft.fillRect(71, 70, 338, 200, BACKGROUND_COLOR);
  
  tft.setTextColor(0xF800, BACKGROUND_COLOR);
  printCenterH(F("Select pump and ingredient"), 60);
  drawPumpSelectionButton();
  //drawIngredientSelectionButton();
}

void drawSubSet_Run() {
  tft.fillRect(0, 16, tft.width(), tft.height(), BACKGROUND_COLOR);
  drawButton(PrimeSelected, 1);
  tft.setCursor(150, 64);
  tft.setTextColor(TEXT_COLOR, BACKGROUND_COLOR);
  tft.print(F("Current Ingredient:"));
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
  
}


/*
 * 
 * Functions for drawing buttons
 * 
 */
void drawButton(ButtonRect button, boolean selected) {
  setTextSize(button.textSize);
  tft.fillRect(button.x, button.y, button.width, button.height, button.borderColor);
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

void drawButton(ButtonTri button, boolean selected) {
  tft.fillTriangle(button.x, button.y, button.x, (button.y + button.height), (button.x + button.width), ((button.y + button.height) / 2), button.borderColor);
}

void printPumpValues(int x, int y, int xSpace, int ySpace, uint16_t textColor, uint16_t backColor) {
  setTextSize(2);
  tft.setTextColor(textColor, backColor);
  getPumpValuesFromMemory();
  //getPumpValuesFromSD();
  //printFileContents(pumpFileName);
  for (uint8_t i = 0; i < numOfPumps; i++) {
    tft.setCursor(x, y + ((TEXT_HEIGHT + ySpace) * i));
    tft.print(String(i +1) + ".");
    tft.setCursor(x + xSpace, y + ((TEXT_HEIGHT + ySpace) * i));
    tft.print(pumps[i].value);
  }
}

void drawPumpSelectionButton() {
  setTextSize(2);
  tft.setCursor(73, 94);
  tft.setTextColor(TEXT_COLOR, BACKGROUND_COLOR);
  tft.print(F("PUMP"));
  tft.fillRect(73, 122, 338, 53, BORDER_COLOR);
  tft.fillRect(76, 125, 332, 47, SECOND_COLOR);
  tft.setCursor(204, 137);
  tft.setTextColor(TEXT_COLOR, SECOND_COLOR);
  tft.print(F("Pump"));
}

/*
 * 
 * Functions for updating button states per screen
 * 
 */
void updateChooseStartingOptionButtons() {
  if(pos == 0) {
    drawButton(UseCurrent, 1);                           //Use Current button selected
    if(lastPos == 1) drawButton(AlterCurrent, 0);        //Alter Current button deselected
    else if(lastPos == 2) drawButton(SetNew, 0);         //Set New button deselected
  }
  else if(pos == 1) {
    drawButton(AlterCurrent, 1);                         //Alter Current button selected
    if(lastPos == 0) drawButton(UseCurrent, 0);          //Use Current button deselected
    else if(lastPos == 2) drawButton(SetNew, 0);         //Set New button deselected
  }
  else if(pos == 2) {
    drawButton(SetNew, 1);                               //Set New button selected
    if(lastPos == 0) drawButton(UseCurrent, 0);          //Use Current button deselected
    else if(lastPos == 1) drawButton(AlterCurrent, 0);   //Alter Current button deselected
  }
}

void updateMainMenu(DrinkList drinkList) {
  int ingPosX = 235;
  int ingPosY = 143;
  uint8_t ingSpace = 2;

  //Overwrite previous drink info
  setTextSize(3); 
  tft.fillRect( ((tft.width() / 2) - ((TEXT_WIDTH * choice.getDrinkName().length()) / 2)), 53, (TEXT_WIDTH * choice.getDrinkName().length()), (35 + TEXT_HEIGHT), BACKGROUND_COLOR); //Overwrites area where information will be added
  setTextSize(2);
  tft.fillRect(ingPosX, ingPosY, (TEXT_WIDTH * 30), (choice.getSize() * (TEXT_HEIGHT + ingSpace)), BACKGROUND_COLOR);

  //Color the arrows according to which direction you turned
  if (lastPos > pos) {
    if (lastPos == (drinkList.getSize() - 1) && pos == 0) {
      tft.fillTriangle(469, (tft.height() / 2), 449, ((tft.height() / 2) + 15), 449, ((tft.height() / 2) - 15), TEXT_COLOR);
    } else {
      tft.fillTriangle(10, (tft.height() / 2), 30, ((tft.height() / 2) + 15), 30, ((tft.height() / 2) - 15), TEXT_COLOR);
    }
  }
  else if (lastPos < pos) {
    if (pos == (drinkList.getSize() - 1) && lastPos == 0) {
      tft.fillTriangle(10, (tft.height() / 2), 30, ((tft.height() / 2) + 15), 30, ((tft.height() / 2) - 15), TEXT_COLOR);
    } else {
      tft.fillTriangle(469, (tft.height() / 2), 449, ((tft.height() / 2) + 15), 449, ((tft.height() / 2) - 15), TEXT_COLOR);
    }
  }

  //Change choice to next drink
  choice = drinkList.getDrink(pos);
  
  //tft.drawRGBBitmap(15, 63, margarita_img, 90, 160);
  tft.setAddrWindow(73, 120, (73 + IMAGE_W - 1), (120 + IMAGE_H - 1));
  tft.pushColors((const uint8_t*)choice.image, IMAGE_W * IMAGE_H, 1);

  //Print new drink info
  setTextSize(3);     
  tft.setTextColor(TEXT_COLOR, BACKGROUND_COLOR);
  printCenterH(choice.getDrinkName(), 53);
  setTextSize(2);
  String tempVol = String(choice.calcTotalVol()) + F(" ml");
  tft.setCursor(257, 84);
  tft.print(tempVol);
  String tempPercent = String(int(choice.calcTotalPercentAlc())) + F(" % alc");
  tft.setCursor((223 - (tempPercent.length() * TEXT_WIDTH)), 84);
  tft.print(tempPercent);

  //Print ingredients
  tft.setTextColor(SECOND_COLOR, BACKGROUND_COLOR);
  for (int i = 0; i < choice.getSize(); i++) {
    tft.setCursor(ingPosX, (ingPosY + ((TEXT_HEIGHT + ingSpace) * i)));
    tft.print(choice.getIngredient(i).getIngName());
  }

  //Reset scroll arrows
  tft.fillTriangle(10, (tft.height() / 2), 30, ((tft.height() / 2) + 15), 30, ((tft.height() / 2) - 15), SECOND_COLOR);
  tft.fillTriangle(469, (tft.height() / 2), 449, ((tft.height() / 2) + 15), 449, ((tft.height() / 2) - 15), SECOND_COLOR);
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
      drawButton(Swap, 1);  //Swap button selected
      drawButton(Run, 0); //Prime button deselected
      break;
    case 1:
      drawButton(Swap, 0);  //Swap button deselected
      drawButton(Run, 1); //Prime button selected
      break;
    default:
#if PRINT_TO_SERIAL
      Serial.println(F("Invalid pos variable"));
#endif
      pos = 0;
      break;
  }
}

void updatePumpSelectionButton() {
  tft.setCursor(264, 137);
  tft.print(pos + 1);
}
