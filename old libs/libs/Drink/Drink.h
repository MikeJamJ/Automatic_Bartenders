#ifndef Drink_h
#define Drink_h

#include "Arduino.h"
#include "../Ingredient/Ingredient.h"

#define MLPERDRINK 18.0

class Drink: public Ingredient {
  private:
    String drinkName;
    const Recipe *recipe;
    byte size;
    char type;
	  int image_size = 14400;
    int totalVol;
    float totalPercentAlc;
    float totalDrinkNum;

  public:
  	const uint16_t *image;
  	
    Drink (String drinkName_, const Recipe *recipe_, byte size_, char type_, const uint16_t *image_) {
      drinkName = drinkName_;
      recipe = recipe_;
      size = size_;
      type = type_;
      image = image_;
      totalVol = calcTotalVol();
      totalPercentAlc = calcTotalPercentAlc();
      totalDrinkNum = calcTotalDrinkNum();
    }
    
    /*Drink (String drinkName_, Ingredient ingredients_[], byte size_, char type_) {
      drinkName = drinkName_;
      ingredients = ingredients_;
      size = size_;
      type = type_;
      image = margarita_img;
    }*/

    Drink () {}
    ~Drink () {}

    String getDrinkName();
    Ingredient getIngredient(int a);
    byte getSize();
    char getType();
    
    int calcTotalVol();
    float calcTotalPercentAlc();
    float calcTotalDrinkNum();

    void serialPrintDrinkInfo();
};

#endif
