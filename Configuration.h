#ifndef CONFIGURATION_h
#define CONFIGURATION_h

#include <stdint.h>

#define TYPE_ICAO 1


struct Configuration_Struct
{
  uint32_t Address;
  uint8_t Type; 
  uint8_t Private;
};   

/////////////////////////////////////////////////////////////////////
class Configuration 
{
  public:
    Configuration();
    void LoadConfiguration(void);
    void WriteConfiguration(void);
    void Report(void);
    void ProcessSerial(void);
    
    uint32_t GetAddress(void); 
    void SetAddress(uint32_t Address); 
    
    uint8_t GetAddressType(void);
    void SetAddressType(uint8_t Type);

    uint8_t GetPrivate(void);
    void SetPrivate(uint8_t Private);
      
  protected:
				
  private:
    struct Configuration_Struct cs;
    uint16_t NONVolatile_Read(void *Object, uint16_t Size);
    uint16_t NONVolatile_Write(void *Object, uint16_t Size);
};


#endif 

