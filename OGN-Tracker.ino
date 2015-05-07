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

#include <SPI.h>
#include <RFM69registers.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <EEPROM.h>
#include <stdint.h>


//#include "uBloxGPS.h"
#include "NMEAGPS.h"
#include "OGNRadio.h"
#include "Configuration.h"
#include "OGNPacket.h"

void FormRFPacket(OGNPacket *Packet);


NMEAGPS *GPS;
OGNRadio *Radio;
Configuration *TrackerConfiguration;


uint32_t ReportTime = 0;
#define REPORTDELAY 1000

uint32_t ClimbAverageTime = 0;
#define CLIMBAVERAGE 30000


void setup() 
{
  Serial.begin(115200);
  TrackerConfiguration = new Configuration();
  TrackerConfiguration->LoadConfiguration();
  TrackerConfiguration->Report();

  GPS = new NMEAGPS(5,4);
  Radio = new OGNRadio(); 
  Radio->Initialise();
}

void loop() 
{
  OGNPacket *ReportPacket;
  
  GPS->ProcessInput();
  
  if( (millis() - ReportTime) > REPORTDELAY)
  {
    ReportPacket = new OGNPacket;
    FormRFPacket(ReportPacket);
        
    Radio->SendPacket(ReportPacket->ManchesterPacket,OGNPACKETSIZE*2,F8682);
    Radio->SendPacket(ReportPacket->ManchesterPacket,OGNPACKETSIZE*2,F8684);
 
    delete ReportPacket;
    ReportTime = millis(); 
  }
  
  if( (millis() - ClimbAverageTime) > CLIMBAVERAGE)
  {
    GPS->CalculateClimbRate(CLIMBAVERAGE/1000);
    ClimbAverageTime = millis();
  }
  if(Serial.available())
  {
    TrackerConfiguration->ProcessSerial();
  }
}

void FormRFPacket(OGNPacket *Packet)
{
  Packet->MakeSync();
 
  Packet->MakeHeader(false,false,0,false,TrackerConfiguration->GetAddressType(),TrackerConfiguration->GetAddress());
   
  Packet->MakeLatitude(GPS->GetOGNFixQuality(), GPS->time.second(), GPS->GetOGNLatitude());
    
  Packet->MakeLongitude(GPS->GetOGNFixMode(), 0, GPS->GetOGNDOP(), GPS->GetOGNLongitude());
  
  Packet->MakeAltitude(0, GPS->GetOGNSpeed(), GPS->GetOGNAltitude());
  
  Packet->MakeHeading(1, TrackerConfiguration->GetPrivate(), GPS->GetOGNClimbRate(), GPS->GetOGNHeading());

  Packet->Whiten();
  
  Packet->AddFEC();
  
  Packet->ManchesterEncodePacket();
}
