#include "pid.h"

PID::PID()
{
    P_GAIN=P_GAIN_DEFAULT;
    D_GAIN=D_GAIN_DEFAULT;
    I_GAIN=I_GAIN_DEFAULT;
}

PID::PID(Point inputVelocity, double carLength, Point currentPos)
{
    P_GAIN=P_GAIN_DEFAULT;
    D_GAIN=D_GAIN_DEFAULT;
    I_GAIN=I_GAIN_DEFAULT;

    previousVelocity = errorVelocity;
    errorVelocity = inputVelocity;
    velocitySet += errorVelocity;
    velocityCount = 1;

    Carlength=carLength;
    currentP=currentPos;
}

void PID::SetP_GAIN(double p)
{
    P_GAIN=p;
}

void PID::SetD_GAIN(double d)
{
    D_GAIN=d;
}

void PID::SetI_GAIN(double i)
{
    I_GAIN=i;
}

void PID::IncreP_GAIN(double incre)
{
    P_GAIN+=incre;
}

void PID::IncreD_GAIN(double incre)
{
    D_GAIN+=incre;
}

void PID::IncreI_GAIN(double incre)
{
    I_GAIN+=incre;
}

// string PID::GetInformation()
// {
//     string message;
//     string convert;
//     convert=to_string(P_GAIN);
//     message=string("P_GAIN: ")+convert+string("\n");

//     convert=to_string(pro.GetX());
//     message=message+string("Proportional: (")+convert+string(",");
//     convert=to_string(pro.GetY());
//     message=message+convert+string(")")+string("\n");

//     convert=to_string(D_GAIN);
//     message=message+string("D_GAIN: ")+convert+string("\n");

//     convert=to_string(deri.GetX());
//     message=message+string("Derivative: (")+convert+string(",");
//     convert=to_string(deri.GetY());
//     message=message+convert+string(")")+string("\n");

//     convert=to_string(I_GAIN);
//     message=message+string("I_GAIN: ")+convert+string("\n");

//     convert=to_string(inte.GetX());
//     message=message+string("Integral: (")+convert+string(",");
//     convert=to_string(inte.GetY());
//     message=message+convert+string(")")+string("\n");

//     return message;
// }

void PID::Input(Point inputVelocity)
{
    previousVelocity = errorVelocity;
    errorVelocity = inputVelocity;
    velocitySet += errorVelocity;
    velocityCount++;
}

void PID::Clean_velocitySet()
{
    //We don't need to set errorVelocity or previousVelocity to 0 since we'll
    //only clean our set when they're both already 0 anyways.
    Point empty;
    velocitySet = empty;
    velocityCount = 0;
}

Point PID::Proportional()
{
    Point proportional;
    proportional=errorVelocity*P_GAIN;
    pro=proportional;
    return pro;
}

Point PID::Derivative()
{
    Point difference;
    
    if(velocityCount < 2){
        deri.SetX(0);
        deri.SetY(0);
    }
    else{
        difference = (errorVelocity - previousVelocity);
        Point derivative=difference*D_GAIN;
        deri=derivative;
    }
    return deri;
}

Point PID::Integral()
{
    Point integral = velocitySet*I_GAIN;
    inte = integral;
    return inte;
}

Point PID::Calculate_AdjustPID()
{
    Point pro=Proportional();
    Point deri=Derivative();
    Point integral=Integral();
    Point pid=pro+deri+integral;
    return pid;
}

void PID::Calculate_output()
{
    Point adjust=Calculate_AdjustPID();
    outputVelocity=errorVelocity+adjust;
}

Point PID::GetOutputVelocity()
{
    return outputVelocity;
}

Point PID::GetPID(Point inputVelocity)
{
    Input(inputVelocity);
    Calculate_output();
    return outputVelocity;
}
Point PID::GetPIDVelocity()
{
    Calculate_output();
    return outputVelocity;
}

double PID::GetRatioVelocity()
{
    Calculate_output();
    
    //We need to ensure that our previousVelocity is actually set.
    ratioVoltage.CalculateRatio(Carlength,previousVelocity,outputVelocity,currentP);

    double ratio=ratioVoltage.GetRatio();
    
    return ratio;
}

Point PID::operator ()(Point inputVelocity)
{
    Input(inputVelocity);
    Calculate_output();
    return outputVelocity;
}
