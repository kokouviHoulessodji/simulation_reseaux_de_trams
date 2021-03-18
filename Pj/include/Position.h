#ifndef POSITION_H
#define POSITION_H
#include<cmath>

class Position
{
    public:
        Position(double x,double y);
        virtual ~Position();
        double getX()const;
        double getY()const;
        void setX(double);
        void setY(double);
        void setPosition(double x,double y);
        double getDistance(const Position& p)const;
        double getDistance(int x,int y)const;

    protected:

    private:
        double _x;
        double _y;
};

#endif // POSITION_H
