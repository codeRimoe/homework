#ifndef SQUARE_H
#define SQUARE_H

#include "shape.h"

class Square:public Shape{
public:
    Square(double=0.0);
    ~Square();
    void setA(double=0.0);
    double getA();
    virtual double area();
    virtual double circum();
    virtual void info();
private:
    double a;
};

#endif
