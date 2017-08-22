#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <inttypes.h>

/////////////////////////////////////////////////////////
/// StopWatch
/// primitive StopWatch
/////////////////////////////////////////////////////////

class StopWatch {
  public:
    StopWatch();
    void startWatch();
    uint32_t stopWatch();
    bool getActualWatch(uint32_t& time);
  
  private:
    StopWatch(const StopWatch& stopWatch);
    void watchDifference(uint32_t& time);
    uint32_t mStartTime;
    uint32_t mFinishTime;
    bool mFirstRun;
    bool mWatchRunning;
};

#endif
