#include <SPI.h>
#include "PID/point.h"
#include "Wheels/wheels.h"
#include "CarProjCommon/CarProjCommon.h"
#include "CommunicationFuncs/CommunicationFuncs.h"
#include "CarCommunication/CarCommunication.h"

CarCommunication CarCom;
CommunicationStatus com_status;

void setup()
{
  Serial.begin(9600);
  delay(2000);
  Serial.println("hello");
  Wire.begin();
  CarCom.Init();
  delay(1000);
}

void loop()
{
  com_status = CarCom.UpdatePosAndDest();
  
  if (com_status == ComSucess){
    // move car
  }
  else if (com_status == ComWifiDisconnect){
    // stop car...
    // reconnect to wifi & server
    CarCom.ReconnectWifi();
    CarCom.ReconnectServer();
  }
  else if (com_status == ComServerDisconnect) {
    // stop car...
    // reconnect to server
    CarCom.ReconnectServer();
  }
  else {
    // stop car...
    // other error...
  }
}

