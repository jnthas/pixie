#include <Arduino.h>
#include "Params.h"
#include "Sensors.h"
#include "dht11.h"

dht11 DHT11;

SensorTrigger presenceTrigger(5, 2, 2);
SensorTrigger wateringTrigger(10, 2, 2);

Sensors::Sensors() {
  pinMode(SENSOR_LIGHT_PIN, INPUT);
  pinMode(SENSOR_PRESENCE_PIN, INPUT);
  pinMode(SENSOR_TEMPERATURE_PIN, INPUT);
  pinMode(SENSOR_SOIL_PIN, INPUT);

  // pinMode(SENSOR_PRESENCE_PIN, INPUT_PULLUP);
  // pinMode(SENSOR_TEMPERATURE_PIN, INPUT_PULLUP);
  // pinMode(SENSOR_SOIL_PIN, INPUT_PULLUP);
  // pinMode(6, INPUT_PULLUP);

}


short perc(float value) {
  return (value * 1000) / MAX_SENSOR_VALUE;
}

void Sensors::read() {
  DHT11.read(SENSOR_TEMPERATURE_PIN);
  ldr = perc(analogRead(SENSOR_LIGHT_PIN));
  pir = perc(analogRead(SENSOR_PRESENCE_PIN));
  
  temperature = (float) DHT11.temperature;
  humidity = (float) DHT11.humidity;

  soil = perc(MAX_SENSOR_VALUE - analogRead(SENSOR_SOIL_PIN));

  Serial.print("PIR: "); Serial.print(pir);
  Serial.print(" LDR: "); Serial.print(ldr);
  Serial.print(" TEMP: "); Serial.print(temperature);
  Serial.print(" HUM: "); Serial.print(humidity);
  Serial.print(" SOIL: "); Serial.println(soil);
  
  presenceTrigger.handle(pir);
  wateringTrigger.handle(soil);
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
    
