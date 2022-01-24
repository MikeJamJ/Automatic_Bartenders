/*
   Creator:
      Michael Jamieson
   Date of last Update:
      07/09/2019
   Description:
      Functions for making a drink:
*/

//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------

/*
   Find the pump to turn on based on the ingredient name

   @param ingNum      ingredient number of the drink being made
   @returns uint8_t   pump position in 'pumps' array
*/
uint8_t findPump(uint8_t ingNum) {
#if PRINT_TO_SERIAL
  Serial.print(F("FINDPUMP():\t\t"));
#endif
  for (uint8_t i = 0; i < numOfPumps; i++) {
    if (choice.getIngredient(ingNum).getIngName() == pumps[i].value) {
#if PRINT_TO_SERIAL
      Serial.print(F("Ingredient Name: "));
      Serial.print(choice.getIngredient(ingNum).getIngName());
      Serial.print(F("\tPosition: "));
      Serial.print(ingNum);
      Serial.print(F("\tFound pump: "));
      Serial.println(pumps[i].value);
#endif
      return i;
    }
  }
  return 10;
}

/*
   Starts a pump
   Used when making a drink

   @param pumpNum   pump position in 'pumps' array
   @param ingNum    ingredient number of the drink being made
*/
void startPump(uint8_t pumpNum, uint8_t ingNum) {
#if PRINT_TO_SERIAL
  Serial.print(F("STARTPUMP():\t\t"));
  Serial.print(F("Passed value: "));
  Serial.print(pumpNum);
  Serial.print(F("\tPump "));
  Serial.print(pumpNum + 1);
  Serial.println(F(" turned on"));
#endif

  digitalWrite(pumps[pumpNum].pin, RELAY_ON);
  pumps[pumpNum].startTime = millis();
  unsigned long volume = choice.getRecipe(ingNum).getIngVol();
  unsigned long multiplier = 60000;
  unsigned long pumpSpeed = PUMPSPEEDML;
  pumps[pumpNum].endTime = pumps[pumpNum].startTime + ((volume * multiplier) / pumpSpeed);

#if PRINT_TO_SERIAL
  Serial.print(F("\tStartTime: "));
  Serial.println(pumps[pumpNum].startTime);
  Serial.print(F("\tEndTime: "));
  Serial.println(pumps[pumpNum].endTime);
#endif
}

/*
   Starts a pump
   Used for settings where no drink is being made

   @param pumpNum   pump position in 'pumps' array
*/
void startPump(uint8_t pumpNum) {
#if PRINT_TO_SERIAL
  Serial.print(F("STARTPUMP():\t\t"));
  Serial.print(F("Passed value: "));
  Serial.print(pumpNum);
  Serial.print(F("\tPump "));
  Serial.print(pumpNum + 1);
  Serial.println(F(" turned on"));
#endif
  digitalWrite(pumps[pumpNum].pin, RELAY_ON);
}

/*
   Iterates through all ingredients in the chosen drink
   to turn on and off necessary pumps for the required volume
   and calculates when the drink is finished
*/
void makeDrink() {
#if PRINT_TO_SERIAL
  Serial.println(F("===================================\nMAKING DRINK\n===================================\n"));
  Serial.print(F("MAKEDRINK():\t\t"));
  Serial.println(choice.getDrinkName());
#endif

  // Turn on all pumps needeed to make the drink
  for (uint8_t a = 0; a < choice.getSize(); a++) {
    startPump(findPump(a), a);
#if PRINT_TO_SERIAL
    Serial.println(F("Timer started:"));
    Serial.print(F("\tIngredient: "));
    Serial.println(choice.getIngredient(a).getIngName());
    Serial.print(F("\tVolume: "));
    Serial.println(choice.getRecipe(a).getIngVol());
    Serial.print(F("\tSeconds: "));
    Serial.println((((choice.getRecipe(a).getIngVol()) * 60000) / PUMPSPEEDML) / 1000);
#endif
    checkForFinishedPump();
  }

  // Calculate the total time to complete the drink for progress bar
  unsigned long totalEndTime = 0;
  unsigned long totalStartTime = pumps[findPump(0)].startTime;
  for (uint8_t i = 0; i < choice.getSize(); i++) {
    if (pumps[findPump(i)].endTime > totalEndTime) totalEndTime = pumps[findPump(i)].endTime;
  }
  int timeSegments = ((totalEndTime - totalStartTime) / 8);
  int lastBarDrawn = 0;

  // Check if a pump is finished and update the progress bar until all pumps have finished
  while (!finishedMakeDrink()) {
    checkForFinishedPump();
    lastBarDrawn = updateDrinkProgressBar(timeSegments, totalStartTime, lastBarDrawn);
  }
#if PRINT_TO_SERIAL
  serialPrintPumpInfo();
  Serial.println(F("===================================\nDONE MAKING DRINK\n===================================\n"));
#endif
}

/*
   Loop through 'pumps' array to check if it is time to turn the pump off
*/
void checkForFinishedPump() {
  for (uint8_t i = 0; i < numOfPumps; i++) {
    if (millis() >= pumps[i].endTime) {
      if (digitalRead(pumps[i].pin) == RELAY_ON) {
#if PRINT_TO_SERIAL
        Serial.print(F("TURNED OFF "));
        Serial.print(pumps[i].name);
        Serial.print(F(":\tendTime: "));
        Serial.print(pumps[i].endTime);
        Serial.print(F("\tcurTime: "));
        Serial.println(millis());
#endif
        // Reset values when pump is turned off
        digitalWrite(pumps[i].pin, RELAY_OFF);
        pumps[i].endTime = 0;
        pumps[i].startTime = 0;
      }
    }
  }
}

/*
   Loop through 'pumps' array to check if any are still running

   @returns bool  boolean value of whether all pumps have been turned off
*/
bool finishedMakeDrink() {
  for (uint8_t i = 0; i < numOfPumps; i++) {
    if (pumps[i].startTime != 0 && pumps[i].endTime != 0) return 0;
  }
  return 1;
}

/*
   Creates a random drink based on ingredients attached to the pumps

   @returns 
*/
void createRandomDrink() {
#if PRINT_TO_SERIAL
  Serial.println(F("===================================\nMAKING RANDOM DRINK\n===================================\n"));
#endif

  uint16_t maxDrinkSize = 250;
  uint16_t randVol;
  uint8_t availPumps, randSize, randPump;
  randomSeed(millis());

  // find pumps that have ingredients
  for (uint8_t i = 0; i < numOfPumps; i++) {
    if (pumps[i].value != "NULL") availPumps++;
  }

  // get random number of ingredients
  randSize = random(1, availPumps + 1);
  Recipe randomDrink_[randSize];
  boolean usedPumps[randSize] = {0};

#if PRINT_TO_SERIAL
  Serial.print(F("Number of available Pumps: "));
  Serial.println(availPumps);
  Serial.print(F("Number of ingredients: "));
  Serial.println(randSize);
#endif

  for (uint8_t i = 0; i < randSize; i++) {
    // find a pump with an ingredient that hasnt been used
    do {
      randPump = random(0, randSize);
#if PRINT_TO_SERIAL
      Serial.print(F("Random Pump Num: "));
      Serial.print(randPump);
      Serial.print(F("\tUsed: "));
      Serial.print(usedPumps[randPump]);
      Serial.print(F("\t\tValue: "));
      Serial.println(pumps[randPump].value);
#endif
    } while (usedPumps[randPump] != 0 && pumps[randPump].value != "NULL");

    // set used value to 1, make random volume, assign it to the Recipe
    usedPumps[randPump] = 1;
    randVol = random(1, maxDrinkSize / (randSize - 1));
    randomDrink_[i] = Recipe(getIngFromString(pumps[randPump].value), randVol);
    
#if PRINT_TO_SERIAL
    Serial.print(F("\tRandom Vol: "));
    Serial.println(randVol);
#endif
  }
  
  Drink randomDrink("Random", randomDrink_, ARRAYCOUNT(randomDrink_), 'A', "default");
  randomDrink.serialPrintDrinkInfo();
}

/*
   Returns the Ingredient with the same name as the string passed

   @param nm            name of the ingredient you want returned
   @returns Ingredient  the Ingredient with the same name as 'nm'
*/
Ingredient getIngFromString(String nm) {
  for (uint8_t i = 0; i < sizeOfIngList; i ++) {
    if (IngredientList[i].getIngName() == nm){
      return IngredientList[i];
    }
  }
}
