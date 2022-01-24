#include "Arduino.h"
#include "Drink.h"
#include <math.h>

String Drink::getDrinkName()
{
  return drinkName;
}

Recipe Drink::getRecipe(int a)
{
  return recipe[a];
}

Ingredient Drink::getIngredient(int a)
{
  return recipe[a].getIng();
}

byte Drink::getSize()
{
  return size;
}

char Drink::getType()
{
  return type;
}

uint16_t Drink::getTotalVol() {
  return totalVol;
}

float Drink::getTotalPercentAlc() {
  return totalPercentAlc;
}

float Drink::getTotalDrinkNum() {
  return totalDrinkNum;
}

// Calculates volume of liquid of drink
uint16_t Drink::calcTotalVol()
{
  int totalVol = 0;
  for (int i = 0; i < size; i++)
  {
    totalVol += recipe[i].getIngVol();
  }
  return totalVol;
}


// Calculates percent alcohol of drink
float Drink::calcTotalPercentAlc()
{
  float totalPercentAlc = 0;
  for (int i = 0; i < size; i++)
  {
    totalPercentAlc += recipe[i].getIng().getPercentAlc() * recipe[i].getIngVol();
  }
  return (totalPercentAlc / totalVol) * 100;
}

// Calculates number of 'standard drinks' of frink based on
// alcohol percent and volume
float Drink::calcTotalDrinkNum()
{
  return ((float(totalVol) * totalPercentAlc) / MLPERDRINK);
}


// Print all information about the drink to the Serial Monitor
void Drink::serialPrintDrinkInfo()
{
  Serial.print(F("Drink Name: "));
  Serial.println(drinkName);
  for (uint8_t i = 0; i < size; i++)
  {
    Serial.print(F("\tIng Name: "));
    Serial.print(recipe[i].getIng().getIngName());
    uint8_t temp = recipe[i].getIng().getIngName().length() / 8;
    switch (temp) {
      case 0:
        Serial.print(F("\t\t\t"));
        break;
      case 1:
        Serial.print(F("\t\t"));
        break;
      case 2:
      default:
        Serial.print(F("\t"));
        break;
    }
    Serial.print(F("Ing Vol: "));
    Serial.println(recipe[i].getIngVol());
  }
  Serial.print(F("\n"));
}
