#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

class Circle:public Shape{
public:
    Circle(double=0.0);
    ~Circle();
    void setR(double=0.0);
    double getR();
    virtual double area();
    virtual double circum();
    virtual void info();
private:
    double radius;
};

#endif
