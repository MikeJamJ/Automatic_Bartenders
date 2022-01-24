/*
 * AUTOMATIC BARTENDER
 * The purpose of this is to create a bartender with 6 pumps. There are pre-defined drinks
 * with correspoding ingredients. Two arrays are made. One (drink_list) containing all 
 * pre-defined drinks, and the second (possible_drinks) contains all the drinks that can be 
 * made using the ingredients attached to the pumps. In the main menu, you can scroll through
 * the possible drinks and select one to be made.
 */


#include "Ingredient.h"
#include "Drink.h"
#include <LiquidCrystal_I2C.h>
#include <LCD.h>
#include <Wire.h>
#include <MemoryFree.h>

//-----------------------------------------------------------------------------------------------
// GLOBAL VARIABLES -----------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------

//Defines relay pins
#define RELAY_ON 0
#define RELAY_OFF 1

#define Relay_1  2
#define Relay_2  3
#define Relay_3  4
#define Relay_4  5
#define Relay_5  6
#define Relay_6  7

//Defines what drink is hooked up to each pump
String pump1 = "Vodka";
String pump2 = "null";
String pump3 = "Cranberry Juice";
String pump4 = "null";
String pump5 = "null";
String pump6 = "null";

String pumps[] = {pump1, pump2, pump3, pump4, pump5, pump6};

//Defines LCD display
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7);

//Defines buttons for scrolling and selecting drinks
int butSelect = 9;
int butLeft = 10;
int butRight = 11;

//Booleans for deciding between settings and main menu
bool MM = true;
bool SET = false;
bool SUBSET = false;

//variables for debouncing
long unsigned eventTime;
long unsigned prevEventTime;

//variables to detect short or long presses
int prevButtonTimer = 0;
int curButtonTimer = 0;

/*
 * Creates custom characters for Logo
 */
byte dropletBL[8] = {
  0x10,
  0x10,
  0x10,
  0x12,
  0x0A,
  0x09,
  0x04,
  0x03
};

byte dropletBR[8] = {
  0x02,
  0x01,
  0x01,
  0x01,
  0x02,
  0x02,
  0x04,
  0x18
};

byte dropletTR[8] = {
  0x00,
  0x00,
  0x00,
  0x10,
  0x10,
  0x08,
  0x04,
  0x04
};

byte dropletTL[8] = {
  0x00,
  0x02,
  0x03,
  0x02,
  0x02,
  0x04,
  0x08,
  0x08
};

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

const Ingredient teqSun_[]{
  Ingredient("Tequila", 50),
  Ingredient("Orange Juice", 150)
};

const Ingredient grGhost_[]{
  Ingredient("Gin", 59),
  Ingredient("Green Chartreuse", 15),
  Ingredient("Lime Juice", 15) 
};

const Ingredient rumAndCoke_[]{
  Ingredient("Rum", 50),
  Ingredient("Coke", 150)
};

const Ingredient scrwDriv_[]{
  Ingredient("Vodka", 50),
  Ingredient("Orange Juice", 150)
};

const Ingredient ginAndJuice_[]{
  Ingredient("Gin", 50),
  Ingredient("Orange Juice", 150)
};

const Ingredient vodCran_[]{
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
const Drink defaultDrink("|Default", defaultIng, (sizeof(defaultIng) / sizeof(defaultIng[0])));

//variable to select which drink to make
Drink choice = defaultDrink;

/*1*/const Drink bRussian("Black Russian", bRussian_, (sizeof(bRussian_) / sizeof(bRussian_[0])));
/*2*/const Drink LITea("Long Island Tea", LITea_, (sizeof(LITea_) / sizeof(LITea_[0])));
/*3*/const Drink wSour("Whiskey Sour", wSour_, (sizeof(wSour_) / sizeof(wSour_[0])));
/*4*/const Drink bMF2("Blue MotherFucker 2", bMf2_, (sizeof(bMf2_) / sizeof(bMf2_[0])));
/*5*/const Drink margMix("Margarita (Mix)", margMix_, (sizeof(margMix_) / sizeof(margMix_[0])));
/*6*/const Drink grGhost("Green Ghost", grGhost_, (sizeof(grGhost_) / sizeof(grGhost_[0])));
/*7*/const Drink rumAndCoke("Rum & Coke", rumAndCoke_, (sizeof(rumAndCoke_) / sizeof(rumAndCoke_[0])));
/*8*/const Drink scrwDriv("Screwdriver", scrwDriv_, (sizeof(scrwDriv_) / sizeof(scrwDriv_[0])));
/*9*/const Drink ginAndJuice("Gin & Juice", ginAndJuice_, (sizeof(ginAndJuice_) / sizeof(ginAndJuice_[0])));
/*10*/const Drink teqSun("Tequila Sunrise", teqSun_, (sizeof(teqSun_) / sizeof(teqSun_[0])));
/*11*/const Drink vodCran("Vodka Cranberry", vodCran_, (sizeof(vodCran_) / sizeof(vodCran_[0])));
/*12*/const Drink bMart("BR Martini (Mix)", bMart_, (sizeof(bMart_) / sizeof(bMart_[0])));
/*13*/const Drink shirTemp("Shirley Temple", shirTemp_, (sizeof(shirTemp_) / sizeof(shirTemp_[0])));

//Array of all drinks
Drink drink_list[] = {bRussian, wSour, margMix, teqSun, LITea, grGhost, rumAndCoke, scrwDriv, ginAndJuice, bMF2, vodCran};//};

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

void setup() {
  Serial.begin(9600);

  Serial.println("freeMemory()= ");
  Serial.println(freeMemory());
  
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
  
  //Setup LCD sccreen size and backlight pin 
  lcd.begin(16, 2);
  lcd.setBacklightPin(3, POSITIVE);
  lcd.setBacklight(HIGH);

  //Setup cutom characters
  lcd.createChar(1, dropletTL);
  lcd.createChar(2, dropletTR);
  lcd.createChar(3, dropletBL);
  lcd.createChar(4, dropletBR);

  //Setup scrolling buttons
  pinMode(butLeft, INPUT);
  pinMode(butRight, INPUT);
  pinMode(butSelect, INPUT);

  displayLogo();
  
  //Sort and compile list of drinks that can be made using the drinks connected to pumps
  printAllDrinks();
  possibleDrinks();
  alphabetize();
  printPossibleDrinks();

  delay(3000);
}

//-----------------------------------------------------------------------------------------------
// LOOP
//-----------------------------------------------------------------------------------------------

void loop() {
  //Decide between settings and main menu screens
  Serial.println("BEGINNING OF LOOP");
  if (SET == true) {
    settings();
  }
  else if (MM == true) {
    mainMenu();
  }
  Serial.println("END OF LOOP");
}
