#include "ledStrip.h"

int redValue = 0; 
int blueValue = 0;
int greenValue = 0;
   
unsigned long previousMillisForTrailChange = 0;
int delayBetweenTrailChange = 10;

unsigned long previousMillisForDotMovement = 0;
int delayBetweenMoves = 10;

unsigned long previousMillisForColorChange = 0;
int delayBetweenColorChange = 10;

int lightDotTrailLenght = 0;
int maxLightDotTrailLength = 0;

void setupLEDstrip(int NUM_LEDS) {
  maxLightDotTrailLength = NUM_LEDS / 2 - 2;
}

void updateLightDotTrailLength(int JOYSTICK_Y) {
  unsigned long currentMillis = millis();
  int analogValueForJOYSTICK_Y = analogRead(JOYSTICK_Y);
  

  delayBetweenTrailChange = map(abs(analogValueForJOYSTICK_Y-532), 0, 512, 1000, 100);

  if (currentMillis - previousMillisForTrailChange >= delayBetweenTrailChange) {
    previousMillisForTrailChange = currentMillis;
    
    if (analogValueForJOYSTICK_Y > 550) {
      lightDotTrailLenght++;

      if (lightDotTrailLenght >= maxLightDotTrailLength){
        lightDotTrailLenght = maxLightDotTrailLength;
      }
    } else if (analogValueForJOYSTICK_Y < 500) {
      lightDotTrailLenght--;

      if (lightDotTrailLenght <= 0){
        lightDotTrailLenght = 0;
      }
    }
  }
}

void updateLightDotColor(int POT_1, int POT_2, int POT_3, int& currentLed, int NUM_LEDS, CRGB* leds) {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillisForColorChange >= delayBetweenColorChange) {
    previousMillisForColorChange = currentMillis;

    redValue = analogRead(POT_1) / 4;
    blueValue = analogRead(POT_2) / 4;
    greenValue = analogRead(POT_3) / 4;

    //setLightDotTrail(currentLed, NUM_LEDS, leds, 1);
    //leds[currentLed] = CRGB(redValue, greenValue, blueValue);
    //FastLED.show();
  }
}

void updateLightDotPosition(int JOYSTICK_X, int& currentLed, int NUM_LEDS, CRGB* leds) {
  unsigned long currentMillis = millis();
  int analogValueForJOYSTICK_X = analogRead(JOYSTICK_X);
     
  delayBetweenMoves = map(abs(analogValueForJOYSTICK_X-520), 0, 512, 1000, 40);

  if (currentMillis - previousMillisForDotMovement >= delayBetweenMoves) {
    previousMillisForDotMovement = currentMillis;
    // leds[currentLed] = CRGB(255-redValue, 255-greenValue, 255-blueValue);
    leds[currentLed] = CRGB(0, 0, 0);
 
    if (analogValueForJOYSTICK_X > 530) {
      currentLed++;
      if (currentLed >= NUM_LEDS){
        currentLed = 0;
      }
      setLightDotTrail(currentLed, NUM_LEDS, leds, 0);
    } else if (analogValueForJOYSTICK_X < 500) {
      currentLed--;
      if (currentLed < 0){
        currentLed = NUM_LEDS - 1;
      }
      setLightDotTrail(currentLed, NUM_LEDS, leds, 2);
    } else {
      setLightDotTrail(currentLed, NUM_LEDS, leds, 1);
    }

    //leds[currentLed] = CRGB(redValue, greenValue, blueValue);
    //FastLED.show();
  } else if (currentMillis - previousMillisForDotMovement >= 20) {
    if (analogValueForJOYSTICK_X < 530 && analogValueForJOYSTICK_X > 500 ) {
     setLightDotTrail(currentLed, NUM_LEDS, leds, 1);
    }
  }
}

// shadow options:
//  0 = left
//  1 = both sides
//  2 = right
void setLightDotTrail(int currentLed, int NUM_LEDS, CRGB* leds, int trailOption) {

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, 0, 0);
  }
  
  leds[currentLed] = CRGB(redValue, greenValue, blueValue);

  if (trailOption == 0 or trailOption == 1) {
    for (int i = 1; i <= lightDotTrailLenght; i++) {
      double ledBrightnessMultiplier = (0.2 * (double(lightDotTrailLenght - i + 1) / double(lightDotTrailLenght))); 
      
      int redValueTrail = redValue*ledBrightnessMultiplier;
      int greenValueTrail = greenValue*ledBrightnessMultiplier;
      int blueValueTrail = blueValue*ledBrightnessMultiplier;

      if (currentLed - i >= 0) {
        leds[currentLed - i] = CRGB(redValueTrail, greenValueTrail, blueValueTrail);
      } else {
        leds[NUM_LEDS - (i - currentLed) ] = CRGB(redValueTrail, greenValueTrail, blueValueTrail);
      }
    }
  }

  if (trailOption == 2 or trailOption == 1) {
    for (int i = 1; i <= lightDotTrailLenght; i++) {
      double ledBrightnessMultiplier = (0.2 * (double(lightDotTrailLenght - i + 1) / double(lightDotTrailLenght))); 
      
      int redValueTrail = redValue*ledBrightnessMultiplier;
      int greenValueTrail = greenValue*ledBrightnessMultiplier;
      int blueValueTrail = blueValue*ledBrightnessMultiplier;

      if (currentLed + i < NUM_LEDS) {
        leds[currentLed + i] = CRGB(redValueTrail, greenValueTrail, blueValueTrail);
      } else {
        leds[i - (NUM_LEDS - currentLed)] = CRGB(redValueTrail, greenValueTrail, blueValueTrail);
      }
    }
  }

  FastLED.show();
}
