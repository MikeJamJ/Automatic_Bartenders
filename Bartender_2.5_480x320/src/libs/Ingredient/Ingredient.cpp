#include "Arduino.h"
#include "Ingredient.h"

String Ingredient::getIngName() {
  return ingName;
}

byte Ingredient::getIngVol() {
  return ingVol;
}

float Ingredient::getPercentAlc() {
  return percentAlc;
}