#include "src/nanoFORTH.h"
void setup() {
  Serial.begin(115200);
  n4_setup();
}

void loop() {
  n4_run();
}
