#ifndef Recipe_h
#define Recipe_h

#include "Arduino.h"

class Recipe {
  private:
    Ingredient *ing
    byte ingVolume

  public:
    Recipe (Ingredient *ing_, float percentAlc_) {
      ing = ing_;
      percentAlc = percentAlc_;
    }

    Recipe () {}
    ~Recipe () {}

    byte getIngVolume();
    Ingredient getIng();
};

#endif
