#include "CarCommunication.h"

CarCommunication::CarCommunication()
{

}

void CarCommunication::Init()
{
    Setup_Wifi_and_Server(client);
    currentDest.SetX(900);
    currentDest.SetY(600);
}

Point CarCommunication::getCurrentPos()
{
    return currentPos;
}

Point CarCommunication::getDest()
{
    return currentDest;
}

Point CarCommunication::getPrevPos()
{
    return prevPos;
}

CommunicationStatus CarCommunication::UpdatePosAndDest()
{
    CommunicationStatus status=CheckConnectionsStatus();
    if(status==ComSucess){

        Send(CAR_CON_REQ_POS,client);
        WaitForUpdate(client);
        Packet p=GetMessage(client);

        if(strCmp(p.Command,COMM_TURN_LIGHT_ON)){
            //turn light on
            status=LightIsOn();
            if(status==ComSucess){
                // if getting our new pos worked out, we need to see if
                // we need a new dest
                if(ReachedDest()) {
                    Serial.println("Destination Reached");
                    status=UpdateDest(); //get new dest if reaced old dest     
                    status=ComError;
                }
                else {
                    Serial.println("Havn't arrived yet.");
                }
            }
            return status;
        }
        else {
            Serial.print("Incorrect Message: "); Serial.println(p.Message);
            return ComError;
        }
    }

    return status;
}

CommunicationStatus CarCommunication::UpdateDest()
{
    CommunicationStatus status=CheckConnectionsStatus();
    if(status==ComSucess){
        Send(CAR_CON_REQ_DEST, client);
        WaitForUpdate(client);
        Packet p = GetMessage(client);
        if(strCmp(p.Command, COMM_YOUR_DEST)){
            Serial.print("new Destination: ");Serial.print(p.Other[0]);Serial.print(p.Other[1]);
            currentDest.SetX(atoi(p.Other[0]));
            currentDest.SetY(atoi(p.Other[1]));
        }
    }
    return status;
}

CommunicationStatus CarCommunication::ReconnectWifi()
{
    ConnectWifi();
    // return val?
}

CommunicationStatus CarCommunication::ReconnectServer()
{
    ConnectServer(client);
    // return val?
}

CommunicationStatus CarCommunication::CheckConnectionsStatus()
{
    if(!GetWifiConnected()) //need check wifi first b/c need wifi to connect to server
    {
        return ComWifiDisconnect;
    } 
    if(!client)
    {
        return ComServerDisconnect;
    }
    return ComSucess;
}

CommunicationStatus CarCommunication::LightIsOn()
{
    // todo: light functionality. remember to turn light off if errors occur
    CommunicationStatus status=CheckConnectionsStatus();
    if(status==ComSucess){
        Send(CAR_CON_LIGHT_ON, client);
        WaitForUpdate(client);
        Packet p=GetMessage(client);

        if(strCmp(p.Command,COMM_YOUR_POS)){
            prevPos=currentPos;
            currentPos.SetX(atoi(p.Other[0]));
            currentPos.SetY(atoi(p.Other[1]));
            //maybe need other return for bad pos?
            return ComSucess;
        } else {
            Serial.print("Incorrect Message: "); Serial.println(p.Message);
            return ComError;
        }
    }   
    return status;
}

bool CarCommunication::ReachedDest()
{
  if(currentPos.Distance(currentDest)<=10)
    return true;
  return false;
}
