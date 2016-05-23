#include "wheels.h"

/*
TODO: Try reducing unjam sample size and adding our unjamCoefficient rather than multiplying it.
      Remove our moveSpeed definition and make it an actual variable so our movement speed can be a little more dynamic.
      Create a timer class to replace all of our currentMillis and previousMillis delay replacement tricks.
*/

///////////////////////////////////////////
////Constructor
///////////////////////////////////////////

Wheels::Wheels() : AFMS(Adafruit_MotorShield()), RightMotor(AFMS.getMotor(RightMotorTerminal)), LeftMotor(AFMS.getMotor(LeftMotorTerminal))
{
	
	// AFMS = Adafruit_MotorShield();
	// RightMotor = AFMS.getMotor(RightMotorTerminal);
	// LeftMotor = AFMS.getMotor(LeftMotorTerminal);

    // AFMS.begin(); //Begin broadcasting / recieving information on the motorshield

	// Serial.begin(9600);
    // Serial.println("QQCK1234567890");
    // Serial.println("ASS");
}

//If we try to do AFMS.being in the constructor we crash since the AFMS object is not actually constructed until after the Wheels constructor finishes.
//We need to call it seperately or else it crashes.
void Wheels::Start()
{
	AFMS.begin();
}
///////////////////////////////////////////
////Private Functions
///////////////////////////////////////////

//This function throttles any unexpected values thrown into our other functions because the library
//we use expects values between 0-255 and does odd things outside of this range.
int Wheels::RestrictSpeed(int Speed)
{
    if (Speed >= 255)
    {
        Speed = 255;
    }
    else if (Speed <= 0)
    {
        Speed = 0;
    }

    return Speed;
}

// //Meant to be used with our PathCorrection function, given that we use the delta between angles
// //as our turn speed we want to restrict them a bit. This allows for much more predictable turns.
// int Wheels::RestrictTurnSpeed(int Speed)
// {
//     if (Speed >= TurnUpperLimit)
//         return TurnUpperLimit;
//     else if (Speed <= TurnLowerLimit)
//         return TurnLowerLimit;
//     else
//         return Speed;
// }

///////////////////////////////////////////
//Here we have access to the definitions:
//FORWARD = 1
//BACKWARD = -1
//RELEASE = 0


//The most basic control for the left wheel, speed and direction of spin
void Wheels::LeftWheel(int Speed, int Direction)
{
    Speed = RestrictSpeed(Speed);

    LeftMotor->run(Direction);
    LeftMotor->setSpeed(Speed);
}

//The most basic control for the right wheel, speed and direction of spin
void Wheels::RightWheel(int Speed, int Direction)
{
    Speed = RestrictSpeed(Speed);

    RightMotor->run(Direction);
    RightMotor->setSpeed(Speed);
}

///////////////////////////////////////////

//If we're stuck then continually increase the constant sent to the wheels until we start moving again.
// void Wheels::UnjamWheels()
// {
//     UnjamCounter++;
//     if (UnjamCounter >= StuckSampleSize)
//     {
//         UnjamMultiplier *= 2;
//         UnjamCounter = 0;
//     }
// }

///////////////////////////////////////////

////If our car drifts +/- AngleMargin from it's expected / locked angle, then stop, and turn the car back
////towards it's expected path.
//void Wheels::PathCorrection(float CurrentAngle, float PreviousAngle, int &StoredAngle)
//{
//    int CurrentAngleRounded = (CurrentAngle / 1);
//    int PreviousAngleRounded = (PreviousAngle / 1);

//    int YawDelta = 0;

//    //The bias for our gyroscope is:
//    //Negative when turning CCW
//    //Positive when turning CW
//    //180 is inclusive, -180 is not.

//    //If our current angle is less than our expected angle, we must be drifing left.
//    //Turn right.
//    if (CurrentAngleRounded < (StoredAngle - AngleMargin))
//    {
//        YawDelta = StoredAngle - CurrentAngleRounded;
//        YawDelta = RestrictTurnSpeed(abs(YawDelta));

//        Stop();
//        TurnRight(YawDelta * UnjamMultiplier);

//        MovingForward = false;

//        //Serial.print(StoredAngle);
//        //Serial.print("\t");
//        //Serial.print(CurrentAngleRounded);
//        //Serial.println(" RIGHT");
//    }

//    //If our current angle is greater than our expected angle, we must be drifing right.
//    //Turn left.
//    if (CurrentAngleRounded > (StoredAngle + AngleMargin))
//    {
//        YawDelta = StoredAngle - CurrentAngleRounded;
//        YawDelta = RestrictTurnSpeed(abs(YawDelta));

//        Stop();
//        TurnLeft(YawDelta * UnjamMultiplier);

//        MovingForward = false;

//        //Serial.print(StoredAngle);
//        //Serial.print("\t");
//        //Serial.print(CurrentAngleRounded);
//        //Serial.println(" LEFT");
//    }


//    //If our current angle is the same as our expected angle, we must be going straight.
//    //Keep going straight.
//    if (StoredAngle == CurrentAngleRounded)
//    {
//        Stop();
//        Forward(MoveSpeed);

//        MovingForward = true;
//        UnjamMultiplier = 1;

//        //Serial.print(StoredAngle);
//        //Serial.print("\t");
//        //Serial.print(CurrentAngleRounded);
//        //Serial.println(" WE ON COURSE");
//    }
//}

/////////////////////////////////////////////

////We use this to convert a real measurement (mm) to an approximate movement cycle for the Arduino
//int Wheels::TravelDistance(int Speed, int MillimetersInput)
//{
//    if (MillimetersInput <= 0)
//        return 0;

//    //The formula used here is:
//    //DistanceUnits * Speed * Constant = mmTraveled
//    //
//    //DistanceUnits is the counter that is incremented as the car moves forward
//    //Speed the the MoveSpeed constant
//    //Constant is the constant derived from observations of moving specific amounts of units
//    //mmTraveled is the millimeters traveled relative to the speed and units given

//    int ReturnMe = ((MillimetersInput / (MillimeterConstant * Speed)) + 1);
//    return ReturnMe;
//}

///////////////////////////////////////////
////Public Functions
///////////////////////////////////////////

//Basic turns with a center axis, spin the wheel in opposite directions at a desired speed

void Wheels::TurnRight(int Speed)
{
    // Serial.println("TURN RIGHT");
    RightWheel(Speed, BACKWARD);
    LeftWheel(Speed, FORWARD);
}

void Wheels::TurnLeft(int Speed)
{
    // Serial.println("TURN LEFT");
    RightWheel(Speed, FORWARD);
    LeftWheel(Speed, BACKWARD);
}

///////////////////////////////////////////
//Basic movement options, move the wheels in the same direction at a desired speed

void Wheels::Forward(int Speed)
{
    // Serial.println("FORWARDS");
    RightWheel(Speed, FORWARD);
    LeftWheel(Speed, FORWARD);
}

void Wheels::Backward(int Speed)
{
    // Serial.println("BACKWARDS");
    RightWheel(Speed, BACKWARD);
    LeftWheel(Speed, BACKWARD);
}

///////////////////////////////////////////

//Halts all voltage sent to the wheels (Doesn't account for leftover momentum)
void Wheels::Stop()
{
	// Serial.println("STOPPPP");
    RightWheel(0, RELEASE);
    LeftWheel(0, RELEASE);
}

//Accounts for leftover momentum, but only seems to work at around 80 speed
// void Wheels::DeadStop()
// {
//     //This all only seems to work well at speeds around 80
//     Backward(100);

//     //Add a timer here using the Timer object.

//     Stop();
// }

///////////////////////////////////////////

//int Wheels::Go(int Angle, int mmDistance)
//{
//    int GoStoredYaw = FindNewAngle(MPU.StoredYawRounded, Angle);

//    int UnitsToTravel = TravelDistance(mmDistance, MoveSpeed);

//    //While the gyroscope is stabalizing print out the status (We can't do anything else until it's stabalized)
//    if (!(Stabalized))
//    {
//        MPU.PrintCalibrationStatus();
//        Stabalized = MPU.IsStabalized();
//    }

//    if ((Stabalized) && (!MovingForward) && (MPU.PreviousAngleComparison()))
//    {
//        UnjamWheels();
//    }

//    //Here is our basic path correction algorithm, turn too much one way or the other and we correct it
//    if (Stabalized)
//    {
//        PathCorrection(MPU.CurrentYaw, MPU.PreviousYaw, GoStoredYaw);
//    }

//    //If we're stable, still have some distance to move, and we're actually moving forward, increase DistanceTraveled
//    if (Stabalized && (DistanceTraveled <= UnitsToTravel) && MovingForward)
//    {
//        DistanceTraveled++;
//    }

//    //If we've moved the expected distance then we stop and show that we aren't moving forward anymore.
//    //Additionally, we change our DistanceTraveled to 0 for our next step in the travel plan.
//    //This function returns a 1 just so we can build a super simple queue for nodes of travel.
//    //(If we didn't move as far as we wanted, we return 0, meaning we don't move to the next step of movement)
//    if (DistanceTraveled >= UnitsToTravel)
//    {
//        if (MovingForward)
//        {
//            DeadStop();
//            MovingForward = false;
//        }
//        else
//        {
//            Stop();
//        }
//        DistanceTraveled = 0;
//        return 1;
//    }
//    return 0;
//}

//int Wheels::GoXY(int XPos, int YPos)
//{
//    double Angle = atan(Y / X);
//    uint8_t mmDistance = sqrt((X*X) + (Y*Y));

//    return Go(Angle, mmDistance);
//}

////////////////////////////////////

double Wheels::RestrictSpeed(double Speed)
{
    if (Speed >= 255)
    {
        Speed = 255;
    }
    else if (Speed <= -255)
    {
        Speed = -255;
    }

    return Speed;
}


void Wheels::LeftWheel(double Speed)
{
	Speed = RestrictSpeed(Speed);

	int Direction = 0;

	if (Speed > 0)
	{
		Direction = 1;
	}
	else if (Speed < 0)
	{
		Direction = -1;
	}
	else
	{
		Direction = 0;
	}

    LeftMotor->run(Direction);
    LeftMotor->setSpeed(Speed);	
}

void Wheels::RightWheel(double Speed)
{
	Speed = RestrictSpeed(Speed);

	int Direction = 0;

	if (Speed > 0)
	{
		Direction = 1;
	}
	else if (Speed < 0)
	{
		Direction = -1;
	}
	else
	{
		Direction = 0;
	}

    RightMotor->run(Direction);
    RightMotor->setSpeed(Speed);
}