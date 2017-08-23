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
    bool startWatch();
    bool stopWatch(uint32_t& time);
    bool getActualWatch(uint32_t& time);
  
  private:
    StopWatch(const StopWatch& stopWatch);
    void getLapTime(uint32_t& time);
    uint32_t mStartTime;
    uint32_t mFinishTime;
    bool mFirstRun;
    bool mWatchRunning;
};

#endif
