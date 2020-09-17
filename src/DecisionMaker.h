
#ifndef DecisionMaker_h
#define DecisionMaker_h

#include <Arduino.h>
#include "Expression.h"

class DecisionMaker {
  private:
    static void seed();

  public:
    static bool doYouLikeIt(byte humor);
    static short waitSomeTime(short maxSeconds);
};

#endif