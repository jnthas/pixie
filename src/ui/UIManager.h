#ifndef UIManager_h
#define UIManager_h

#include <Arduino.h>
#include <LedControl.h>
#include "Sensors.h"
#include "State.h"

class UIManager
{
  private:
    LedControl* lc;
    byte indexCurrentFrame = 0;
    long passedMillis = 0;
    bool updated = false;
    byte indexCurrentExpression = 0;
    byte repeatCount = 0;
    byte totalNumExpressions = 0;
    byte expressions[4] = {0}; // Hold the index for the expressions that is being showed currently
    const byte EXPRESSIONS_ARR_SIZE = 4;
    void drawImage(uint64_t image);
    int countExpressions(ExpressionEnum expression);

  public:
    UIManager(LedControl* lc);
    void update(ExpressionEnum expression);
    void render();
};

#endif