#include <Arduino.h>
#include "StopWatch.h"

StopWatch::StopWatch()
{
  mFirstRun = true;
  mWatchRunning = false;
}

bool StopWatch::startWatch()
{
  if(mWatchRunning)
    return false;
  mWatchRunning = true;
  mStartTime = millis();
  return true;
}

bool StopWatch::stopWatch(uint32_t& time)
{
  if(!mWatchRunning)
  {
    time = 0;
    return false;
  }
  mFirstRun = false;
  mWatchRunning = false;
  getLapTime(mFinishTime);
  time = mFinishTime;
  return true;
}

bool StopWatch::getActualWatch(uint32_t& time)
{
  if(mWatchRunning)
  {
    getLapTime(time);
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

void StopWatch::getLapTime(uint32_t& time)
{
  time = millis() - mStartTime;  
}
