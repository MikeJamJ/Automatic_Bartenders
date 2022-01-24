//-----------------------------------------------------------------------------------------------
// FUNCTIONS for making the drink
//-----------------------------------------------------------------------------------------------

/*
   Returns pump name in pump array that corresponds to the selected ingredient in position 'a'
*/
String findPump(int a) {
  for (int l = 0; l < (sizeof pumps / sizeof pumps[0]); l++) {
    if (choice.ingredients[a].ingName == pumps[l]) {
      Serial.print("\nIngredient Name: ");
      Serial.print(choice.ingredients[a].ingName);
      Serial.print("\nPosition: ");
      Serial.print(a);
      Serial.print("\nFound pump: ");
      Serial.print(pumps[l]);
      //Serial.print("\n");
      return pumps[l];
    }
  }
}


//-----------------------------------------------------------------------------------------------

/*
   Returns pump position in pump array that corresponds to the selected ingredient
*/
int choosePump(String pump) {
  for (int m = 0; m < sizeof pumps / sizeof pumps[0]; m++) {
    if (pump == pumps[m]) {
      Serial.print("Pump Number: ");
      Serial.print(m);
      Serial.print("\n");
      return m;
    }
  }
}

//-----------------------------------------------------------------------------------------------

/*
   Starts pump that corresponds to the needed ingredient
*/
String startPump(int d) {
  Serial.print("Passed value: ");
  Serial.println(d);
  if ( d == 0) {
    digitalWrite(Relay_1, RELAY_ON);
    Serial.print("relay 1 turned on");
    return "pump1";
  }
  else if (d == 1) {
    digitalWrite(Relay_2, RELAY_ON);
    Serial.print("relay 2 turned on");
    return "pump2";
  }
  else if (d == 2) {
    digitalWrite(Relay_3, RELAY_ON);
    Serial.print("relay 3 turned on");
    return "pump3";
  }
  else if (d == 3) {
    digitalWrite(Relay_4, RELAY_ON);
    Serial.print("relay 4 turned on");
    return "pump4";
  }
  else if (d == 4) {
    digitalWrite(Relay_5, RELAY_ON);
    Serial.print("relay 5 turned on");
    return "pump5";
  }
  else if (d == 5) {
    digitalWrite(Relay_6, RELAY_ON);
    Serial.print("relay 6 turned on");
    return "pump6";
  }
}

//-----------------------------------------------------------------------------------------------

/*
   For each ingredient in a specified drink, finds and turns on the needed pump for the required time
*/
void makeDrink() {
  Serial.print(choice.drinkName);
  for (int n = 0; n < choice.size; n++) {
    startPump(choosePump(findPump(n)));
    Serial.println("\nTimer started");
    Serial.print(choice.ingredients[n].ingName);
    Serial.print("\t");
    Serial.print(choice.ingredients[n].ingVal);
    Serial.print("\t");
    Serial.print(((choice.ingredients[n].ingVal * 60000) / 100) / 1000);

    delay((choice.ingredients[n].ingVal * 60000) / 100);
    Serial.println("Timer ended");
    digitalWrite(Relay_1, RELAY_OFF);
    digitalWrite(Relay_2, RELAY_OFF);
    digitalWrite(Relay_3, RELAY_OFF);
    digitalWrite(Relay_4, RELAY_OFF);
    digitalWrite(Relay_5, RELAY_OFF);
    digitalWrite(Relay_6, RELAY_OFF);
    Serial.println("All relays turned off");
  }
}
