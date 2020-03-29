#ifndef ListofRecipesComponents_h
#define ListofRecipesComponents_h

#include "Arduino.h"
#include "../Recipe/Recipe.h"

const struct RC default_RC [] = {
    RC{defaultIng, 0}
};

const struct RC blackRussian_RC[] = {
    RC{Kahlua, 30},
    RC{Vodka, 30}
};

const struct RC LITea_RC[] = {
    RC{Vodka, 15},
    RC{Rum, 15},
    RC{Gin, 15},
    RC{TripleSec, 15},
    RC{Tequila, 15},
    RC{SweetSourMix, 30}
};

const struct RC whiskeySour_RC[] = {
  RC{Bourbon, 45},
  RC{LemonJuice, 22},
  RC{SimpleSyrup, 22}
};

const struct RC bMf2_RC[] = {
  RC{Vodka, 15},
  RC{Gin, 15},
  RC{Rum, 15},
  RC{Tequila, 15,},
  RC{BlueCuracao, 15},
  RC{SweetSourMix, 44},
  RC{Sprite, 148}
};

const struct RC margaritaMix_RC[] {
  RC{MargaritaMix, 120},
  RC{Tequila, 30}
};

const struct RC tequilaSunrise_RC[] {
  RC{Tequila, 50},
  RC{OrangeJuice, 150}
};

const struct RC greenGhost_RC[] {
  RC{Gin, 59},
  RC{GreenChartreuse, 15},
  RC{LimeJuice, 15}
};

const struct RC rumAndCoke_RC[] {
  RC{Rum, 50},
  RC{Coke, 150}
};

const struct RC screwDriver_RC[] {
  RC{Vodka, 50},
  RC{OrangeJuice, 150}
};

const struct RC ginAndOrangeJuice_RC[] {
  RC{Gin, 50},
  RC{OrangeJuice, 150}
};

const struct RC vodkaCran_RC[] {
  RC{Vodka, 44},
  RC{CranberryJuice, 226}
};

const struct RC blueMartini_RC[] = {
  RC{Vodka, 30},
  RC{MartiniMix, 90}
};

const struct RC shirleyTemple_RC[] = {
  RC{OrangeJuice, 59},
  RC{Sprite, 59},
  RC{Grenadine, 4}
};

#endif