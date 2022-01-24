/*
   Main Menu of the system where drinks can be selected
*/

void mainMenu() {
  Serial.println("ENTERING MENU");
  
  int position_ = 0;
  int totalVol = 0;
  int endOfArray = findEndOfArray(endOfArray);

  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Main Menu");
  delay(2000);
  lcd.clear();

  /*for (int temp = 0; temp < sizeof pumps / sizeof pumps[0]; temp ++){
    Serial.println(pumps[temp]);
  }*/
  
  printDrinkInfo(position_, totalVol);

  while (MM == true) {
    /*
       If the user presses the left button, the menu will select and print the name and total
       volume of the drink left in the array. If the array is at the beginning, the drink at
       the end of the array will be displayed
    */
    if (digitalRead(butLeft) == HIGH) {
      eventTime = millis();
      if ((eventTime - prevEventTime) > 400) {
        prevEventTime = eventTime;
        if (position_ == 0) {
          position_ = endOfArray;
        }
        else {
          position_--;
        }
        printDrinkInfo(position_, totalVol);
      }
    }

    /*
       If the user presses the right button, the menu will select and prnt the name and total
       volume of the drink right in the array. If the array is at the end of possible drinks,
       the drink at the beginning of the array will be displayed
    */
    if (digitalRead(butRight) == HIGH) {
      eventTime = millis();
      if ((eventTime - prevEventTime) > 400) {
        prevEventTime = eventTime;
        if (possible_drinks[position_ + 1].drinkName[0] == defaultDrink.drinkName[0]) {
          position_ = 0;
        }
        else {
          position_++;
        }
        printDrinkInfo(position_, totalVol);
      }
    }

    /*
       If the user presses the select button, the drink that is currently being displayed will
       be made
    */
    if (digitalRead(butSelect) == HIGH) {
      eventTime = millis();
      if ((eventTime - prevEventTime) > 400) {
        prevEventTime = eventTime;
        prevButtonTimer = millis();

        /*
         * This checks for a long or short button press. While the button is held, the system constantly 
         * updates the current time. If the button is released under 2 seconds, a drink is made. If the 
         * button is held for more than 2 seconds, the system immediately goes to the Settings menu
         */
        while (digitalRead(butSelect) == HIGH) {
          curButtonTimer = millis();
          if ((curButtonTimer - prevButtonTimer) >= 2000) {
            MM = false;
            SET = true;
            break;
          }
        }
        if ((curButtonTimer - prevButtonTimer) < 2000) {
          Serial.println("Making drink");
          lcd.clear();
          lcd.setCursor(3, 0);
          lcd.print("Please Wait");
          lcd.setCursor(1, 1);
          lcd.print("For Your Drink");
          makeDrink();
          lcd.clear();
          lcd.setCursor(5, 0);
          lcd.print("Enjoy!");
          delay(2000);
          printDrinkInfo(position_, totalVol);
        }
      }
    }
  }
  Serial.println("END OF MENU");
  Serial.print("MM: ");
  Serial.println(MM);
}

//-----------------------------------------------------------------------------------------------

/*
   Calclates the volume of liquid each drink will produce
*/
int calcTotalVol(int totalVol) {
  for (int b = 0; b < choice.size; b++) {
    totalVol += choice.ingredients[b].ingVal;
  }
  return totalVol;
}

//-----------------------------------------------------------------------------------------------

/*
   Prints out drink name on the first line of the LCD
   and the drink volume on the second line
*/
void printDrinkInfo(int position_, int totalVol) {
  choice = possible_drinks[position_];
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(possible_drinks[position_].drinkName);
  lcd.setCursor(0, 1);
  lcd.print("ml: ");
  lcd.setCursor(4, 1);
  lcd.print(calcTotalVol(totalVol));
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



