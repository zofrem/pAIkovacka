#include <Arduino.h>
#include "PowerModes.h"
#include "StopWatch.h"

PowerModes::PowerModes()
{
  mHeaterStopWatch = new StopWatch();
}

PowerModes::~PowerModes()
{
  if(mHeaterStopWatch)
    delete(mHeaterStopWatch);
}

void PowerModes::bookHeating(bool onOffHeat)
{
  uint32_t time;
  if(onOffHeat)
    mHeaterStopWatch->startWatch();
  else
    mHeaterStopWatch->stopWatch(time);
}

bool PowerModes::heatTime(uint32_t& time)
{
  return mHeaterStopWatch->getActualWatch(time);
}
