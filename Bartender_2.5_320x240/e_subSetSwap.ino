/*
   SS_Swap functions. Will go through the ingredient array and swap
   the current drink with the selected ingredient
*/

//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------

void subSetSwap() {
  Serial.println("\n===================================\nENTERING SWAP\n===================================\n");

  int numOfPumps = 5;
  pos = 0;
  Serial.print("position: ");
  Serial.println(pos);
  int lastButton = 0;
  printPumpButtons();
  printCurrentIngInfo();

  while (SUBSET == true) {
    if (pos != lastPos) {
      //Turns off interrupt to allow the code to finish before another value can be checked
      noInterrupts();  
      if (pos < 0) pos = numOfPumps;
      else if (pos > numOfPumps) pos = 0;
      Serial.print("position: ");
      Serial.println(pos);
      updatePumpButtons(lastButton);
      printCurrentIngInfo();
      lastPos = pos;
      lastButton = pos;
      interrupts();
    }

    if (!digitalRead(butSelect)) {
      curButtonTime = millis();
      prevButtonTime = curButtonTime;
      while (!digitalRead(butSelect)) {
        curButtonTime = millis();
        if ((curButtonTime - prevButtonTime) >= 2000) {
          SET = true;
          SUBSET = false;
          break;
        }
      }
      if (SUBSET) {
        swapFunc(pos);
        Serial.println("Back in subsetswap");
      }
    }
  }
  Serial.print("END OF SWAP\nSUBSET: ");
  Serial.println(SUBSET);
  Serial.println("\n===================================\nREENTERING SETTINGS\n===================================\n");
  resetPosValue();
  settingsScreen();
  while (!digitalRead(butSelect)) {}
}


void swapFunc (int pumpNum) {
  Serial.println("\n===================================\nENTERING SUBSWAP\n===================================\n");
  bool SWAP = true;
  resetPosValue();
  myGLCD.setColor(OFF_WHITE);
  myGLCD.setBackColor(OFF_BLACK);
  myGLCD.print("New Ingredient:", 150, 144);

  String ings[] = {
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
  byte sizeOfIngArray = 36;

  printSwapInfo(ings);

  while (SWAP == true) {
    if (pos != lastPos) {
      if (pos < 0) pos = sizeOfIngArray - 1;
      else if (pos > sizeOfIngArray - 1) pos = 0;
      Serial.print("position: ");
      Serial.println(pos);
      printSwapInfo(ings);
      lastPos = pos;
      delay(20);
    }

    if (!digitalRead(butSelect)) {
      curButtonTime = millis();
      prevButtonTime = curButtonTime;
      while (!digitalRead(butSelect)) {
        curButtonTime = millis();
        if ((curButtonTime - prevButtonTime) >= 2000) {
          SWAP = false;
          break;
        }
      }
      if (SWAP) {
        pumps[pumpNum] = ings[pos];
        SWAP = false;
      }
    }
  }
  Serial.print("END OF SUBSWAP\nSWAP: ");
  Serial.println(SWAP);
  Serial.println("\n===================================\nREENTERING SWAP\n===================================\n");
  resetPosValue();
  resetSwap(pumpNum);
  while (!digitalRead(butSelect)) {}
}


void printSwapInfo(String ings[]) {
  myGLCD.setColor(OFF_BLACK);
  myGLCD.fillRect(160, 164, 319, 176);
  myGLCD.setColor(OFF_WHITE);
  myGLCD.setBackColor(OFF_BLACK);
  myGLCD.print(ings[pos], 160, 164);
}


void resetSwap(byte n){
  pos = n;
  myGLCD.setColor(OFF_BLACK);
  myGLCD.fillRect(150, 144, 319, 176);
  printCurrentIngInfo();
}




/*void subSettingsMenu(boolean SUBSET, String pumpNames[], int pumpPosition_, int position_) {
  Serial.println("ENTERING SUBSETTINGS");

  String subSetOptions[] = {"Clean Pump    ", "Swap Ing's    ", "Prime Pump    "};
  int subSetPosition_ = 0;
  //String pumpNames[] = {"pump 1", "pump 2", "pump 3", "pump 4", "pump 5", "pump 6"};
  //int pumpPosition_ = 0;

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

  printSubSettingInfo(subSetOptions, subSetPosition_);

  delay(400);

  while (SUBSET == true) {

    /*if (digitalRead(butLeft) == HIGH) {
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
            swap(swap_, position_, ing);
          }
          else if (subSetPosition_ == 2) {
            runPump_ = true;
            runPump(runPump_, position_, word1Prime, word2Prime);
          }
        }
      }
    }
*//*
  }
  Serial.println("END OF SUBSETTINGS\nSUBSET: " + SUBSET);
  }


  void printSubSettingInfo(String subSetOptions[], int subSetPosition_) {
  //lcd.setCursor(0, 1);
  //lcd.print(subSetOptions[subSetPosition_]);
  }


  void runPump(boolean runPump_, int position_, String word1, String word2) {
  int prevTime;
  int currentTime;

  myGLCD.print("Hold Button to ", 100, 100);
  myGLCD.print(word1, 250, 100);

  prevTime = millis();

  while (runPump_ == true) {

    if (digitalRead(butSelect) == HIGH) {
      eventTime = millis();
      if ((eventTime - prevEventTime) > 400) {
        //lcd.print(word2);
        while (digitalRead(butSelect) == HIGH) {
          if (position_ == 0) {
            digitalWrite(Relay_1, RELAY_ON);
          }
          else if (position_ == 1) {
            digitalWrite(Relay_2, RELAY_ON);
          }
          else if (position_ == 2) {
            digitalWrite(Relay_3, RELAY_ON);
          }
          else if (position_ == 3) {
            digitalWrite(Relay_4, RELAY_ON);
          }
          else if (position_ == 4) {
            digitalWrite(Relay_5, RELAY_ON);
          }
          else if (position_ == 5) {
            digitalWrite(Relay_6, RELAY_ON);
          }
        }
        digitalWrite(Relay_1, RELAY_OFF);
        digitalWrite(Relay_2, RELAY_OFF);
        digitalWrite(Relay_3, RELAY_OFF);
        digitalWrite(Relay_4, RELAY_OFF);
        digitalWrite(Relay_5, RELAY_OFF);
        digitalWrite(Relay_6, RELAY_OFF);
      }

      prevTime = millis();
    }

    currentTime = millis();
    if ((currentTime - prevTime) > 3000) {
      runPump_ = false;
      break;
    }
  }
  settings();
  }

  //-----------------------------------------------------------------------------------------------

  /*void swap(boolean swap_, int position_, String ing[], int sizeOfIngArray) {
  int prevTime;
  int currentTime;
  int arrayPosition = 0;

  lcd.clear();
  lcd.print("Swap pump");
  lcd.print(position_);
  lcd.print(" with: ");
  lcd.setCursor(0, 1);
  lcd.print(ing[arrayPosition]);

  prevTime = millis();

  while (swap_ == true) {

    if (digitalRead(butRight) == HIGH) {
      eventTime = millis();
      if ((eventTime - prevEventTime) > 400) {
        prevEventTime = eventTime;
        if (arrayPosition == sizeOfIngArray - 1) {
          arrayPosition = 0;
        }
        else {
          arrayPosition++;
        }
        lcd.clear();
        lcd.print("Swap pump");
        lcd.print(position_ + 1);
        lcd.print(" with: ");
        lcd.setCursor(0, 1);
        lcd.print(ing[arrayPosition]);
      }
      prevTime = millis();
    }

    if (digitalRead(butLeft) == HIGH) {
      eventTime = millis();
      if ((eventTime - prevEventTime) > 400) {
        prevEventTime = eventTime;
        if (arrayPosition == 0) {
          arrayPosition = sizeOfIngArray - 1;
        }
        else {
          arrayPosition--;
        }
        lcd.clear();
        lcd.print("Swap pump");
        lcd.print(position_ + 1);
        lcd.print(" with: ");
        lcd.setCursor(0, 1);
        lcd.print(ing[arrayPosition]);
      }
      prevTime = millis();
    }

    if (digitalRead(butSelect) == HIGH) {
      eventTime = millis();
      if ((eventTime - prevEventTime) > 400) {
        prevEventTime = eventTime;
        pumps[position_] = ing[arrayPosition];
        swap_ = false;
        possibleDrinks();
        alphabetize();
        break;
      }
    }
    currentTime = millis();
    if ((currentTime - prevTime) > 3000) {
      swap_ = false;
      break;
    }
  }
  settings();
  }
*/


