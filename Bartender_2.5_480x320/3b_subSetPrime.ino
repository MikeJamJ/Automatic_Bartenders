/*
   Creator:
      Michael Jamieson
   Date of last Update:
      07/09/2019
   Description:
      Function for running a desired pump.
*/

//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------

void SubSet_Run() {
#if PRINT_TO_SERIAL
  Serial.println(F("\n===================================\nENTERING RUN\n===================================\n"));
#endif

  uint8_t lastButton = 0;
  drawSubSet_Run();
  resetPosValue();
  updatePumpSelectionButton(1);
  updateIngredientSelection(0);
  while (!digitalRead(butSelect)) {} // wait until button not held

  while (b_SUBSET == true) {
    if (pos != lastPos) {
      //Turns off interrupt to allow the code to finish before another value can be checked
      noInterrupts();
      if (pos < 0) pos = numOfPumps - 1;
      else if (pos > numOfPumps - 1) pos = 0;
      serialPrintPosValue();
      updatePumpSelectionButton(1);
      updateIngredientSelection(0);
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
          b_SET = true;
          b_SUBSET = false;
          break;
        }
      }
      if (b_SUBSET) {
        runPump(pos);
        pos = lastButton;
        lastPos = pos;
      }
    }
  }

  drawSettingsMenu();
  resetPosValue();
  while (!digitalRead(butSelect)) {}
}


void runPump(byte pumpNum) {
#if PRINT_TO_SERIAL
  Serial.println(F("\n===================================\nENTERING SUBPRIME\n===================================\n"));
#endif

  // cover previous instruction and print new ones
  drawRunPump();
  bool b_RUN = true;
  prevButtonTime = millis();

  while (b_RUN == true) {

    // while the button is not pressed, countdown to return
    curButtonTime = millis();
    if ((curButtonTime - prevButtonTime) == 500) {
      tft.setCursor((tft.width() / 2) + (TEXT_WIDTH * 5), 300);
      tft.print(F("3"));
    }
    else if ((curButtonTime - prevButtonTime) == 1500) {
      tft.setCursor((tft.width() / 2) + (TEXT_WIDTH * 5), 300);
      tft.print(F("2"));
    }
    else if ((curButtonTime - prevButtonTime) == 2500) {
      tft.setCursor((tft.width() / 2) + (TEXT_WIDTH * 5), 300);
      tft.print(F("1"));
    }
    else if ((curButtonTime - prevButtonTime) >= 3500) {
      b_RUN = false;
      break;
    }

    // Run the pump if button is pressed
    if (!digitalRead(butSelect)) {
      tft.fillRect( ((tft.width() / 2) - (TEXT_WIDTH * 12 / 2)), 300, TEXT_WIDTH * 12, TEXT_HEIGHT, BACKGROUND_COLOR);
      startPump(pumpNum);
      while (!digitalRead(butSelect)) {}  // don't do anything until the button is released
      digitalWrite(pumps[pumpNum].pin, RELAY_OFF);
      prevButtonTime = millis();
      printCenterH(F("Exiting in  "), 300);
    }
  }

  reset_Run();
  while (!digitalRead(butSelect)) {}
}
