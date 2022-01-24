#ifndef Ingredient_h
#define Ingredient_h

#include "Arduino.h"

class Ingredient {
  private:
    String ingName;
    byte ingVol;
    float percentAlc;

  public:
    Ingredient (String ingName_, int ingVol_) {
      ingName = ingName_;
      ingVol = ingVol_;
      percentAlc = 0.0;
    }

    Ingredient () {}
    ~Ingredient () {}

    String getIngName();
    byte getIngVol();
    float getPercentAlc();
};

#endif
