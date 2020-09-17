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

int DIN = 25; 
int CS =  33;
int CLK = 32;

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

  lc.shutdown(0,false);
  lc.setIntensity(0,0);
  // Clear the display
  lc.clearDisplay(0);  

  DecisionMaker::initialize();

  initialMillis = millis();
}

void checkState() {
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
  
  if ((millis() - initialMillis) > SENSOR_READING_FREQ) {
    sensors.read();
    checkState();
    initialMillis = millis();
  }

  ui.render();
}

