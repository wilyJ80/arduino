#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <nanoFORTH.h>

const byte ROWS = 4;
const byte COLS = 4;

// Placeholder: hex digits
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { 'F', '0', 'E', 'D' }
};
byte rowPins[ROWS] = { 11, 10, 9, 8 };
byte colPins[COLS] = { 7, 6, 5, 4 };

LiquidCrystal_I2C lcd(0x27, 16, 2);

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void continuous() {
  for (;;) {
    char key = keypad.getKey();
    if (key) {
      if (key == 'D') {
        lcd.clear();
      } else {
        lcd.print(key);
      }
    }
  }
}

const char code[] PROGMEM =
  "0 API\n";
// First: define C function as loop that *continuously* checks for a char
// Char types: value for stack, value for stack and Arduino-specific operations (push, pop, pin, out?)
// Fire this 0 API function in startup as Forth word and keep it in a forever loop...

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(115200);
  n4_api(0, continuous);
  n4_setup(code);
}

void loop() {
  n4_run();
}
