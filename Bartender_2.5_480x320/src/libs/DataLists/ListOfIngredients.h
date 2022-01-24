#ifndef ListofIngredients_h
#define ListofIngredients_h

#include "../Ingredient/Ingredient.h"

const Ingredient DefaultIng = Ingredient("NULL", 0);
const Ingredient Kahlua = Ingredient("Kahlua", 0.20);
const Ingredient Vodka = Ingredient("Vodka", 0.40);
const Ingredient Rum = Ingredient("Rum", 0.40);
const Ingredient Gin = Ingredient("Gin", 0.40);
const Ingredient TripleSec = Ingredient("Triple Sec", 0.30);
const Ingredient Tequila = Ingredient("Tequila", 0.40);
const Ingredient SandSMix = Ingredient("S&S Mix", 0);
const Ingredient Bourbon = Ingredient("Bourbon", 0.40);
const Ingredient LemonJuice = Ingredient("Lemon Juice", 0);
const Ingredient SimpleSyrup = Ingredient("Simple Syrup", 0);
const Ingredient BlueCuracao = Ingredient("Blue Curacao", 0.40);
const Ingredient Sprite = Ingredient("Sprite", 0);
const Ingredient MargaritaMix = Ingredient("Margarita Mix", 0);
const Ingredient OrangeJuice = Ingredient("Orange Juice", 0);
const Ingredient GreenChartreuse = Ingredient("Green Chartreuse", 0.55);
const Ingredient LimeJuice = Ingredient("Lime Juice", 0);
const Ingredient Coke = Ingredient("Coke", 0);
const Ingredient CranberryJuice = Ingredient("Cranberry Juice", 0);
const Ingredient MartiniMix = Ingredient("Martini Mix", 0);
const Ingredient Grenadine = Ingredient("Grenadine", 0);
const Ingredient PassionJuice = Ingredient("Passion Fruit Juice", 0);
const Ingredient Milk = Ingredient("Milk", 0);
const Ingredient Prosecco = Ingredient("Prosecco", 0.12);
const Ingredient PineappleJuice = Ingredient("Pineapple Juice", 0);
const Ingredient Rev = Ingredient("Rev", 0.07);


const Ingredient IngredientList[] = {
    DefaultIng,
    BlueCuracao,
    Bourbon,
    Coke,
    CranberryJuice,
    Gin,
    GreenChartreuse,
    Grenadine,
    Kahlua,
    LemonJuice,
    LimeJuice,
    MargaritaMix,
    MartiniMix,
    Milk,
    OrangeJuice,
    PassionJuice,
    PineappleJuice,
    Prosecco,
    Rev,
    Rum,
    SandSMix,
    SimpleSyrup,
    Sprite,
    TripleSec,
    Tequila,
    Vodka
};
const uint8_t sizeOfIngList = ARRAYCOUNT(IngredientList);

#endif