#include <Arduino.h>
#include "SevenSegment.h"

SevenSegment::SevenSegment(uint8_t segA, uint8_t segB, uint8_t segC, uint8_t segD, uint8_t segE, uint8_t segF, uint8_t segG)
{
    pinMode(segA, OUTPUT);
    pinMode(segB, OUTPUT);
    pinMode(segC, OUTPUT);
    pinMode(segD, OUTPUT);
    pinMode(segE, OUTPUT);
    pinMode(segF, OUTPUT);
    pinMode(segG, OUTPUT);
    mPinSegA = segA;
    mPinSegB = segB;
    mPinSegC = segC;
    mPinSegD = segD;
    mPinSegE = segE;
    mPinSegF = segF;
    mPinSegG = segG;
}

/////////////////////////////////////////////////////////
/// showCharacter 
/// show selected one character on seven segment display unit
/////////////////////////////////////////////////////////
void SevenSegment::showCharacter(uint8_t numberOfCharacter)
{
    if(numberOfCharacter >= 16) // cut unsupported chars
        numberOfCharacter = 0;
    digitalWrite(mPinSegA, mSegmentMap[numberOfCharacter][0]);
    digitalWrite(mPinSegB, mSegmentMap[numberOfCharacter][1]);
    digitalWrite(mPinSegC, mSegmentMap[numberOfCharacter][2]);
    digitalWrite(mPinSegD, mSegmentMap[numberOfCharacter][3]);
    digitalWrite(mPinSegE, mSegmentMap[numberOfCharacter][4]);
    digitalWrite(mPinSegF, mSegmentMap[numberOfCharacter][5]);
    digitalWrite(mPinSegG, mSegmentMap[numberOfCharacter][6]);
}
