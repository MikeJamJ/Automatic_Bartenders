/*

  Functions for making a drink:

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

//Used for making drink
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
  unsigned long volume = choice.getIngredient(ingNum).getIngVol();
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

//Used for run pump setting
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

void makeDrink() {
#if PRINT_TO_SERIAL
  Serial.println(F("===================================\nMAKING DRINK\n===================================\n"));
  Serial.print(F("MAKEDRINK():\t\t"));
  Serial.println(choice.getDrinkName());
#endif

  //Turn on all pumps
  for (uint8_t a = 0; a < choice.getSize(); a++) {
    startPump(findPump(a), a);
#if PRINT_TO_SERIAL
    Serial.println(F("Timer started:"));
    Serial.print(F("\tIngredient: "));
    Serial.println(choice.getIngredient(a).getIngName());
    Serial.print(F("\tVolume: "));
    Serial.println(choice.getIngredient(a).getIngVol());
    Serial.print(F("\tSeconds: "));
    Serial.println((((choice.getIngredient(a).getIngVol()) * 60000) / PUMPSPEEDML) / 1000);
#endif
    checkForFinishedPump();
  }
  
  //Find total time
  unsigned long totalEndTime = 0;
  unsigned long totalStartTime = pumps[findPump(0)].startTime;
  for (uint8_t i = 0; i < choice.getSize(); i++) {
    if (pumps[findPump(i)].endTime > totalEndTime) totalEndTime = pumps[findPump(i)].endTime;
  }
  int timeSegments = ((totalEndTime - totalStartTime) / 8);
  int lastBarDrawn = 0;
  while (!finishedMakeDrink()) {
    checkForFinishedPump();
    lastBarDrawn = updateDrinkProgressBar(timeSegments, totalStartTime, lastBarDrawn);
  }
#if PRINT_TO_SERIAL
  serialPrintPumpInfo();
  Serial.println(F("===================================\nDONE MAKING DRINK\n===================================\n"));
#endif
}

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
        digitalWrite(pumps[i].pin, RELAY_OFF);
        pumps[i].endTime = 0;
        pumps[i].startTime = 0;
      }
    }
  }
}

bool finishedMakeDrink() {
  for (uint8_t i = 0; i < numOfPumps; i++) {
    if (pumps[i].startTime != 0 && pumps[i].endTime != 0) return 0;
  }
  return 1;
}
