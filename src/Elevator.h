#pragma once
class Elevator{
  public:
    Elevator(int btnPins[4], int swPins[4], int nfloors, int btnSource, int swSource);
    int checkRequest();
    int getCurrentFloor();
    void setMaintenanceMode(int mode);
    int underMaintenance = 0;
  private: 
    int checkFloor();
    int swSource;
    int btnSource;
    int currentFloor = 0;
    int nfloors;
    int btnPins[4];
    int swPins[4];
};
