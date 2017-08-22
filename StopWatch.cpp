#include <Arduino.h>
#include "StopWatch.h"

StopWatch::StopWatch()
{
  mFirstRun = true;
  mWatchRunning = false;
}

void StopWatch::startWatch()
{
  mWatchRunning = true;
  mStartTime = millis();
}

uint32_t StopWatch::stopWatch()
{
  if(!mWatchRunning)
    return 0;
  mFirstRun = false;
  mWatchRunning = false;
  watchDifference(mFinishTime);
  return mFinishTime;
}

bool StopWatch::getActualWatch(uint32_t& time)
{
  if(mWatchRunning)
  {
    watchDifference(time);
    return true;    
  }
  else
  {
    if(mFirstRun)
    {
      time = 0;
      return false;
    }
    else
    {
      time = mFinishTime;
      return false;
    }
  }
}

void StopWatch::watchDifference(uint32_t& time)
{
  time = millis() - mStartTime;  
}
