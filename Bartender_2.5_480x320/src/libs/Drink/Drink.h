#ifndef Drink_h
#define Drink_h

#include "../Recipe/Recipe.h"

#define MLPERDRINK 18.0

class Drink: public Ingredient {
  private:
    String drinkName;
    const Recipe *recipe;
    uint8_t size;
    char type;
    uint16_t totalVol;
    float totalPercentAlc;
    float totalDrinkNum;

  public:
  	String image;
  	
    Drink (String drinkName_, const Recipe *recipe_, byte size_, char type_, String image_) {
      drinkName = drinkName_;
      recipe = recipe_;
      size = size_;
      type = type_;
      image = image_;
      totalVol = calcTotalVol();
      totalPercentAlc = calcTotalPercentAlc();
      totalDrinkNum = calcTotalDrinkNum();
    }

    Drink () {}
    ~Drink () {}

    String getDrinkName();
    Recipe getRecipe(int a);
    Ingredient getIngredient(int a);
    byte getSize();
    char getType();
    uint16_t getTotalVol();
    float getTotalPercentAlc();
    float getTotalDrinkNum();
    
    uint16_t calcTotalVol();
    float calcTotalPercentAlc();
    float calcTotalDrinkNum();

    void serialPrintDrinkInfo();
};

#endif
