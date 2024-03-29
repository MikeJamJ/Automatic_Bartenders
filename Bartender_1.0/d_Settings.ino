/*
   Settings and sub-settings menus that allwo the user to clean and prime individual pumps and also
*/
void settings() {
  Serial.println("ENTERING SETTINGS");

  int numOfSettingOptions = 3;
  int position_ = 0;

  String pumpNames[] = {"pump 1", "pump 2", "pump 3", "pump 4", "pump 5", "pump 6"};
  int pumpPosition_ = 0;

  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Settings");
  delay(2000);
  lcd.clear();

  printSettingsInfo(position_);

  while (SET == true) {
    /*
       If the user presses the left button, the settings menu will select and print the pump
       name. If the array is at the beginning, the pump at the end of the array will be displayed
    */
    if (digitalRead(butLeft) == HIGH) {
      eventTime = millis();
      if ((eventTime - prevEventTime) > 400) {
        prevEventTime = eventTime;
        if (position_ == 0) {
          position_ = 5;
        }
        else {
          position_--;
        }
        printSettingsInfo(position_);
      }
    }

    /*
       If the user presses the right button, the settings menu will select and print the pump
       name. If the array is at the end, the pump at the beginning of the array will be displayed
    */
    if (digitalRead(butRight) == HIGH) {
      eventTime = millis();
      if ((eventTime - prevEventTime) > 400) {
        prevEventTime = eventTime;
        if (position_ == 5) {
          position_ = 0;
        }
        else {
          position_++;
        }
        printSettingsInfo(position_);
      }
    }

    if (digitalRead(butSelect) == HIGH) {
      eventTime = millis();
      if ((eventTime - prevEventTime) > 400) {
        prevEventTime = eventTime;
        prevButtonTimer = millis();
        while (digitalRead(butSelect) == HIGH) {
          curButtonTimer = millis();
          if ((curButtonTimer - prevButtonTimer) >= 2000) {
            SET = false;
            MM = true;
            break;
          }
        }
        if ((curButtonTimer - prevButtonTimer) < 2000) {
          SUBSET = true;
          subSettingsMenu(SUBSET, pumpNames, pumpPosition_, position_);
        }
      }
    }
  }
  Serial.println("END OF SETTINGS");
  Serial.print("SET: ");
  Serial.println(SET);
}

//-----------------------------------------------------------------------------------------------

void subSettingsMenu(boolean SUBSET, String pumpNames[], int pumpPosition_, int position_) {
  Serial.println("ENTERING SUBSETTINGS");

  String subSetOptions[] = {"Clean Pump    ", "Swap Ing's    ", "Prime Pump    "};
  int subSetPosition_ = 0;

  String ing[] = {
    "Apple Juice",
    "Bourbon",
    "Brandy",
    "Champagne",
    "Club Soda",
    "Cointreau",
    "Coke",
    "Cranberry Juice",
    "Curacao Blue",
    "Curacao Orange",
    "Gin",
    "Green Chartreuse",
    "Grenadine",
    "Kahlua",
    "Lemon Juice",
    "Lime Juice",
    "Margarita Mix",
    "Martini Mix",
    "Milk",
    "Orange Juice",
    "Pineapple Juice",
    "Rum",
    "Scotch",
    "Simple Syrup",
    "Sprite",
    "SP Apple",
    "SP Blue",
    "SP Raspberry",
    "SP Watermelon",
    "S&S Mix",
    "Tequila",
    "Vermouth (Dry)",
    "Vermouth (Sweet)",
    "Vex",
    "Vodka",
    "null"
  };

  int sizeOfIngArray = (sizeof ing / sizeof ing[0]);

  boolean runPump_ = false;
  boolean swap_ = false;

  String word1Clean = "Clean";
  String word2Clean = "Cleaning";
  String word1Prime = "Prime";
  String word2Prime = "Priming";

  lcd.clear();
  lcd.print("Action For Pump:");
  lcd.setCursor(15, 1);
  lcd.print("S");
  printSubSettingInfo(subSetOptions, subSetPosition_);

  delay(400);

  while (SUBSET == true) {

    if (digitalRead(butLeft) == HIGH) {
      eventTime = millis();
      if ((eventTime - prevEventTime) > 400) {
        prevEventTime = eventTime;
        if (subSetPosition_ == 0) {
          subSetPosition_ = 2;
        }
        else {
          subSetPosition_--;
        }
        printSubSettingInfo(subSetOptions, subSetPosition_);
      }
    }


    if (digitalRead(butRight) == HIGH) {
      eventTime = millis();
      if ((eventTime - prevEventTime) > 400) {
        prevEventTime = eventTime;
        if (subSetPosition_ == 2) {
          subSetPosition_ = 0;
        }
        else {
          subSetPosition_++;
        }
        printSubSettingInfo(subSetOptions, subSetPosition_);
      }
    }


    if (digitalRead(butSelect) == HIGH) {
      eventTime = millis();
      if ((eventTime - prevEventTime) > 400) {
        prevEventTime = eventTime;
        prevButtonTimer = millis();

        while (digitalRead(butSelect) == HIGH) {
          curButtonTimer = millis();
          if ((curButtonTimer - prevButtonTimer) >= 2000) {
            SUBSET = false;
            SET = true;
            break;
          }
        }
        if ((curButtonTimer - prevButtonTimer) < 2000) {
          if (subSetPosition_ == 0) {
            runPump_ = true;
            runPump(runPump_, position_, word1Clean, word2Clean);
          }
          else if (subSetPosition_ == 1) {
            swap_ = true;
            swap(swap_, position_, ing, sizeOfIngArray);
          }
          else if (subSetPosition_ == 2) {
            runPump_ = true;
            runPump(runPump_, position_, word1Prime, word2Prime);
          }
        }
      }
    }
  }
  Serial.println("END OF SUBSETTINGS");
  Serial.print("SUBSET: ");
  Serial.println(SUBSET);
}

//-----------------------------------------------------------------------------------------------

void printSettingsInfo(int position_) {
  lcd.clear();
  lcd.print("Select: pump ");
  lcd.setCursor(13, 0);
  lcd.print(position_ + 1);
  lcd.setCursor(0, 1);
  lcd.print(pumps[position_]);
  lcd.setCursor(15, 1);
  lcd.print("S");
}

//-----------------------------------------------------------------------------------------------

void printSubSettingInfo(String subSetOptions[], int subSetPosition_) {
  lcd.setCursor(0, 1);
  lcd.print(subSetOptions[subSetPosition_]);
}

