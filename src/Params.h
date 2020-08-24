#ifndef Params_h
#define Params_h

#include <Arduino.h>

// System
const unsigned int SENSOR_READING_FREQ = 1000;

const byte SENSOR_TEMPERATURE_PORT = 2;
const byte SENSOR_LIGHT_PORT = 3;
const byte SENSOR_SOIL_PORT = 4;
const byte SENSOR_PRESENCE_PORT = 5;



// Expressions
const unsigned int HAPPY_SHORT_TIME = 3000;
const unsigned int HAPPY_LONG_TIME = 10000;

const unsigned int SLEEPING_WAKEUP_TIMEOUT = 10000;

const unsigned int CURIOUS_SHORT_TIME = 3000;


// Sensors readings 
const byte TEMPERATURE_MAX_TOLERANT = 10;
const byte TEMPERATURE_MIN_IDEAL = 3;
const byte TEMPERATURE_MAX_IDEAL = 6;

const byte LIGHT_DARK_BELOW = 3;
const byte LIGHT_BRIGHT_ABOVE = 7;

const byte SOIL_MIN_IDEAL = 4;
const byte SOIL_MAX_IDEAL = 6;
const byte SOIL_VARIATION = 2;

#endif