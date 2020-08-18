#include <Arduino.h>

enum Expression {
  NONE = 0,
  IDLE = 1,
  HAPPY = 2,
  SAD = 3,  
  CURIOUS = 4,
  SLEEPING = 5
} expression;


struct History {
  Expression current;
  Expression previous;
} history;


class Sensors {
  public:
    int pir;
    int ldr;
    int dht;
    int soil;

    void read() {
      this->pir = 10;
      this->ldr = 10;
      this->dht = 10;
      this->soil = 10;      
    }
};


class State {
  public:
    virtual void determineState(Sensors& sensors, History& history) = 0;
    virtual bool canHandle(Expression expression) = 0;
};

class SadState: public State {
   public:
    void determineState(Sensors& sensors, History& history) {
      Serial.println("determine state - sad");
    }
    bool canHandle(Expression expression) {
      return expression == SAD;
    }
};

class SleepingState: public State {
  public:
    void determineState(Sensors& sensors, History& history) {
      if (sensors.dht >= 11 && history.current == SLEEPING) {
        history.current = SAD;
      } else {
        history.current = IDLE;
      }
    }
    bool canHandle(Expression expression) {
      return expression == SLEEPING;
    }
};


Sensors sensors;

SleepingState sleepingState;
SadState sadState;

State *states[] = {&sleepingState, &sadState};

//State* currentState;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  sensors.read();

  expression = SLEEPING;
  
  history.previous = NONE;
  history.current = SLEEPING;

  //current.setCurrent(sleepingState);
}


void showValue(Expression exp) {

  switch(exp) {
    case NONE:
      Serial.println("None");
      break;
    case IDLE:
      Serial.println("Idle");
      break;      
    case HAPPY:
      Serial.println("Happy");
      break;
    case SAD:  
      Serial.println("Sad");
      break;
    case CURIOUS:
      Serial.println("Curious");
      break;
     case SLEEPING:
      Serial.println("Sleeping");
      break;   
  }
}


void loop() {
  delay(5000);

  sensors.read();
  //Serial.println(sensors.pir);

  Serial.println("Current State: ");
  showValue(history.current);

  for (int i=0; i<2; i++) {
    if (states[i]->canHandle(history.current)) {
      states[i]->determineState(sensors, history);
    }
  }

  //sleepingState.determineState(sensors, history);
}
