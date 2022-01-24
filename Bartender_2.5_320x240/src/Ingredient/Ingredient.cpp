#include "Arduino.h"
#include "Ingredient.h"

String Ingredient::getIngName() {
  return ingName;
}

byte Ingredient::getIngVal() {
  return ingVal;
}

