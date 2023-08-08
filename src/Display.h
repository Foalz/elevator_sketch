#pragma once
class Display{
  public:
    Display(
      int pins[7]
    );
    void printNumber(int num);
  private:
    int displayPins[7];
    int pinA;
    int pinB;
    int pinC;
    int pinD;
    int pinE;
    int pinF;
    int pinG;
};
