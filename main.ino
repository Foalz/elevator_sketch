#include <Stepper.h>
#include <Wire.h>
#include "src/Elevator.h"
#include "src/Display.h"
long int t1;
long int t2;
long int elapsed_time;
long int tfloor = 15000;

//Defining button pins array & voltage source pin
int btnPins[4] = { 2, 3, 4, 5 };
int btnSource = 7;
//Defining reed switches array & voltage source pin
int swPins[4] = { A0, A1, A2, A3 };
int swSource = 6;
int nfloors = 4;

int stepsPerRevolution = 2048;
int speed = 10;
int dt = 500;
int cfloor;
int req;
//Variable for handling current request from server
String incomingByte;

Elevator 
elevator(btnPins, swPins, nfloors, btnSource, swSource);
Stepper
stepper(stepsPerRevolution, 8, 10, 9, 11);

void goUp(int start, int req, int end){
  t1 = millis();
  while (true){
    t2 = millis();
    //Elapsed time measures the time elevator has in motion
    //approximated time for this project is 15 seconds per floor,
    //so, if more than 15 seconds has elapsed, it means the elevator is lost.
    elapsed_time = abs(t1 - t2);
    if (elapsed_time > abs(start - req)*tfloor){
      elevator.setMaintenanceMode(1);
      break;
    };
    //If a swith pin has been read, prints the floor value in 7 segment display,
    //Wire library is sending a signal to the SLAVE arduino, which has Display 
    //library, which has been.
    if (digitalRead(end)) {
      Wire.beginTransmission(9);
      Wire.write(elevator.getCurrentFloor());
      Wire.endTransmission();
      break;
    };
    for (int i = 0; i < 4; i++){
      if (digitalRead(swPins[i])){
        Wire.beginTransmission(9);
        Wire.write(elevator.getCurrentFloor());
        Wire.endTransmission();
      }
    }
    stepper.step(1);
  }
  for (int i = 0; i < 500; i++){
    if (end == A3) break;
    stepper.step(1);
  }
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  t1 = 0;
  t2 = 0;
  elapsed_time = 0;
}

void goDown(int start, int req, int end){
  t1 = millis();
  while (true){
    t2 = millis();
    //Elapsed time measures the time elevator has in motion
    //approximated time for this project is 15 seconds per floor,
    //so, if more than 15 seconds has elapsed, it means the elevator is lost.
    elapsed_time = abs(t1 - t2);
    if (elapsed_time > abs(start - req)*tfloor){
      elevator.setMaintenanceMode(1);
      break;
    };

    //If a swith pin has been read, prints the floor value in 7 segment display,
    //Wire library is sending a signal to the SLAVE arduino, which has Display 
    //library, which has been.
    if (digitalRead(end)) {
      Wire.beginTransmission(9);
      Wire.write(elevator.getCurrentFloor());
      Wire.endTransmission();
      break;
    };
    for (int i = 0; i < 4; i++){
      if (digitalRead(swPins[i])){
        Wire.beginTransmission(9);
        Wire.write(elevator.getCurrentFloor());
        Wire.endTransmission();
      }
    }
    stepper.step(-1);
  }
  for (int i = 0; i < 1000; i++){
    stepper.step(-1);
  }
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  t1 = 0;
  t2 = 0;
  elapsed_time = 0;
}

void checkServerInput(){
  //This function checks messages through serial port, 
  //in this case, expressjs servers is sending messages 
  //through POST requests.

  //These messages are related to setting maintenance mode
  //ON or OFF, and requesting floors to the elevator circuit.

  //If elevator is lost, is recommended to request first floor,
  //or floor 0.
  while (elevator.underMaintenance){
    Serial.println("under maintenance");
    if (Serial.available() > 0){
      incomingByte = Serial.readString();
      if (incomingByte == "0") moveCar(0);
      if (incomingByte == "1") moveCar(1);
      if (incomingByte == "2") moveCar(2);
      if (incomingByte == "3") moveCar(3);
      if (incomingByte == "i") moveCar(9);
      if (incomingByte == "n") elevator.setMaintenanceMode(0);
    }
  }
}

void moveCar(int req){
  //This function checks if elevator has to go up or go down.
  if (( req > cfloor ) && ( req != nfloors + 1 )){
    goUp(elevator.getCurrentFloor(), req, swPins[req]);
  } else if (( req < cfloor ) && ( req != nfloors + 1 )){
    goDown(elevator.getCurrentFloor(), req, swPins[req]);
  }
}

void setup() {
  //Begins the serial port at 9600 bauds and initializing
  //wire library, setting this arduino as MASTER
  Serial.begin(9600);
  Serial.setTimeout(100);
  stepper.setSpeed(speed);
  Wire.begin();
}

void loop() {
  //Gets current floor from elevator class
  cfloor = elevator.getCurrentFloor();
  //Sends current floor to SLAVE arduino
  Wire.beginTransmission(9);
  Wire.write(cfloor);
  Wire.endTransmission();

  //If serial port is available to receive messages, then read them
  //and proccess them. 
  if (Serial.available() > 0){
    incomingByte = Serial.readString();
    if (incomingByte == "m"){
      elevator.setMaintenanceMode(1);
    } else if (incomingByte == "n"){
      elevator.setMaintenanceMode(0);
    }
  }
  if ((cfloor >= 0) && (cfloor <= nfloors)){
    switch(elevator.underMaintenance){
      case 0:
        req = elevator.checkRequest();
        moveCar(req); 
        break;
      case 1:
        checkServerInput();
        break;
    }
    //This condition means that elevator is lost, for security,
    //sends it to maintenance mode (physical buttons does not work)
  } else if (cfloor == nfloors + 1){
    elevator.setMaintenanceMode(1);
    checkServerInput();
  }
  delay(100);
}
