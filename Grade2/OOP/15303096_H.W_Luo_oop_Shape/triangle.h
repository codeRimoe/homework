#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "shape.h"

class Triangle:public Shape{
public:
    Triangle(double=0.0,double=0.0,double=0.0);
    ~Triangle();
    void setA(double=0.0);
    void setB(double=0.0);
    void setC(double=0.0);
    double getA();
    double getB();
    double getC();
    virtual double area();
    virtual double circum();
    virtual void info();
private:
    double a,b,c;
};

#endif
