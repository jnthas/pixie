#include <Arduino.h>

bool buttonPressed;

enum ExpressionEnum {
  NONE = 0,
  IDLE = 1,
  HAPPY = 2,
  SAD = 3,  
  CURIOUS = 4,
  SLEEPING = 5
};

enum ReasonEnum {
  NO_REASON,
  HIGH_TEMPERATURE,
  DRY_SOIL,
  SOIL_WATERED,
  HAPPY_TIMEDOUT,
  LIGHTS_ON,
  LIGHTS_OFF
};


class State {
  private: 
    ExpressionEnum _current;
    ExpressionEnum _previous;
    ReasonEnum reason;

  public:  
    State(ExpressionEnum expression) {
      this->_current = expression;
      this->_previous = NONE;
    }
    void setState(ExpressionEnum expression, ReasonEnum reason) {
      this->_previous = _current;
      this->_current = expression;
      this->reason = reason;
    } 
    bool is(ExpressionEnum state) {
      return this->_current == state;
    }
    bool was(ExpressionEnum state) {
      return this->_previous == state;
    }
    ExpressionEnum getCurrentState() {
      return this->_current;
    }
    ExpressionEnum getPreviousState() {
      return this->_previous;
    }
    ReasonEnum getReason() {
      return this->reason;
    }
    String getName(ExpressionEnum expression) {
      switch(expression) {
        case IDLE:
          return "Idle";
        case HAPPY:
          return "Happy";
        case SAD:  
          return "Sad";
        case CURIOUS:
          return "Curious";
        case SLEEPING:
          return "Sleeping";
        default:
          return "None";
      }
    }
};

class Sensors {
  public:
    int pir;
    int ldr;
    int dht;
    int soil;
    Sensors() {
      this->pir = 0;
      this->ldr = 6;
      this->dht = 0;
      this->soil = 0;
    }
    void read() {
      if (digitalRead(2) == LOW && digitalRead(6) != LOW) {
        this->pir++;
        buttonPressed = true;
      } else if (digitalRead(2) == LOW && digitalRead(6) == LOW) {
        this->pir--;
        buttonPressed = true;
      }

      if (digitalRead(3) == LOW && digitalRead(6) != LOW) {
        this->ldr++;
        buttonPressed = true;
      } else if (digitalRead(3) == LOW && digitalRead(6) == LOW) {
        this->ldr--;
        buttonPressed = true;
      }

      if (digitalRead(4) == LOW && digitalRead(6) != LOW) {
        this->dht++;
        buttonPressed = true;
      } else if (digitalRead(4) == LOW && digitalRead(6) == LOW) {
        this->dht--;
        buttonPressed = true;
      }

      if (digitalRead(5) == LOW && digitalRead(6) != LOW) {
        this->soil++;
        buttonPressed = true;
      } else if (digitalRead(5) == LOW && digitalRead(6) == LOW) {
        this->soil--;
        buttonPressed = true;
      }



    }
    bool isPresent() {
      return pir > 0;
    }
    bool isDark() {
      return ldr < 5;
    }
    bool isHot() {
      return dht > 5;
    }
    bool isDry() {
      return soil < 5;
    }

};


class Expression {
  public:
   /**
    * Evaluate the current state based on sensors and current state
    * Returns true if state has changed
    **/ 
    virtual bool evaluate(Sensors& sensors, State& state) = 0;
};

class IdleExpression: public Expression {
   public:
    bool evaluate(Sensors& sensors, State& state) override {
      //Serial.println("Evaluate IDLE");
      if (!state.is(IDLE)) 
        return false;

      if (sensors.isDry()) {
        state.setState(SAD, DRY_SOIL);
      } else if (sensors.isDark()) {
        state.setState(SLEEPING, LIGHTS_OFF);
      }


      return state.was(IDLE);
    }
};

class SadExpression: public Expression {
   public:
    bool evaluate(Sensors& sensors, State& state) override {
      //Serial.println("Evaluate SAD");

      if (!state.is(SAD))
        return false;

      if (!sensors.isDry()) {
        state.setState(HAPPY, SOIL_WATERED);
      }
      
      return state.was(SAD);
    }
};

class SleepingExpression: public Expression {
  public:
    bool evaluate(Sensors& sensors, State& state) override {
      //Serial.println("Evaluate SLEEPING");
      if (!state.is(SLEEPING)) 
        return false;
 
      if (!sensors.isDark()) {
        state.setState(IDLE, LIGHTS_ON);  
      }

      return state.was(SLEEPING);
    }
};

class HappyExpression: public Expression {
  private:
    unsigned long timeout = 0;
  public:
    bool evaluate(Sensors& sensors, State& state) override {
      //Serial.println("Evaluate HAPPY");

      if (!state.is(HAPPY))
        return false;

      if (timeout == 0) {
        timeout = millis();
      } else if ((millis() - timeout) > 3000) {
        state.setState(IDLE, HAPPY_TIMEDOUT);
        timeout = 0;
      }
      
      return state.was(HAPPY);
    }
};


State state(IDLE);
Sensors sensors;

IdleExpression idleState;
SleepingExpression sleepingState;
SadExpression sadState;
HappyExpression happyState;

Expression *expressions[] = {&idleState, &sleepingState, &sadState, &happyState};

unsigned long millisStart;




void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);

  millisStart = millis();


  // Serial.println("GETSAD: ");
  // Serial.println(getSad()->canHandle(SAD));
  // Serial.println(getSad()->canHandle(HAPPY));
}

void checkState() {
  Serial.print("PIR: ");
  Serial.print(sensors.pir);
  Serial.print(" LDR: ");
  Serial.print(sensors.ldr);
  Serial.print(" DHT: ");
  Serial.print(sensors.dht);
  Serial.print(" SOIL: ");
  Serial.println(sensors.soil);

  Serial.println(state.getName(state.getCurrentState()));

  for (int i=0; i<4; i++) {
    if (expressions[i]->evaluate(sensors, state)) {
      Serial.println("State has changed from " + state.getName(state.getPreviousState()) + " to " + state.getName(state.getCurrentState()));
      break;
    }
  }
}

void loop() {
  //
  
  if (!buttonPressed) {
    sensors.read();
  }
  if ((millis() - millisStart) > 1000) {
    checkState();
    millisStart = millis();
    buttonPressed = false;
  }
}

