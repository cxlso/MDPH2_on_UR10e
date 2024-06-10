/*
  Stepper Motor Extruder Pulse and Direction

  This Arduino sketch controls a stepper motor using analog signals for speed (Pul/Step) and direction (Dir).

  Author:   cxlso (cxl.so)
  Year:     2024
  Version:  1

  Hardware Compatibility:
  - Stepper motor-based extruders (e.g., LDM WASP Extruders, Massive Dimension MDPH2 Extruder)

  Library Dependencies:
  - AccelStepper library (https://www.airspayce.com/mikem/arduino/AccelStepper/)

  License: GNU General Public License, version 2 or later (GPL-2.0-or-later) (https://www.gnu.org/licenses/gpl-2.0.html)
*/



#include <AccelStepper.h>

// Define driver digital pin connections
#define PulPin 2
#define DirPin 3
#define EnaPin 4

// Create a new AccelStepper object
AccelStepper stepper(AccelStepper::DRIVER, PulPin, DirPin);



void setup() {

  // Define stepper maximum speed in steps per second (steps/s)
  stepper.setMaxSpeed(4000);

  // Enable stepper
  pinMode(EnaPin, OUTPUT);
  digitalWrite(EnaPin, HIGH);

}



void loop() {

  // Read sensor values
  int Step_Reading = analogRead(A0);
  int Dir_Reading = analogRead(A1);

  // Limit minimum speed
  if (Step_Reading < 100) Step_Reading = 0;

  // Map Step_Reading to a speed range from 0 to 4000 steps/s
  int stepperMotorSpeed = map(Step_Reading, 0, 1023, 0, 4000);
  // Map Dir_Reading to a voltage range from 0V to 5V
  float stepperMotorDir = map(Dir_Reading, 0, 1023, 0, 5);

  // Set motor direction and speed
  if (stepperMotorDir > 0.5) {
    stepper.setSpeed(-stepperMotorSpeed);
  } else {
    stepper.setSpeed(stepperMotorSpeed);
  }
  stepper.runSpeed();
  
}

//Note: Arduino analog pins take from 0 to 5V and translate it to a digital range of 0 to 1023 (10 bits).