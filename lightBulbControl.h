#ifndef LIGHT_BULB_CONTROL_H 
#define LIGHT_BULB_CONTROL_H
#include <Arduino.h>

void setupLightBulbModule();
void checkLightGateState(int LIGHT_GATE_1, int LIGHT_GATE_2, int LIGHT_BULB_RELAY);
void toggleLightBulb(int LIGHT_BULB_RELAY, byte lightBulbState);


#endif
