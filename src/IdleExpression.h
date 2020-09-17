
#ifndef IdleExpression_h
#define IdleExpression_h

#include <Arduino.h>
#include "Expression.h"
#include "State.h"


class IdleExpression: public Expression {
  private:
    unsigned long timeout = 0;
  public:
    bool evaluate(Sensors& sensors, State& state) override;
};

#endif