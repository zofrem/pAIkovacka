#include <Arduino.h>
#include "Solder.h"

void Solder::heatIron(const bool onOff)
{
  if(mHeatStatus != onOff) //do only difference
  {
    mHeatStatus = onOff;
    digitalWrite(mHeatPin, onOff);
    //powerModes->bookHeating(onOff);
  }
}

void Solder::lowFreqPwm(const unsigned int level)
{        
  if(mPwmTimer->timer())
  {
    ++mCyclus;
    if(mCyclus < getLevelFromPercentage(level))
    {
      heatIron(true);
    }
    else
    {
      heatIron(false);
    }
  }
}

bool Solder::isHeating() const
{
  return mHeatStatus;
}

uint8_t Solder::getLevelFromPercentage(const uint8_t percentage) const
{
  uint8_t level = 0;
  if(100 < percentage)
    level = 100;
  else
    level = percentage;
  return (level * 2) + mLowPowerLevel;
}

