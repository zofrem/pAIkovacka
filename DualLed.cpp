#include <Arduino.h>
#include "DualLed.h"


DualLed::DualLed(const uint8_t red, const uint8_t green)
{
    pinMode(red, OUTPUT);
    pinMode(green, OUTPUT);
    mPinRed = red;
    mPinGreen = green;
    mBlinkLastStatus = false;
    mBlinkLastTime = millis();
    mActiveBrightType = LED_OFF;
}

void DualLed::showBright(const LedStatuses ledBrightType)
{
  switch(ledBrightType)
  {
    case LED_OFF:
      if(ledBrightType != mActiveBrightType)
      {
        digitalWrite(mPinRed, false);
        digitalWrite(mPinGreen, false);
      }
      break;
    case LED_RED:
      if(ledBrightType != mActiveBrightType)
      {
        digitalWrite(mPinRed, true);
        digitalWrite(mPinGreen, false);
      }
      break;
    case LED_GREEN:
      if(ledBrightType != mActiveBrightType)
      {
        digitalWrite(mPinRed, false);
        digitalWrite(mPinGreen, true);
      }
      break;
    case LED_GREEN_BLINK:
      digitalWrite(mPinRed, false);
      doBlink(mPinGreen, 100);
      break;
    case LED_RED_BLINK:
      digitalWrite(mPinGreen, false);
      doBlink(mPinRed, 100);
      break;
  }
}

void DualLed::doBlink(const uint8_t currentPin, const unsigned int halfOfPeriode)
{
  if(millis() > (mBlinkLastTime + halfOfPeriode))
  {
    mBlinkLastTime = millis();
    mBlinkLastStatus = !mBlinkLastStatus;
  } 
  digitalWrite(currentPin, mBlinkLastStatus);
}

