
#ifndef SadExpression_h
#define SadExpression_h

#include <Arduino.h>
#include "Expression.h"
#include "State.h"

class SadExpression: public Expression {
  public:
    bool evaluate(Sensors& sensors, State& state) override;
};

#endif