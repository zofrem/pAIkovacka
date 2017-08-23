#ifndef POWERMODES_H
#define POWERMODES_H

#include <inttypes.h>
#include "StopWatch.h"

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

};

#endif
