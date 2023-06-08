#ifndef STEPPER_MOTOR_CONTROL_H 
#define STEPPER_MOTOR_CONTROL_H 
#include <Stepper.h>
#include <Arduino.h>

void setupStepperMotor(Stepper& myStepper);
void spinStepperMotorLeftRight(Stepper myStepper, int stepsPerRevolution);


#endif
