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

bool Solder::lowFreqPwm(const unsigned int level)
{        
  if(mPwmTimer->timer())
  {
    ++mCyclus;
    if(mCyclus < getLevelFromPercentage(level))
    {
      heatIron(true);
      return false;
    }
    else if(0xFF == mCyclus) // last moment before heating numeric_limits<uint8_t>::max() not for 8bit
    {
      heatIron(false);
      return true; //now measure temperature
    }
    else
    {
      heatIron(false);
      return false;
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
  return (level * 2.55);
}

