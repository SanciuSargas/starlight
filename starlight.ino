//#include <FastLED.h>
#include "ledStrip.h"
#include "stepperMotorControl.h"
#include "lightBulbControl.h"

#define JOYSTICK_BUTTON 4
#define LED_PIN 7
#define NUM_LEDS 16


#define POT_1 A0
#define POT_2 A1
#define POT_3 A2
#define JOYSTICK_Y A3
#define JOYSTICK_X A4

#define STEPPER_ENABLE_A 12
#define STEPPER_ENABLE_B 13

#define LIGHT_GATE_1 2
#define LIGHT_GATE_2 3
#define LIGHT_BULB_RELAY 5

//settings for the menu
bool lastMenuButtonState = true;
int currentMenuOption = 0;
int numberOfMenuOptions = 2;

// variables for light dot movement
int currentLed = 0;

int lightDotShadowLength = 3;

CRGB leds[NUM_LEDS];


// variables for stepper motor
const int stepsPerRevolution = 200;
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);



void setup() {
  pinMode(JOYSTICK_BUTTON, INPUT);

  pinMode(POT_1, INPUT);
  pinMode(POT_2, INPUT);
  pinMode(POT_3, INPUT);
  pinMode(JOYSTICK_X, INPUT);
  pinMode(JOYSTICK_Y, INPUT);

  pinMode(STEPPER_ENABLE_A, OUTPUT);
  pinMode(STEPPER_ENABLE_B, OUTPUT);

  pinMode(LIGHT_GATE_1, INPUT);
  pinMode(LIGHT_GATE_1, INPUT);
  pinMode(LIGHT_BULB_RELAY, OUTPUT);

  Serial.begin(9600);
  setupLEDstrip(NUM_LEDS);
  setupStepperMotor(myStepper);
  setupLightBulbModule();
  
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {
  unsigned long currentMillis = millis();
  
  //changing the menue with a button click
  if (digitalRead(JOYSTICK_BUTTON) == LOW and lastMenuButtonState) {
    lastMenuButtonState = 0;
    currentMenuOption++;

    if (currentMenuOption >= numberOfMenuOptions) {
      currentMenuOption = 0;
    }
  } else if (digitalRead(JOYSTICK_BUTTON)) {
    lastMenuButtonState = 1;
  }

  //control part
  if (currentMenuOption == 0) {
    updateLightDotTrailLength(JOYSTICK_Y);
    updateLightDotColor(POT_1, POT_2, POT_3, currentLed, NUM_LEDS, leds);
    updateLightDotPosition(JOYSTICK_X, currentLed, NUM_LEDS, leds);
  } else if (currentMenuOption == 1) {
    updateStepperMotorPosition(JOYSTICK_X, myStepper, STEPPER_ENABLE_A, STEPPER_ENABLE_B);
  }

  //uncontroled/default part
  if (currentMenuOption == 0) {
    stepperMotorAutomaticState(myStepper, STEPPER_ENABLE_A, STEPPER_ENABLE_B);
  } else if (currentMenuOption == 1) {
    automaticallyUpdateLightDotPosition(JOYSTICK_Y, currentLed, NUM_LEDS, leds);
  }

  
  checkLightGateState(LIGHT_GATE_1, LIGHT_GATE_2, LIGHT_BULB_RELAY);
}

