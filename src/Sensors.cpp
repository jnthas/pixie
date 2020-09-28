#include <Arduino.h>
#include "Params.h"
#include "Sensors.h"
#include "dht11.h"

dht11 DHT11;

SensorTrigger presenceTrigger(PRESENCE_THRESHOLD, PRESENCE_DETECTION_CYCLES, PRESENCE_RECOVERY_CYCLES);
SensorTrigger wateringTrigger(WATERING_THRESHOLD, WATERING_DETECTION_CYCLES, WATERING_RECOVERY_CYCLES);
SensorTrigger touchTrigger(TOUCH_THRESHOLD, TOUCH_DETECTION_CYCLES, TOUCH_RECOVERY_CYCLES);

Sensors::Sensors() {
  pinMode(SENSOR_LIGHT_PIN, INPUT);
  pinMode(SENSOR_PRESENCE_PIN, INPUT);
  pinMode(SENSOR_TEMPERATURE_PIN, INPUT);
  pinMode(SENSOR_SOIL_PIN, INPUT);
  pinMode(SENSOR_TOUCH_PIN, INPUT);
}

void Sensors::read() {
  DHT11.read(SENSOR_TEMPERATURE_PIN);
  ldr = map(analogRead(SENSOR_LIGHT_PIN), 0, MAX_SENSOR_VALUE, 0, 1000);
  pir = map(analogRead(SENSOR_PRESENCE_PIN), 0, MAX_SENSOR_VALUE, 0, 10000);
  
  
  soil = map((MAX_SENSOR_VALUE - analogRead(SENSOR_SOIL_PIN)), 0, MAX_SENSOR_VALUE, 0, 1000);
  touch = touchRead(SENSOR_TOUCH_PIN);
  
  temperature = (float) DHT11.temperature;
  humidity = (float) DHT11.humidity;


  Serial.print("PIR: "); Serial.print(pir);
  Serial.print(" LDR: "); Serial.print(ldr);
  Serial.print(" TEMP: "); Serial.print(temperature);
  Serial.print(" HUM: "); Serial.print(humidity);
  Serial.print(" SOIL: "); Serial.print(soil);
  Serial.print(" TOUCH: "); Serial.println(touch);
  
  presenceTrigger.handle(pir);
  wateringTrigger.handle(soil);
  touchTrigger.handle(touch);
}

bool Sensors::isMaxTemperature() {
  return temperature > TEMPERATURE_MAX_TOLERANT;
}

bool Sensors::hasMotionDetected() {
  bool presence = presenceTrigger.checkTriggerAndDisable();

  if (presence) {
    
    Serial.print("Detected variation from ");
    Serial.print(presenceTrigger.firstValue);    
    Serial.print(" to ~");
    Serial.println(presenceTrigger.sum/presenceTrigger._detectionCycles);
    return true;
  }

  return presence;
}

bool Sensors::isDark() {
  return ldr < LIGHT_DARK_BELOW_PERC;
}

bool Sensors::isBright() {
  return ldr > LIGHT_BRIGHT_ABOVE_PERC;
}

bool Sensors::isHot() {
  return temperature > TEMPERATURE_MAX_IDEAL;
}

bool Sensors::isDry() {
  return soil < SOIL_MIN_IDEAL_PERC;
}

bool Sensors::isWet() {
  return soil > SOIL_MAX_IDEAL_PERC;
}

bool Sensors::isWatering() {  

  bool watering = wateringTrigger.checkTriggerAndDisable();

  if (watering && wateringTrigger.isIncreased()) {
    
    Serial.print("Watering variation from ");
    Serial.print(wateringTrigger.firstValue);    
    Serial.print(" to ~");
    Serial.println(wateringTrigger.sum/wateringTrigger._detectionCycles);
    return true;
  }

  return false;
}

bool Sensors::isTouching() {  

  bool touching = touchTrigger.checkTriggerAndDisable();

  if (touching && touchTrigger.isDecreased()) {
    
    Serial.print("Touching variation from ");
    Serial.print(touchTrigger.firstValue);    
    Serial.print(" to ~");
    Serial.println(touchTrigger.sum/touchTrigger._detectionCycles);
    return true;
  }

  return false;
}
    
