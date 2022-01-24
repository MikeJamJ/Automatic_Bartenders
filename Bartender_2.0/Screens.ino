
/*
   Dislpays logo
*/
void displayLogo() {

}

//-----------------------------------------------------------------------------------------------

void homeScreen() {
  myGLCD.fillScr(13, 13, 13);
  myGLCD.setColor(252, 252, 252);  

  //Top Banner
  myGLCD.fillRect(0, 0, 319, 15);
  myGLCD.setColor(13, 13, 13);
  myGLCD.setBackColor(252, 252, 252);
  myGLCD.setFont(SmallFont);
  myGLCD.print("PROFESSOR SMIRNOFF", CENTER, 3);

  //bottom 4 buttons
  myGLCD.setColor(144, 172, 24);
  myGLCD.fillRect(0, 189, 78, 239);
  
  myGLCD.setColor(13, 13, 13);
  myGLCD.setBackColor(144, 172, 24);
  myGLCD.print("Alcohol", 10, 208);
  myGLCD.setColor(199, 239, 31);
  myGLCD.fillRect(80, 189, 158, 239);
  myGLCD.fillRect(160, 189, 238, 239);
  myGLCD.fillRect(240, 189, 319, 239);

  //Bottom button lines
  myGLCD.setColor(13, 13, 13);
  myGLCD.drawLine(79, 189, 79, 239);
  myGLCD.drawLine(159, 189, 159, 239);
  myGLCD.drawLine(239, 189, 239, 239);

  myGLCD.setFont(SmallFont);
  myGLCD.setColor(13, 13, 13);
  myGLCD.setBackColor(199, 239, 31);
  myGLCD.print("Non-Alc", 93, 208);
  myGLCD.print("Shots", 180, 208);
  myGLCD.print("Settings", 250, 208);
}

//-----------------------------------------------------------------------------------------------

void updateButtons() {
  if ((lastButtonPressed == 1) && (x > 78)) {
    myGLCD.setColor(199, 239, 310);
    myGLCD.fillRect(0, 189, 78, 239);
    myGLCD.setColor(13, 13, 13);
    myGLCD.setBackColor(199, 239, 310);
    myGLCD.print("Alcohol", 10, 208);
  }
  else if ((lastButtonPressed == 2) && ((x > 158) || (x < 80))) {
    myGLCD.setColor(199, 239, 310);
    myGLCD.fillRect(80, 189, 158, 239);
    myGLCD.setColor(13, 13, 13);
    myGLCD.setBackColor(199, 239, 310);
    myGLCD.print("Non-Alc", 93, 208);
  }
  else if ((lastButtonPressed == 3) && ((x > 238) || (x < 160))) {
    myGLCD.setColor(199, 239, 310);
    myGLCD.fillRect(160, 189, 238, 239);
    myGLCD.setColor(13, 13, 13);
    myGLCD.setBackColor(199, 239, 310);
    myGLCD.print("Shots", 180, 208);
  }
  else if ((lastButtonPressed == 4) && (x < 240)) {
    myGLCD.setColor(199, 239, 310);
    myGLCD.fillRect(240, 189, 319, 239);
    myGLCD.setColor(13, 13, 13);
    myGLCD.setBackColor(199, 239, 310);
    myGLCD.print("Settings", 250, 208);
  }
}

//-----------------------------------------------------------------------------------------------

void settingsScreen(){
  myGLCD.setColor(13, 13, 13);
  myGLCD.fillRect(0, 16, 319, 187);
  myGLCD.setColor(252, 252, 252);
  myGLCD.setBackColor(13, 13, 13); 
  myGLCD.print("SETTINGS", CENTER, 50);
}

//-----------------------------------------------------------------------------------------------

void sorryScreen(){
  myGLCD.setColor(13, 13, 13);
  myGLCD.fillRect(0, 16, 319, 187);
  myGLCD.setColor(252, 252, 252);
  myGLCD.setBackColor(13, 13, 13); 
  myGLCD.print("Non of this Drink Type \nare available", CENTER, 50);
}



