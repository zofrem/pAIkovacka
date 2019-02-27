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

    if(mPower == 0xFF)
      mPower = 0;
    else if(mMaxPower < mPower)
      mPower = mMaxPower;

  }
}

bool Solder::lowFreqPwm(const unsigned int level)
{
  bool measure = false;
  if(mPwmTimer->timer())
  {
    ++mCyclus;
    bool heat = false;
    if(PERCENTAGE_100 < mCyclus)
    {
      mCyclus = 0;
    }
    if(mCyclus <= getLevelFromPercentage(level))
    {
      heat = true;
    }
    else if(87 == mCyclus) //with 20ms is arround 1.75s
    {
      measure = true;      //now measure temperature
    }
    heatIron(heat);
  }
  return measure;
}

bool Solder::isHeating() const
{
  return mHeatStatus;
}

uint8_t Solder::getLevelFromPercentage(const uint8_t percentage) const
{
  uint8_t level = 0;
  if(PERCENTAGE_100 < percentage)
    level = PERCENTAGE_100;
  else if(mMaxPower <= percentage)
    level = mMaxPower;
  else
    level = percentage;
  return (level);
}

int Solder::getIronTemperature()
{
  mIronTemp = mThermocouple.readCelsius();
  return mIronTemp; //TODO pass by reference 8bit only
}

int Solder::getSelectedTemperature()
{
  mSelectedTemp = (0.195503 * analogRead(mSelectPin)) + 200; // linear conversion for potentiometer from 0-1023 analog read to 200-400 degrees of celsius
  return mSelectedTemp; //TODO pass by reference 8bit only
}

uint8_t Solder::getPower() const
{
  return mPower;
}

