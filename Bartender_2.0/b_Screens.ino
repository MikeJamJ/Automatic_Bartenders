/*
   Functions for drawing the various screens for the 32x240 UTFT display
*/

//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------

/*
   Dislpays logo
*/
void displayLogo() {
  myGLCD.fillScr(13, 13, 13);

  //Product Name
  myGLCD.setColor(252, 252, 252);
  myGLCD.setFont(BigFont);
  myGLCD.print("PROFESSOR", CENTER, 99);
  myGLCD.print("SMIRNOFF", CENTER, 123); 
}

//-----------------------------------------------------------------------------------------------

/*
 * Draws Home screen of the bartender which displays the drink name, 
 * ingredients, and total volume
 */
void homeScreen() {
  myGLCD.fillScr(13, 13, 13);  

  //Top Banner
  myGLCD.setColor(252, 252, 252);
  myGLCD.fillRect(0, 0, 319, 15);
  myGLCD.setColor(13, 13, 13);
  myGLCD.setBackColor(252, 252, 252);
  myGLCD.setFont(SmallFont);
  myGLCD.print("PROFESSOR SMIRNOFF", CENTER, 3);
}

//-----------------------------------------------------------------------------------------------

/*
 * Displays the settings screen
 */
void settingsScreen(){
  myGLCD.setColor(13, 13, 13);
  myGLCD.fillRect(0, 16, 319, 187);
  myGLCD.setColor(252, 252, 252);
  myGLCD.setBackColor(13, 13, 13); 
  myGLCD.print("SETTINGS", CENTER, 50);
}

//-----------------------------------------------------------------------------------------------

/*
 * Displays if no drinks of the selected type are available with the current
 * ingredients
 */
void sorryScreen(){
  myGLCD.setColor(13, 13, 13);
  myGLCD.fillRect(0, 16, 319, 187);
  myGLCD.setColor(252, 252, 252);
  myGLCD.setBackColor(13, 13, 13); 
  myGLCD.print("Non of this Drink Type \nare available", CENTER, 50);
}



