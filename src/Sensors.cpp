#include <Arduino.h>
#include "Params.h"
#include "Sensors.h"

void Sensors::read() {
  if (digitalRead(2) == LOW && digitalRead(6) != LOW) {
    this->pir = true;
    buttonPressed = true;
  } else if (digitalRead(2) == LOW && digitalRead(6) == LOW) {
    this->pir = false;
    buttonPressed = true;
  }

  if (digitalRead(3) == LOW && digitalRead(6) != LOW) {
    this->ldr++;
    buttonPressed = true;
  } else if (digitalRead(3) == LOW && digitalRead(6) == LOW) {
    this->ldr--;
    buttonPressed = true;
  }

  if (digitalRead(4) == LOW && digitalRead(6) != LOW) {
    this->dht++;
    buttonPressed = true;
  } else if (digitalRead(4) == LOW && digitalRead(6) == LOW) {
    this->dht--;
    buttonPressed = true;
  }

  if (digitalRead(5) == LOW && digitalRead(6) != LOW) {
    int oldValue = this->soil;
    this->soil++;
    int newValue = this->soil;

    this->soil_var += newValue - oldValue;
    buttonPressed = true;
  } else if (digitalRead(5) == LOW && digitalRead(6) == LOW) {
    // variation stops at zero
    int oldValue = this->soil;
    this->soil--;
    int newValue = this->soil;
    
    if (this->soil_var > 0) {
      this->soil_var += newValue - oldValue;  
    }

    buttonPressed = true;
  }

}

void Sensors::resetSoilVariation() {
  this->soil_var = 0;
}

bool Sensors::isMaxTemperature() {
  return dht > TEMPERATURE_MAX_TOLERANT;
}

bool Sensors::hasMotionDetected() {
  return pir;
}

bool Sensors::isDark() {
  return ldr < LIGHT_DARK_BELOW;
}

bool Sensors::isBright() {
  return ldr > LIGHT_BRIGHT_ABOVE;
}

bool Sensors::isHot() {
  return dht > TEMPERATURE_MAX_IDEAL;
}

bool Sensors::isDry() {
  return soil < SOIL_MIN_IDEAL;
}

bool Sensors::isWet() {
  return soil > SOIL_MAX_IDEAL;
}

bool Sensors::isWatering() {
  return soil_var > SOIL_VARIATION;
}
    
