#include <Arduino.h>
#include "GlobalDefinition.h"
#include "Expression.h"
#include "State.h"
#include "SadExpression.h"

bool SadExpression::evaluate(Sensors& sensors, State& state) {
  DEBUG_PRINTLN("Evaluate SAD");

  if (!state.is(SAD))
    return false;
    
  if (sensors.hasMotionDetected()) {
    state.setState(CURIOUS, MOTION_DETECTED);

  } else if (sensors.isWatering() && !sensors.isDry()) {
    state.setState(HAPPY, SOIL_WATERED);

  } if (!sensors.isMaxTemperature() && state.is(SAD | SUN))  {
    state.setState(state.getPreviousState(), TEMPERATURE_DECRESED);
  }
  
  return state.was(SAD);
}
