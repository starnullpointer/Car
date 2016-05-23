#ifndef POINT_H
#define POINT_H
// #include <cmath.h>
// #include <ostream>
#include <Arduino.h>
using namespace std;

class Point
{
public:
    Point();
    Point(double X,double Y);
    Point(const Point& P);
    double GetX();
    double GetY();
    void SetX(double X);
    void SetY(double Y);
    Point operator =(Point P);
    Point operator +(Point P);
    Point operator +=(Point P);
    Point operator -(Point P);
    Point operator *(double value);
    double Distance(Point P);
    double Slope(Point P);
    bool isSame(Point P);
    // friend ostream& operator<<(ostream& outs,Point print){
        // outs<<"("<<print.GetX()<<","<<print.GetY()<<")"<<"\t";
    // }
    friend bool operator==( Point LHS, Point RHS){
        if(LHS.GetX()==RHS.GetX()){
            if(LHS.GetY()==RHS.GetY()){
                return true;
            }
        }
        return false;
    }
private:
    double _x;
    double _y;
};

#endif // POINT_H
