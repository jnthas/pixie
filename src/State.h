#ifndef State_h
#define State_h

#include <Arduino.h>


enum ExpressionEnum {
  NONE = 0,
  LOADING = 1,
  IDLE = 2,
  HAPPY = 4,
  SAD = 8,  
  CURIOUS = 16,
  SLEEPING = 32,
  SUN = 64,
  WATER = 128,
  HEART = 256,
  MOON = 512  
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
  PLANT_TOUCH,
  LOADING_TIMEDOUT
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