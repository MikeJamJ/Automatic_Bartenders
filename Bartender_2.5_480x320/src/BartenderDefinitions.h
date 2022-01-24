#ifndef BartenderDefinitions_h
#define BartenderDefinitions_h

//LIBRARIES
#include "libs/Ingredient/Ingredient.h"
#include "libs/Drink/Drink.h"
#include "libs/DrinkList/DrinkList.h"
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

int PALLETTE = 1;

//if (PALLETTE == 1) {
  // Pallette 1
  /*#define BACKGROUND_COLOR	0xF7BD	//F1F7ED
  #define TEXT_COLOR	      0x0A0B	//08415C
  #define BASE_COLOR		    0xFB8C	//FF7063
  #define SECOND_COLOR	    0xC547	//C2A83E
  #define BORDER_COLOR	    0x6C11	//6B818C*/
//}
//else if (PALLETTE == 2) {
  // Pallette 2
  #define BACKGROUND_COLOR		0xFFFF	//FFFFFF
  #define TEXT_COLOR	        0x0000	//000000
  #define BASE_COLOR	        0xFFFF	//FFFFFF
  #define SECOND_COLOR	      0xC638	//C0C5C1
  #define BORDER_COLOR	      0x0000	//000000
//}

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

ButtonTri MainMenuRight = {458, 160, 422, 128, 422, 156, SECOND_COLOR, BORDER_COLOR};
ButtonTri MainMenuLeft = {20, 160, 56, 128, 56, 156, SECOND_COLOR, BORDER_COLOR};
ButtonTri PumpScrollRight = {398, 148, 362, 134, 362, 162, BACKGROUND_COLOR, BORDER_COLOR};
ButtonTri PumpScrollLeft = {86, 148, 122, 134, 122, 162, BACKGROUND_COLOR, BORDER_COLOR};
ButtonTri IngredientScrollLeft = {398, 191, 362, 177, 362, 205, BACKGROUND_COLOR, BORDER_COLOR};
ButtonTri IngredientScrollRight = {86, 191, 122, 177, 122, 205, BACKGROUND_COLOR, BORDER_COLOR};

#endif