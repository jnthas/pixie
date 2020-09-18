
#include <Arduino.h>
#include "GlobalDefinition.h"
#include "Expression.h"
#include "State.h"
#include "Params.h"
#include "LoadingExpression.h"

bool LoadingExpression::evaluate(Sensors& sensors, State& state) {
  DEBUG_PRINTLN("Evaluate LOADING");
  if (!state.is(LOADING))
    return false;
  
  if (timeout == 0) {
    timeout = millis();
  } else if ((millis() - timeout) > PIXIE_LOADING_DURATION) {
    timeout = 0;

    state.setState(IDLE, LOADING_TIMEDOUT);    
  }
  
  return state.was(LOADING);
}
