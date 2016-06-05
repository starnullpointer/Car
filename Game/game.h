#ifndef GAME
#define GAME
#include "../PID/point.h"
#include "../PID/pid.h"
#include "../Wheels/wheels.h"
#include "../CarProjCommon/CarProjCommon.h"
#include "../CommunicationFuncs/CommunicationFuncs.h"
#include "../CarCommunication/CarCommunication.h"

class Game
{
public:
	Game();
	Game(double base,double carSize);
	void Init();
	//base functions for moving
	void Move(double Left_Speed,double Right_Speed);
	void GoAhead(int Speed);
	void GoBack(int Speed);
	void Turn_Left(int Speed);
	void Turn_Right(int Speed);
	void Stop_Car();

	//communication function
	void Update();
	void UpdateDataFromCommunication();

	//access functions
	double GetMultipler();
	Point GetCurrentPos();
	Point GetDestPos();
	double GetTime();

private:
	//to initial classes
	Wheels wheels;	//for motions
	CarCommunication CarCom;	//for communications
	CommunicationStatus com_status;

	//data
	Point currentPos;
	Point previousPos;
	Point destPos;
	double time;
	double multipler;
	double carLength;
};

#endif // GAME

