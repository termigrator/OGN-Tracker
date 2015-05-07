#ifndef NMEAGPS_h
#define NMEAGPS_h

#include <stdint.h>

#include <SoftwareSerial.h>
#include <TinyGPS++.h>

class NMEAGPS : public TinyGPSPlus
{
  public:
    NMEAGPS(uint8_t TxPin, uint8_t RxPin);
    void ProcessInput(void);
    
    uint32_t GetOGNLatitude();
    uint32_t GetOGNLongitude();
    uint32_t GetOGNAltitude();
    uint32_t GetOGNSpeed();
    uint32_t GetOGNDOP();
    uint8_t  GetOGNFixQuality();
    uint8_t  GetOGNFixMode();
    uint16_t GetOGNHeading();
    int16_t GetOGNClimbRate();
    void CalculateClimbRate(uint32_t DeltaT);
      
  protected:
				
  private:
    SoftwareSerial *NMEAGPSStream;
    float TurnRate;
    uint32_t LastHeading;
    float ClimbRate;
    int32_t LastAltitude;
    uint32_t LastTime;
};


#endif 

