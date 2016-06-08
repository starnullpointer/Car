#ifndef CARCOMMUNICATION
#define CARCOMMUNICATION
#include "../CarProjCommon/CarProjCommon.h"
#include "../PID/point.h"
#include "../CommunicationFuncs/CommunicationFuncs.h"
#include <Adafruit_WINC1500Client.h>


class CarCommunication
{
public:
	CarCommunication();

	void Init();
	Point getCurrentPos();
	Point getDest();
	Point getPrevPos();
	int getCmdLeft();
	int getCmdRight();

	CommunicationStatus UpdatePosAndDest();
	CommunicationStatus UpdateDest();
	CommunicationStatus UpdateCmd();

	CommunicationStatus ReconnectWifi();
	CommunicationStatus ReconnectServer();

private:
	Point currentPos;
	Point prevPos;
	Point currentDest;
	Adafruit_WINC1500Client client;

	int cmdLeft;
	int cmdRight;

	CommunicationStatus CheckConnectionsStatus();
	CommunicationStatus LightIsOn();
	bool ReachedDest();
};

#endif // CARCOMMUNICATION

