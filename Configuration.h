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

