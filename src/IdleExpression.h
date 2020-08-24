
#ifndef IdleExpression_h
#define IdleExpression_h

#include <Arduino.h>
#include "Expression.h"
#include "State.h"


class IdleExpression: public Expression {
  public:
    bool evaluate(Sensors& sensors, State& state) override;
};

#endif