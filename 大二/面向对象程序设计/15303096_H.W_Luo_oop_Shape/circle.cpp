#include <iostream>
using namespace std;

#include "circle.h"

Circle::Circle(double r){
    setR(r);
}

Circle::~Circle(){
}

void Circle::setR(double r){
    radius=r;
}

double Circle::getR(){
    return radius;
}

double Circle::area(){
    return 3.14159*radius*radius;
}

double Circle::circum(){
    return 3.14159*radius*2;
}

void Circle::info(){
    cout<<"===================="<<endl
        <<"Circle"<<endl
        <<"Radius:"<<radius<<endl
        <<"Area:"<<this->area()<<endl
        <<"Circumference:"<<this->circum()<<endl;
}
