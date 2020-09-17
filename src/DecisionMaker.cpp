
#include <Arduino.h>
#include "DecisionMaker.h"
#include "Expression.h"
#include "Params.h"


void DecisionMaker::initialize() {
  unsigned long seed = 0;
  for (int i=0; i<16; i++)
  {
    seed = seed | ((analogRead(SENSOR_SOIL_PIN) & 0x01) << i) | ((analogRead(SENSOR_LIGHT_PIN) & 0x01) << i);
  }

  Serial.print("Seed: "); Serial.println(seed);
  randomSeed(seed);
}

bool DecisionMaker::doYouLikeIt(byte humor) {    
  byte num = random(100);
  Serial.print("Random: "); Serial.println(num);
  return humor >= num;
}

short DecisionMaker::waitSomeTime(short maxSeconds) {  
  short num = random(maxSeconds);
  Serial.print("Random: "); Serial.println(num);
  return num;
}

