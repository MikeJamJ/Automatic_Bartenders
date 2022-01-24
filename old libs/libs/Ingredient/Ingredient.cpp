#include "Arduino.h"
#include "Ingredient.h"

String Ingredient::getIngName() {
  return ingName;
}

float Ingredient::getPercentAlc() {
  return percentAlc;
}