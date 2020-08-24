#ifndef Expression_h
#define Expression_h

#include "Sensors.h"
#include "State.h"

inline ExpressionEnum operator|(ExpressionEnum a, ExpressionEnum b) {
    return static_cast<ExpressionEnum>(static_cast<int>(a) | static_cast<int>(b));
}

class Expression {
  public:
   /**
    * Evaluate the current state based on sensors and current state
    * Returns true if state has changed
    **/ 
    virtual bool evaluate(Sensors& sensors, State& state) = 0;
};

#endif