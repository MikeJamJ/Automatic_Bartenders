#ifndef Drink_h
#define Drink_h

#include "Arduino.h"
#include "Ingredient.h"

class Drink {
  public:
    String drinkName;
    Ingredient *ingredients;
    byte size;

    Drink (String drinkName_, Ingredient ingredients_[], byte size_) {
      drinkName = drinkName_;
      ingredients = ingredients_;
      size = size_;
    }
};

#endif
