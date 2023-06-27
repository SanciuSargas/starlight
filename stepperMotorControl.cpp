#include "stepperMotorControl.h"


unsigned long previousMillisForStepperMotorPosition = 0;
int delayBetweenStepperMoves = 10;


void setupStepperMotor(Stepper& myStepper) {
  myStepper.setSpeed(50);
}

void updateStepperMotorPosition(int JOYSTICK_X, Stepper myStepper, int STEPPER_ENABLE_A, int STEPPER_ENABLE_B) {
  unsigned long currentMillis = millis();
  int analogValueForJOYSTICK_X = analogRead(JOYSTICK_X);

   
  delayBetweenStepperMoves = map(abs(analogValueForJOYSTICK_X-520), 0, 512, 1000, 40);

  if (currentMillis - previousMillisForStepperMotorPosition  >= delayBetweenStepperMoves)  {
    digitalWrite(STEPPER_ENABLE_A, HIGH); 
    digitalWrite(STEPPER_ENABLE_B, HIGH); 
    
    previousMillisForStepperMotorPosition  = currentMillis;
 
    if (analogValueForJOYSTICK_X > 530) {
      myStepper.step(5);
    } else if (analogValueForJOYSTICK_X < 500) {
      myStepper.step(-5);
    }

    digitalWrite(STEPPER_ENABLE_A, LOW); 
    digitalWrite(STEPPER_ENABLE_B, LOW);
  } 
}


void stepperMotorAutomaticState(Stepper myStepper, int STEPPER_ENABLE_A, int STEPPER_ENABLE_B) {
  digitalWrite(STEPPER_ENABLE_A, HIGH); 
  digitalWrite(STEPPER_ENABLE_B, HIGH); 
  myStepper.step(10);
  digitalWrite(STEPPER_ENABLE_A, LOW); 
  digitalWrite(STEPPER_ENABLE_B, LOW); 
}
