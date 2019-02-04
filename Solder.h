#ifndef SOLDER_H
#define SOLDER_H

#include <inttypes.h>
#include "LoopTimer.h"

/////////////////////////////////////////////////////////
/// solder
/// main class for Soldering Station pAIkovacka
/////////////////////////////////////////////////////////

class Solder {
  public:
    Solder(const uint8_t heatPin, const uint32_t time = 20) : mHeatPin(heatPin), mTime(time), mMaxPower(50) 
    {
        pinMode(mHeatPin, OUTPUT);           //inicialization pin discrete heating for behavior like output
        mPwmTimer = new LoopTimer(mTime);
        mCyclus = 0;
        mHeatStatus = false;
        
    }; 
    bool lowFreqPwm(const unsigned int level);
    bool isHeating() const;

  
  private:
    Solder(const Solder& notPaste);
    void heatIron(const bool onOff);
    uint8_t getLevelFromPercentage(const uint8_t percentage) const;
    LoopTimer* mPwmTimer;
    uint8_t mCyclus;
    const uint8_t mHeatPin;
    const uint8_t mMaxPower;
    uint32_t mTime;
    bool mHeatStatus;               //state of heating iron

};

#endif
