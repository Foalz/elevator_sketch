#include "Display.h"
#include "Arduino.h"

Display::Display(int pins[7]){
  for (int i = 0; i < 7; i++){
    pinMode(pins[i], OUTPUT);
  }
  this->pinA = pins[0];
  this->pinB = pins[1];
  this->pinC = pins[2];
  this->pinD = pins[3];
  this->pinE = pins[4];
  this->pinF = pins[5];
  this->pinG = pins[6];
}

void Display::printNumber(int num){
  switch(num){
    case 0:
      //Prints "P"
      digitalWrite(this->pinA, 1);
      digitalWrite(this->pinB, 1);
      digitalWrite(this->pinC, 0);
      digitalWrite(this->pinD, 0);
      digitalWrite(this->pinE, 1);
      digitalWrite(this->pinF, 1);
      digitalWrite(this->pinG, 1);
      break;
    case 1:
      //Prints "1"
      digitalWrite(this->pinA, 0);
      digitalWrite(this->pinB, 1);
      digitalWrite(this->pinC, 1);
      digitalWrite(this->pinD, 0);
      digitalWrite(this->pinE, 0);
      digitalWrite(this->pinF, 0);
      digitalWrite(this->pinG, 0);
      break;
    case 2:
      //Prints "2"
      digitalWrite(this->pinA, 1);
      digitalWrite(this->pinB, 1);
      digitalWrite(this->pinC, 0);
      digitalWrite(this->pinD, 1);
      digitalWrite(this->pinE, 1);
      digitalWrite(this->pinF, 0);
      digitalWrite(this->pinG, 1);
      break;
    case 3:
      //Prints "3"
      digitalWrite(this->pinA, 1);
      digitalWrite(this->pinB, 1);
      digitalWrite(this->pinC, 1);
      digitalWrite(this->pinD, 1);
      digitalWrite(this->pinE, 0);
      digitalWrite(this->pinF, 0);
      digitalWrite(this->pinG, 1);
      break;
    case 4:
      //Prints "L"
      digitalWrite(this->pinA, 0);
      digitalWrite(this->pinB, 0);
      digitalWrite(this->pinC, 0);
      digitalWrite(this->pinD, 1);
      digitalWrite(this->pinE, 1);
      digitalWrite(this->pinF, 1);
      digitalWrite(this->pinG, 0);
      break;
    case 5:
      //Prints "S"
      digitalWrite(this->pinA, 0);
      digitalWrite(this->pinB, 0);
      digitalWrite(this->pinC, 0);
      digitalWrite(this->pinD, 1);
      digitalWrite(this->pinE, 1);
      digitalWrite(this->pinF, 1);
      digitalWrite(this->pinG, 0);
      break;
    case 6:
      //Turns off all the display
      digitalWrite(this->pinA, 0);
      digitalWrite(this->pinB, 0);
      digitalWrite(this->pinC, 0);
      digitalWrite(this->pinD, 0);
      digitalWrite(this->pinE, 0);
      digitalWrite(this->pinF, 0);
      digitalWrite(this->pinG, 0);
      break;
  }
}
