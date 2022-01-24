/*
   Main Menu of the system where drinks can be selected
*/

//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------

void mainMenu() {
  Serial.println("===================================");
  Serial.println("ENTERING MENU");
  Serial.println("===================================\n");
  
  int position_ = 0;
  int totalVol = 0;
  printDrinkInfo(position_, totalVol);

  Serial.print("position: ");
  Serial.println(position_);
    
  while (MM == true) {

    if (position_ != lastPosition) {
      Serial.print("position: ");
      Serial.println(position_);
      printDrinkInfo(position_, totalVol);

      lastPosition = position_;
      delay(20);
    }

    /*
       If the user presses the select button, the drink that is currently being displayed will
       be made
    */
    if (!digitalRead(butSelect)) {
      eventTime = millis();
      if ((eventTime - prevEventTime) > 400) {
        prevEventTime = eventTime;
        prevButtonTimer = millis();

        /*
          This checks for a long or short button press. While the button is held, the system constantly
          updates the current time. If the button is released under 2 seconds, a drink is made. If the
          button is held for more than 2 seconds, the system immediately goes to the Settings menu
        */
        while (!digitalRead(butSelect)) {
          curButtonTimer = millis();
          if ((curButtonTimer - prevButtonTimer) >= 2000) {
            MM = false;
            SET = true;
            break;
          }
        }
        Serial.println("===================================");
        Serial.println("MAKING DRINK");
        Serial.println("===================================\n");
        makeDrink();
        myGLCD.print("ENJOY!", CENTER, 100);
        delay(2000);
        printDrinkInfo(position_, totalVol);
      }
    }

  }
  Serial.println("END OF MENU");
  Serial.print("MM: ");
  Serial.println(MM);
}

//-----------------------------------------------------------------------------------------------

/*
   Finds the end of possible drinks in the possible_drinks array and returns it's value
*/
int findEndOfArray(int endOfArray) {
  for (int j = 0; j < (sizeof possible_drinks / sizeof possible_drinks[0]); j++) {
    if (possible_drinks[j + 1].drinkName[0] == defaultDrink.drinkName[0]) {
      endOfArray = j;
      return endOfArray;
    }
  }
}

//-----------------------------------------------------------------------------------------------

/*
   Prints out drink name and total volume onto the screen
*/
void printDrinkInfo(int position_, int totalVol) {
  int ingPos = 90;
  choice = possible_drinks[position_];

  myGLCD.setColor(13, 13, 13);
  myGLCD.fillRect(130, 50, 319, 187);

  //Print Drink Name and Total Volume
  myGLCD.setFont(SmallFont);
  myGLCD.setColor(252, 252, 252);
  myGLCD.setBackColor(13, 13, 13);
  myGLCD.print(possible_drinks[position_].drinkName, 130, 50);
  myGLCD.printNumI(calcTotalVol(totalVol), 202, 70, 3, " ");
  myGLCD.print(" ml", 226, 70);

  //Print ingredients in a list
  for (int i = 0; i < possible_drinks[position_].size; i++) {
    myGLCD.printNumI(possible_drinks[position_].ingredients[i].ingVal, 130, (ingPos + (12 * i)));
    myGLCD.print(" ml:", 154, (ingPos + (12 * i)));
    myGLCD.print(possible_drinks[position_].ingredients[i].ingName, 190, (ingPos + (12 * i)));
  }

  //Prints drink type in the bottom corner
  myGLCD.setFont(BigFont);
  //myGLCD.print(possibe_drinks[position_].type, 299, 219);
}

//-----------------------------------------------------------------------------------------------

void printMakingDrink(){
  
}

//-----------------------------------------------------------------------------------------------

/*
   Calculates the volume of liquid each drink will produce
*/
int calcTotalVol(int totalVol) {
  for (int b = 0; b < choice.size; b++) {
    totalVol += choice.ingredients[b].ingVal;
  }
  return totalVol;
}


