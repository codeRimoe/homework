#include <iostream>
using namespace std;

#include "square.h"

Square::Square(double r){
    setA(r);
}

Square::~Square(){
}

void Square::setA(double r){
    a=r;
}

double Square::getA(){
    return a;
}

double Square::area(){
    return a*a;
}

double Square::circum(){
    return a*4;
}

void Square::info(){
    cout<<"===================="<<endl
        <<"Square"<<endl
        <<"Side:"<<a<<endl
        <<"Area:"<<this->area()<<endl
        <<"Circumference:"<<this->circum()<<endl;
}
