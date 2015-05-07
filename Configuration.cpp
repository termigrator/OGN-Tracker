/* 
 OGN Tracker Client>
    Copyright (C) <2015>  <Mike Roberts>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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

