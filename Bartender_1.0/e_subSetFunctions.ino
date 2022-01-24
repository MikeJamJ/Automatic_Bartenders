/*
   SubSetting functions. The first will run the pump while the select button
   is being held. The second will go through the ingredient array and swap
   the current drink with the selected ingredient
*/

void runPump(boolean runPump_, int position_, String word1, String word2) {
  int prevTime;
  int currentTime;

  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Hold Button");
  lcd.setCursor(4, 1);
  lcd.print("to ");
  lcd.print(word1);

  prevTime = millis();

  while (runPump_ == true) {

    if (digitalRead(butSelect) == HIGH) {
      eventTime = millis();
      if ((eventTime - prevEventTime) > 400) {
        lcd.clear();
        lcd.setCursor(4, 0);
        lcd.print(word2);
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
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("Hold Button");
      lcd.setCursor(4, 1);
      lcd.print("to ");
      lcd.print(word1);
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

void swap(boolean swap_, int position_, String ing[], int sizeOfIngArray) {
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


