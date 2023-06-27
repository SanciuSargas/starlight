#ifndef STEPPER_MOTOR_CONTROL_H 
#define STEPPER_MOTOR_CONTROL_H 
#include <Stepper.h>
#include <Arduino.h>

void setupStepperMotor(Stepper& myStepper);
void stepperMotorAutomaticState(Stepper myStepper, int stepsPerRevolution, int STEPPER_ENABLE_A, int STEPPER_ENABLE_B);


#endif
