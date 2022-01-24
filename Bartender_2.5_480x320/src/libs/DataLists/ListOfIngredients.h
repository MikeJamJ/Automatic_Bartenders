#ifndef ListofIngredients_h
#define ListofIngredients_h

#include "Arduino.h"
#include "../Ingredient/Ingredient.h"

const Ingredient defaultIng[] = {
  Ingredient("default", 0)
};

const Ingredient bRussian_[] = {
  Ingredient("Kahlua", 30),
  Ingredient("Vodka", 30)
};

const Ingredient LITea_[] = {
  Ingredient("Vodka", 15),
  Ingredient("Rum", 15),
  Ingredient("Gin", 15),
  Ingredient("Triple Sec", 15),
  Ingredient("Tequila", 15),
  Ingredient("S&S Mix", 30)
};

const Ingredient wSour_[] = {
  Ingredient("Bourbon", 45),
  Ingredient("Lemon Juice", 22),
  Ingredient("Simple Syrup", 22)
};

const Ingredient bMf2_[] = {
  Ingredient("Vodka", 15),
  Ingredient("Gin", 15),
  Ingredient("Rum", 15),
  Ingredient("Tequila", 15),
  Ingredient("Blue Curacao", 15),
  Ingredient("S&S Mix", 44),
  Ingredient("Sprite", 148)
};

const Ingredient margMix_[] {
  Ingredient("Margarita Mix", 120),
  Ingredient("Tequila", 30)
};

const Ingredient teqSun_[] {
  Ingredient("Tequila", 50),
  Ingredient("Orange Juice", 150)
};

const Ingredient grGhost_[] {
  Ingredient("Gin", 59),
  Ingredient("Green Chartreuse", 15),
  Ingredient("Lime Juice", 15)
};

const Ingredient rumAndCoke_[] {
  Ingredient("Rum", 50),
  Ingredient("Coke", 150)
};

const Ingredient scrwDriv_[] {
  Ingredient("Vodka", 50),
  Ingredient("Orange Juice", 150)
};

const Ingredient ginAndJuice_[] {
  Ingredient("Gin", 50),
  Ingredient("Orange Juice", 150)
};

const Ingredient vodCran_[] {
  Ingredient("Vodka", 44),
  Ingredient("Cranberry Juice", 226)
};

const Ingredient bMart_[] = {
  Ingredient("Vodka", 30),
  Ingredient("Martini Mix", 90)
};

const Ingredient shirTemp_[] = {
  Ingredient("Orange Juice", 59),
  Ingredient("Sprite", 59),
  Ingredient("Grenadine", 4)
};


#endif