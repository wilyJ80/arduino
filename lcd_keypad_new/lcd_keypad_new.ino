#include "Keypad.h"
#include <Wire.h>
#include "LiquidCrystal_I2C.h"

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { 'F', '0', 'E', 'D' }
};
byte rowPins[ROWS] = { 11, 10, 9, 8 };
byte colPins[COLS] = { 7, 6, 5, 4 };

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

char hexChars[2] = { 'X', 'X' };

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Change the address (0x27) if needed

void setup() {
  lcd.init();
  lcd.backlight();
}

byte charCount = 0;
byte isSecondLine = 0;

void loop() {
  char key = keypad.getKey();

  if (key) {
    if (hexChars[0] == 'X') {
      hexChars[0] = key;
      hexChars[1] = 'X';
    } else {
      hexChars[1] = key;

      byte decValues[2];
      for (byte i = 0; i < 2; i++) {
        if (hexChars[i] >= '0' && hexChars[i] <= '9') {
          decValues[i] = hexChars[i] - '0';
        } else if (hexChars[i] >= 'a' && hexChars[i] <= 'f') {
          decValues[i] = hexChars[i] - 'a' + 10;
        } else if (hexChars[i] >= 'A' && hexChars[i] <= 'F') {
          decValues[i] = hexChars[i] - 'A' + 10;
        } else {
          lcd.clear();
          lcd.println("ERR");
        }
      }

      byte combinedValue = (decValues[0] << 4) | decValues[1];
      char asciiChar = (char)combinedValue;

      if (asciiChar == '\r') {
        lcd.clear();  // Clear the LCD

      } else {

        if (charCount >= 16 && !isSecondLine) {
          lcd.setCursor(0, 1);
          isSecondLine = 1;
          charCount = 0;

        } else if (charCount >= 16 && isSecondLine) {
          lcd.clear();
          lcd.setCursor(0, 0);
          isSecondLine = 0;
          charCount = 0;
        }

        lcd.print(asciiChar);
        charCount++;
      }
      hexChars[0] = 'X';
    }
  }
}
