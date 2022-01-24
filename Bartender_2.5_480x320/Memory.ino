/*
   Functions for struct Pump

*/

/*

   Reading and writing to memory

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

void getPumpValuesFromSD() {
  myFile = SD.open(pumpFileName);
  for (uint8_t i = 0; i < 8; i++) {
    char value[30] = {};
    uint8_t curString = 0;
#if PRINT_TO_SERIAL
    Serial.println(F("NEW FOR LOOP"));
    Serial.print(F("Spot in for loop: "));
    Serial.println(i);
    Serial.print(F("curString: "));
    Serial.println(curString);
#endif
    while (myFile.available()) {
      byte tempByte = myFile.read();
#if PRINT_TO_SERIAL
      Serial.print(tempByte);
      Serial.print(F("\t"));
      Serial.println(char(tempByte));
#endif
      if (tempByte == '\0') {
#if PRINT_TO_SERIAL
        Serial.println(F("BREAK REACHED"));
#endif
        break;
      }
      else {
        value[curString] = char(tempByte);
        curString++;
      }
    }
    pumps[i].value = String(value);
  }
  myFile.close();
}

void setPumpValuesToSD() {
  if (SD.exists(pumpFileName)) {
    SD.remove(pumpFileName);
  }
  myFile = SD.open(pumpFileName, FILE_WRITE);
  if (myFile) {
    for (uint8_t i = 0; i < 8; i++) {
      myFile.println(pumps[i].value + '\0');
    }
  }
}

void writeDataLog(String str) {
  dataLog = SD.open(F("dataLog.txt"), FILE_WRITE);
  if(dataLog) {
    dataLog.println(str);
    dataLog.close();
  }
}

void readDataLog() {
  dataLog = SD.open("dataLog.txt");
  Serial.println(F("dataLog.txt"));
  while(dataLog.available()) {
    Serial.write(dataLog.read());
  }
  dataLog.close();
}

/*

   Test functions

*/
void serialPrintPumpInfo() {
#if PRINT_TO_SERIAL
  Serial.println(F("\nPRINTING PUMP INFO\n~~~~~~~~~~~~~~~~~~~~~~~~~~~"));
  for (uint8_t i = 0; i < numOfPumps; i++) {
    Serial.print(F("Pump Name: "));
    Serial.print(pumps[i].name);
    Serial.print(F("\tPump Value: "));
    Serial.print(pumps[i].value);
    Serial.print(F("\t\t\tPump Address: "));
    Serial.print(pumps[i].address);
    Serial.print(F("\tStart: "));
    Serial.print(pumps[i].startTime);
    Serial.print(F("\tEnd: "));
    Serial.println(pumps[i].endTime);
  }
#endif
}

void printFileContents(String fileName) {
  myFile = SD.open(fileName);
  while (myFile.available()) {
    Serial.write(myFile.read());
  }
  myFile.close();
}

void relayTest() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(pumps[i].pin, RELAY_ON);
    Serial.print(pumps[i].name);
    Serial.println(" Turned On");
    delay(1000);
    digitalWrite(pumps[i].pin, RELAY_OFF);
    Serial.print(pumps[i].name);
    Serial.println(" Turned Off");
  }
}
