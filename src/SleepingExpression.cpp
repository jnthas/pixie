#include <Arduino.h>
#include "GlobalDefinition.h"
#include "Expression.h"
#include "State.h"
#include "Params.h"
#include "DecisionMaker.h"
#include "SleepingExpression.h"

bool SleepingExpression::evaluate(Sensors& sensors, State& state) {
  DEBUG_PRINTLN("Evaluate SLEEPING");
  if (!state.is(SLEEPING)) 
    return false;

  //short TIME_TO_WAKEUP = DecisionMaker::waitSomeTime(SLEEPING_TIMEOUT);

  if (sensors.isMaxTemperature())  {
    state.setState(SAD | SUN, HIGH_TEMPERATURE);
  
  } else if (sensors.isDry()) {
    state.setState(SAD | WATER, DRY_SOIL);
  
  } else if (sensors.isWatering()) {
    state.setState(HAPPY | WATER, SOIL_WATERED);

  } else if (!sensors.isDark()) {
    if (timeout == 0) {
      timeout = millis();
    } else if ((millis() - timeout) > TIME_TO_WAKEUP) {
      timeout = 0;
      // TODO I could create a "next" state concept, in this case, next state would be IDLE, and current state CURIOUS
      state.setState(IDLE, LIGHTS_ON);
    }
  }


  return state.was(SLEEPING);
}
