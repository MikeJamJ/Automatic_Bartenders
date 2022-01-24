#ifndef DrinkList_h
#define DrinkList_h

#include "Arduino.h"
#include "../Drink/Drink.h"

class DrinkList: public Drink {
  private:
    Drink *drinks;
    byte size;

  public:
    DrinkList (Drink drinks_[], byte size_) {
      drinks = drinks_;
      size = size_;
    }

    ~DrinkList() {}

    Drink getDrink (int a);
    void setDrink (Drink drink, int pos);
    byte getSize ();

    void printDrinks ();
    void findPossibleDrinks (DrinkList possible_drinks, String pumps[], Drink fillDrink);
    void fillRemaining (DrinkList drink_list, int n, Drink fillDrink);
    void alphabetize (Drink defaultDrink);
    byte findEndOfDrinkList(Drink defaultDrink);
};

#endif
