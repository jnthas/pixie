#ifndef LoadingExpression_h
#define LoadingExpression_h

#include <Arduino.h>
#include "Expression.h"
#include "State.h"

class LoadingExpression: public Expression {
  private:
    unsigned long timeout = 0;
  public:
    bool evaluate(Sensors& sensors, State& state) override;
};

#endif