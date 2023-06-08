#ifndef LED_STRIP_H 
#define LED_STRIP_H
#include <FastLED.h>
#include <Arduino.h>

void setupLEDstrip(int NUM_LEDS);
void updateLightDotTrailLength(int JOYSTICK_Y);
void updateLightDotColor(int POT_1, int POT_2, int POT_3, int& currentLed, CRGB* leds);
void updateLightDotPosition(int JOYSTICK_X, int& currentLed, int NUM_LEDS, CRGB* leds);
void setLightDotTrail(int currentLed, int NUM_LEDS, CRGB* leds, int trailOption);

#endif
