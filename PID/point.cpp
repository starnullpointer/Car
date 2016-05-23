#include "point.h"

Point::Point()
{
    _x=0;
    _y=0;
}

Point::Point(double X,double Y)
{
    _x=X;
    _y=Y;
}

Point::Point(const Point& P)
{
    _x=P._x;
    _y=P._y;
}

double Point::GetX()
{
    return _x;
}

double Point::GetY()
{
    return _y;
}

void Point::SetX(double X)
{
    _x=X;
}

void Point::SetY(double Y)
{
    _y=Y;
}

Point Point::operator =(Point P)
{
    _x=P.GetX();
    _y=P.GetY();
    return *this;
}

Point Point::operator +(Point P)
{
    Point result;
    result.SetX(P.GetX()+_x);
    result.SetY(P.GetY()+_y);
    return result;
}

Point Point::operator +=(Point P)
{
    _x += P.GetX();
    _y += P.GetY();
    return *this;
}

Point Point::operator -(Point P)
{
    Point result;
    result.SetX(_x-P.GetX());
    result.SetY(_y-P.GetY());
    return result;
}

Point Point::operator *(double value)
{
    Point result;
    result.SetX(_x*value);
    result.SetY(_y*value);
    return result;
}

double Point::Distance(Point P)
{
    double distance=0;
    distance=sqrt((_x-P._x)*(_x-P._x)+(_y-P._y)*(_y-P._y));
    return distance;
}

double Point::Slope(Point P)
{
    double slope=0;
    slope=(P.GetY()-_y)/(P.GetX()-_x);
    return slope;
}

bool Point::isSame(Point P)
{
    if(_x==P._x && _y==P._y){
        return true;
    }
    else{
        return false;
    }
}
