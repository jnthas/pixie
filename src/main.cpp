#include <Arduino.h>


bool buttonPressed;


enum ExpressionEnum {
  NONE = 0,
  IDLE = 1,
  HAPPY = 2,
  SAD = 4,  
  CURIOUS = 8,
  SLEEPING = 16,
  SUN = 32,
  WATER = 64
};

inline ExpressionEnum operator|(ExpressionEnum a, ExpressionEnum b)
{
    return static_cast<ExpressionEnum>(static_cast<int>(a) | static_cast<int>(b));
}


enum ReasonEnum {
  NO_REASON,
  HIGH_TEMPERATURE,
  TEMPERATURE_DECRESED,
  DRY_SOIL,
  SOIL_WATERED,
  HAPPY_TIMEDOUT,
  CURIOUS_TIMEDOUT,
  LIGHTS_ON,
  LIGHTS_OFF,
  MOTION_DETECTED,
  IN_THE_SUN
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
      return ((this->_current & state) == state);
    }
    bool was(ExpressionEnum state) {
      return ((this->_previous & state) == state);
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
        exp = exp + (exp.length() > 0 ? " & " : "") + + "Sad";
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
};


class SensorHistory {
  static const int HISTORY_MAX_SIZE = 10;
  
  private:
    int buffer[HISTORY_MAX_SIZE] = {0};

  public:
    void addElement(int element) {
      //Serial.print("Adding -> "); Serial.println(element);
  
      for (byte i=HISTORY_MAX_SIZE - 1; i > 0; i--) {
        buffer[i] = buffer[i-1];
      }
      buffer[0] = element;
    }

    int getLast() {
        return buffer[0];
    }

    int* getFullHistory() {
      return this->buffer;
    }

    int getVariation() {      
      int diff = 0;

      for (int i=0; i < HISTORY_MAX_SIZE - 1; i++) {
        diff += buffer[i+1] - buffer[i];
      }

      return diff;
    }

};

class Sensors {
  private:
    int _MAX_TEMPERATURE;
  public:
    int pir = 0;
    int ldr = 0;
    int dht = 0;
    int soil = 5;
    int soil_var = 0;

    Sensors(int maxTemperature) {
      this->_MAX_TEMPERATURE = maxTemperature;
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
        int oldValue = this->soil;
        this->soil++;
        int newValue = this->soil;

        this->soil_var += newValue - oldValue;
        buttonPressed = true;
      } else if (digitalRead(5) == LOW && digitalRead(6) == LOW) {        
        // variation only for increasing values        
        
        this->soil--;

        buttonPressed = true;
      }

    }
    void resetSoilVariation() {
      this->soil_var = 0;
    }
    bool isMaxTemperature() {
      return dht >= _MAX_TEMPERATURE;
    }
    bool hasMotionDetected() {
      return pir > 0;
    }
    bool isDark() {
      return ldr < 5;
    }
    bool isBright() {
      return ldr > 7;
    }
    bool isHot() {
      return dht > 5;
    }
    bool isDry() {
      return soil < 5;
    }
    bool isWatering() {
      return soil_var >= 3;
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

      
      if (sensors.hasMotionDetected()) {
        state.setState(CURIOUS, MOTION_DETECTED);

      } else if (sensors.isDark()) {
        state.setState(SLEEPING, LIGHTS_OFF);

      } else if (sensors.isHot() && 
          sensors.isBright() && 
          !sensors.isMaxTemperature() && 
          !state.was(HAPPY | SUN))  {
        state.setState(HAPPY | SUN, IN_THE_SUN);

      } else if (sensors.isBright() && sensors.isMaxTemperature())  {
        state.setState(SAD | SUN, HIGH_TEMPERATURE);

      } else if (sensors.isDry()) {
        state.setState(SAD | WATER, DRY_SOIL);

      } else if (sensors.isWatering()) {
        state.setState(HAPPY | WATER, SOIL_WATERED);
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
        

      if (sensors.hasMotionDetected()) {
        state.setState(CURIOUS, MOTION_DETECTED);

      } else if (sensors.isWatering() && !sensors.isDry()) {
        state.setState(HAPPY, SOIL_WATERED);

      } if (!sensors.isMaxTemperature() && state.getReason() == HIGH_TEMPERATURE)  {
        state.setState(state.getPreviousState(), TEMPERATURE_DECRESED);
      }
      
      return state.was(SAD);
    }
};

class CuriousExpression: public Expression {
  private:
    unsigned long timeout = 0;
    unsigned int limit = 3000;
  public:
    bool evaluate(Sensors& sensors, State& state) override {
      //Serial.println("Evaluate CURIOUS");
      if (!state.is(CURIOUS))
        return false;
      
      if (timeout == 0) {
        timeout = millis();
      } else if ((millis() - timeout) > limit) {
        timeout = 0;
        state.setState(state.getPreviousState(), CURIOUS_TIMEDOUT);        
      }
      
      return state.was(CURIOUS);
    }
};

class SleepingExpression: public Expression {
  private:
    unsigned long timeout = 0;

  public:
    bool evaluate(Sensors& sensors, State& state) override {
      //Serial.println("Evaluate SLEEPING");
      if (!state.is(SLEEPING)) 
        return false;
 
      if (sensors.isMaxTemperature())  {
        state.setState(SAD | SUN, HIGH_TEMPERATURE);
      
      } else if (sensors.isDry()) {
        state.setState(SAD | WATER, DRY_SOIL);
      
      } else if (sensors.isWatering()) {
        state.setState(HAPPY | WATER, SOIL_WATERED);

      } else if (sensors.isBright()) {
        if (timeout == 0) {
          timeout = millis();
        } else if ((millis() - timeout) > 10000) {
          timeout = 0;
          state.setState(IDLE, LIGHTS_ON);
        }
      }


      return state.was(SLEEPING);
    }
};

class HappyExpression: public Expression {
  private:
    unsigned long timeout = 0;
    unsigned int limit = 3000;
  public:
    bool evaluate(Sensors& sensors, State& state) override {
      //Serial.println("Evaluate HAPPY");

      if (!state.is(HAPPY))
        return false;

      if (state.getReason() == IN_THE_SUN) {
        limit = 10000;
      }

      if (timeout == 0) {
        timeout = millis();
      } else if ((millis() - timeout) > limit) {
        timeout = 0;
        if (state.getReason() == SOIL_WATERED) {
          sensors.resetSoilVariation();
        }
        state.setState(IDLE, HAPPY_TIMEDOUT);
      }
      
      return state.was(HAPPY);
    }
};


State state(IDLE);
Sensors sensors(10);

IdleExpression idleState;
SleepingExpression sleepingState;
SadExpression sadState;
HappyExpression happyState;
CuriousExpression curiousState;




//  IDLE, HAPPY, SAD, CURIOUS, SLEEPING 

Expression *expressions[] = { &idleState, &happyState, &sadState, &curiousState, &sleepingState };

const byte NUM_EXPRESSIONS = sizeof(expressions) / sizeof(expressions[0]);

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
  Serial.print("PIR: "); Serial.print(sensors.pir);
  Serial.print(" LDR: "); Serial.print(sensors.ldr);
  Serial.print(" DHT: "); Serial.print(sensors.dht);
  Serial.print(" SOIL: "); Serial.print(sensors.soil);
  Serial.print(" SOIL_VAR: "); Serial.println(sensors.soil_var);

  Serial.println(state.getName(state.getCurrentState()));

  for (int i=0; i<NUM_EXPRESSIONS; i++) {
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

