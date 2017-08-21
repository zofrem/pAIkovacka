#ifndef DualLed_h
#define DualLed_h

#include <inttypes.h>

    enum LedStatuses
    {
      LED_OFF,
      LED_GREEN,
      LED_RED,
      LED_GREEN_BLINK,
      LED_RED_BLINK  
    };

class DualLed;
typedef void (*dualLedEventHandler)(DualLed&);

class DualLed {
  public:    
    DualLed(const uint8_t red, const uint8_t green);   
    void showBright(const LedStatuses ledBrightType);
    
  private:
    DualLed(const DualLed& paste);
    void doBlink(const uint8_t currentPin, const unsigned int periode);
    uint8_t mPinRed;
    uint8_t mPinGreen;
    LedStatuses mCurrentBrightStatus;
    bool mBlinkLastStatus;
    unsigned long mBlinkLastTime;
    LedStatuses mActiveBrightType;
};

#endif
