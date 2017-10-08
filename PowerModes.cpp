#include <Arduino.h>
#include "PowerModes.h"
#include "StopWatch.h"
#include "LoopTimer.h"

PowerModes::PowerModes()
{
  mHeaterStopWatch = new StopWatch();
  mCoolingDiffTimes = new LoopRecorder<int8_t>(TIME_SAMPLES);
  mFirstRun = true;
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
        storeCoolingTimeDifference(time);
    }
}

bool PowerModes::coolingTime(int8_t& time)
{
  //return mHeaterStopWatch->getActualWatch(time);
  return mCoolingDiffTimes->getLastSample(0, time);
}

void PowerModes::storeCoolingTimeDifference(uint32_t& time)
{
  if(!mFirstRun)
  {
    int32_t diffTime = time - mLastCoolingTime;
    diffTime = diffTime / 1000; //ms to sec
    if(diffTime > 127)
      diffTime = 127;
    else if(diffTime < -127)
      diffTime = -127;
    mCoolingDiffTimes->pushBack(static_cast<int8_t>(diffTime));
  }
  else
    mFirstRun = false;
  mLastCoolingTime = time;
}
