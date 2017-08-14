#include <SoftwareSerial.h>
#include <inttypes.h>
#include <max6675.h>
#include "DualLed.h"
#include "LoopRecorder.h"
#include "LoopTimer.h"

//pAIkovacka
//artificial inteligence soldering station
//rework of PCB for soldering sation ERS50 TESLA

const uint8_t AVERAGE_SAMPLES = 16;    //statistic count of samples for average

MAX6675 thermocouple(5, 6, 7);
DualLed* heatIndicator = new DualLed(3,4);
LoopRecorder<int>* statHeatTemp = new LoopRecorder<int>(AVERAGE_SAMPLES);
LoopRecorder<int>* statSetTemp = new LoopRecorder<int>(AVERAGE_SAMPLES);
LoopTimer* serialResponse = new LoopTimer(1000);

const uint8_t HEAT_PIN = 2;            //discrete on/off heating
const uint8_t TEMP_PIN = 0;            //analog voltage of iron termocoupler
const uint8_t SET_TEMP_PIN = 1;        //analog voltage at preselected temperature on potentiometer
const uint8_t INTERNAL_TEMP_PIN = 2;   //analog LM35 internal check for overheating
int actualSetelectedTemp = 0;          //current temperature value of preselected temperature 
int actualHeatTemp = 0;                //current temperature value at iron termocoupler
int actualInternalTemp = 0;            //current temperature value inside soldering station
const int THRESHOLD_TEMP = 10;         //when heating temperature decrease by that value, heat will start again
bool heatStatus = false;               //state of heating iron

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
  pinMode(HEAT_PIN, OUTPUT);           //inicialization pin discrete heating for behavior like output
}

void loop() 
{  
  getActualIronTemperature();
  getActualSelectedTemperature();
  if(actualHeatTemp < actualSetelectedTemp - THRESHOLD_TEMP)      //always heat until reach actualSetelectedTemp - THRESHOLD_TEMP
  {
    heatIron(true);
  }
  else if(actualHeatTemp < actualSetelectedTemp && heatStatus)    //continue heat when temperature rise, othewise cool down to actualSetelectedTemp - THRESHOLD_TEMP
  {
    heatIron(true);
  }
  else if(actualHeatTemp > actualSetelectedTemp + THRESHOLD_TEMP) //error case for inexplicable iron overheat
  {
    heatIron(false);
  }
  else                                                            //selected temperature was reached stop heat
  {
    heatIron(false);
  }
  if(serialResponse->timer())
    dataOutput();
}

void dataOutput()
{
  Serial.print("Selected temperature:");
  Serial.println(actualSetelectedTemp);
  Serial.print("Iron temperature:");
  Serial.println(actualHeatTemp);
  heatStatus ? Serial.println("Heating") : Serial.println("Cooling");
}

void heatIron(bool onOff)
{
  if(heatStatus != onOff) //do only difference
  {
    heatStatus = onOff;
    digitalWrite(HEAT_PIN, onOff);
  }
  if(onOff)
  {
    heatIndicator->showBright(LED_RED);
  }
  else
  {
    heatIndicator->showBright(LED_GREEN);
  }
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
  int temp = thermocouple.readCelsius();
  statHeatTemp->pushBack(temp); //TODO make conversion voltage to temperature
  actualHeatTemp = temp;
}

void getActualSelectedTemperature()
{
  statSetTemp->pushBack((0.195503 * analogRead(SET_TEMP_PIN)) + 200); // linear conversion for potentiometer from 0-1023 analog read to 200-400 degrees of celsius
  actualSetelectedTemp = getAverageValue(*statSetTemp, AVERAGE_SAMPLES);
}

void getActualInternalTemperature()
{
  actualInternalTemp = (analogRead(INTERNAL_TEMP_PIN) * 0.00488) * 100;
}
