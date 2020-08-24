#ifndef Sensors_h
#define Sensors_h

#include <Arduino.h>


class Sensors 
{
  public:
    bool buttonPressed = true;
    bool pir = false;
    int ldr = 0;
    int dht = 0;
    int soil = 0;
    int soil_var = 0;
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