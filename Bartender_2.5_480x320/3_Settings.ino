/*
   Creator:
      Michael Jamieson
   Date of last Update:
      07/09/2019
   Description:
      Settings menu that allows the user to choose between cleaning and priming individual pumps:
*/

//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------

void settings() {
#if PRINT_TO_SERIAL
  Serial.println(F("\n===================================\nENTERING SETTINGS\n===================================\n"));
#endif
  
  int8_t numOfSettingOptions = 1;
  drawSettingsMenu();
  resetPosValue();
  while (!digitalRead(butSelect)) {}  // wait until button not held

  while (b_SET == true) {
    if (pos != lastPos) {
      noInterrupts();  
      if (pos < 0) pos = numOfSettingOptions;
      else if (pos > numOfSettingOptions) pos = 0;
      serialPrintPosValue();
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
          SubSet_Swap();
        }
        else if (pos == 1) {
          SubSet_Run();
        }
      }      
    }
  }
}
