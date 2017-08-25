#ifndef WIFE_H
#define WIFE_H

#include <iostream>
using namespace std;

#include "pubProperty.h"

class Wife:virtual public PubProperty{
public:
    Wife(int a=0,int b=0):PubProperty(a){
        personProperty=b;
    };
    void changePer(int a=0){
        personProperty=a;
    }; 
    int getPer(){
        return personProperty;
    };
    void disp(){
        cout<<"Wife's Property"<<endl
            <<"==================="<<endl
            <<"public:"<<balance<<endl
            <<"-------------------"<<endl
            <<"private:"<<personProperty<<endl
            <<"==================="<<endl<<endl;
    };
private:
    int personProperty;
};

#endif
