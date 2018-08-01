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
    if(mCyclus < level)
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

