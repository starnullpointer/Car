#ifndef WHEELS_H
#define WHEELS_H

//#include <Arduino>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
//#include <gyro.h>

class Wheels
{
public:
//    friend class Gyro;

    Wheels();
    void Start();

    void TurnRight(int Speed);
    void TurnLeft(int Speed);
    void Forward(int Speed);
    void Backward(int Speed);
    void Stop();
    // void DeadStop(); //Inconsistent until we get real acceleration values. Maybe even private? It's pretty hacky, probably just rewrite entirely.

//    int Go(int Angle, int mmDistance);
//    int GoXY(int XPos, int YPos);

// private:
    // //Which terminals our motors are connected to
    #define RightMotorTerminal 1
    #define LeftMotorTerminal 2

    // #define MillimeterConstant 0.018375 //The observed constant for converting millimeters traveled to "unit" of travel. (The unit is 1 tick of the loop() cycle)

    // #define StuckSampleSize 250 //A value of around 500 is the standard (Use lower if you're impatient)

    // #define AngleMargin 1 //The margin of error allowed in our path correction

    // #define MoveSpeed 180 //The speed constant of our car, most of these functions were designed with a speed of 80 in mind.

    // //Arbitrary numbers chosen to limit the speed at which our car turns (No other values have been tested)
    // #define TurnUpperLimit 80 //Prototype 2: 80
    // #define TurnLowerLimit 60 //Prototype 2: 32

    // bool Stabalized = false;  //Keeps track of whether the gyroscope has stabalized, is the gateway flag for almost all the functions in higher level movement

    // bool MovingForward = true; //How we keep track of whether our car is moving (As of now it's strictly assumed that this will always be correct)
    // int UnjamMultiplier = 1; //A multiplier for movement, when we are stuck this value increases until we aren't stuck anymore

    // int DistanceTraveled = 0; //A counter to keep track of how long we've been moving forward
    // int StabalizationCounter = 0; //A counter to keep track of how many times the gyroscope has been stable when checked against it's angle from the previous loop() cycle
    // int UnjamCounter = 0; //A counter to keep track of how many loop() cycles we haven't moved we we're supposed to be turning

    //////////////////////////////////////////////

    Adafruit_MotorShield AFMS; //Initialize the motorshield so the Arduino knows what it's talking to

    Adafruit_DCMotor *RightMotor; //Initialize the right motor on it's appropriate terminal
    Adafruit_DCMotor *LeftMotor; //Initialize the left motor on it's appropriate terminal

    //////////////////////////////////////////////

//    Gyro MPU;

    //////////////////////////////////////////////

    int RestrictSpeed(int Speed);
    // int RestrictTurnSpeed(int Speed);
    void LeftWheel(int Speed, int Direction);
    void RightWheel(int Speed, int Direction);
    double RestrictSpeed(double Speed);
    void LeftWheel(double Speed);
    void RightWheel(double Speed);
    // void UnjamWheels();
    // void PathCorrection(float CurrentAngle, float PreviousAngle, int &StoredAngle); //We need a friended Gyro class for this to be not terrible.
    // int TravelDistance(int Speed, int MillimetersInput);
};

#endif // WHEELS_H
