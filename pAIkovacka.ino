#include <SchedulerARMAVR.h>
#include <SoftwareSerial.h>
#include <inttypes.h>
#include "SevenSegment.h"
#include "DualLed.h"

//pAIkovacka
//artificial inteligence soldering station
//rework of PCB for soldering sation ERS50 TESLA


SevenSegment statusIndicator = SevenSegment(5,6,7,8,9,11,12);
DualLed heatIndicator = DualLed(3,4);

uint8_t heatPin = 2;           //discrete on/off heating
uint8_t tempPin = 0;           //analog voltage of iron termocoupler
uint8_t setTempPin = 1;        //analog voltage at preselected temperature on potentiometer
uint8_t internalTempPin = 2;   //analog LM35 internal check for overheating
int actualSetelectedTemp = 0;  //current temperature value of preselected temperature 
int actualHeatTemp = 0;        //current temperature value at iron termocoupler
int actualInternalTemp = 0;    //currebt temperature value inside soldering station

void setup()
{
  Scheduler.startLoop(dataOutput);
  Serial.begin(9600);  
}

void loop() 
{  
  getActualIronTemperature();
  getActualSelectedTemperature();
  actualHeatTemp = analogRead(tempPin);
  yield();
}

void dataOutput()
{
  Serial.println(actualSetelectedTemp);
  Scheduler.delay(1000);
  yield(); 
}

void getActualIronTemperature()
{
  actualHeatTemp = analogRead(tempPin); //TODO make conversion voltage to temperature
}

void getActualSelectedTemperature()
{
  actualSetelectedTemp = (0.195503 * analogRead(setTempPin)) + 200; // linear conversion for potentiometer from 0-1023 analog read to 200-400 degrees of celsius
}

void getActualInternalTemperature()
{
  actualInternalTemp = (analogRead(internalTempPin) * 0.00488) * 100;
}

