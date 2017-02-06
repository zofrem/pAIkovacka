#include <Arduino.h>
#include "DualLed.h"
//#include <SchedulerARMAVR.h>


DualLed::DualLed(const uint8_t red, const uint8_t green)
{
    pinMode(red, OUTPUT);
    pinMode(green, OUTPUT);
    mPinRed = red;
    mPinGreen = green;
    mCurrentBrightStatus = LED_OFF;
    mBlinkLastStatus = false;
    mBlinkLastTime = millis();
}

void DualLed::showBright(const LedStatuses ledBrightType)
{
  mCurrentBrightStatus = ledBrightType;
  switch(mCurrentBrightStatus)
  {
    case LED_OFF:
      digitalWrite(mPinRed, false);
      digitalWrite(mPinGreen, false);
      break;
    case LED_RED:
      digitalWrite(mPinRed, true);
      digitalWrite(mPinGreen, false);
      break;
    case LED_GREEN:
      digitalWrite(mPinRed, false);
      digitalWrite(mPinGreen, true);
      break;
    case LED_GREEN_BLINK:
      digitalWrite(mPinRed, false);
      doBlink(mPinGreen, 250);
      break;
    case LED_RED_BLINK:
      digitalWrite(mPinGreen, false);
      doBlink(mPinRed, 250);
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

