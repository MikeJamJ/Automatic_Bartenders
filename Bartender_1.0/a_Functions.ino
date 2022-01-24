//-----------------------------------------------------------------------------------------------
// FUNCTIONS for sorting and preparing drink varibales
//-----------------------------------------------------------------------------------------------

/*
 * Dislpays logo
 */
void displayLogo() {
  lcd.setCursor(2, 0);
  lcd.write(1);
  lcd.setCursor(3, 0);
  lcd.write(2);
  lcd.print(" Professor");
  lcd.setCursor(2, 1);
  lcd.write(3);
  lcd.setCursor(3, 1);
  lcd.write(4);
  lcd.print(" Smirnoff");
}

//-----------------------------------------------------------------------------------------------


/*
   Prints Array of all drinks
*/
void printAllDrinks() {
  for (int a = 0; a < (sizeof drink_list / sizeof drink_list[0]); a++) {
    Serial.println(drink_list[a].drinkName);
    for (int b = 0; b < drink_list[a].size; b++) {
      Serial.print("\t");
      Serial.print(drink_list[a].ingredients[b].ingName);
      Serial.print("\t");
      Serial.print(drink_list[a].ingredients[b].ingVal);
      Serial.print("\n");
    }
  }
}

//-----------------------------------------------------------------------------------------------

/*
   Prints array of the drinks that can be made using drinks hooked up to pumps
*/
void printPossibleDrinks() {
  for (int c = 0; c < (sizeof possible_drinks / sizeof possible_drinks[0]); c++) {
    Serial.println(possible_drinks[c].drinkName);
    for (int d = 0; d < possible_drinks[c].size; d++) {
      Serial.print("\t");
      Serial.print(possible_drinks[c].ingredients[d].ingName);
      Serial.print("\t");
      Serial.print(possible_drinks[c].ingredients[d].ingVal);
      Serial.print("\n");
    }
  }
}

//-----------------------------------------------------------------------------------------------

/*
   Identifies drinks that can be made using drinks hooked up to pumps
*/
void possibleDrinks() {
  int pbArrayNum = 0;
  for (int e = 0; e < (sizeof drink_list / sizeof drink_list[0]); e++) {
    int numOfConfirmedIngs = 0;
    for (int f = 0; f < drink_list[e].size; f++) {
      for (int g = 0; g < (sizeof pumps / sizeof pumps[0]); g++) {
        if (drink_list[e].ingredients[f].ingName == pumps[g]) {
          numOfConfirmedIngs++;
          if (numOfConfirmedIngs == drink_list[e].size) {
            possible_drinks[pbArrayNum] = drink_list[e];
            pbArrayNum++;
            break;
          }
          break;
        }
      }
      for (int h = 0; h < (sizeof possible_drinks / sizeof possible_drinks[0]); h++) {
        Serial.print(possible_drinks[h].drinkName);
        Serial.print("\t");
      }
      Serial.print("\n");
    }
  }
  fillRemaining(pbArrayNum);
}

//-----------------------------------------------------------------------------------------------

/*
 * Fills remaining un-used spots in the possible_drinks array for "defaultDrink"
 */
void fillRemaining(int n) {
  for (int y = n; y < (sizeof possible_drinks / sizeof possible_drinks[0]); y++) {
    possible_drinks[y] = defaultDrink;
  }
}

//-----------------------------------------------------------------------------------------------

/*
   Sorts array of possible drinks into alphabetical order
*/
void alphabetize() {
  Drink smallest = defaultDrink;
  Drink ogSmallest = defaultDrink;
  Drink temp = defaultDrink;
  String smallDrinkName;

  int smallestPosition;

  /*
   * Goes through all elements of possible_drinks and decreases the amount of 
   * positions that need to be checked everytime a new smallest drink is placed 
   * in the first position of the iteration
   */
  for (int x = 0; x < ((sizeof possible_drinks / sizeof possible_drinks[0]) - 1); x++) {
    smallest = possible_drinks[x];
    ogSmallest = smallest;

    /*
     * Checks each drinkName in an iteration to find the smallest drinkName 
     */
    for ( int y = 0; y < (sizeof possible_drinks / sizeof possible_drinks[0]) - (x + 1); y++) {
      /*
       * Finds the shortest drinkName between the current smallest and the next
       * position's drinkName. Only checks characters until the shortest drinkName 
       * is done
       */
      if (possible_drinks[y + 1].drinkName.length() < possible_drinks[y].drinkName.length()) {
        smallDrinkName = possible_drinks[y + 1].drinkName;
      }
      else {
        smallDrinkName = possible_drinks[y].drinkName;
      }

      /*
       * Goes through each character in the drinkName of smallest and next position 
       * of the possible_drinks array. If the new position is smaller, it becomes
       * the new smallest. If smallest is ever found to be less than the new position,
       * the loop breaks and a new iteration begins
       */
      for (int z  = 0; z < smallDrinkName.length(); z++) {
        if (possible_drinks[x + y + 1].drinkName[z] < smallest.drinkName[z]) {
          smallest = possible_drinks[x + y + 1];
          smallestPosition = x + y + 1;
          break;
        }
        else if (possible_drinks[x + y + 1].drinkName[z] > smallest.drinkName[z]) {
          break;
        }
      }
    }
    
    /*
     * If the smallest drinkName has not chnaged in this iteration, the next iteration
     * begins. Else, the smallest is brought to the front and the drink in that postion
     * is moved to where the smallest drinkname was 
     */
    if (ogSmallest.drinkName != smallest.drinkName) {
      temp = possible_drinks[x];
      possible_drinks[x] = smallest;
      possible_drinks[smallestPosition] = temp;
    }
    else {
    }
    Serial.println("freeMemory()= ");
    Serial.println(freeMemory());
  }
}

