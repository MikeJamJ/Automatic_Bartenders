#ifndef Ingredient_h
#define Ingredient_h

#include "Arduino.h"

class Ingredient {
  private:
    String ingName;
    float percentAlc;

  public:
    Ingredient (String ingName_, float percentAlc_) {
      ingName = ingName_;
      percentAlc = percentAlc_;
    }

    Ingredient () {}
    ~Ingredient () {}

    String getIngName();
    float getPercentAlc();
};

#endif
