#include "ratio.h"

Ratio::Ratio()
{
    ratio=0;
}

void Ratio::CalculateRatio(double carLength,Point lastVelocity,Point currentVelocity,Point currentPos)
{
    double slope_perpendicular_last=0,slope_last=0;
    Point P1_last,P2_last;
    Point midPoint_last=currentPos;
    if(lastVelocity.GetY()==0){
        //case: the slope of this is 0, so perpendicular slope will be infinite
            //so we know the perpendicular line will be vertical, so directly find two points
        P1_last=midPoint_last+Point(0,carLength/2);
        P2_last=midPoint_last+Point(0,-carLength/2);
    }
    else{
        if(lastVelocity.GetX()==0){
            //case: the slope of this is infinite, so perpendicular slope will be 0
            slope_perpendicular_last=0;
        }
        else{
            slope_last=Slope(lastVelocity);
            slope_perpendicular_last=Slope_Perpendicular(slope_last);
        }
        P1_last=GetPoint(slope_perpendicular_last,carLength/2,midPoint_last);
        P2_last=GetPoint(slope_perpendicular_last,-carLength/2,midPoint_last);
    }
    // cout<<"lastVelocity: "<<lastVelocity<<endl;
    // cout<<"slope_last: "<<slope_last<<endl;
    // cout<<"slope_perpendicular_last: "<<slope_perpendicular_last<<endl;
    // cout<<"P1_last: "<<P1_last<<endl;
    // cout<<"P2_last: "<<P2_last<<endl;
    double slope_current=0,slope_perpendicular_current=0;
    Point P1_current,P2_current;
    Point midPoint_current=currentPos+currentVelocity;
    if(currentVelocity.GetY()==0){
        //case: the slope of this is 0, so perpendicular slope will be infinite
            //so we know the perpendicular line will be vertical, so directly find two points
        P1_current=midPoint_current+Point(0,carLength/2);
        P2_current=midPoint_current+Point(0,-carLength/2);
    }
    else{
        if(currentVelocity.GetX()==0){
            //case: the slope of this is infinite, so perpendicular slope will be 0
            slope_perpendicular_current=0;
        }
        else{
            slope_current=Slope(currentVelocity);
            slope_perpendicular_current=
                    Slope_Perpendicular(slope_current);
        }
        P1_current=GetPoint(slope_perpendicular_current,carLength/2,midPoint_current);
        P2_current=GetPoint(slope_perpendicular_current,-carLength/2,midPoint_current);
    }
    // cout<<"currentVelocity: "<<currentVelocity<<endl;
    // cout<<"slope_current: "<<slope_current<<endl;
    // cout<<"slope_perpendicular_current: "<<slope_perpendicular_current<<endl;
    // cout<<"P1_current: "<<P1_current<<endl;
    // cout<<"P2_current: "<<P2_current<<endl;
    double distance_1=P1_current.Distance(P1_last);
    double distance_2=P2_current.Distance(P2_last);
    // cout<<"distance_1: "<<distance_1<<endl;
    // cout<<"distance_2: "<<distance_2<<endl;
    ratio=distance_2/distance_1;
}

double Ratio::GetRatio()
{
    return ratio;
}

double Ratio::Slope(Point Velocity)
{
    Point origin(0,0);
    double slope=Velocity.Slope(origin);
    return slope;
}

double Ratio::Slope_Perpendicular(double slope)
{
    double perpendicular_slope=-1/slope;
    return perpendicular_slope;
}

Point Ratio::GetPoint(double slope,double l,Point midPoint)
{
    double angle=atan(slope);
    double x=l*cos(angle);
    double y=l*sin(angle);
    Point increPoint(x,y);
    Point point=midPoint+increPoint;
    return point;
}
