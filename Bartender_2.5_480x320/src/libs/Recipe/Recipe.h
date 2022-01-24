#ifndef Recipe_h
#define Recipe_h

#include "../Ingredient/Ingredient.h"

class Recipe {
  private:
    Ingredient ing;
    int ingVolume;

  public:
    Recipe (Ingredient ing_, int ingVolume_) {
      ing = ing_;
      ingVolume = ingVolume_;
    }

    Recipe () {}
    ~Recipe () {}
    
    int getIngVol();
    Ingredient getIng();
};

#endif
