#ifndef SOLDER_H
#define SOLDER_H


#include <inttypes.h>
#include "max6675.h"
#include "LoopTimer.h"

/////////////////////////////////////////////////////////
/// solder
/// main class for Soldering Station pAIkovacka
/////////////////////////////////////////////////////////

class Solder {
  public:
    Solder(const uint8_t heatPin, const uint8_t selectPin, MAX6675& max6675, const uint32_t time = 20) : mHeatPin(heatPin), mSelectPin(selectPin), mThermocouple(max6675), mTime(time), mMaxPower(50), mPower(20) 
    {
        pinMode(mHeatPin, OUTPUT);           //inicialization pin discrete heating for behavior like output
        mPwmTimer = new LoopTimer(mTime);
        mCyclus = 0;
        mHeatStatus = false;
        
    };
    void runtime(); 
    bool lowFreqPwm(const unsigned int level);
    bool isHeating() const;
    int getIronTemperature();
    int getSelectedTemperature();
    uint8_t getPower() const;

  
  private:
    Solder(const Solder& notPaste);
    void heatIron(const bool onOff);
    uint8_t getLevelFromPercentage(const uint8_t percentage) const;
    
    const uint8_t mHeatPin;
    const uint8_t mSelectPin;
    MAX6675& mThermocouple;
    uint32_t mTime;
    const uint8_t mMaxPower;
    uint8_t mPower;
    LoopTimer* mPwmTimer;
    uint8_t mCyclus;
    bool mHeatStatus;           //state of heating iron
    int mIronTemp;              //current temperature value of preselected temperature 
    int mSelectedTemp;          //current temperature value at iron termocoupler
};

#endif
