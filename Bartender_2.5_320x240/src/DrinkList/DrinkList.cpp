#include "Arduino.h"
#include "DrinkList.h"

Drink DrinkList::getDrink (int a) {
  return drinks[a];
}


void DrinkList::setDrink (Drink drink, int pos) {
  drinks[pos] = drink;
}


byte DrinkList::getSize () {
  return size;
}


//Prints Array of all drinks
void DrinkList::printDrinks () {
  Serial.println("===================================\nPRINTING DRINKLIST\n===================================\n");

  for (int i = 0; i < size; i++) {
    Serial.println(drinks[i].getDrinkName());
    for (int j = 0; j < drinks[i].getSize(); j++) {
      Serial.print("\t");
      Serial.print(drinks[i].getIngredient(j).getIngName());
      Serial.print("\t");
      Serial.println(drinks[i].getIngredient(j).getIngVal());
    }
  }
  Serial.print("\n");
}


void DrinkList::findPossibleDrinks (DrinkList possible_drinks, String pumps[], Drink fillDrink) {
  Serial.println("===================================\nFINDING POSSIBLE DRINKS\n===================================\n");

  bool notGonnaWork = false;
  int pbArrayNum = 0;

  for (int e = 0; e < size; e++) {
    notGonnaWork = false;
    int numOfConfirmedIngs = 0;
    Serial.print("Drink Being Checked: ");
    Serial.println(drinks[e].getDrinkName());
    Serial.println("==============================================");
    
    Serial.print("Number of Ingredients: ");
    Serial.println(drinks[e].getSize());
    
    for (int f = 0; f < drinks[e].getSize(); f++) {
      
      Serial.print("Ing Being Checked: \t");
      Serial.println(drinks[e].getIngredient(f).getIngName());
      
      for (int g = 0; g < 6; g++) {
        
        Serial.print("\tPump Being Checked: \t");
        Serial.println(pumps[g]);        
        
        if (drinks[e].getIngredient(f).getIngName() == pumps[g]) {
          numOfConfirmedIngs++;
          Serial.print("Confirmed Ings: ");
          Serial.println(numOfConfirmedIngs);

          if (numOfConfirmedIngs == drinks[e].getSize()) {
            possible_drinks.setDrink(drinks[e], pbArrayNum);
            pbArrayNum++;
            break;
          }
          break;
        }
        /*
           If the pump array has been gone through once and an ingredient has not been found,
           then it is safe to assume the drink cannot be made so the loop moves on to the next
           drink
        */
        else if ((drinks[e].getIngredient(f).getIngName() != pumps[g]) && (g == (6 - 1))) {
          Serial.print("Position of G: \t");
          Serial.println(g);
          notGonnaWork = true;
        }
      }
      Serial.print("\n");
      for (int h = 0; h < possible_drinks.getSize(); h++) {
        Serial.print(possible_drinks.getDrink(h).getDrinkName());
        Serial.print("\t");
      }
      Serial.print("\n\n");
      if (notGonnaWork == true) {
        break;
      }
    }
  }
  fillRemaining(possible_drinks, pbArrayNum, fillDrink);
  Serial.print("\n");
}


void DrinkList::fillRemaining (DrinkList drink_list, int n, Drink fillDrink) {
  for (int i = n; i < size; i++) {
    drink_list.setDrink(fillDrink, i);
  }
}


void DrinkList::alphabetize (Drink defaultDrink) {
  Serial.println("===================================\nALPHABETIZING DRINKLIST\n===================================\n");

  Drink smallest = defaultDrink;
  Drink ogSmallest = defaultDrink;
  Drink temp = defaultDrink;
  String smallDrinkName;
  int smallestPosition;

  //Goes through all elements of DrinkList passed and decreases the amount of positions that need to be checked everytime a new smallest drink is placed in the first position of the iteration
  for (int x = 0; x < (size - 1); x++) {
    smallest = drinks[x];
    ogSmallest = smallest;

    //Checks each drinkName in an iteration to find the smallest drinkName
    for ( int y = 0; y < (size - (x + 1)); y++) {
      //Finds the shortest drinkName between the current smallest and the next position's drinkName. Only checks characters until the shortest drinkName is done
      if (drinks[y + 1].getDrinkName().length() < drinks[y].getDrinkName().length()) {
        smallDrinkName = drinks[y + 1].getDrinkName();
      }
      else {
        smallDrinkName = drinks[y].getDrinkName();
      }
      //Goes through each character in the drinkName of smallest and next position of the possible_drinks array.
      for (int z  = 0; z < smallDrinkName.length(); z++) {
        //If the new position is smaller, it becomes the new smallest.
        if (drinks[x + y + 1].getDrinkName()[z] < smallest.getDrinkName()[z]) {
          smallest = drinks[x + y + 1];
          smallestPosition = x + y + 1;
          break;
        }
        //If smallest is ever found to be less than the new position, the loop breaks and a new iteration begins
        else if (drinks[x + y + 1].getDrinkName()[z] > smallest.getDrinkName()[z]) {
          break;
        }
      }
    }
    //If the smallest drinkName has not changed in this iteration, the next iteration begins.
    if (ogSmallest.getDrinkName() != smallest.getDrinkName()) {
      temp = drinks[x];
      drinks[x] = smallest;
      drinks[smallestPosition] = temp;
    }
    //Else, the smallest is brought to the front and the drink in that postion is moved to where the smallest drinkname was
    else {
    }
  }
}


// Finds the end of the DrinkList and returns it's value
byte DrinkList::findEndOfDrinkList(Drink defaultDrink) {
  byte endOfArray = 0;
  for (int i = 0; i < size; i++) {
    if (drinks[i + 1].getDrinkName()[0] == defaultDrink.getDrinkName()[0]) {
      endOfArray = i;
      return endOfArray;
    }
  }
}


