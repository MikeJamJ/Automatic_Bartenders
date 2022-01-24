#ifndef ListofDrinks_h
#define ListofDrinks_h


#include "../Drink/Drink.h"
#include "ListOfRecipes.h"

/*~*/const Drink defaultDrink("|Default", defaultIng, ARRAYCOUNT(defaultIng), 'X', "default"); //default drink for placeholder
/*0*/const Drink blackRussian("Black Russian", bRussian_, ARRAYCOUNT(bRussian_), 'A', "default");
/*1*/const Drink LITea("Long Island Tea", LITea_, ARRAYCOUNT(LITea_), 'A', "default");
/*2*/const Drink whiskeySour("Whiskey Sour", wSour_, ARRAYCOUNT(wSour_), 'A', "default");
/*3*/const Drink bMF2("Blue MotherFucker 2", bMf2_, ARRAYCOUNT(bMf2_), 'A', "default");
/*4*/const Drink margaritaMix("Margarita (Mix)", margMix_, ARRAYCOUNT(margMix_), 'A', "margMix");
/*5*/const Drink greenGhost("Green Ghost", grGhost_, ARRAYCOUNT(grGhost_), 'A', "default");
/*6*/const Drink rumAndCoke("Rum & Coke", rumAndCoke_, ARRAYCOUNT(rumAndCoke_), 'A', "default");
/*7*/const Drink screwDriver("Screwdriver", scrwDriv_, ARRAYCOUNT(scrwDriv_), 'A', "default");
/*8*/const Drink ginAndOrangeJuice("Gin & Juice", ginAndJuice_, ARRAYCOUNT(ginAndJuice_), 'A', "default");
/*9*/const Drink tequilaSunrise("Tequila Sunrise", teqSun_, ARRAYCOUNT(teqSun_), 'A', "default");
/*10*/const Drink vodkaCran("Vodka Cranberry", vodCran_, ARRAYCOUNT(vodCran_), 'A', "default");
/*11*/const Drink blueMartini("BR Martini (Mix)", bMart_, ARRAYCOUNT(bMart_), 'A', "default");
/*12*/const Drink shirleyTemple("Shirley Temple", shirTemp_, ARRAYCOUNT(shirTemp_), 'N', "shirTemp");
/*13*/const Drink hurricane("Hurricane", hurricane_, ARRAYCOUNT(hurricane_), 'A', "default");
/*14*/const Drink wRussian("White Russian", wRussian_, ARRAYCOUNT(wRussian_), 'A', "default");
/*15*/const Drink easterChampagne("Easter Champagne", easterChampagne_, ARRAYCOUNT(easterChampagne_), 'A', "default");
/*15*///const Drink test("test", test_, ARRAYCOUNT(test_), 'A', "default");


const Drink masterDrinkList[] = {
  blackRussian,
  LITea,
  whiskeySour,
  bMF2,
  margaritaMix,
  greenGhost,
  rumAndCoke,
  screwDriver,
  ginAndOrangeJuice,
  tequilaSunrise,
  vodkaCran,
  blueMartini,
  shirleyTemple,
  hurricane,
  wRussian,
  easterChampagne
};
const uint8_t MDLsize = ARRAYCOUNT(masterDrinkList);

#endif