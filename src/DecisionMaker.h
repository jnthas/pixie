
#ifndef DecisionMaker_h
#define DecisionMaker_h

#include <Arduino.h>
#include "Expression.h"

class DecisionMaker {
  public:
    static void initialize();
    static bool doYouLikeIt(byte humor);
    static short waitSomeTime(short maxSeconds);
};

#endif