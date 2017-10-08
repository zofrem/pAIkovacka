#ifndef POWERMODES_H
#define POWERMODES_H

#include <inttypes.h>
#include "StopWatch.h"
#include "LoopRecorder.h"

/////////////////////////////////////////////////////////
/// PowerModes
/// Power modes of soldering iron heating system
/////////////////////////////////////////////////////////

class PowerModes {
public:
  PowerModes();
  ~PowerModes();
  void bookHeating(bool onOffHeat);
  bool coolingTime(int8_t& time);

private:
  PowerModes(const PowerModes& powerModes);
  void storeCoolingTimeDifference(uint32_t& time);
  StopWatch* mHeaterStopWatch;
  LoopRecorder<int8_t>* mCoolingDiffTimes;
  static const uint8_t TIME_SAMPLES = 16;
  bool mFirstRun;
  uint32_t mLastCoolingTime;

};

#endif

