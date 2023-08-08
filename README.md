# elevator_sketch

A university project for Control Systems I; this is an Elevator with 4 floors (ground, 1, 2 & 3).
Circuit

For this project, you will need the following components:

- Arduino UNO (2): Master & Slave.
- Reed Switch normally open (4): Or you can use any similar, like infrarred, because they are used to indicate the elevator it has arrived to requested floor.
- 7 segment display (1): Common cathode.
- Push Buttons (4): To request the elevator a certain floor.

## Pins used

### Master Arduino

#### Digital Pins

- 2, 3, 4, 5: Used as INPUT mode to read if the button was pressed.
- 6, 7: Used as OUTPUT mode to be the voltage source
- 8, 9, 10, 11: Used for stepper motor H bridge.

#### Analog Pins

- A0, A1, A2, A3: Used as INPUT mode to read if reed switches are closed.
- A4, A5: Used to comunicate and send instructions to slave arduino.

### Slave Arduino

#### Digital Pins

- 2, 3, 4, 5, 6, 7, 8: Used as OUTPUT mode, to be the voltage source for 7 segmend display.

#### Analog Pins

- A4, A5: Used to comunicate and receive instructions from master arduino.

## Circuit diagrams

### Buttons

Used to request elevator to go to desired floor.

![Buttons circuit](/assets/buttons.png)

### Reed Switches

Used to detect if elevator has arrived to desired floor. Elevator car has inside a small magnet.

![Reed switches circuit](/assets/reedswitch.png)

### Stepper motor

Used to turn on and send instructions to stepper motor, the motor used was stepper motor 28byj-48. This will need to be used
with its respective driver (or H bridge).

![Stepper circuit](/assets/stepper.png)

### Master and Slave connections

Used to send instructions from master to slave in real time about which floor is currently the elevator car.

![Master and slave circuit](/assets/display.png)

## Code

### main.ino

This code has all the functions to make elevator work, it uses Wire and Stepper libraries (provided by arduino) and Elevator 
and Display libraries (provided by us). This code needs to be loaded to MASTER arduino.

### slave.ino

This code has an small definition and use of Wire library to receive all information from master arduino. This code needs to be loaded to SLAVE arduino.

### Elevator library

Is used to simplify main code, ensuring this could be used as guide to other students. 

Elevator.cpp:

```cpp
#include "Elevator.h"
#include "Arduino.h"

Elevator::Elevator(int btnPins[4], int swPins[4], int nfloors, int btnSource, int swSource){
  //This is the constructor of the class, here we are defining all the necessary variables to
  //make easier the use of main code, and keep it simpler as possible.
  //
  //It needs to initialize with two arrays, one for button pins, and other for reed switches pins.
  //btnPins[4] & swPins[4] respectively (for 4 floors, if elevator has 6 floors, put 6 elements instead).
  //nfloors variable sets the maximum number of floors of the elevator,
  //
  //btnSource and swSource are the voltage sources of buttons and switches.
  for (int i = 0; i < nfloors; i++){
    this->btnPins[i] = btnPins[i];
    this->swPins[i] = swPins[i];
  }
  this->nfloors = nfloors;
  this->currentFloor = 0;
  this->swSource = swSource;
  this->btnSource = btnSource;
  pinMode(this->btnSource, OUTPUT);
  digitalWrite(this->btnSource, HIGH);
  pinMode(this->swSource, OUTPUT);
  digitalWrite(this->swSource, HIGH);
}

void Elevator::setMaintenanceMode(int mode){
  //Maintenance mode ensures all the buttons remains in LOW mode, to avoid misfunctions between server
  //and physical circuit.
  this->underMaintenance = mode;
  digitalWrite(this->btnSource, !mode);
}

int Elevator::checkFloor(){
  for (int i = 0; i < this->nfloors; i++){
    if (digitalRead(this->swPins[i])) return i;
  }
  return nfloors + 1;
}

int Elevator::checkRequest(){
  for (int i = 0; i < this->nfloors; i++){
    if (digitalRead(this->btnPins[i])) return i;
  }
  return nfloors + 1;
}

int Elevator::getCurrentFloor(){
  this->currentFloor = checkFloor();
  return this->currentFloor;
}
```

### Display library

This is used to turn on certain pins of 7 segment display. 

Display.cpp:

```cpp
#include "Display.h"
#include "Arduino.h"

Display::Display(int pins[7]){
  //Sets all the pins as OUTPUT, in this constructor, we need to pass the list
  //of pins we will connect to the digital pins (except for ground).
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
  //Change it as you need! Make sure you have connected it at right way.
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
```
## Warnings

Make sure to follow this guide and the circuit exactly, otherwise you can damage your arduino and your components, we recommend you to use this code and this project as a guide, and if you want to test it, connect carefully all the components, we are not
responsible for any damages on your boards.
