#ifndef SOLDER_H
#define SOLDER_H

#include <inttypes.h>
#include "DualLed.h"
#include "LoopTimer.h"

/////////////////////////////////////////////////////////
/// solder
/// main class for Soldering Station pAIkovacka
/////////////////////////////////////////////////////////

class Solder {
  public:
    Solder(const uint8_t heatPin, const uint32_t time) : mHeatPin(heatPin), mTime(time)
    {
        pinMode(mHeatPin, OUTPUT);           //inicialization pin discrete heating for behavior like output
        mHeaterTimer = new LoopTimer(mTime);
        mCyclus = 0;
        mHeatStatus = false;
        
    }; 
    void lowFreqPwm(const unsigned int level, DualLed& dualLed);

  
  private:
    Solder(const Solder& notPaste);
    void heatIron(const bool onOff);
    LoopTimer* mHeaterTimer;
    uint8_t mCyclus;
    uint8_t mHeatPin;
    uint32_t mTime;
    bool mHeatStatus;               //state of heating iron

};

#endif
