#ifndef HUSBAND_H
#define HUSBAND_H

#include <iostream>
using namespace std;

#include "pubProperty.h"

class Husband:virtual public PubProperty{
public:
    Husband(int a=0,int b=0):PubProperty(a){
        personProperty=b;
    };
    void changePer(int a=0){
        personProperty=a;
    };
    int getPer(){
        return personProperty;
    };
    void disp(){
        cout<<"Husband's Property"<<endl
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
