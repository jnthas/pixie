
#ifndef HappyExpression_h
#define HappyExpression_h

#include <Arduino.h>
#include "Expression.h"
#include "State.h"


class HappyExpression: public Expression {
  private:
    unsigned long timeout = 0;
    unsigned int limit = 0;
  public:
    bool evaluate(Sensors& sensors, State& state) override;
};

#endif