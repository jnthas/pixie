#ifndef State_h
#define State_h

#include <Arduino.h>


enum ExpressionEnum {
  NONE = 0,
  IDLE = 1,
  HAPPY = 2,
  SAD = 4,  
  CURIOUS = 8,
  SLEEPING = 16,
  SUN = 32,
  WATER = 64,
  HEART = 128,
  MOON = 256
};

enum ReasonEnum {
  NO_REASON,
  HIGH_TEMPERATURE,
  TEMPERATURE_DECRESED,
  DRY_SOIL,
  SOIL_WATERED,
  HAPPY_TIMEDOUT,
  CURIOUS_TIMEDOUT,
  LIGHTS_ON,
  LIGHTS_OFF,
  MOTION_DETECTED,
  IN_THE_SUN,
  PLANT_TOUCH
};


class State {
  private: 
    ExpressionEnum _current;
    ExpressionEnum _previous;
    ReasonEnum reason;

  public:  
    State(ExpressionEnum expression);
    void setState(ExpressionEnum expression, ReasonEnum reason);
    bool is(ExpressionEnum state);
    bool was(ExpressionEnum state);
    ExpressionEnum getCurrentState();
    ExpressionEnum getPreviousState();
    ReasonEnum getReason();
    String getName(ExpressionEnum expression);
};

#endif