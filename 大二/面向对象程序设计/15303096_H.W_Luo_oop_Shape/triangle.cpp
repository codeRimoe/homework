#include <iostream>
#include <cmath>
using namespace std;

#include "triangle.h"

Triangle::Triangle(double aa,double bb,double cc){
    setA(aa),setB(bb),setC(cc);
}

Triangle::~Triangle(){
}

void Triangle::setA(double r){
    a=r;
}

void Triangle::setB(double r){
    b=r;
}

void Triangle::setC(double r){
    c=r;
}

double Triangle::getA(){
    return a;
}

double Triangle::getB(){
    return b;
}

double Triangle::getC(){
    return c;
}

double Triangle::area(){
	double s=0,p=0;
	p=this->circum();
	if(p==-1)return -1;
	p/=2;
	s=p*(p-a)*(p-b)*(p-c);
	s=sqrt(s);
    return s;
}

double Triangle::circum(){
	double k=max(max(a,b),c),lc=a+b+c;
	if(a+b+c-k<=k)return -1;
    return lc;
}

void Triangle::info(){
    cout<<"===================="<<endl
        <<"Triangle"<<endl
        <<"Side:"<<a<<","<<b<<","<<c<<endl
        <<"Area:"<<this->area()<<endl
        <<"Circumference:"<<this->circum()<<endl;
}
