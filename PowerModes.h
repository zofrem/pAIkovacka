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
  bool heatTime(uint32_t& time);

private:
  PowerModes(const PowerModes& powerModes);
  StopWatch* mHeaterStopWatch;
  LoopRecorder<uint8_t>* heatTimes;
  static const uint8_t TIME_SAMPLES = 16;

};

#endif
