#include "Arduino.h"
#include "DrinkList.h"

Drink DrinkList::getDrink(int a)
{
  return drinks[a];
}

void DrinkList::setDrink(Drink drink, int pos)
{
  drinks[pos] = drink;
}

byte DrinkList::getSize()
{
  return size;
}

//Prints Array of all drinks
void DrinkList::serialPrintDrinks()
{
  Serial.println("===================================\nPRINTING DRINKLIST\n===================================\n");

  for (int i = 0; i < size; i++)
  {
    Serial.println(drinks[i].getDrinkName());
    for (int j = 0; j < drinks[i].getSize(); j++)
    {
      Serial.print(F("\t"));
      Serial.print(drinks[i].getIngredient(j).getIngName());
      Serial.print(F("\t"));
      Serial.println(drinks[i].getIngredient(j).getIngVol());
    }
  }
  Serial.print(F("\n"));
}

void DrinkList::findPossibleDrinks(Pump pumps[], uint8_t pumpArraySize, Drink returningArray[], uint8_t returningArraySize)
{
  Serial.println("===================================\nFINDING POSSIBLE DRINKS\n===================================\n");

  bool notGonnaWork = false;
  uint8_t numOfDrinksFound = 0;

  Serial.print(F("Size of Pumps:\t"));
  Serial.println(pumpArraySize);

  for (uint8_t e = 0; e < size; e++)  //Go through all drinks in the DrinkList
  {
    notGonnaWork = false;
    int numOfConfirmedIngs = 0;
    Serial.print(F("Drink Being Checked: "));
    Serial.println(drinks[e].getDrinkName());
    Serial.print(F("==============================================\nNumber of Ingredients: "));
    Serial.println(drinks[e].getSize());

    for (uint8_t f = 0; f < drinks[e].getSize(); f++) //Go through all ingredients of the current Drink
    {
      Serial.print(F("Ing Being Checked: \t"));
      Serial.println(drinks[e].getIngredient(f).getIngName());

      for (uint8_t g = 0; g < pumpArraySize; g++)     //Go though all pump values for the current Ingredient
      {
        Serial.print(F("\tPump Being Checked: \t"));
        Serial.println(pumps[g].value);

        if (drinks[e].getIngredient(f).getIngName() == pumps[g].value)  //Check if the pump value is equal to the drink name
        {
          numOfConfirmedIngs++;
          Serial.print(F("Confirmed Ings: "));
          Serial.println(numOfConfirmedIngs);

          if (numOfConfirmedIngs == drinks[e].getSize())  //If we have check all ingredients, break out to next drink
          {
            returningArray[numOfDrinksFound] = drinks[e];
            numOfDrinksFound++;
            break;
          }
          break;
        }
        else if ((drinks[e].getIngredient(f).getIngName() != pumps[g].value) && (g == (pumpArraySize - 1))) //If no pumps match the value for an ingredient, break out to next drink
        {
          Serial.print(F("Position of G: \t"));
          Serial.println(g);
          notGonnaWork = true;
        }
      }
      if (notGonnaWork == true)
      {
        break;
      }
    }
    if (numOfDrinksFound == returningArraySize) {
      break;
    }
    Serial.print(F("\n"));
  }
  Serial.print(F("\n"));
}


uint8_t DrinkList::findPossibleDrinksSize(Pump pumps[], uint8_t pumpArraySize)
{
  Serial.println("===================================\nFINDING POSSIBLE DRINKS SIZE\n===================================\n");

  bool notGonnaWork = false;
  uint8_t drinkLocationsArrayNum = 0;

  for (uint8_t e = 0; e < size; e++)  //Go through all drinks in the DrinkList
  {
    notGonnaWork = false;
    int numOfConfirmedIngs = 0;
    for (uint8_t f = 0; f < drinks[e].getSize(); f++) //Go through all ingredients of the current Drink
    {
      for (uint8_t g = 0; g < pumpArraySize; g++)     //Go though all pump values for the current Ingredient
      {
        if (drinks[e].getIngredient(f).getIngName() == pumps[g].value)  //Check if the pump value is equal to the drink name
        {
          numOfConfirmedIngs++;
          if (numOfConfirmedIngs == drinks[e].getSize())  //If we have check all ingredients, break out to next drink
          {
            drinkLocationsArrayNum++;
            break;
          }
          break;
        }
        else if ((drinks[e].getIngredient(f).getIngName() != pumps[g].value) && (g == (pumpArraySize - 1))) //If no pumps match the value for an ingredient, break out to next drink
        {
          notGonnaWork = true;
        }
      }
      if (notGonnaWork == true) break;
    }
  }
  return drinkLocationsArrayNum;
}

void DrinkList::alphabetize()
{
  Serial.println("===================================\nALPHABETIZING DRINKLIST\n===================================\n");

  Drink curSmallest;
  Drink ogSmallest;
  Drink temp = drinks[0];
  String shortestDrinkName;
  int smallestPosition;

  for (uint8_t x = 0; x < (size - 1); x++)                      //Goes through all drinks of the passed DrinkList
  {
    curSmallest = drinks[x];
    ogSmallest = curSmallest;
    for (uint8_t y = 0; y < (size - (x + 1)); y++)              //Goes through all drinks that have yet to be sorted
    {
      if (drinks[y + 1].getDrinkName().length() < drinks[y].getDrinkName().length()) {shortestDrinkName = drinks[y + 1].getDrinkName();}
      else {shortestDrinkName = drinks[y].getDrinkName();}
      for (uint8_t z = 0; z < shortestDrinkName.length(); z++)  //Goes through each character of the smallestDrinkName 
      {
        if (drinks[x + y + 1].getDrinkName()[z] < curSmallest.getDrinkName()[z])      //If the next position's character is smaller, it becomes the new smallest.
        {
          curSmallest = drinks[x + y + 1];
          smallestPosition = x + y + 1;
          break;
        }
        else if (drinks[x + y + 1].getDrinkName()[z] > curSmallest.getDrinkName()[z]) //If curSmallest's character is smaller, break the loop
        {
          break;
        }
      }
    }
    if (ogSmallest.getDrinkName() != curSmallest.getDrinkName())  //The smallest is brought to the front and the drink in that postion is moved to where the smallest drinkname was
    {
      temp = drinks[x];
      drinks[x] = curSmallest;
      drinks[smallestPosition] = temp;
    } 
    else {} //If the smallest drinkName has not changed in this iteration, the next iteration begins.
  }
}

/*
DrinkList DrinkList::findPossibleDrinksOg(Pump pumps[], uint8_t pumpArraySize)
{
  Serial.println("===================================\nFINDING POSSIBLE DRINKS\n===================================\n");

  bool notGonnaWork = false;
  uint8_t drinkLocationsArrayNum = 0;
  uint8_t drinkLocations[size] = {};

  Serial.print(F("Size of Pumps:\t"));
  Serial.println(pumpArraySize);
  Serial.print(F("DrinkLocations Size: "));
  Serial.print(sizeof(drinkLocations));
  Serial.print(F("\t"));
  Serial.print(sizeof(drinkLocations[0]));
  Serial.print(F("\t"));
  Serial.println((sizeof(drinkLocations) / sizeof(drinkLocations[0])));
  Serial.print(F("\n"));

  for (uint8_t e = 0; e < size; e++)
  {
    notGonnaWork = false;
    int numOfConfirmedIngs = 0;
    Serial.print(F("Drink Being Checked: "));
    Serial.println(drinks[e].getDrinkName());
    Serial.print(F("==============================================\nNumber of Ingredients: "));
    Serial.println(drinks[e].getSize());


    for (uint8_t f = 0; f < drinks[e].getSize(); f++)
    {

      Serial.print(F("Ing Being Checked: \t"));
      Serial.println(drinks[e].getIngredient(f).getIngName());

      for (uint8_t g = 0; g < pumpArraySize; g++)
      {

        Serial.print(F("\tPump Being Checked: \t"));
        Serial.println(pumps[g].value);

        if (drinks[e].getIngredient(f).getIngName() == pumps[g].value)
        {
          numOfConfirmedIngs++;
          Serial.print(F("Confirmed Ings: "));
          Serial.println(numOfConfirmedIngs);

          if (numOfConfirmedIngs == drinks[e].getSize())
          {
            Serial.print(F("drinkLocationsArrayNum: "));
            Serial.print(drinkLocationsArrayNum);
            Serial.print(F("\te: "));
            Serial.println(e);
            drinkLocations[drinkLocationsArrayNum] = e;
            drinkLocationsArrayNum++;

            Serial.println("\ndrinkLocations Array: ");
            for (uint8_t z = 0; z < (sizeof(drinkLocations) / sizeof(drinkLocations[0])); z++) {
              Serial.println(drinkLocations[z]);
            }

            break;
          }
          break;
        }
        /*
           If the pump array has been gone through once and an ingredient has not been found,
           then it is safe to assume the drink cannot be made so the loop moves on to the next
           drink
        *//*
        else if ((drinks[e].getIngredient(f).getIngName() != pumps[g].value) && (g == (pumpArraySize - 1)))
        {
          Serial.print(F("Position of G: \t"));
          Serial.println(g);
          notGonnaWork = true;
        }
      }
      if (notGonnaWork == true)
      {
        break;
      }
    }
    Serial.print(F("\n"));
  }

  Serial.print(F("Array Size: "));
  Serial.println(drinkLocationsArrayNum);
  Drink returningArray[drinkLocationsArrayNum];

  for (uint8_t i = 0; i < drinkLocationsArrayNum; i++)
  {
    Serial.print(F("Position in int array: "));
    Serial.print(i);
    Serial.print(F("\tValue: "));
    Serial.println(drinkLocations[i]);
  }
  Serial.print(F("\n"));

  for (uint8_t i = 0; i < drinkLocationsArrayNum; i++)
  {
    Serial.println(F("Drink at location: "));
    drinks[drinkLocations[i]].serialPrintDrinkInfo();   
    returningArray[i] = drinks[drinkLocations[i]];
  }
  Serial.print(F("\n"));
  Serial.print(F("\n"));

  DrinkList returningDrinkList(returningArray, (sizeof(returningArray) / sizeof(returningArray[0])));
  returningDrinkList.serialPrintDrinks();
  return returningDrinkList;
}*/