#include "Arduino.h"
#include "Drink.h"
#include <math.h>


String Drink::getDrinkName() {
  return drinkName;
}


Ingredient Drink::getIngredient(int a){
  return recipe[a].getIng();
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
    totalVol += ingredients[i].getIngVol();
  }
  return totalVol;
}


float Drink::calcTotalPercentAlc() {
  float totalPercentAlc = 0;
  for (int i=0; i < size; i++){
    totalPercentAlc += ingredients[i].getPercentAlc() * ingredients[i].getIngVol();
  }
  return (totalPercentAlc / totalVol) * 100;
}


float Drink::calcTotalDrinkNum() {
  return ((float(totalVol) * totalPercentAlc) / MLPERDRINK);
}

void Drink::serialPrintDrinkInfo() {
  Serial.print(F("Drink Name: "));
  Serial.println(drinkName);
  for (uint8_t i = 0; i < size; i++) {
    Serial.print(F("\tIng Name: "));
    Serial.println(ingredients[i].getIngName());
  }
  Serial.print(F("\n"));
}
