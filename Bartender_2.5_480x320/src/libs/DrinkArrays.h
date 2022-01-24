#ifndef DrinkArrays_h
#define DrinkArrays_h

#include "DataLists/ListOfDrinks.h"

struct Pump {
  String name;
  String value;
  uint16_t address;
  uint8_t pin;
  unsigned long startTime;
  unsigned long endTime;
};

// Print all information about each drink in an array to the Serial Monitor
void serialPrintDrinkArray(uint8_t drinks[], uint8_t size)
{
  Serial.println(F("===================================\nPRINTING DRINKLIST\n===================================\n"));
  for (int i = 0; i < size; i++)
  {
    Serial.print(masterDrinkList[drinks[i]].getDrinkName());
    Serial.print(F("\tPos: "));
    Serial.println(drinks[i]);
    for (int j = 0; j < masterDrinkList[drinks[i]].getSize(); j++)
    {
      Serial.print(F("\t"));
      Serial.print(masterDrinkList[drinks[i]].getIngredient(j).getIngName());
      int temp = masterDrinkList[drinks[i]].getIngredient(j).getIngName().length() / 8;
      switch (temp) {
        case 0:
          Serial.print(F("\t\t\t"));
          break;
        case 1:
          Serial.print(F("\t\t"));
          break;
        case 2:
        default:
          Serial.print(F("\t"));
          break;
      }
      Serial.println(masterDrinkList[drinks[i]].getRecipe(j).getIngVol());
    }
  }
  Serial.print(F("\n"));
}

// Print all information about each drink in an array to the Serial Monitor
void serialPrintMDL()
{
  Serial.println(F("===================================\nPRINTING DRINKLIST\n===================================\n"));
  for (int i = 0; i < MDLsize; i++)
  {
    Serial.println(masterDrinkList[i].getDrinkName());
    for (int j = 0; j < masterDrinkList[i].getSize(); j++)
    {
      Serial.print(F("\t"));
      Serial.print(masterDrinkList[i].getIngredient(j).getIngName());
      int temp = masterDrinkList[i].getIngredient(j).getIngName().length() / 8;
      switch (temp) {
        case 0:
          Serial.print(F("\t\t\t"));
          break;
        case 1:
          Serial.print(F("\t\t"));
          break;
        case 2:
        default:
          Serial.print(F("\t"));
          break;
      }
      Serial.println(masterDrinkList[i].getRecipe(j).getIngVol());
    }
  }
  Serial.print(F("\n"));
}

/*
  Find drinks that can be made based on connected ingredients

  @param pumps[]             array of pumps containing the ingredients to check against
  @param pumpArraySize       size of pumps[] being passed
  @param returningArray[]    array of drink positions to set values to
  @param returningArraySize  size of drink array being passed
*/
void findPossibleDrinks(Pump pumps[], uint8_t pumpArraySize, uint8_t returningArray[], uint8_t returningArraySize)
{
  Serial.println(F("===================================\nFINDING POSSIBLE DRINKS\n===================================\n"));

  bool notGonnaWork = false;
  uint8_t numOfDrinksFound = 0;

  Serial.print(F("Size of Pumps:\t"));
  Serial.println(pumpArraySize);

  for (uint8_t curDrink = 0; curDrink < MDLsize; curDrink++)  //Go through all drinks in the DrinkList
  {
    notGonnaWork = false;
    int numOfConfirmedIngs = 0;
    Serial.print(F("Drink Being Checked: "));
    Serial.println(masterDrinkList[curDrink].getDrinkName());
    Serial.print(F("==============================================\nNumber of Ingredients: "));
    Serial.println(masterDrinkList[curDrink].getSize());

    for (uint8_t curIng = 0; curIng < masterDrinkList[curDrink].getSize(); curIng++) //Go through all ingredients of the current Drink
    {
      Serial.print(F("Ing Being Checked: \t"));
      Serial.println(masterDrinkList[curDrink].getIngredient(curIng).getIngName());

      for (uint8_t curPump = 0; curPump < pumpArraySize; curPump++)     //Go though all pump values for the current Ingredient
      {
        Serial.print(F("\tPump Being Checked: \t"));
        Serial.println(pumps[curPump].value);

        if (masterDrinkList[curDrink].getIngredient(curIng).getIngName() == pumps[curPump].value)  //Check if the pump value is equal to the drink name
        {
          numOfConfirmedIngs++;
          Serial.print(F("Confirmed Ings: "));
          Serial.println(numOfConfirmedIngs);

          if (numOfConfirmedIngs == masterDrinkList[curDrink].getSize())  //If we have check all ingredients, break out to next drink
          {
            returningArray[numOfDrinksFound] = curDrink;
            numOfDrinksFound++;
            break;
          }
          break;
        }
        else if ((masterDrinkList[curDrink].getIngredient(curIng).getIngName() != pumps[curPump].value) && (curPump == (pumpArraySize - 1))) //If no pumps match the value for an ingredient, break out to next drink
        {
          Serial.print(F("Position of G: \t"));
          Serial.println(curPump);
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

/*
  Find drinks that can be made based on connected ingredients
   
  @Note: Functions nearly identically to 'findPossibleDrinks' but instead of writing to an array,
  it returns the number of possible drinks. This is inefficient but necesarry to avoid pointers

  @param pumps[]         array of pumps containing the ingredients to check against
  @param pumpArraySize   size of pumps[] being passed
  @returns uint8_t       number of possible drinks    
*/
uint8_t findPossibleDrinksSize(Pump pumps[], uint8_t pumpArraySize)
{
  Serial.println(F("===================================\nFINDING POSSIBLE DRINKS SIZE\n===================================\n"));

  bool notGonnaWork = false;
  uint8_t drinkLocationsArrayNum = 0;

  for (uint8_t e = 0; e < MDLsize; e++)  //Go through all drinks in the DrinkList
  {
    notGonnaWork = false;
    int numOfConfirmedIngs = 0;
    for (uint8_t f = 0; f < masterDrinkList[e].getSize(); f++) //Go through all ingredients of the current Drink
    {
      for (uint8_t g = 0; g < pumpArraySize; g++)     //Go though all pump values for the current Ingredient
      {
        if (masterDrinkList[e].getIngredient(f).getIngName() == pumps[g].value)  //Check if the pump value is equal to the drink name
        {
          numOfConfirmedIngs++;
          if (numOfConfirmedIngs == masterDrinkList[e].getSize())  //If we have check all ingredients, break out to next drink
          {
            drinkLocationsArrayNum++;
            break;
          }
          break;
        }
        else if ((masterDrinkList[e].getIngredient(f).getIngName() != pumps[g].value) && (g == (pumpArraySize - 1))) //If no pumps match the value for an ingredient, break out to next drink
        {
          notGonnaWork = true;
        }
      }
      if (notGonnaWork == true) break;
    }
  }
  return drinkLocationsArrayNum;
}

/*
  Alphabetize drinks in the DrinkList
*/
void alphabetize(uint8_t drinks[], uint8_t size)
{
  Serial.println(F("===================================\nALPHABETIZING DRINKLIST\n===================================\n"));

  Drink curSmallest, ogSmallest;
  String shortestDrinkName;
  uint8_t temp, smallestPosition;

  // Loop through all drinks in the DrinkList
  for (uint8_t x = 0; x < (size - 1); x++)                      
  {
    curSmallest = masterDrinkList[drinks[x]];
    ogSmallest = curSmallest;

    // Loop through all drinks that have yet to be sorted
    for (uint8_t y = 0; y < (size - (x + 1)); y++)              
    {
      if (masterDrinkList[drinks[y + 1]].getDrinkName().length() < masterDrinkList[drinks[y]].getDrinkName().length()) {shortestDrinkName = masterDrinkList[drinks[y + 1]].getDrinkName();}
      else {shortestDrinkName = masterDrinkList[drinks[y]].getDrinkName();}
      
      // Loop through each character of the smallestDrinkName 
      for (uint8_t c = 0; c < shortestDrinkName.length(); c++)  
      {
        // If the next position's character is smaller, it becomes the new smallest.
        if (masterDrinkList[drinks[x + y + 1]].getDrinkName()[c] < curSmallest.getDrinkName()[c]) 
        {
          curSmallest = masterDrinkList[drinks[x + y + 1]];
          smallestPosition = x + y + 1;
          break;
        }
        // If curSmallest's character is smaller, break the loop
        else if (masterDrinkList[drinks[x + y + 1]].getDrinkName()[c] > curSmallest.getDrinkName()[c]) 
        {
          break;
        }
      }
    }
    // The smallest is brought to the front and the drink in that postion is moved to where the smallest drinkname was
    if (ogSmallest.getDrinkName() != curSmallest.getDrinkName())  
    {
      temp = drinks[x];
      drinks[x] = drinks[smallestPosition];
      drinks[smallestPosition] = temp;
    } 
    else {
      //If the smallest drinkName has not changed in this iteration, the next iteration begins.
    } 
  }
}

#endif
