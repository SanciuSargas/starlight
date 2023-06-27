#include "lightBulbControl.h"

byte lightBulbState = LOW;
byte lightGatePreviousState1 = HIGH;
byte lightGatePreviousState2 = HIGH;

unsigned long previousMillisForLighGate = 0;
int delayBetweenLighGate = 1;


void setupLightBulbModule() {

}

void checkLightGateState(int LIGHT_GATE_1, int LIGHT_GATE_2, int LIGHT_BULB_RELAY) {
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillisForLighGate >= delayBetweenLighGate) {
    previousMillisForLighGate = currentMillis;
    
    if ((digitalRead(LIGHT_GATE_1) && !lightGatePreviousState1) || (digitalRead(LIGHT_GATE_2) && !lightGatePreviousState2)) {
      lightBulbState = !lightBulbState; 

      toggleLightBulb(LIGHT_BULB_RELAY, lightBulbState);
    }

    lightGatePreviousState1 = digitalRead(LIGHT_GATE_1);
    lightGatePreviousState2 = digitalRead(LIGHT_GATE_2);
  }
}

void toggleLightBulb(int LIGHT_BULB_RELAY, byte lightBulbState) {
  digitalWrite(LIGHT_BULB_RELAY, lightBulbState);
}


