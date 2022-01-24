#ifndef ListofDrinks_h
#define ListofDrinks_h

#include "Arduino.h"
#include "../Drink/Drink.h"
#include "ListOfRecipes.h"

#include "../../images/margarita_img.h"
#include "../../images/shirleyTemple_img.h"

/*~*/const Drink defaultDrink("|Default", defaultIng, (sizeof(defaultIng) / sizeof(defaultIng[0])), 'X', margarita_img); //default drink for placeholder
/*1*/const Drink blackRussian("Black Russian", bRussian_, (sizeof(bRussian_) / sizeof(bRussian_[0])), 'A', margarita_img);
/*2*/const Drink LITea("Long Island Tea", LITea_, (sizeof(LITea_) / sizeof(LITea_[0])), 'A', margarita_img);
/*3*/const Drink whiskeySour("Whiskey Sour", wSour_, (sizeof(wSour_) / sizeof(wSour_[0])), 'A', margarita_img);
/*4*/const Drink bMF2("Blue MotherFucker 2", bMf2_, (sizeof(bMf2_) / sizeof(bMf2_[0])), 'A', margarita_img);
/*5*/const Drink margaritaMix("Margarita (Mix)", margMix_, (sizeof(margMix_) / sizeof(margMix_[0])), 'A', margarita_img);
/*6*/const Drink greenGhost("Green Ghost", grGhost_, (sizeof(grGhost_) / sizeof(grGhost_[0])), 'A', margarita_img);
/*7*/const Drink rumAndCoke("Rum & Coke", rumAndCoke_, (sizeof(rumAndCoke_) / sizeof(rumAndCoke_[0])), 'A', margarita_img);
/*8*/const Drink screwDriver("Screwdriver", scrwDriv_, (sizeof(scrwDriv_) / sizeof(scrwDriv_[0])), 'A', margarita_img);
/*9*/const Drink ginAndOrangeJuice("Gin & Juice", ginAndJuice_, (sizeof(ginAndJuice_) / sizeof(ginAndJuice_[0])), 'A', margarita_img);
/*10*/const Drink tequilaSunrise("Tequila Sunrise", teqSun_, (sizeof(teqSun_) / sizeof(teqSun_[0])), 'A', margarita_img);
/*11*/const Drink vodkaCran("Vodka Cranberry", vodCran_, (sizeof(vodCran_) / sizeof(vodCran_[0])), 'A', margarita_img);
/*12*/const Drink blueMartini("BR Martini (Mix)", bMart_, (sizeof(bMart_) / sizeof(bMart_[0])), 'A', margarita_img);
/*13*/const Drink shirleyTemple("Shirley Temple", shirTemp_, (sizeof(shirTemp_) / sizeof(shirTemp_[0])), 'N', shirleyTemple_img);

#endif