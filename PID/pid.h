#ifndef PID_H
#define PID_H

#include "point.h"
#include "constants.h"
#include "ratio.h"

class PID
{
public:
    PID();
    //inputVelocity = DestPos - CurrentPos;!!!!!!
    PID(Point inputVelocity,double carLength,Point currentPos);
    Point GetPID(Point inputVelocity);
    Point GetPIDVelocity();
    double GetRatioVelocity();
    Point operator ()(Point inputVelocity);
    void Clean_velocitySet();
    void SetP_GAIN(double p);
    void SetD_GAIN(double d);
    void SetI_GAIN(double i);
    void IncreP_GAIN(double incre);
    void IncreD_GAIN(double incre);
    void IncreI_GAIN(double incre);
    void Input(Point inputVelocity);
    // string GetInformation();
private:
    //private functions:

    void Calculate_output();
    Point GetOutputVelocity();
    Point Proportional();
    Point Derivative();
    Point Integral();
    Point Calculate_AdjustPID();

    //private variables:
    Point errorVelocity;    //the inputVelocity
    Point previousVelocity;

    Point velocitySet;
    unsigned int velocityCount = 0;

    Point pro;  //proportional part
    Point deri; //derivative part
    Point inte; //integral part
    Point outputVelocity;       //the total of PID
    double Carlength;   //used for the ratio
    Ratio ratioVoltage;
    Point currentP; //used for the ratio

    //all the GAIN constants
    double P_GAIN;
    double D_GAIN;
    double I_GAIN;
};

#endif // PID_H
