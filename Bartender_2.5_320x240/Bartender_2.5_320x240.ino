/*
   AUTOMATIC BARTENDER 2.5
   The purpose of this is to create a bartender with 6 pumps. There are pre-defined drinks
   with correspoding ingredients. Two arrays are made. One (drink_list) containing all
   pre-defined drinks, and the second (possible_drinks) contains all the drinks that can be
   made using the ingredients attached to the pumps. In the main menu, you can scroll through
   the possible drinks and select one to be made. 
*/

//Libraries I made
#include "src/Ingredient/Ingredient.h"
#include "src/Drink/Drink.h"
#include "src/DrinkList/DrinkList.h"
//Libraries for screen
//#include <SdFat.h>
#include <Adafruit_GFX.h>
#include <UTFTGLUE.h>
#include <avr/pgmspace.h>
#include <Wire.h>
//#include <UTFT_SdRaw.h>
//Library to see arduino memory
#include <MemoryFree.h>
//Saving Drink values
#include <EEPROM.h>

//Defines relay pins on/off
#define RELAY_ON 0
#define RELAY_OFF 1

//Color definitions
#define OFF_BLACK 13, 13, 13
#define OFF_WHITE 252, 252, 252
#define SM_DARK_GREY 43, 43, 43
#define SM_LIGHT_GREY 150, 150, 150

/*
   DEFINITIONS TO CHANGE
*/
//Pump speed
#define PUMPSPEEDML 100
//Motor pins
#define Relay_1  A8
#define Relay_2  A9
#define Relay_3  A10
#define Relay_4  A11
#define Relay_5  A12
#define Relay_6  A13
#define Relay_7  A14
#define Relay_8  A15

//-----------------------------------------------------------------------------------------------
// GLOBAL VARIABLES -----------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------

/*
   PIN DEFINITOIONS
*/
//Rotary Encooder
const byte rotRight = 19; //CLK interrupt pin 4
const byte rotLeft = 18; //DT interrupt pin 5
const byte butSelect = 17; //SW

/*
   PUMP DEFINITOIONS
*/
//Defines what ingredient is hooked up to each pump
String pump1 = "Vodka";
String pump2 = "Tequila";
String pump3 = "Rum";
String pump4 = "Coke";
String pump5 = "Orange Juice";
String pump6 = "Margarita Mix";
String pumps[] = {pump1, pump2, pump3, pump4, pump5, pump6};

/*
   BOOLEAN DEFINITOIONS
*/
//Booleans for deciding between settings and main menu
bool MM = true;
bool SET = false;
bool SUBSET = false;

/*
   OTHER DEFINITIONS
*/
//variables for debouncing
volatile unsigned long eventTime = 0;
volatile unsigned long prevEventTime = 0;
volatile boolean changed = false;
int curButtonTime = 0;
int prevButtonTime = 0;
//variables for position in array
volatile int pos = 0;
byte lastPos = 0;
byte endOfDrinkList = 0;

extern uint8_t SmallFont[];
extern uint8_t BigFont[];

extern unsigned short margarita_img[0x3840];
extern unsigned short shirleyTemple_img[0x3840];
extern unsigned short color_gradient[0x2008];

//Defines 320x240 Screen and x and y coordinates of touch
UTFTGLUE myGLCD(0x9486, A3, A2, A1, A0, A4);
//URTouch myTouch( 6, 5, 4, 3, 2);

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

/*~*/const Drink defaultDrink("|Default", defaultIng, (sizeof(defaultIng) / sizeof(defaultIng[0])), 'X'); //default drink for placeholder
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

Drink drink_list[] = {bRussian, LITea, wSour, bMF2, margMix, grGhost, rumAndCoke, scrwDriv, ginAndJuice, teqSun, vodCran, bMart, shirTemp}; //Array of all drinks
DrinkList completeDrinks(drink_list, (sizeof(drink_list) / sizeof(drink_list[0])));

Drink choice = defaultDrink; //variable to select which drink to make

//-----------------------------------------------------------------------------------------------
// ISR's
//-----------------------------------------------------------------------------------------------

void isrA() {
  eventTime = millis();
  if (eventTime - prevEventTime > 2) {
    if (changed == true) {
      pos--;
      changed = false;
    }
    else if (changed == false) changed = true;
  }
  prevEventTime = eventTime;
}


void isrB() {
  eventTime = millis();
  if (eventTime - prevEventTime > 2) {
    if (changed == true) {
      pos++;
      changed = false;
    }
    else if (changed == false) changed = true;
  }
  prevEventTime = eventTime;
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
  //myTouch.InitTouch(LANDSCAPE);
  //myTouch.setPrecision(PREC_HI);

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
  setIngs();  
  completeDrinks.printDrinks();

  cli();
  attachInterrupt(4, isrA, CHANGE);
  attachInterrupt(5, isrB, CHANGE);
  sei();

  Serial.println("START");
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
    menuScreen();
    mainMenu();
  }
  Serial.println("END OF LOOP");

}


void resetPosValue(){
  pos = 0;
  Serial.print("position: ");
  Serial.println(pos);
}


//Sort and compile list of drinks that can be made using the drinks connected to pumps
void mainMenuSetup(DrinkList possible_drinks){
  completeDrinks.findPossibleDrinks(possible_drinks, pumps, defaultDrink);
  possible_drinks.alphabetize(defaultDrink);
  possible_drinks.printDrinks();
  endOfDrinkList = possible_drinks.findEndOfDrinkList(defaultDrink);
}


void setIngs() {

}

