#include <Arduino.h>
#include "State.h"


State::State(ExpressionEnum initial) {
  this->_current = initial;
  this->_previous = NONE;
}

void State::setState(ExpressionEnum expression, ReasonEnum reason) {
  this->_previous = _current;
  this->_current = expression;
  this->reason = reason;
} 

bool State::is(ExpressionEnum state) {
  return ((this->_current & state) == state);
}

bool State::was(ExpressionEnum state) {
  return ((this->_previous & state) == state);
}

ExpressionEnum State::getCurrentState() {
  return this->_current;
}

ExpressionEnum State::getPreviousState() {
  return this->_previous;
}

ReasonEnum State::getReason() {
  return this->reason;
}

String State::getName(ExpressionEnum expression) {
  if (expression == NONE)
    return "None";

  String exp;
  
  if ((IDLE & expression) == IDLE) {
    exp = "Idle";
  }
  if ((HAPPY & expression) == HAPPY) {
    exp = exp + (exp.length() > 0 ? " & " : "") + "Happy";
  }
  if ((SAD & expression) == SAD) {
    exp = exp + (exp.length() > 0 ? " & " : "") + "Sad";
  }
  if ((CURIOUS & expression) == CURIOUS) {
    exp = exp + (exp.length() > 0 ? " & " : "") + "Curious";
  }
  if ((SLEEPING & expression) == SLEEPING) {
    exp = exp + (exp.length() > 0 ? " & " : "") + "Sleeping";
  }
  if ((SUN & expression) == SUN) {
    exp = exp + (exp.length() > 0 ? " & " : "") + "Sun";
  }
  if ((WATER & expression) == WATER) {
    exp = exp + (exp.length() > 0 ? " & " : "") + "Water";
  }
  
  return exp;
}

