#include "Arduino.h"
#include "Recipe.h"

int Recipe::getIngVol() {
    return ingVolume;
}

Ingredient Recipe::getIng() {
    return ing;
}