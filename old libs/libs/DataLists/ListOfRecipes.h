#ifndef ListofRecipes_h
#define ListofRecipes_h

#include "Arduino.h"
#include "../Recipe/Recipe.h"
#include "ListOfIngredients"

const Recipe defaultIng[] = {
  Recipe(&DefaultIng, 0)
};

const Recipe bRussian_[] = {
  Recipe(Kahlua, 30),
  Recipe(Vodka, 30)
};

const Recipe LITea_[] = {
  Recipe(Vodka, 15),
  Recipe(Rum, 15),
  Recipe(Gin, 15),
  Recipe(TripleSec, 15),
  Recipe(Tequila, 15),
  Recipe(SandSMix, 30)
};

const Recipe wSour_[] = {
  Recipe(Bourbon, 45),
  Recipe(LemonJuice, 22),
  Recipe(SimpleSyrup, 22)
};

const Recipe bMf2_[] = {
  Recipe(Vodka, 15),
  Recipe(Gin, 15),
  Recipe(Rum, 15),
  Recipe(Tequila, 15),
  Recipe(BlueCuracao, 15),
  Recipe(SandSMix, 44),
  Recipe(Sprite, 148)
};

const Recipe margMix_[] {
  Recipe(MargaritaMix, 120),
  Recipe(Tequila, 30)
};

const Recipe teqSun_[] {
  Recipe(Tequila, 50),
  Recipe(OrangeJuice, 150)
};

const Recipe grGhost_[] {
  Recipe(Gin, 59),
  Recipe(GreenChartreuse, 15),
  Recipe(LimeJuice, 15)
};

const Recipe rumAndCoke_[] {
  Recipe(Rum, 50),
  Recipe(Coke, 150)
};

const Recipe scrwDriv_[] {
  Recipe(Vodka, 50),
  Recipe(OrangeJuice, 150)
};

const Recipe ginAndJuice_[] {
  Recipe(Gin, 50),
  Recipe(OrangeJuice, 150)
};

const Recipe vodCran_[] {
  Recipe(Vodka, 44),
  Recipe(CranberryJuice, 226)
};

const Recipe bMart_[] = {
  Recipe(Vodka, 30),
  Recipe(MartiniMix, 90)
};

const Recipe shirTemp_[] = {
  Recipe(OrangeJuice, 59),
  Recipe(Sprite, 59),
  Recipe(Grenadine, 4)
};
