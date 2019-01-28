#include <SoftwareSerial.h>
#include <inttypes.h>
#include <max6675.h>
#include "DualLed.h"
#include "LoopRecorder.h"
#include "LoopTimer.h"
#include "PowerModes.h"
#include "Solder.h"

//pAIkovacka
//artificial inteligence soldering station
//rework of PCB for soldering sation ERS50 TESLA

const uint8_t AVERAGE_SAMPLES = 16;    //statistic count of samples for average

MAX6675* thermocouple =  new MAX6675(5, 6, 7);
DualLed* heatIndicator = new DualLed(3,4);
LoopRecorder<int>* statHeatTemp = new LoopRecorder<int>(AVERAGE_SAMPLES);
LoopRecorder<int>* statSetTemp = new LoopRecorder<int>(AVERAGE_SAMPLES);
LoopTimer* serialResponse = new LoopTimer(250);
//max6675Response is 225ms take care
PowerModes* powerModes = new PowerModes();


const uint8_t HEAT_PIN = 2;            //discrete on/off heating
const uint8_t TEMP_PIN = 0;            //analog voltage of iron termocoupler
const uint8_t SET_TEMP_PIN = 1;        //analog voltage at preselected temperature on potentiometer
int actualSetelectedTemp = 0;          //current temperature value of preselected temperature 
int actualHeatTemp = 0;                //current temperature value at iron termocoupler
int actualInternalTemp = 0;            //current temperature value inside soldering station
const int THRESHOLD_TEMP = 15;         //when heating temperature decrease by that value, heat will start again

Solder* solder = new Solder(HEAT_PIN, 20);

enum HeatStatus
{
  HEAT_OFF,
  HEAT_STARTUP,
  HEAT_CONTINUE,
  HEAT_WAIT,
  HEAT_OVERHEAT = 14
};

void setup()
{ 
  Serial.begin(9600); 
}

void loop()
{
  uint8_t power = 50;
  if(solder->lowFreqPwm(power)) //TODO check response of MAX 225ms but you call 20ms before
  {
    getActualIronTemperature();
    getActualSelectedTemperature();
  }
  if(solder->isHeating())
    heatIndicator->showBright(LED_RED);
  else
    heatIndicator->showBright(LED_GREEN);
    

  if(serialResponse->timer())
    dataOutput();
}

void dataOutput()
{
  Serial.print("Selected temperature:");
  Serial.println(actualSetelectedTemp);
  Serial.print("Iron temperature:");
  Serial.println(actualHeatTemp);
  //heatStatus ? Serial.println("Heating") : Serial.println("Cooling");
  int8_t time = 0;
  bool run = powerModes->coolingTime(time);
  run ? Serial.println("TimerRun") : Serial.println("TimerStop");
  Serial.println(time);
}



int getAverageValue(const LoopRecorder<int>& data, const uint8_t samplesCount)
{
  int value = 0;
  uint8_t empty = 0;
  int sumOfValues = 0;
  for(uint8_t i = 0; i < samplesCount; ++i)
  {
    if(data.getLastSample(i, value))
      sumOfValues += value;
    else
      ++empty;
  }
  return sumOfValues / (samplesCount - empty);
}

void getActualIronTemperature()
{
  int temp = thermocouple->readCelsius() - 300;
  statHeatTemp->pushBack(temp); //TODO make conversion voltage to temperature
  actualHeatTemp = temp;
}

void getActualSelectedTemperature()
{
  statSetTemp->pushBack((0.195503 * analogRead(SET_TEMP_PIN)) + 200); // linear conversion for potentiometer from 0-1023 analog read to 200-400 degrees of celsius
  actualSetelectedTemp = getAverageValue(*statSetTemp, AVERAGE_SAMPLES);
}
