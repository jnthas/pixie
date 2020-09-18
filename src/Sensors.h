#ifndef Sensors_h
#define Sensors_h

#include <Arduino.h>
#include "GlobalDefinition.h"

#define MAX_SENSOR_VALUE 4095

struct SensorTrigger {
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
  bool triggered = false;

  SensorTrigger(int threshold, byte detectionCycles, byte recoveryCycles) {
    this->_threshold = threshold;
    this->_detectionCycles = detectionCycles;
    this->_recoveryCycles = recoveryCycles;
  }
  
  void handle(int value) {
    this->currentValue = value;    

    if (this->recovering) {
      DEBUG_PRINTLN("Recovering");
      this->cycleCounter++;
      
      if (this->cycleCounter >= this->_recoveryCycles) {
        DEBUG_PRINTLN("Recovered");
        this->recovering = false;
        this->possibleChange = false;
        this->triggered = false;

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

          DEBUG_PRINTLN("Nevermind");
        }

      } else if (abs(this->currentValue - this->previousValue) > this->_threshold) {
        this->possibleChange = true;
        this->cycleCounter = 1;
        this->firstValue = this->previousValue;
        this->sum = this->currentValue;

        DEBUG_PRINTLN("Possible change");
      }

      if (this->cycleCounter >= this->_detectionCycles) {
        DEBUG_PRINTLN("Detected change");
        this->recovering = true;
        this->cycleCounter = 0;
        this->triggered = true;
      }
    }

    this->previousValue = this->currentValue;
  }

  bool checkTriggerAndDisable() {
    if (this->triggered) {
      this->triggered = false;
      return true;
    }

    return false;
  }

  bool isIncreased() {
    return (firstValue <= (sum/_detectionCycles));
  }

  bool isDecreased() {
    return (firstValue > (sum/_detectionCycles));
  }
  
};


class Sensors 
{
  private:
    int pir = 0;
    int ldr = 0;
    float temperature = 0;
    float humidity = 0;
    int soil = 0;
    int touch = 0;
  public:    
    Sensors();
    void read();
    bool isMaxTemperature();
    bool hasMotionDetected();
    bool isDark();
    bool isBright();
    bool isHot();
    bool isDry();
    bool isWet();
    bool isWatering();
    bool isTouching();
};

#endif