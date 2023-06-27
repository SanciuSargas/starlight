#include "stepperMotorControl.h"

void setupStepperMotor(Stepper& myStepper) {
  myStepper.setSpeed(50);
}

void stepperMotorAutomaticState(Stepper myStepper, int stepsPerRevolution, int STEPPER_ENABLE_A, int STEPPER_ENABLE_B) {
  digitalWrite(STEPPER_ENABLE_A, HIGH); 
  digitalWrite(STEPPER_ENABLE_B, HIGH); 
  myStepper.step(10);
  digitalWrite(STEPPER_ENABLE_A, LOW); 
  digitalWrite(STEPPER_ENABLE_B, LOW); 
}
