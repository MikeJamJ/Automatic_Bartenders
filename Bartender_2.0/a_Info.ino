/*
 * Functions for sorting and preparing drink varibales
 * Most of the functions are related to bug-finding
 */

//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------

/*
   Prints Array of all drinks
*/
void SerialPrintAllDrinks() {
  Serial.println("===================================");
  Serial.println("PRINTING ALL DRINKS");
  Serial.println("===================================\n");

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
  Serial.print("\n");
}

//-----------------------------------------------------------------------------------------------

/*
   Prints array of the drinks that can be made using drinks hooked up to pumps
*/
void SerialPrintPossibleDrinks() {
  Serial.println("===================================");
  Serial.println("PRINTING POSSIBLE DRINKS");
  Serial.println("===================================\n");

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
  Serial.print("\n");
}
