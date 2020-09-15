#ifndef Params_h
#define Params_h

#include <Arduino.h>

// System
const unsigned int SENSOR_READING_FREQ = 1000;

const byte SENSOR_SOIL_PIN = 34;
const byte SENSOR_PRESENCE_PIN = 26;
const byte SENSOR_TEMPERATURE_PIN = 27;
const byte SENSOR_LIGHT_PIN = 39;



// Expressions
const unsigned int HAPPY_SHORT_TIME = 5000;
const unsigned int HAPPY_LONG_TIME = 10000;

const unsigned int SLEEPING_WAKEUP_TIMEOUT = 10000;

const unsigned int CURIOUS_SHORT_TIME = 3000;


// Sensors readings 
const float TEMPERATURE_MAX_TOLERANT = 29;
const float TEMPERATURE_MIN_IDEAL = 12;
const float TEMPERATURE_MAX_IDEAL = 26;

const short LIGHT_DARK_BELOW = 0;
const short LIGHT_BRIGHT_ABOVE = 900;

const byte SOIL_MIN_IDEAL = 15;
const byte SOIL_MAX_IDEAL = 25;
const byte SOIL_VARIATION = 5;

#endif