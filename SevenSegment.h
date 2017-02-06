#ifndef SevenSegment_h
#define SevenSegment_h

#include <inttypes.h>


class SevenSegment;
typedef void (*sevenSegmentEventHandler)(SevenSegment&);

class SevenSegment {
  public:
    SevenSegment(uint8_t segA, uint8_t segB, uint8_t segC, uint8_t segD, uint8_t segE, uint8_t segF, uint8_t segG);   
    void showCharacter(uint8_t numberOfCharacter);
    
  private:  
    uint8_t mPinSegA;
    uint8_t mPinSegB;
    uint8_t mPinSegC;
    uint8_t mPinSegD;
    uint8_t mPinSegE;
    uint8_t mPinSegF;
    uint8_t mPinSegG;
    
    const bool mSegmentMap[16][7]= 
    {
      {0,0,0,0,0,0,1}, // 0 code = 0
      {1,0,0,1,1,1,1}, // 1 code = 1
      {0,0,1,0,0,1,0}, // 2 code = 2
      {0,0,0,0,1,1,0}, // 3 code = 3
      {1,0,0,1,1,0,0}, // 4 code = 4
      {0,1,0,0,1,0,0}, // 5 code = 5
      {0,1,0,0,0,0,0}, // 6 code = 6
      {0,0,0,1,1,1,1}, // 7 code = 7
      {0,0,0,0,0,0,0}, // 8 code = 8
      {0,0,0,1,1,0,0}, // 9 code = 9
      {0,0,0,1,0,0,0}, // A code = 10
      {1,1,0,0,0,0,0}, // b code = 11
      {0,1,1,0,0,0,1}, // C code = 12
      {1,0,0,0,0,1,0}, // D code = 13
      {0,1,1,0,0,0,0}, // E code = 14
      {0,1,1,1,0,0,0}  // F code = 15
    };       
};

#endif
