#include "Keypad.h"

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { 'F', '0', 'E', 'D' }
};
byte rowPins[ROWS] = { 9, 8, 7, 6 };
byte colPins[COLS] = { 5, 4, 3, 2 };

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

char hexChars[2] = { 'X', 'X' };

void setup() {
  Serial.begin(9600);
}

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
        // Serial.print(hexChars[i]);

        if (hexChars[i] >= '0' && hexChars[i] <= '9') {
          decValues[i] = hexChars[i] - '0';
        } else if (hexChars[i] >= 'a' && hexChars[i] <= 'f') {
          decValues[i] = hexChars[i] - 'a' + 10;
        } else if (hexChars[i] >= 'A' && hexChars[i] <= 'F') {
          decValues[i] = hexChars[i] - 'A' + 10;
        } else {
          Serial.println("Invalid hex character detected\n");
        }
      }

      byte combinedValue = (decValues[0] << 4) | decValues[1];
      char asciiChar = (char)combinedValue;

      if (asciiChar == '\r') {
        Serial.println();
      } else {
        Serial.print(asciiChar);
      }
      hexChars[0] = 'X';
    }
  }
}
