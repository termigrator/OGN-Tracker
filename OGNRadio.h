#ifndef OGNRADIO_h
#define OGNRADIO_h

#include <stdint.h>
#include <Arduino.h>

#define F8682 2
#define F8684 4

#include <SPI.h>
#include <RFM69registers.h>

class OGNRadio 
{
  public:
    OGNRadio(void);
    void Initialise(void);
    void SendPacket(uint8_t *Packet, uint16_t Size, uint16_t freq);
      
  protected:
				
  private:
    void WriteRegister(uint8_t Register, uint8_t Data);
    uint8_t ReadRegister(uint8_t Register);
};


#endif 

