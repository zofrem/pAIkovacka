#include <SoftwareSerial.h>
#include <inttypes.h>

#include "DualLed.h"
#include "LoopTimer.h"
#include "Solder.h"

//pAIkovacka
//artificial inteligence soldering station
//rework of PCB for soldering sation ERS50 TESLA

const uint8_t HEAT_PIN = 2;            //discrete on/off heating
const uint8_t SET_TEMP_PIN = 1;        //analog voltage at preselected temperature on potentiometer

DualLed* heatIndicator = new DualLed(3,4);
LoopTimer* serialResponse = new LoopTimer(1000);
MAX6675* max6675 = new MAX6675(5, 6, 7); //max6675Response is 225ms take care
Solder* solder = new Solder(HEAT_PIN, SET_TEMP_PIN, *max6675);


void setup()
{ 
  Serial.begin(9600); 
}

void loop()
{
  solder->runtime();
  
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
  Serial.println(solder->getSelectedTemperature());
  Serial.print("Iron temperature:");
  Serial.println(solder->getIronTemperature());
  Serial.print("Iron power:");
  Serial.println(solder->getPower());
}



