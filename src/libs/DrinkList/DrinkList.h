#ifndef DrinkList_h
#define DrinkList_h

#include "Arduino.h"
#include "../Drink/Drink.h"

struct Pump {
  String name;
  String value;
  uint16_t address;
  uint8_t pin;
  unsigned long startTime;
  unsigned long endTime;
};

class DrinkList: public Drink {
  private:
    Drink *drinks;
    byte size;

  public:
    DrinkList (Drink *drinks_, byte size_) {
      drinks = drinks_;
      size = size_;
    }

    DrinkList () {}
    ~DrinkList() {}

    Drink getDrink (int a);
    void setDrink (Drink drink, int pos);
    byte getSize ();

    void serialPrintDrinks ();
    void findPossibleDrinks (Pump pumps[], uint8_t pumpArraySize, Drink returningArray[], uint8_t returningArraySize);
    uint8_t findPossibleDrinksSize(Pump pumps[], uint8_t pumpArraySize);
    void alphabetize ();
    //DrinkList findPossibleDrinksOg (Pump pumps[], uint8_t pumpArraySize);
};



#endif
