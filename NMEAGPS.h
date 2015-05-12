/* 
    OGN Tracker Client
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

#ifndef NMEAGPS_h
#define NMEAGPS_h

#include <stdint.h>

#include <SoftwareSerial.h>
#include <TinyGPS++.h>

class NMEAGPS : public TinyGPSPlus
{
  public:
    NMEAGPS(uint8_t DataInPin, uint8_t DataOutPin);
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
    void CalculateClimbRate(int32_t DeltaT);
      
  protected:
				
  private:
    SoftwareSerial *NMEAGPSStream;
    float TurnRate;
    uint32_t LastHeading;
    uint32_t ClimbRate;
    int32_t LastAltitude;
    uint32_t LastTime;
};


#endif 

