#include <Arduino.h>
#include <LedControl.h>

#include "GlobalDefinition.h"
#include "Expression.h"
#include "State.h"
#include "Sensors.h"
#include "Params.h"

#include "IdleExpression.h"
#include "SleepingExpression.h"
#include "SadExpression.h"
#include "HappyExpression.h"
#include "CuriousExpression.h"

#include "ui/UIManager.h"

int DIN = 8; 
int CS =  9;
int CLK = 10;

LedControl lc = LedControl(DIN,CLK,CS,1);

State state(IDLE);
Sensors sensors;
UIManager ui(&lc);

IdleExpression idleState;
SleepingExpression sleepingState;
SadExpression sadState;
HappyExpression happyState;
CuriousExpression curiousState;

//  IDLE, HAPPY, SAD, CURIOUS, SLEEPING 
Expression *expressions[] = { &idleState, &happyState, &sadState, &curiousState, &sleepingState };
const byte EXPRESSION_ARR_SIZE = sizeof(expressions) / sizeof(expressions[0]);
unsigned long initialMillis;


void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  
  pinMode(SENSOR_PRESENCE_PORT, INPUT_PULLUP);
  pinMode(SENSOR_LIGHT_PORT, INPUT_PULLUP);
  pinMode(SENSOR_TEMPERATURE_PORT, INPUT_PULLUP);
  pinMode(SENSOR_SOIL_PORT, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);


  lc.shutdown(0,false);
  lc.setIntensity(0,0);
  // Clear the display
  lc.clearDisplay(0);  



  initialMillis = millis();

  // DEBUG_PRINTLN("GETSAD: ");
  // DEBUG_PRINTLN(getSad()->canHandle(SAD));
  // DEBUG_PRINTLN(getSad()->canHandle(HAPPY));
}

void checkState() {
  Serial.print("PIR: "); Serial.print(sensors.pir);
  Serial.print(" LDR: "); Serial.print(sensors.ldr);
  Serial.print(" DHT: "); Serial.print(sensors.dht);
  Serial.print(" SOIL: "); Serial.print(sensors.soil);
  Serial.print(" SOIL_VAR: "); Serial.println(sensors.soil_var);

  DEBUG_PRINTLN(state.getName(state.getCurrentState()));

  for (int i=0; i<EXPRESSION_ARR_SIZE; i++) {
    if (expressions[i]->evaluate(sensors, state)) {
      DEBUG_PRINTLN("State has changed from " + state.getName(state.getPreviousState()) + " to " + state.getName(state.getCurrentState()));
      ui.update(state.getCurrentState());
      break;
    }
  }
}

void loop() {
  
  if (!sensors.buttonPressed) {
    sensors.read();
  }
  if ((millis() - initialMillis) > SENSOR_READING_FREQ) {
    checkState();
    initialMillis = millis();
    sensors.buttonPressed = false;
  }

  ui.render();

}

