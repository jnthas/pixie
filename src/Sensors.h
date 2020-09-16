#ifndef Sensors_h
#define Sensors_h

#include <Arduino.h>

struct ChangeDetector {
  int _threshold;
  byte _detectionCycles;
  byte _recoveryCycles;
  bool recovering = false;
  bool possibleChange = false;  
  int firstValue;
  int previousValue;
  int currentValue;
  int sum;
  byte cycleCounter;

  ChangeDetector(int threshold, byte detectionCycles, byte recoveryCycles) {
    this->_threshold = threshold;
    this->_detectionCycles = detectionCycles;
    this->_recoveryCycles = recoveryCycles;
  }
  
  bool handle(int value) {
    this->currentValue = value;    
    bool changeDetected = false;

    if (this->recovering) {
      Serial.println("Recovering");
      this->cycleCounter++;
      
      if (this->cycleCounter >= this->_recoveryCycles) {
        Serial.println("Recovered");
        this->recovering = false;
        this->possibleChange = false;

        this->cycleCounter = 0;
        this->firstValue = 0;
        this->sum = 0;
      }

    } else {
      
      if (this->possibleChange) {

        if (abs(this->currentValue - this->firstValue) > this->_threshold) {
          this->cycleCounter++;
          this->sum += this->currentValue;
        } else {
          this->recovering = true;
          this->cycleCounter = 0;

          Serial.println("Nevermind");
        }

      } else if (abs(this->currentValue - this->previousValue) > this->_threshold) {
        this->possibleChange = true;
        this->cycleCounter = 1;
        this->firstValue = this->previousValue;
        this->sum = this->currentValue;

        Serial.println("Possible change");
      }

      if (this->cycleCounter >= this->_detectionCycles) {
        Serial.println("Detected change");
        this->recovering = true;
        this->cycleCounter = 0;
        changeDetected = true;
      }
    }

    this->previousValue = this->currentValue;

    return changeDetected;
  }

};


class Sensors 
{
  public:
    int pir = 0;
    int ldr = 0;
    float temperature = 0;
    float humidity = 0;
    int soil = 0;
    int soil_var = 0;
    Sensors();
    void read();
    void resetSoilVariation();
    bool isMaxTemperature();
    bool hasMotionDetected();
    bool isDark();
    bool isBright();
    bool isHot();
    bool isDry();
    bool isWet();
    bool isWatering();
};

#endif