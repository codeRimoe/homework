#include <iostream>
using namespace std;

#include "accounting.h"

Accounting::Accounting(int a,int b,int c,int d,int e,int f)
:Compulsory(a,b,c,d){
    setAcc(e),setEco(f);
}

Accounting::~Accounting(){
}

void Accounting::setAcc(int a){
    acc=a;
}

void Accounting::setEco(int a){
    eco=a;
}

int Accounting::getAcc(){
    return acc;
}

int Accounting::getEco(){
    return eco;
}

int Accounting::sum(){
    return Compulsory::sum()+acc+eco;
}

double Accounting::avg(){
    return sum()/5.0;
}

void Accounting::disp(){
    Compulsory::disp();
    cout<<"===================="<<endl
        <<"Professional Course"<<endl
        <<"Accounting:"<<acc<<endl
        <<"Economics:"<<eco<<endl
        <<"===================="<<endl
        <<"Sum:"<<sum()<<endl
        <<"Avg:"<<avg()<<endl;
}
