
#include <Arduino.h>
#include "GlobalDefinition.h"
#include "Expression.h"
#include "State.h"
#include "Params.h"
#include "CuriousExpression.h"
#include "DecisionMaker.h"

bool CuriousExpression::evaluate(Sensors& sensors, State& state) {
  DEBUG_PRINTLN("Evaluate CURIOUS");
  if (!state.is(CURIOUS))
    return false;
  
  if (timeout == 0) {
    timeout = millis();
  } else if ((millis() - timeout) > CURIOUS_SHORT_TIME) {
    timeout = 0;

    if (DecisionMaker::doYouLikeIt(5) && !state.was(SAD)) {
      state.setState(HAPPY, CURIOUS_TIMEDOUT);
    } else {
      state.setState(state.getPreviousState(), CURIOUS_TIMEDOUT);
    }

    
  }
  
  return state.was(CURIOUS);
}
