#ifndef Drink_h
#define Drink_h

#include "Arduino.h"
#include "../Ingredient/Ingredient.h"

class Drink: public Ingredient {
  private:
    String drinkName;
    Ingredient *ingredients;
    byte size;
    char type;

  public:
    Drink (String drinkName_, Ingredient ingredients_[], byte size_, char type_) {
      drinkName = drinkName_;
      ingredients = ingredients_;
      size = size_;
      type = type_;
    }

    Drink () {}
    ~Drink () {}

    String getDrinkName();
    Ingredient getIngredient(int a);
    byte getSize();
    char getType();
    int calcTotalVol();
};

#endif
