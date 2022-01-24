/*
   AUTOMATIC BARTENDER 2.0
   The purpose of this is to create a bartender with 6 pumps. There are pre-defined drinks
   with correspoding ingredients. Two arrays are made. One (drink_list) containing all
   pre-defined drinks, and the second (possible_drinks) contains all the drinks that can be
   made using the ingredients attached to the pumps. In the main menu, you can scroll through
   the possible drinks and select one to be made.
*/

//Libraries I made
#include "Ingredient.h"
#include "Drink.h"

//Libraries for screen
#include <UTFT.h>
#include <URTouch.h>
#include <avr/pgmspace.h>
#include <Wire.h>

extern uint8_t SmallFont[];
extern uint8_t BigFont[];

//Library to see arduino memory
#include <MemoryFree.h>

//-----------------------------------------------------------------------------------------------
// GLOBAL VARIABLES -----------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------

//Defines relay pins on/off
#define RELAY_ON 0
#define RELAY_OFF 1

/*
 * PIN DEFINITOIONS
 */
//Motor pins
#define Relay_1  A0
#define Relay_2  A1
#define Relay_3  A2
#define Relay_4  A3
#define Relay_5  A4
#define Relay_6  A5

//Rotary Encooder
const int rotRight = 19; //CLK
const int rotLeft = 8; //DT
const int butSelect = 9; //SW

//Defines what ingredient is hooked up to each pump
String pump1 = "Sprite";
String pump2 = "Grenadine";
String pump3 = "Cranberry Juice";
String pump4 = "Margarita Mix";
String pump5 = "Orange Juice";
String pump6 = "Tequila";

String pumps[] = {pump1, pump2, pump3, pump4, pump5, pump6};

bool typeAlc = false;
bool typeNonAlc = false;
bool typeShot = false;

int endOfArray;

//Booleans for deciding between settings and main menu
bool MM = true;
bool SET = false;
bool SUBSET = false;

//variables for debouncing
volatile static unsigned long prevEventTime = 0;
volatile unsigned long eventTime;
int prevButtonTimer = 0;
int curButtonTimer = 0;

//variables for position in array
int lastPosition = 0;
volatile int position_ = 0;

//Defines 320x240 Screen and x and y coordinates of touch
UTFT myGLCD;
URTouch myTouch( 6, 5, 4, 3, 2);
int x = 0;
int y = 0;
byte lastButtonPressed = 1;

//-----------------------------------------------------------------------------------------------
// INGREDIENTS
//-----------------------------------------------------------------------------------------------

const Ingredient defaultIng[] = {
  Ingredient("default", 0)
};

const Ingredient bRussian_[] = {
  Ingredient("Kahlua", 30),
  Ingredient("Vodka", 30)
};

const Ingredient LITea_[] = {
  Ingredient("Vodka", 15),
  Ingredient("Rum", 15),
  Ingredient("Gin", 15),
  Ingredient("Triple Sec", 15),
  Ingredient("Tequila", 15),
  Ingredient("S&S Mix", 30)
};

const Ingredient wSour_[] = {
  Ingredient("Bourbon", 45),
  Ingredient("Lemon Juice", 22),
  Ingredient("Simple Syrup", 22)
};

const Ingredient bMf2_[] = {
  Ingredient("Vodka", 15),
  Ingredient("Gin", 15),
  Ingredient("Rum", 15),
  Ingredient("Tequila", 15),
  Ingredient("Blue Curacao", 15),
  Ingredient("S&S Mix", 44),
  Ingredient("Sprite", 148)
};

const Ingredient margMix_[] {
  Ingredient("Margarita Mix", 120),
  Ingredient("Tequila", 30)
};

const Ingredient teqSun_[] {
  Ingredient("Tequila", 50),
  Ingredient("Orange Juice", 150)
};

const Ingredient grGhost_[] {
  Ingredient("Gin", 59),
  Ingredient("Green Chartreuse", 15),
  Ingredient("Lime Juice", 15)
};

const Ingredient rumAndCoke_[] {
  Ingredient("Rum", 50),
  Ingredient("Coke", 150)
};

const Ingredient scrwDriv_[] {
  Ingredient("Vodka", 50),
  Ingredient("Orange Juice", 150)
};

const Ingredient ginAndJuice_[] {
  Ingredient("Gin", 50),
  Ingredient("Orange Juice", 150)
};

const Ingredient vodCran_[] {
  Ingredient("Vodka", 44),
  Ingredient("Cranberry Juice", 226)
};

const Ingredient bMart_[] = {
  Ingredient("Vodka", 30),
  Ingredient("Martini Mix", 90)
};

const Ingredient shirTemp_[] = {
  Ingredient("Orange Juice", 59),
  Ingredient("Sprite", 59),
  Ingredient("Grenadine", 4)
};


//-----------------------------------------------------------------------------------------------
// DRINKS
//-----------------------------------------------------------------------------------------------

//default drink for placeholder
const Drink defaultDrink("|Default", defaultIng, (sizeof(defaultIng) / sizeof(defaultIng[0])), 'X');

//variable to select which drink to make
Drink choice = defaultDrink;

/*1*/const Drink bRussian("Black Russian", bRussian_, (sizeof(bRussian_) / sizeof(bRussian_[0])), 'A');
/*2*/const Drink LITea("Long Island Tea", LITea_, (sizeof(LITea_) / sizeof(LITea_[0])), 'A');
/*3*/const Drink wSour("Whiskey Sour", wSour_, (sizeof(wSour_) / sizeof(wSour_[0])), 'A');
/*4*/const Drink bMF2("Blue MotherFucker 2", bMf2_, (sizeof(bMf2_) / sizeof(bMf2_[0])), 'A');
/*5*/const Drink margMix("Margarita (Mix)", margMix_, (sizeof(margMix_) / sizeof(margMix_[0])), 'A');
/*6*/const Drink grGhost("Green Ghost", grGhost_, (sizeof(grGhost_) / sizeof(grGhost_[0])), 'A');
/*7*/const Drink rumAndCoke("Rum & Coke", rumAndCoke_, (sizeof(rumAndCoke_) / sizeof(rumAndCoke_[0])), 'A');
/*8*/const Drink scrwDriv("Screwdriver", scrwDriv_, (sizeof(scrwDriv_) / sizeof(scrwDriv_[0])), 'A');
/*9*/const Drink ginAndJuice("Gin & Juice", ginAndJuice_, (sizeof(ginAndJuice_) / sizeof(ginAndJuice_[0])), 'A');
/*10*/const Drink teqSun("Tequila Sunrise", teqSun_, (sizeof(teqSun_) / sizeof(teqSun_[0])), 'A');
/*11*/const Drink vodCran("Vodka Cranberry", vodCran_, (sizeof(vodCran_) / sizeof(vodCran_[0])), 'A');
/*12*/const Drink bMart("BR Martini (Mix)", bMart_, (sizeof(bMart_) / sizeof(bMart_[0])), 'A');
/*13*/const Drink shirTemp("Shirley Temple", shirTemp_, (sizeof(shirTemp_) / sizeof(shirTemp_[0])), 'N');

//Array of all drinks
Drink drink_list[] = {bRussian, LITea, wSour, bMF2, margMix, grGhost, rumAndCoke, scrwDriv, ginAndJuice, teqSun, vodCran, bMart, shirTemp};//};

//Empty drink array for the ones that are displayed on the screen
Drink possible_drinks[] = {
  defaultDrink, //1
  defaultDrink, //2
  defaultDrink, //3
  defaultDrink, //4
  defaultDrink, //5
  defaultDrink, //6
  defaultDrink, //7
  defaultDrink, //8
  defaultDrink, //9
  defaultDrink, //10
  defaultDrink, //11
  defaultDrink, //12
  defaultDrink  //13
};

//-----------------------------------------------------------------------------------------------
// ISR
//-----------------------------------------------------------------------------------------------

void isr() {
  eventTime = millis();

  if (eventTime - prevEventTime > 5) {
    if (digitalRead(rotLeft) == LOW) {
      if (position_ == 0) {
        position_ = endOfArray;
      }
      else {
        position_--;
      }
    }

    else {
      if (possible_drinks[position_ + 1].drinkName[0] == defaultDrink.drinkName[0]) {
        position_ = 0;
      }
      else {
        position_++;
      }
    }

    prevEventTime = eventTime;
  }
}


//-----------------------------------------------------------------------------------------------
// SETUP
//-----------------------------------------------------------------------------------------------

void setup() {
  Serial.begin(74880);

  Serial.print("Beginning freeMemory() = ");
  Serial.println(freeMemory());
  Serial.print("\n");

  //Setup 320x240 TouchScreen
  myGLCD.InitLCD(LANDSCAPE);
  myGLCD.clrScr();
  myTouch.InitTouch(LANDSCAPE);
  myTouch.setPrecision(PREC_HI);

  //Setup relays
  digitalWrite(Relay_1, RELAY_OFF);
  digitalWrite(Relay_2, RELAY_OFF);
  digitalWrite(Relay_3, RELAY_OFF);
  digitalWrite(Relay_4, RELAY_OFF);
  digitalWrite(Relay_5, RELAY_OFF);
  digitalWrite(Relay_6, RELAY_OFF);

  pinMode(Relay_1, OUTPUT);
  pinMode(Relay_2, OUTPUT);
  pinMode(Relay_3, OUTPUT);
  pinMode(Relay_4, OUTPUT);
  pinMode(Relay_5, OUTPUT);
  pinMode(Relay_6, OUTPUT);

  //Setup scrolling buttons
  pinMode(rotRight, INPUT);
  pinMode(rotLeft, INPUT);
  pinMode(butSelect, INPUT_PULLUP);

  displayLogo();

  Serial.println("SORTING");
  Serial.print("\n");
  //displayLogo();

  //Sort and compile list of drinks that can be made using the drinks connected to pumps
  printAllDrinks();
  delay(500);
  possibleDrinks();
  delay(500);
  alphabetize();
  delay(500);
  printPossibleDrinks();

  delay(3000);

  cli();
  attachInterrupt(4, isr, LOW);
  sei();

  Serial.println("START");
  endOfArray = findEndOfArray(endOfArray);
}

//-----------------------------------------------------------------------------------------------
// LOOP
//-----------------------------------------------------------------------------------------------

void loop() {
  //Decide between settings and main menu screens
  Serial.println("BEGINNING OF LOOP");
  if (SET == true) {
    settingsScreen();
    settings();
  }
  else if (MM == true) {
    homeScreen();
    mainMenu();
  }
  Serial.println("END OF LOOP");
}
