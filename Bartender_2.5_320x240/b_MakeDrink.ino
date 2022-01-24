/*
   Functions for making the selected drink:
   findPump(int a);
   choosePump(String pump);
   startPump(int a);
   makeDrink();
*/

//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------

//Returns pump name in pump array that corresponds to the selected ingredient in position 'a'
String findPump(int a) {
  for (int i = 0; i < (sizeof pumps / sizeof pumps[0]); i++) {
    if (choice.getIngredient(a).getIngName() == pumps[i]) {
      Serial.print("\nIngredient Name: ");
      Serial.println(choice.getIngredient(a).getIngName());
      Serial.print("Position: ");
      Serial.println(a);
      Serial.print("Found pump: ");
      Serial.println(pumps[i]);
      return pumps[i];
    }
  }
}


//Returns pump position in pump array that corresponds to the selected ingredient
int choosePump(String pump) {
  for (int i = 0; i < sizeof pumps / sizeof pumps[0]; i++) {
    if (pump == pumps[i]) {
      Serial.print("Pump Number: ");
      Serial.println(i + 1);
      return i;
    }
  }
}


//Starts pump that corresponds to the needed ingredient
void startPump(int a) {
  Serial.print("Passed value: ");
  Serial.println(a);
  switch (a) {
    case 0:
      digitalWrite(Relay_1, RELAY_ON);
      break;
    case 1:
      digitalWrite(Relay_2, RELAY_ON);
      break;
    case 2:
      digitalWrite(Relay_3, RELAY_ON);
      break;
    case 3:
      digitalWrite(Relay_4, RELAY_ON);
      break;
    case 4:
      digitalWrite(Relay_5, RELAY_ON);
      break;
    case 5:
      digitalWrite(Relay_6, RELAY_ON);
      break;
    default:
      Serial.println("No pumped turned on");
      break;
  }
  Serial.print("pump");
  Serial.print(a);
  Serial.println(" turned on");
}


//For each ingredient in a specified drink, finds and turns on the needed pump for the required time
void makeDrink() {
  Serial.println(choice.getDrinkName());
  for (int a = 0; a < choice.getSize(); a++) {
    startPump(choosePump(findPump(a)));
    Serial.println("Timer started:");
    Serial.print("\tIngredient: ");
    Serial.println(choice.getIngredient(a).getIngName());
    Serial.print("\tVolume: ");
    Serial.println(choice.getIngredient(a).getIngVal());
    Serial.print("\tSeconds: ");
    Serial.println(((choice.getIngredient(a).getIngVal() * 60000) / PUMPSPEEDML) / 1000);

    delay((choice.getIngredient(a).getIngVal() * 60000) / PUMPSPEEDML);
    Serial.println("Timer ended");

    digitalWrite(Relay_1, RELAY_OFF);
    digitalWrite(Relay_2, RELAY_OFF);
    digitalWrite(Relay_3, RELAY_OFF);
    digitalWrite(Relay_4, RELAY_OFF);
    digitalWrite(Relay_5, RELAY_OFF);
    digitalWrite(Relay_6, RELAY_OFF);
    Serial.println("All relays turned off");
  }
  
  myGLCD.setColor(OFF_WHITE);
  myGLCD.setBackColor(OFF_BLACK);
  myGLCD.setFont(BigFont);
  myGLCD.print("ENJOY!", CENTER, 100);
  delay(2000);
  Serial.println("Done the Drink");
}
