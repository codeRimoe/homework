#include <iostream>
using namespace std;

#include "gis.h"

Gis::Gis(int a,int b,int c,int d,int e,int f)
:Compulsory(a,b,c,d){
    setSpa(e),setRS(f);
}

Gis::~Gis(){
}

void Gis::setSpa(int a){
    spa=a;
}

void Gis::setRS(int a){
    RS=a;
}

int Gis::getSpa(){
    return spa;
}

int Gis::getRS(){
    return RS;
}

int Gis::sum(){
    return Compulsory::sum()+spa+RS;
}

double Gis::avg(){
    return sum()/5.0;
}

void Gis::disp(){
    Compulsory::disp();
    cout<<"===================="<<endl
        <<"Professional Course"<<endl
        <<"Spatial Analysis:"<<spa<<endl
        <<"Remote Sencing:"<<RS<<endl
        <<"===================="<<endl
        <<"Sum:"<<sum()<<endl
        <<"Avg:"<<avg()<<endl;
}
