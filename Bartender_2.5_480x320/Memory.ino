
/*
   Creator:
      Michael Jamieson
   Date of last Update:
      07/09/2019
   Description:
      Functions for reading and writing from memory. 
      This can be either from EEPROM or an SD card.
*/

//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------

/*
   Read a string from EEPROM memory

   @param add       address to begin reading from
   @returns String  the string stored
*/
String readStringMemory(uint16_t add) {
  char data[30]; //Max 30 Bytes
  uint16_t len = 0;
  unsigned char k = EEPROM.read(add);
  while (k != '\0' && len < 30) //Read until null character
  {
    k = EEPROM.read(add + len);
    data[len] = k;
    len++;
  }
  data[len] = '\0';
  return String(data);
}

/*
   Add String to EEPROM memory
   The function checks if the characters are different before writing
   to save on write calls

   @param add   address to begin reading from
   @param data  the string to be stored
*/
void updateStringMemory(uint16_t add, String data) {
  uint16_t _size = data.length();
#if PRINT_TO_SERIAL
  Serial.println(F("\nWRITING STRING\n~~~~~~~~~~~~~~~~~~~~~~~~~~~"));
  Serial.print(F("Size of String: "));
  Serial.print(_size);
  Serial.print(F("\t\tCurrent Info: "));
  Serial.print(readStringMemory(add));
  Serial.print(F("\tNew Info: "));
  Serial.print(data);
  Serial.print(F("\tEqual: "));
  Serial.println(readStringMemory(add) == data);
#endif
  if (readStringMemory(add) != data) {
    for (uint8_t i = 0; i < _size; i++)
    {
      EEPROM.write(add + i, data[i]);
    }
    EEPROM.write(add + _size, '\0'); //Add termination null character for String Data
#if PRINT_TO_SERIAL
    Serial.println(F("DONE WRITING STRING\n"));
#endif
  }
  else {
#if PRINT_TO_SERIAL
    Serial.println(F("STRING ALREADY THERE\n"));
#endif
  }
}

/*
   Loop through 'pumps' array and retrieve all ingredients used during the last run,
   then updates each pump's 'name' value
*/
void getPumpValuesFromMemory() {
#if PRINT_TO_SERIAL
  Serial.println(F("\nGETTING PUMP VALUES FROM MEMORY\n~~~~~~~~~~~~~~~~~~~~~~~~~~~"));
#endif
  for (uint8_t i = 0; i < numOfPumps; i++) {
#if PRINT_TO_SERIAL
    Serial.print(F("Pump:  "));
    Serial.print(i + 1);
    Serial.print(F("\tAddress: "));
    Serial.print(pumps[i].address);
    Serial.print(F("\tValue: "));
    Serial.println(pumps[i].value);
#endif
    pumps[i].value = readStringMemory(pumps[i].address);
  }
  serialPrintPumpInfo();
}

/*
   Loop through 'pumps' array and write all current ingreient names to EEPROM memory
*/
void setPumpValuesToMemory() {
#if PRINT_TO_SERIAL
  Serial.println(F("\nSETTING PUMP VALUES TO MEMORY\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"));
#endif
  for (uint8_t i = 0; i < numOfPumps; i++) {
#if PRINT_TO_SERIAL
    Serial.print(F("Pump:  "));
    Serial.print(i + 1);
    Serial.print(F("\tAddress: "));
    Serial.print(pumps[i].address);
    Serial.print(F("\tValue: "));
    Serial.println(pumps[i].value);
#endif
    updateStringMemory(pumps[i].address, pumps[i].value);
  }
  serialPrintPumpInfo();
}

/*
   Read a file stored on the SD card and retrieve all ingredients used during the last run,
   then update each pump's 'name' value
*/
void getPumpValuesFromSD() {
  File myFile = SD.open(F("PVALS.txt"));
  byte tempByte;
  for (uint8_t i = 0; i < 8; i++) {
    char value[30] = {};
    uint8_t curString = 0;
    
    while (myFile.available()) {
      tempByte = myFile.read();
#if PRINT_TO_SERIAL
      Serial.print(tempByte);
      Serial.print(F("\t"));
      Serial.println(char(tempByte));
#endif
      if (tempByte == 13)       {break;}  // Carriage return character
      else if (tempByte == 10)  {}        // New line character
      else {
        value[curString] = char(tempByte);
        curString++;
      }
    }
    if (String(value) == "")  pumps[i].value = "NULL";
    else                      pumps[i].value = String(value);
  }
  myFile.close();
}

/*
   Loop through 'pumps' array and write all current ingreient names to a file
   stored on the SD card
*/
void setPumpValuesToSD() {
  if (SD.exists("PVALS.txt")) {
    SD.remove(F("PVALS.txt"));
  }
  File myFile = SD.open(F("PVALS.txt"), FILE_WRITE);
  if (myFile) {
    for (uint8_t i = 0; i < numOfPumps; i++) {
      Serial.println(pumps[i].value);
      myFile.println(pumps[i].value);
    }
  }
  myFile.close();
}

/*
   Write a string to the dataLog stored on the SD card
   Used for debugging purposes

   @param str   the string to write to the data log
*/
void writeDataLog(String str) {
  File myFile = SD.open("dataLog.txt", FILE_WRITE);
  if (myFile) {
    myFile.println(str);
    myFile.close();
  }
}

/*
   Print the entire contents of the data log to the Serial Monitor
*/
void readDataLog() {
  File myFile = SD.open(F("dataLog.txt"));
  Serial.println(F("dataLog.txt"));
  while (myFile.available()) {
    Serial.write(myFile.read());
  }
  myFile.close();
}

//================================================================================
// TEST FUNCTIONS
//================================================================================

/*
   Print to Serial all information relating to the pump objects in the 'pumps' array
*/
void serialPrintPumpInfo() {
#if PRINT_TO_SERIAL
  Serial.println(F("\nPRINTING PUMP INFO\n~~~~~~~~~~~~~~~~~~~~~~~~~~~"));
  for (uint8_t i = 0; i < numOfPumps; i++) {
    Serial.print(F("Pump Name: "));
    Serial.print(pumps[i].name);
    Serial.print(F("\tPump Value: "));
    Serial.print(pumps[i].value);
    uint8_t temp = pumps[i].value.length() / 8;
    switch (temp) {
      case 0:
        Serial.print(F("\t\t\t"));
        break;
      case 1:
        Serial.print(F("\t\t"));
        break;
      case 2:
      default:
        Serial.print(F("\t"));
        break;
    }
    Serial.print(F("Pump Address: "));
    Serial.print(pumps[i].address);
    Serial.print(F("\tStart: "));
    Serial.print(pumps[i].startTime);
    Serial.print(F("\tEnd: "));
    Serial.println(pumps[i].endTime);
  }
#endif
}

/*
   Print to Serial the entire contents of a chosen file on the SD card

   @param fileName  file name of desired file to read and print contents of
*/
void printFileContents(String fileName) {
  File myFile = SD.open(fileName);
  while (myFile.available()) {
    Serial.write(myFile.read());
  }
  myFile.close();
}

/*
   Loop through 'pumps' array turning on every relay associated
   Used for visually checking if relays are connected correctly
*/
void relayTest() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(pumps[i].pin, RELAY_ON);
#if PRINT_TO_SERIAL
    Serial.print(pumps[i].name);
    Serial.println(F(" Turned On"));
#endif
    delay(1000);
    digitalWrite(pumps[i].pin, RELAY_OFF);
#if PRINT_TO_SERIAL
    Serial.print(pumps[i].name);
    Serial.println(F(" Turned Off"));
#endif
  }
}
