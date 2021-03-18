#include "Position.h"

Position::Position(double x,double y):
    _x{x},
    _y{y}
{
}
void Position::setX(double val){_x=val;}
void Position::setY(double val){_y=val;}
void Position::setPosition(double x,double y){
    _x=x;
    _y=y;
}
double Position::getX()const{return _x;}
double Position::getY()const{return _y;}
double Position::getDistance(const Position& p)const{
    return sqrt(((_x-p.getX())*(_x-p.getX()))
         +
         ((_y-p.getY())*(_y-p.getY()))
        );


   /* double x =  p.getX() - _x;
    double y =  p.getY() - y;
    double distance = sqrt(x*x + y*y);
    return distance;*/
}
double Position::getDistance(int x,int y)const{
    double xx=_x-x;
    double yy= _y-y;
    double distance= sqrt(xx*xx + yy*yy);
    return distance;
}
Position::~Position()
{
    //dtor
}
