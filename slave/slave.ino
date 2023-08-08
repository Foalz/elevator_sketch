#include <Wire.h>
#include "src/Display.h"
int displayPins[7] = { 2, 3, 4, 5, 6, 7, 8 };
int x = 0;
Display
display(displayPins);
void setup() {
  Wire.begin(9);   
  Wire.onReceive(receiveEvent);
}
void   receiveEvent(int bytes) {
  x = Wire.read();
}
void loop() {
  display.printNumber(x);
}
