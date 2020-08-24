#include <Arduino.h>
#include "GlobalDefinition.h"
#include "Expression.h"
#include "State.h"
#include "IdleExpression.h"

bool IdleExpression::evaluate(Sensors& sensors, State& state) {
  DEBUG_PRINTLN("Evaluate IDLE");
  if (!state.is(IDLE)) 
    return false;

  
  if (sensors.hasMotionDetected()) {
    state.setState(CURIOUS, MOTION_DETECTED);

  } else if (sensors.isDark()) {
    state.setState(SLEEPING, LIGHTS_OFF);

  } else if (sensors.isHot() && 
      sensors.isBright() && 
      !sensors.isMaxTemperature() && 
      !state.was(HAPPY | SUN))  {
    state.setState(HAPPY | SUN, IN_THE_SUN);

  } else if (sensors.isBright() && sensors.isMaxTemperature())  {
    state.setState(SAD | SUN, HIGH_TEMPERATURE);

  } else if (sensors.isDry()) {
    state.setState(SAD | WATER, DRY_SOIL);

  } else if (sensors.isWatering()) {
    state.setState(HAPPY | WATER, SOIL_WATERED);
  }


  return state.was(IDLE);
}