#ifndef Params_h
#define Params_h

#include <Arduino.h>
#include "DecisionMaker.h"

// System
const unsigned int SENSOR_READING_FREQ = 1000;

const byte SENSOR_SOIL_PIN = 34;
const byte SENSOR_PRESENCE_PIN = 26;
const byte SENSOR_TEMPERATURE_PIN = 27;
const byte SENSOR_LIGHT_PIN = 39;



// Expressions
const unsigned int HAPPY_SHORT_TIME = 5000;
const unsigned int HAPPY_LONG_TIME = 10000;

const unsigned int SLEEPING_MAX_TIMEOUT = 15000;

const unsigned int CURIOUS_SHORT_TIME = 3000;


// Sensors readings 
const float TEMPERATURE_MAX_TOLERANT = 29;
const float TEMPERATURE_MIN_IDEAL = 12;
const float TEMPERATURE_MAX_IDEAL = 26;

const short PRESENCE_THRESHOLD = 5;
const short PRESENCE_DETECTION_CYCLES = 3;
const short PRESENCE_RECOVERY_CYCLES = 3;
const short WATERING_THRESHOLD = 100;
const short WATERING_DETECTION_CYCLES = 3;
const short WATERING_RECOVERY_CYCLES = 3;


// SENSOR VALUE ACCEPT A RANGE FROM 0 TO 1000 

// 0 - TOTALLY DARK
// 4095 - TOTALLY BRIGHT
const short LIGHT_DARK_BELOW_PERC = 1;
const short LIGHT_BRIGHT_ABOVE_PERC = 800;

// 1520 -> TOTALLY WET
// 4095 -> TOTALLY DRY
const short SOIL_MIN_IDEAL_PERC = 250;
const short SOIL_MAX_IDEAL_PERC = 750;

#endif