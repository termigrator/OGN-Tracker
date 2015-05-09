# OGN-Tracker
    OGN Tracker Client
    
    This repository implements a Open Glider Network Tracker client.
    
    Details of the tracking network and tracking client are provided here
    
    http://wiki.glidernet.org/
    http://wiki.glidernet.org/ogn-tracking-protocol
    
    Hardware
    
    The original target hardware was the Low Power Lab Moteino USB
    https://lowpowerlab.com/shop/index.php?_route_=moteinousb
    
    but it sould run on any similar hardware.
    
    You will also need a TTL GPS module.  There are plenty to choose from on your favorite internet auction site.
    
    To build.
    Attach the GPS power wires to the Moteino power.
    Attach the GPS Tx and Rx wires to pins 4 & 5 on the Moteino
    
    The data needs to low out of the GPS into pin ?? and out of the Moteino pin ?? to the GPS.
    
    You're done.
    
    Software
    
    I used the Arduino build enviroment. It is available to download here
    www.arduino.cc
    
    In addition you need the following libraries
    TinyGPSPlus - This is installable through the library manager
    RFM69 - Again available through download manager.
    
    Setup / Configuration
    After building and uploading the source you can setup your new tracker by accessing through the virtual serial port. 
    Default access is 15200Kb
    
    
    
    
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

    
