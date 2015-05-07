#include "Configuration.h"

#include <Arduino.h>
#include <eeprom.h>

Configuration::Configuration(void)
{
}

void Configuration::LoadConfiguration(void)
{
  cs.Address = 0x405DA8;
  cs.Type = TYPE_ICAO;
  cs.Private = 0;

  //NONVolatile_Read((void *)&cs,sizeof(cs));  
}

uint32_t Configuration::GetAddress(void)
{
  return cs.Address;
}

void Configuration::SetAddress(uint32_t Address)
{
  cs.Address = Address;
}

uint8_t Configuration::GetAddressType(void)
{
  return cs.Type;
}

void Configuration::SetAddressType(uint8_t Type)
{
  cs.Address = Type;
}

uint8_t Configuration::GetPrivate(void)
{
  return cs.Private;
}

void Configuration::SetPrivate(uint8_t Private)
{
  cs.Private = Private;
}

void Configuration::WriteConfiguration(void)
{
  //NONVolatile_Write((void *)&cs,sizeof(cs));
}

void Configuration::Report(void)
{
    Serial.println("OGN Tracker");
    Serial.print("Device Address "); Serial.println(cs.Address,HEX);
    
}

void Configuration::ProcessSerial(void)
{
} 


uint16_t Configuration::NONVolatile_Write(void *Object, uint16_t Size)
{
  const byte* p = (byte*)Object;
  unsigned int i;
  for (i = 0; i < Size; i++)
    EEPROM.write(i, *p++);
  return i;
}

uint16_t Configuration::NONVolatile_Read(void *Object, uint16_t Size)
{
    byte* p = (byte*)(void*)Object;
    unsigned int i;
    for (i = 0; i < Size; i++)
          *p++ = EEPROM.read(i);
    return i;
}

