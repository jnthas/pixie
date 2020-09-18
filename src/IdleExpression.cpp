#include <Arduino.h>
#include "GlobalDefinition.h"
#include "Expression.h"
#include "State.h"
#include "Params.h"
#include "IdleExpression.h"

bool IdleExpression::evaluate(Sensors& sensors, State& state) {
  DEBUG_PRINTLN("Evaluate IDLE");
  if (!state.is(IDLE)) 
    return false;

  if (sensors.hasMotionDetected()) {
    state.setState(CURIOUS, MOTION_DETECTED);

  } else if (sensors.isDark()) {
    // TODO create a schedule class to deal with situations like this
    if (timeout == 0) {
      timeout = millis();
    } else if ((millis() - timeout) > SLEEPING_TIME_TO_SLEEP) {
      timeout = 0;
      state.setState(SLEEPING | MOON, LIGHTS_OFF);
    }
   
  } else if (sensors.isHot() && 
      sensors.isBright() && 
      !sensors.isMaxTemperature() && 
      !state.was(HAPPY | SUN))  {
    state.setState(HAPPY | SUN, IN_THE_SUN);

  } else if (sensors.isMaxTemperature())  {
    state.setState(SAD | SUN, HIGH_TEMPERATURE);

  } else if (sensors.isDry()) {
    state.setState(SAD | WATER, DRY_SOIL);

  } else if (sensors.isWatering()) {
    state.setState(HAPPY | WATER, SOIL_WATERED);
  } else if (sensors.isTouching()) {
    state.setState(HAPPY, PLANT_TOUCH);
  }


  return state.was(IDLE);
}