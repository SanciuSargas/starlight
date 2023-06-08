#include "stepperMotorControl.h"

void setupStepperMotor(Stepper& myStepper) {
  myStepper.setSpeed(60);
}

void spinStepperMotorLeftRight(Stepper myStepper, int stepsPerRevolution) {
  // step one revolution  in one direction:
  myStepper.step(stepsPerRevolution);
  delay(500);

  // step one revolution in the other direction:
  myStepper.step(-stepsPerRevolution);
  delay(500);
}
