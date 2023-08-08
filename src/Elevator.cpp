#include "Elevator.h"
#include "Arduino.h"

Elevator::Elevator(int btnPins[4], int swPins[4], int nfloors, int btnSource, int swSource){
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
