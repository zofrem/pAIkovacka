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

const uint8_t HEAT_PIN = 2;            //discrete on/off heating
const uint8_t TEMP_PIN = 0;            //analog voltage of iron termocoupler
const uint8_t SET_TEMP_PIN = 1;        //analog voltage at preselected temperature on potentiometer
const uint8_t INTERNAL_TEMP_PIN = 2;   //analog LM35 internal check for overheating
int actualSetelectedTemp = 0;          //current temperature value of preselected temperature 
int actualHeatTemp = 0;                //current temperature value at iron termocoupler
int actualInternalTemp = 0;            //current temperature value inside soldering station
const int THRESHOLD_TEMP = 10;         //when heating temperature decrease by that value, heat will start again
bool heatStatus = false;               //state of heating iron

void setup()
{
  Scheduler.startLoop(dataOutput);
  Serial.begin(9600);  
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
    //TODO log and sign error
    heatIron(false);
  }
  else                                                            //selected temperature was reached stop heat
  {
    heatIron(false);
  }
  yield();
}

void dataOutput()
{
  Serial.print("Selected temperature:");
  Serial.println(actualSetelectedTemp);
  Serial.print("Iron temperature:");
  Serial.println(actualHeatTemp);
  heatStatus ? Serial.println("Heating") : Serial.println("Cooling");
  Scheduler.delay(1000);
  yield(); 
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
    heatIndicator.showBright(LED_RED);
  }
  else
  {
    heatIndicator.showBright(LED_GREEN);
  }
}

void getActualIronTemperature()
{
  actualHeatTemp = analogRead(TEMP_PIN); //TODO make conversion voltage to temperature
}

void getActualSelectedTemperature()
{
  actualSetelectedTemp = (0.195503 * analogRead(SET_TEMP_PIN)) + 200; // linear conversion for potentiometer from 0-1023 analog read to 200-400 degrees of celsius
}

void getActualInternalTemperature()
{
  actualInternalTemp = (analogRead(INTERNAL_TEMP_PIN) * 0.00488) * 100;
}

