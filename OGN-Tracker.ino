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

#include <SPI.h>
#include <RFM69registers.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <EEPROM.h>
#include <stdint.h>


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
  TrackerConfiguration = new Configuration();
  TrackerConfiguration->LoadConfiguration();
  
  Serial.begin(115200);
  ConfigurationReport();

  GPS = new NMEAGPS(TrackerConfiguration->GetDataInPin(),TrackerConfiguration->GetDataOutPin());
  Radio = new OGNRadio(); 
  Radio->Initialise();
}

void loop() 
{
  OGNPacket *ReportPacket;
  
  GPS->ProcessInput();
  
  if( (millis() - ReportTime) > REPORTDELAY)
  {
    if(GPS->location.isValid())
    {
      if( (millis() - ClimbAverageTime) > CLIMBAVERAGE)
      {
        GPS->CalculateClimbRate(CLIMBAVERAGE/1000);
        ClimbAverageTime = millis();
      }

      ReportPacket = new OGNPacket;
      FormRFPacket(ReportPacket);
        
      Radio->SendPacket(ReportPacket->ManchesterPacket,OGNPACKETSIZE*2,F8682);
      Radio->SendPacket(ReportPacket->ManchesterPacket,OGNPACKETSIZE*2,F8684);
 
      delete ReportPacket;
      ReportTime = millis(); 
    }
  }

  if(Serial.available())
  {
    ProcessSerial();
  }
}

void FormRFPacket(OGNPacket *Packet)
{
  Packet->MakeSync();
 
  Packet->MakeHeader(false,false,0,false,TrackerConfiguration->GetAddressType(),TrackerConfiguration->GetAddress());
   
  Packet->MakeLatitude(GPS->GetOGNFixQuality(), GPS->time.second(), GPS->GetOGNLatitude());
    
  Packet->MakeLongitude(GPS->GetOGNFixMode(), 0, GPS->GetOGNDOP(), GPS->GetOGNLongitude());
  
  Packet->MakeAltitude(0, GPS->GetOGNSpeed(), GPS->GetOGNAltitude());
  
  Packet->MakeHeading(TrackerConfiguration->GetAircraftType(), TrackerConfiguration->GetPrivate(), GPS->GetOGNClimbRate(), GPS->GetOGNHeading());

  Packet->Whiten();
  
  Packet->AddFEC();
  
  Packet->ManchesterEncodePacket();
}













void ConfigurationReport(void)
{
    Serial.print(F("Device Address \t")); Serial.println(TrackerConfiguration->GetAddress(),HEX);
    Serial.print(F("Address Type \t"));
    switch(TrackerConfiguration->GetAddressType())
    {
      case ADDRESS_TYPE_RANDOM  : Serial.println(F("Random")); break;
      case ADDRESS_TYPE_ICAO   : Serial.println(F("ICAO")); break; 
      case ADDRESS_TYPE_FLARM  : Serial.println(F("Flarm")); break;
      case ADDRESS_TYPE_OGN   : Serial.println(F("OGN")); break; 
      default : Serial.println();
    }
    
    Serial.print(F("Aircraft Type is\t"));
    switch(TrackerConfiguration->GetAircraftType())
    {
      case AIRCRAFT_TYPE_UNKNOWN  : Serial.println(F("Unknown")); break;
      case AIRCRAFT_TYPE_GLIDER   : Serial.println(F("Glider")); break; 
      case AIRCRAFT_TYPE_TOW_PLANE : Serial.println(F("Tow Plane")); break;
      case AIRCRAFT_TYPE_HELICOPTER : Serial.println(F("Helicopter")); break;
      case AIRCRAFT_TYPE_PARACHUTE : Serial.println(F("Parachute")); break;
      case AIRCRAFT_TYPE_DROP_PLANE : Serial.println(F("Drop Plane")); break;
      case AIRCRAFT_TYPE_HANG_GLIDER : Serial.println(F("Hang Glider")); break;
      case AIRCRAFT_TYPE_PARA_GLIDER : Serial.println(F("Para Glider")); break;
      case AIRCRAFT_TYPE_POWERED_AIRCRAFT : Serial.println(F("Powered Aircraft")); break; 
      case AIRCRAFT_TYPE_JET_AIRCRAFT : Serial.println(F("Jet Aircraft")); break;
      case AIRCRAFT_TYPE_UFO : Serial.println(F("UFO")); break;
      case AIRCRAFT_TYPE_BALLOON : Serial.println(F("Balloon")); break;
      case AIRCRAFT_TYPE_AIRSHIP : Serial.println(F("Airship")); break;
      case AIRCRAFT_TYPE_UAV : Serial.println(F("UAV")); break;
      case AIRCRAFT_TYPE_STATIC_OBJECT : Serial.println(F("Static")); break;
      default : Serial.println();
    }
    
    Serial.print(F("Serial Baud Rate \t")); Serial.println(TrackerConfiguration->GetSerialBaud());
    Serial.print(F("GPS Type is \t")); Serial.println("NMEA");
    Serial.print(F("GPS Baud Rate \t")); Serial.println(TrackerConfiguration->GetGPSBaud(),DEC);
    Serial.print(F("Listening for data on pin "));  Serial.println(TrackerConfiguration->GetDataInPin(),DEC);
    Serial.print(F("Sending Data to GPS on pin "));  Serial.println(TrackerConfiguration->GetDataOutPin(),DEC);
    Serial.print(F("Privacy is "));  if(TrackerConfiguration->GetPrivate()) Serial.println(F("On")); else Serial.println(F("Off"));
    Serial.println();
}

void StatusReport(void)
{
  Serial.print(F("Tracking "));Serial.print(GPS->satellites.value()); Serial.println(F(" satellites"));
  if (GPS->location.isValid())
  {
    Serial.print(GPS->location.lat(), 6);
    Serial.print(F(","));
    Serial.print(GPS->location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }
  
  Serial.print(F(" "));
  if(GPS->altitude.isValid());
  {
    Serial.print(GPS->altitude.meters());
    Serial.print(F(" "));
  }
  
  if (GPS->date.isValid())
  {
    Serial.print(GPS->date.month());
    Serial.print(F("/"));
    Serial.print(GPS->date.day());
    Serial.print(F("/"));
    Serial.print(GPS->date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (GPS->time.isValid())
  {
    if (GPS->time.hour() < 10) Serial.print(F("0"));
    Serial.print(GPS->time.hour());
    Serial.print(F(":"));
    if (GPS->time.minute() < 10) Serial.print(F("0"));
    Serial.print(GPS->time.minute());
    Serial.print(F(":"));
    if (GPS->time.second() < 10) Serial.print(F("0"));
    Serial.print(GPS->time.second());
    Serial.print(F("."));
    if (GPS->time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(GPS->time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }
  Serial.println();
}

#define BUFFERSIZE 40
void ProcessSerial(void)
{
  static char CommandBuffer[BUFFERSIZE+1];
  static int8_t BufferUsed = 0;
  uint32_t Address;
  uint8_t Type;
  
  while (Serial.available())
  {
    if(BufferUsed < BUFFERSIZE)
    {
      CommandBuffer[BufferUsed] = toupper(Serial.read());
      Serial.print(CommandBuffer[BufferUsed]);
      
      if ((CommandBuffer[BufferUsed] == '\r' ) || (CommandBuffer[BufferUsed] == '\n' ))
      {
        Serial.println();
        CommandBuffer[BufferUsed] = '\0';
        if(strstr(CommandBuffer,"STATUS"))
        {
          StatusReport();
        }
        else if(strstr(CommandBuffer,"CONFIG"))
        {
          ConfigurationReport();
        }         
        else if(strstr(CommandBuffer,"ADDRESS "))
        {
          Address = strtoul(&CommandBuffer[7],NULL,16);
          if(Address)
            TrackerConfiguration->SetAddress(Address);
          ConfigurationReport();
        }         
        else if(strstr(CommandBuffer,"SAVE"))
        {
          Serial.println(F("Saving Config"));
          TrackerConfiguration->WriteConfiguration();
          TrackerConfiguration->LoadConfiguration();
          Serial.print(F("\r\nSaved Configuration\r\n"));
          ConfigurationReport();          
        }         
        else if(strstr(CommandBuffer,"ADDRESSTYPE "))
        {
          Type = (uint8_t)strtol(&CommandBuffer[11],NULL,10);
          TrackerConfiguration->SetAddressType(Type);
          ConfigurationReport();
        }         
        else if(strstr(CommandBuffer,"AIRCRAFTTYPE "))
        {
          Type = (uint8_t)strtol(&CommandBuffer[12],NULL,10);
          Serial.println(Type,DEC);
          TrackerConfiguration->SetAircraftType(Type);
          ConfigurationReport();
        }         

        //else if...
        BufferUsed = 0;
      }
      else
      {
         BufferUsed ++;
      }
    }
    else
    {
      BufferUsed = 0;
    }  
  }
} 


