#include "Arduino.h"
#include "Drink.h"


String Drink::getDrinkName() {
  return drinkName;
}


Ingredient Drink::getIngredient(int a){
  return ingredients[a];
}


byte Drink::getSize() {
  return size;
}


char Drink::getType() {
  return type;
}


// Calculates the volume of liquid each drink will produce
int Drink::calcTotalVol () {
  int totalVol = 0;
  for (int i = 0; i < size; i++) {
    totalVol += ingredients[i].getIngVal();
  }
  return totalVol;
}


