#include <Arduino.h>
#include "PowerModes.h"
#include "StopWatch.h"
#include "LoopTimer.h"

PowerModes::PowerModes()
{
  mHeaterStopWatch = new StopWatch();
  mCoolingTimes = new LoopRecorder<uint8_t>(TIME_SAMPLES);
}

PowerModes::~PowerModes()
{
  if(mHeaterStopWatch)
    delete(mHeaterStopWatch);
}

void PowerModes::bookHeating(bool onOffHeat)
{
  //booking only cooling intervals between heating, usage of produced heat
  if(!onOffHeat) //book only when onOffHeat difference, but handled at above call
    mHeaterStopWatch->startWatch();
  else
    {
      uint32_t time;
      if(mHeaterStopWatch->stopWatch(time))
      {
        time = time / 1000; //ms to sec
        if(time > 255)
          time = 255;
        mCoolingTimes->pushBack(static_cast<uint8_t>(time));
      }
    }
}

bool PowerModes::coolingTime(uint8_t& time)
{
  //return mHeaterStopWatch->getActualWatch(time);
  return mCoolingTimes->getLastSample(0, time);
}
