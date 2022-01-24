#ifndef DrinkList_h
#define DrinkList_h

class DrinkList{
  private:
    Drink *drinks;

  public:
    DrinkList(Drink drinks_[]){
      drinks = drinks_;
    }

    ~DrinkList(){}
};

#endif
