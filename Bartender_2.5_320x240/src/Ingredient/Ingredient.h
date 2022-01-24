#ifndef Ingredient_h
#define Ingredient_h

#include "Arduino.h"

class Ingredient {
  private:
    String ingName;
    byte ingVal;

  public:
    Ingredient (String ingName_, int ingVal_) {
      ingName = ingName_;
      ingVal = ingVal_;
    }

    Ingredient () {}
    ~Ingredient () {}

    String getIngName();
    byte getIngVal();
};

#endif
