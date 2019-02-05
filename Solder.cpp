#include <Arduino.h>
#include "Solder.h"

void Solder::heatIron(const bool onOff)
{
  if(mHeatStatus != onOff) //do only difference
  {
    mHeatStatus = onOff;
    digitalWrite(mHeatPin, onOff);
  }
}

void Solder::runtime()
{
  if(lowFreqPwm(mPower))
  {
    getIronTemperature();
    getSelectedTemperature();

    if(mSelectedTemp > mIronTemp)
      ++mPower;
    else
      --mPower;

    if(51 == mPower)
      mPower = 50;
    else if(mPower == 0)
    mPower = 0;
  }
}

bool Solder::lowFreqPwm(const unsigned int level)
{        
  if(mPwmTimer->timer())
  {
    ++mCyclus;
    if(101 == mCyclus)
    {
      mCyclus = 0;
    }
    if(mCyclus <= getLevelFromPercentage(level))
    {
      heatIron(true);
      return false;
    }
    else if(75 == mCyclus) // last moment before heating numeric_limits<uint8_t>::max() not for 8bit
    {
      heatIron(false);
      return true; //now measure temperature
    }
    else
    {
      heatIron(false);
      return false;
    }
  }
  return false;
}

bool Solder::isHeating() const
{
  return mHeatStatus;
}

uint8_t Solder::getLevelFromPercentage(const uint8_t percentage) const
{
  uint8_t level = 0;
  if(100 < percentage)
    level = 100;
  else if(mMaxPower <= percentage)
    level = mMaxPower;
  else
    level = percentage;
  return (level);
}

int Solder::getIronTemperature()
{
  mIronTemp = mThermocouple.readCelsius() - 300;
  return mIronTemp; // todopass by reference 8bit 
}

int Solder::getSelectedTemperature()
{
  mSelectedTemp = (0.195503 * analogRead(mSelectPin)) + 200 + 100; // linear conversion for potentiometer from 0-1023 analog read to 200-400 degrees of celsius
  return mSelectedTemp; // todopass by reference 8bit 
}

uint8_t Solder::getPower() const
{

  return mPower;
}

