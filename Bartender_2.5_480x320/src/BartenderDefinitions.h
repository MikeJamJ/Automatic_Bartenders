#ifndef BartenderDefinitions_h
#define BartenderDefinitions_h

#define ARRAYCOUNT(x)     (sizeof(x)/sizeof(x[0]))

//LIBRARIES
#include "libs/Ingredient/Ingredient.h"
#include "libs/Recipe/Recipe.h"
#include "libs/Drink/Drink.h"
#include "libs/DrinkArrays.h"
#include "libs/DataLists/ListOfIngredients.h"
#include "libs/DataLists/ListOfDrinks.h"

//  RELAY ON/OFF
#define RELAY_ON 0
#define RELAY_OFF 1

//  DRINK IMAGE SIZES
#define IMAGE_W 90
#define IMAGE_H 160

/*
  SD Card:
  MISO/DO = 50
  MOSI/DI = 51
  SCK = 52
*/
#define chipSelect 53

#define PALLETTE1 0
#define PALLETTE2 1

#if PALLETTE1
  #define BACKGROUND_COLOR	0xF7BD	//F1F7ED
  #define TEXT_COLOR	      0x0A0B	//08415C
  #define BASE_COLOR		    0xFB8C	//FF7063
  #define SECOND_COLOR	    0xC547	//C2A83E
  #define BORDER_COLOR	    0x6C11	//6B818C
#endif
#if PALLETTE2
  #define BACKGROUND_COLOR  0xFFFF	//FFFFFF
  #define TEXT_COLOR	      0x0000	//000000
  #define BASE_COLOR	      0xFFFF	//FFFFFF
  #define SECOND_COLOR	    0xC638	//C0C5C1
  #define BORDER_COLOR	    0x0000	//000000
#endif

struct ButtonRect {
  int x;
  int y;
  uint16_t width;
  uint16_t height;
  uint16_t baseColor;
  uint16_t selectColor;
  String string;
  uint8_t textSize;
  uint16_t textColor;
  byte border;
  uint16_t borderColor;
};

struct ButtonTri {
  int x1;
  int y1;
  int x2;
  int y2;
  int x3;
  int y3;
  uint16_t baseColor;
  uint16_t selectColor;
};

ButtonRect UseCurrent = {20, 73, 187, 53, BASE_COLOR, SECOND_COLOR, "Use Current", 2, TEXT_COLOR, 3, BORDER_COLOR};
ButtonRect AlterCurrent = {20, 150, 187, 53, BASE_COLOR, SECOND_COLOR, "Alter Current", 2, TEXT_COLOR, 3, BORDER_COLOR};
ButtonRect SetNew = {20, 227, 187, 53, BASE_COLOR, SECOND_COLOR, "Set New", 2, TEXT_COLOR, 3, BORDER_COLOR};
ButtonRect Swap = {71, 70, 338, 53, BASE_COLOR, SECOND_COLOR, "Swap Ingredients", 2, TEXT_COLOR, 3, BORDER_COLOR};
ButtonRect Run = {71, 134, 338, 53, BASE_COLOR, SECOND_COLOR, "Prime / Run Pump", 2, TEXT_COLOR, 3, BORDER_COLOR};

ButtonTri MainMenuRight = {458, 160, 438, 146, 438, 174, SECOND_COLOR, BORDER_COLOR};
ButtonTri MainMenuLeft = {20, 160, 40, 146, 40, 174, SECOND_COLOR, BORDER_COLOR};
ButtonTri PumpScrollRight = {416, 148, 396, 134, 396, 162, BACKGROUND_COLOR, BORDER_COLOR};
ButtonTri PumpScrollLeft = {62, 148, 82, 134, 82, 162, BACKGROUND_COLOR, BORDER_COLOR};
ButtonTri IngredientScrollRight = {416, 245, 396, 231, 396, 259, BACKGROUND_COLOR, BORDER_COLOR};
ButtonTri IngredientScrollLeft = {62, 245, 82, 231, 82, 259, BACKGROUND_COLOR, BORDER_COLOR};

#endif