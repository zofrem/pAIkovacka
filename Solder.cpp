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

void Solder::lowFreqPwm(const unsigned int level, DualLed& dualLed)
{
  ++mCyclus;
  if(level < mCyclus)
  {
    dualLed->showBright(LED_RED);
    heatIron(true);
  }
  else
  {
    dualLed->showBright(LED_GREEN);
    heatIron(false);  
  }
}

