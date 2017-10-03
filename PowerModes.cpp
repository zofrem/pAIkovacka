#include <Arduino.h>
#include "PowerModes.h"
#include "StopWatch.h"
#include "LoopTimer.h"

PowerModes::PowerModes()
{
  mHeaterStopWatch = new StopWatch();
  heatTimes = new LoopRecorder<uint8_t>(TIME_SAMPLES);
}

PowerModes::~PowerModes()
{
  if(mHeaterStopWatch)
    delete(mHeaterStopWatch);
}

void PowerModes::bookHeating(bool onOffHeat)
{
  if(onOffHeat) //book only when onOffHeat difference, but handled at above call
    mHeaterStopWatch->startWatch();
  else
    {
      uint32_t time;
      mHeaterStopWatch->stopWatch(time);
      time = time / 1000; //ms to sec
      if(time > 255)
        time = 255;
      heatTimes->pushBack(static_cast<uint8_t>(time));
    }
}

bool PowerModes::heatTime(uint8_t& time)
{
  //return mHeaterStopWatch->getActualWatch(time);
  return heatTimes->getLastSample(0, time);
}
