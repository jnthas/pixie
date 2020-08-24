
#include <Arduino.h>
#include "GlobalDefinition.h"
#include "Expression.h"
#include "State.h"
#include "Params.h"
#include "HappyExpression.h"


bool HappyExpression::evaluate(Sensors& sensors, State& state) {
  DEBUG_PRINTLN("Evaluate HAPPY");

  if (!state.is(HAPPY))
    return false;

  limit = (state.getReason() != IN_THE_SUN) ? HAPPY_SHORT_TIME : HAPPY_LONG_TIME;
  
  if (timeout == 0) {
    timeout = millis();
  } else if ((millis() - timeout) > limit) {
    timeout = 0;
    if (state.getReason() == SOIL_WATERED) {
      sensors.resetSoilVariation();
    }
    state.setState(IDLE, HAPPY_TIMEDOUT);
  }
  
  return state.was(HAPPY);
}
