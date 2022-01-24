/*
   settings menu that allow the user to choose between cleaning and priming individual pumps:
   settings();
   printSettingsInfo(int pos);
*/

//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------

void settings() {
  Serial.println(F("\n===================================\nENTERING SETTINGS\n===================================\n"));

  int numOfSettingOptions = 1;
  resetPosValue();

  while (!digitalRead(butSelect)) {}

  while (b_SET == true) {
    if (pos != lastPos) {
      //Turns off interrupt to allow the code to finish before another value can be checked
      noInterrupts();  
      if (pos < 0) pos = numOfSettingOptions;
      else if (pos > numOfSettingOptions) pos = 0;
      Serial.print(F("position: "));
      Serial.println(pos);
      updateSettingsButtons();
      lastPos = pos;
      interrupts();
    }

    if (!digitalRead(butSelect)) {
      curButtonTime = millis();
      prevButtonTime = curButtonTime;
      while (!digitalRead(butSelect)) {
        curButtonTime = millis();
        if ((curButtonTime - prevButtonTime) >= 2000) {
          b_SET = false;
          b_MM = true;
          break;
        }
      }
      if (!b_MM) {
        b_SUBSET = true;
        if (pos == 0) {
          drawSubSet_Swap();
          SubSet_Swap();
        }
        else if (pos == 1) {
          drawSubSet_Run();
          SubSet_Run();
        }
      }      
    }
  }
  Serial.print(F("END OF b_SETTINGS\nb_SET: "));
  Serial.println(b_SET);
}


//For b_SUBSET menus
void printCurrentIngInfo() {
  tft.fillRect(160, 84, 319, 96, BACKGROUND_COLOR);
  tft.setCursor(160, 84);
  tft.setTextColor(TEXT_COLOR, BACKGROUND_COLOR);
  tft.print(pumps[pos].value);
}
