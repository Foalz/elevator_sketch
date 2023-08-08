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

    2, 3, 4, 5: Used as INPUT mode to read if the button was pressed.
    6, 7: Used as OUTPUT mode to be the voltage source
    8, 9, 10, 11: Used for stepper motor H bridge.

#### Analog Pins

    A0, A1, A2, A3: Used as INPUT mode to read if reed switches are closed.
    A4, A5: Used to comunicate and send instructions to slave arduino.

### Slave Arduino

#### Digital Pins

    2, 3, 4, 5, 6, 7, 8: Used as OUTPUT mode, to be the voltage source for 7 segmend display.

#### Analog Pins

    A4, A5: Used to comunicate and receive instructions from master arduino.

## Circuit diagrams

### Buttons

Used to request elevator to go to desired floor.

![Buttons circuit](/assets/buttons.png)

### Reed Switches

Used to detect if elevator has arrived to desired floor. Elevator car has inside a small magnet.

![Reed switches circuit](/assets/reedswitch.png)

### Stepper motor

Used to turn on and send instructions to stepper motor, the motor used was stepper motor 28byj-48.

![Stepper circuit](/assets/stepper.png)

### Master and Slave connections

Used to send instructions from master to slave in real time about which floor is currently the elevator car.

![Master and slave circuit](/assets/display.png)
