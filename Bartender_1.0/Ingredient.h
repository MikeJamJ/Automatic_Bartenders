#ifndef Ingredient_h
#define Ingredient_h

#include "Arduino.h"

class Ingredient {
  public:
    String ingName;
    int ingVal;

    Ingredient (String ingName_, int ingVal_) {
      ingName = ingName_;
      ingVal = ingVal_;
    }
};

#endif
