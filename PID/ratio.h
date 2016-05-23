#ifndef RATIO_H
#define RATIO_H
// #include <iostream>
// using namespace std;
#include "point.h"
// #include <cmath>

class Ratio
{
public:
    Ratio();
    void CalculateRatio(double carLength,Point lastVelocity,Point currentVelocity,Point currentPos);
    double GetRatio();
private:
    //private functions:
    double Slope(Point Velocity);
    double Slope_Perpendicular(double slope);
    Point GetPoint(double slope, double l, Point midPoint);

    //private variables:
    double ratio;
};

#endif // RATIO_H
