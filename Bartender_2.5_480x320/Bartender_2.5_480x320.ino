/*
   AUTOMATIC BARTENDER 2.5
   The purpose of this is to create a bartender with 8 pumps. There are pre-defined drinks
   with correspoding ingredients. Two arrays are made. One (drink_list) containing all
   pre-defined drinks, and the second (possible_drinks) contains all the drinks that can be
   made using the ingredients attached to the pumps. In the main menu, you can scroll through
   the possible drinks and select one to be made.
*/

#include "src/BartenderDefinitions.h"
//  SCREEN LIBRARIES
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
//  SD LIBRARIES
#include <SPI.h>
#include <SD.h>
//  ARDUINO MEMORY
#include <MemoryFree.h>
#include <EEPROM.h>

#define PRINT_TO_SERIAL 1

/*
   DEFINITIONS TO CHANGE
*/

#define PUMPSPEEDML   500   //Pump speed
#define Relay_1       A8    //Motor pins
#define Relay_2       A9
#define Relay_3       A10
#define Relay_4       A11
#define Relay_5       A12
#define Relay_6       A13
#define Relay_7       A14
#define Relay_8       A15
#define Pump1Address  0     //EEPROM Pump Addresses 
#define Pump2Address  30
#define Pump3Address  60
#define Pump4Address  90
#define Pump5Address  120
#define Pump6Address  150
#define Pump7Address  180
#define Pump8Address  210

//================================================================================
// GLOBAL VARIABLES
//================================================================================

//  DEFUALT FONT DIMENSIONS
byte TEXT_HEIGHT = 8;
byte TEXT_WIDTH = 6;

//  ROTARY PIN DEFINITIONS
const byte rotRight = 19;   //CLK interrupt pin 4
const byte rotLeft = 18;    //DT interrupt pin 5
const byte butSelect = 17;  //SW

//  PUMP DEFINITIONS
Pump pumps[] = {
  Pump{"Pump 1", "NULL", Pump1Address, Relay_1, 0, 0},
  Pump{"Pump 2", "NULL", Pump2Address, Relay_2, 0, 0},
  Pump{"Pump 3", "NULL", Pump3Address, Relay_3, 0, 0},
  Pump{"Pump 4", "NULL", Pump4Address, Relay_4, 0, 0},
  Pump{"Pump 5", "NULL", Pump5Address, Relay_5, 0, 0},
  Pump{"Pump 6", "NULL", Pump6Address, Relay_6, 0, 0},
  Pump{"Pump 7", "NULL", Pump7Address, Relay_7, 0, 0},
  Pump{"Pump 8", "NULL", Pump8Address, Relay_8, 0, 0}
};
uint8_t numOfPumps = ARRAYCOUNT(pumps);

//  BOOLEAN DEFINITIONS
bool b_MM = true;
bool b_SET = false;
bool b_SUBSET = false;
bool b_SD_CONNECTED = false;

//  ROTARY ENCODER
volatile unsigned long time_isrA = 0;
volatile unsigned long prevTime_isrA = 0;
volatile unsigned long time_isrB = 0;
volatile unsigned long prevTime_isrB = 0;
volatile boolean isrATrig = 0;
volatile boolean isrBTrig = 0;

//  DEBOUNCING
uint16_t curButtonTime = 0;
uint16_t prevButtonTime = 0;

//  POSITION IN ARRAY
volatile int8_t pos = 0;
uint8_t lastPos = 0;
uint8_t endOfDrinkList = 0;

//  DEFINES 480x320 SCREEN
MCUFRIEND_kbv tft;

//================================================================================
// DRINK
//================================================================================

Drink choice = defaultDrink; //variable to select which drink to make

//================================================================================
// ISR's
//================================================================================

void isrA() {
  time_isrA = millis();
  if (time_isrA - prevTime_isrA > 2) {
    if (isrATrig) {}  //do nothing, isrA should not be called twice in a row
    else if (!isrATrig) {
      if (isrBTrig) {
        pos--;
        isrATrig = 1;
      }
      else if (!isrBTrig) {
        isrATrig = 1;
      }
    }
  }
  if (isrATrig && isrBTrig) {
    isrATrig = 0;
    isrBTrig = 0;
  }
  prevTime_isrA = time_isrA;
  while (digitalRead(rotRight) != digitalRead(rotLeft)) {}
}

void isrB() {
  time_isrB = millis();
  if (time_isrB - prevTime_isrB > 2) {
    if (isrBTrig) {}  //do nothing, isrB should not be called twice in a row
    else if (!isrBTrig) {
      if (isrATrig) {
        pos++;
        isrBTrig = 1;
      }
      else if (!isrATrig) {
        isrBTrig = 1;
      }
    }
  }
  if (isrATrig && isrBTrig) {
    isrATrig = 0;
    isrBTrig = 0;
  }
  prevTime_isrB = time_isrB;
  while (digitalRead(rotRight) != digitalRead(rotLeft)) {}
}

//================================================================================
// SETUP
//================================================================================

void setup() {
  Serial.begin(74880);

  Serial.print(F("SD card initializing on pin "));
  Serial.print(chipSelect);
  Serial.print(F("..."));
  if (!SD.begin(chipSelect)) {
    Serial.println(F("initialization failed"));
    b_SD_CONNECTED = false;
  } else {
    b_SD_CONNECTED = true;
  }
  Serial.println(F("initialization succeeded"));

  Serial.print(F("Beginning freeMemory() = "));
  Serial.println(freeMemory());
  Serial.print(F("\n"));

  tft.reset();  //setup 480x320 TouchScreen
  tft.begin(tft.readID());
  tft.setRotation(1);

  drawLogo();

  //setup relay pins
  digitalWrite(Relay_1, RELAY_OFF);
  digitalWrite(Relay_2, RELAY_OFF);
  digitalWrite(Relay_3, RELAY_OFF);
  digitalWrite(Relay_4, RELAY_OFF);
  digitalWrite(Relay_5, RELAY_OFF);
  digitalWrite(Relay_6, RELAY_OFF);
  digitalWrite(Relay_7, RELAY_OFF);
  digitalWrite(Relay_8, RELAY_OFF);
  pinMode(Relay_1, OUTPUT);
  pinMode(Relay_2, OUTPUT);
  pinMode(Relay_3, OUTPUT);
  pinMode(Relay_4, OUTPUT);
  pinMode(Relay_5, OUTPUT);
  pinMode(Relay_6, OUTPUT);
  pinMode(Relay_7, OUTPUT);
  pinMode(Relay_8, OUTPUT);
  // setup rotary encoder pins
  pinMode(rotRight, INPUT);
  pinMode(rotLeft, INPUT);
  pinMode(butSelect, INPUT_PULLUP);
  // setup interrupts
  cli();
  attachInterrupt(4, isrA, CHANGE);
  attachInterrupt(5, isrB, CHANGE);
  sei();

  delay(2000);

  if (b_SD_CONNECTED) getPumpValuesFromSD();
  else      getPumpValuesFromMemory();
  serialPrintPumpInfo();

  chooseOption();
  serialPrintMDL();

  Serial.println(F("START"));
}

//================================================================================
// LOOP
//================================================================================

void loop() {
#if PRINT_TO_SERIAL
  Serial.println(F("BEGINNING OF LOOP"));
#endif

  if (b_SET == true)      settings();
  else if (b_MM == true)  mainMenu();

#if PRINT_TO_SERIAL
  Serial.println(F("END OF LOOP"));
#endif
}


void resetPosValue() {
  pos = 0;
  lastPos = pos;
#if PRINT_TO_SERIAL
  Serial.print(F("position: "));
  Serial.println(pos);
#endif
}

void serialPrintPosValue() {
#if PRINT_TO_SERIAL
  Serial.print(F("position: "));
  Serial.println(pos);
#endif
}
