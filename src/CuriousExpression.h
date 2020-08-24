
#ifndef CuriousExpression_h
#define CuriousExpression_h

#include <Arduino.h>
#include "Expression.h"
#include "State.h"

class CuriousExpression: public Expression {
  private:
    unsigned long timeout = 0;
    unsigned int limit = 0;
  public:
    bool evaluate(Sensors& sensors, State& state) override;
};

#endif