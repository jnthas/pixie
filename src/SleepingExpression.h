
#ifndef SleepingExpression_h
#define SleepingExpression_h

#include <Arduino.h>
#include "Expression.h"
#include "State.h"

class SleepingExpression: public Expression {
  private:
    unsigned long timeout = 0;

  public:
    bool evaluate(Sensors& sensors, State& state) override;
};

#endif