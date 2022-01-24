#include "Arduino.h"
#include "Recipe.h"

byte Recipe::getIngVolume() {
    return ingVolume;
}

Ingredient Recipe::getIng() {
    return ing;
}