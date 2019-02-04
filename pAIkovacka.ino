#include <SoftwareSerial.h>
#include <inttypes.h>
#include <max6675.h>
#include "DualLed.h"
#include "LoopTimer.h"
#include "Solder.h"

//pAIkovacka
//artificial inteligence soldering station
//rework of PCB for soldering sation ERS50 TESLA

const uint8_t HEAT_PIN = 2;            //discrete on/off heating
const uint8_t SET_TEMP_PIN = 1;        //analog voltage at preselected temperature on potentiometer
const uint8_t AVERAGE_SAMPLES = 16;    //statistic count of samples for average

MAX6675* thermocouple =  new MAX6675(5, 6, 7); //max6675Response is 225ms take care
DualLed* heatIndicator = new DualLed(3,4);
LoopTimer* serialResponse = new LoopTimer(1000);
Solder* solder = new Solder(HEAT_PIN);

int actualSetelectedTemp = 0;          //current temperature value of preselected temperature 
int actualHeatTemp = 0;                //current temperature value at iron termocoupler
uint8_t power = 50;


enum HeatStatus // TODO future use
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
  if(solder->lowFreqPwm(power)) //TODO check response of MAX 225ms but you call 20ms before
  {
    getActualIronTemperature();
    getActualSelectedTemperature();
        
    if(actualSetelectedTemp > actualHeatTemp) 
      ++power;
    else
      --power;
      
    if(51 == power)
      power = 50;
    else if(power == 0)
    power = 0;
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
  Serial.print("Iron power:");
  Serial.println(power);
}


void getActualIronTemperature()
{
  actualHeatTemp = thermocouple->readCelsius() - 300;
}

void getActualSelectedTemperature()
{
  actualSetelectedTemp = (0.195503 * analogRead(SET_TEMP_PIN)) + 200 + 100; // linear conversion for potentiometer from 0-1023 analog read to 200-400 degrees of celsius
}
