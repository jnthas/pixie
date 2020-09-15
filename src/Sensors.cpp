#include <Arduino.h>
#include "Params.h"
#include "Sensors.h"
#include "dht11.h"

dht11 DHT11;

//ChangeDetector soilChangeDetector;
//ChangeDetector lightChangeDetector(5, 3);
ChangeDetector presenceChangeDetector(10, 1, 3);
//ChangeDetector temperatureChangeDetector;


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

void Sensors::read() {
  //soil = 20;
  DHT11.read(SENSOR_TEMPERATURE_PIN);
  ldr = analogRead(SENSOR_LIGHT_PIN);
  pir = analogRead(SENSOR_PRESENCE_PIN);
  
  temperature = (float) DHT11.temperature;
  humidity = (float) DHT11.humidity;

  soil = analogRead(SENSOR_SOIL_PIN);  


  presenceChangeDetector.read(pir);

      
  
}

void Sensors::resetSoilVariation() {
  this->soil_var = 0;
}

bool Sensors::isMaxTemperature() {
  return temperature > TEMPERATURE_MAX_TOLERANT;
}

bool Sensors::hasMotionDetected() {

  if (presenceChangeDetector.detected) {
    
    Serial.print("Detected variation from ");
    Serial.print(presenceChangeDetector.firstValue);    
    Serial.print(" to ~");
    Serial.println(presenceChangeDetector.sum/presenceChangeDetector._detectionCycles);
    return true;
  }


  return false; //abs(pir) > 10;
}

bool Sensors::isDark() {
  return ldr < LIGHT_DARK_BELOW;
}

bool Sensors::isBright() {
  return ldr > LIGHT_BRIGHT_ABOVE;
}

bool Sensors::isHot() {
  return temperature > TEMPERATURE_MAX_IDEAL;
}

bool Sensors::isDry() {
  return soil < SOIL_MIN_IDEAL;
}

bool Sensors::isWet() {
  return soil > SOIL_MAX_IDEAL;
}

bool Sensors::isWatering() {
  return false;
}
    
