#include <Arduino.h>
#include <string.h>
#include <LedControl.h>
#include "GlobalDefinition.h"
#include "Sensors.h"
#include "State.h"
#include "Sprites.h"
#include "UIManager.h"

UIManager::UIManager(LedControl* lcInstance)
{
  lc = lcInstance;
}

void UIManager::drawImage(uint64_t image)
{ 
  // unsigned long long1 = (unsigned long)((image & 0xFFFF0000) >> 16 );
  // unsigned long long2 = (unsigned long)((image & 0x0000FFFF));
  // String hex = String(long1, HEX) + String(long2, HEX); // six octets
  // Serial.println(hex);


  for (int i = 0; i < 8; i++)
  {
    byte row = (image >> i * 8) & 0xFF;
    for (int j = 0; j < 8; j++)
    {
      lc->setLed(0, i, j, bitRead(row, j));
    }
  }
}

int UIManager::countExpressions(ExpressionEnum expression)
{
  int count = 0;

  int expAsInt = expression;

  while (expAsInt != 0)
  {
    expAsInt = expAsInt & (expAsInt - 1);
    count++;
  }

  return count;
}

void UIManager::update(ExpressionEnum expression)
{
  // Serial.print("Updating display to: ");
  // Serial.println(expression);

  byte numImages = 0;
  indexCurrentExpression = 0;
  repeatCount = 0;
  indexCurrentFrame = 0;

  for (byte i = 0; i < SPRITE_METADATA_ARR_SIZE; i++)
  {
    if ((sprites[i].expression & expression) == sprites[i].expression)
    {
      if (numImages >= EXPRESSIONS_ARR_SIZE)
        break;
      expressions[numImages] = i;
      numImages++;
    }
  }

  totalNumExpressions = numImages;

  //Serial.println(totalNumExpressions);
  updated = true;
}

void UIManager::render()
{

  if (updated)
  {
    updated = false;
    lc->setIntensity(0, sprites[expressions[indexCurrentExpression]].intensity);
    drawImage(sprites[expressions[indexCurrentExpression]].images[indexCurrentFrame]);
    passedMillis = millis();
  }
  else if ((millis() - passedMillis) >= sprites[expressions[indexCurrentExpression]].interval[indexCurrentFrame])
  {
    indexCurrentFrame++;

    if (indexCurrentFrame >= sprites[expressions[indexCurrentExpression]].length)
    {
      indexCurrentFrame = 0;
      repeatCount++;

      if (repeatCount >= sprites[expressions[indexCurrentExpression]].repeats)
      {
        repeatCount = 0;
        indexCurrentExpression++;

        if (indexCurrentExpression >= totalNumExpressions)
        {
          indexCurrentExpression = 0;
        }

        lc->setIntensity(0, sprites[expressions[indexCurrentExpression]].intensity);
      }
    }

    //Serial.println(sprites[expressions[indexCurrentExpression]].name);

    drawImage(sprites[expressions[indexCurrentExpression]].images[indexCurrentFrame]);
    passedMillis = millis();
  }
}
