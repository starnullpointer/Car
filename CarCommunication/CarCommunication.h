#ifndef CARCOMMUNICATION
#define CARCOMMUNICATION
#include "../CommunicationFuncs/CommunicationFuncs.h"
#include "../PID/point.h"
#include "../constants.h"
#include "../messageblock/packet.h"
#include <Adafruit_WINC1500Client.h>


class CarCommunication
{
public:
	CarCommunication();

	void Init();
	Point getCurrentPos();
	Point getDest();

	CommunicationStatus UpdatePosAndDest();
	CommunicationStatus UpdateDest();

	CommunicationStatus ReconnectWifi();
	CommunicationStatus ReconnectServer();

private:
	Point currentPos;
	Point prevPos;
	Point currentDest;
	Adafruit_WINC1500Client client;

	CommunicationStatus CheckConnectionsStatus();
	CommunicationStatus LightIsOn();
	bool ReachedDest();

};

#endif // CARCOMMUNICATION

