#ifndef CHILD_H
#define CHILD_H

#include <iostream>
using namespace std;

#include "pubProperty.h"
#include "husband.h"
#include "wife.h"

class Child:public Husband,public Wife{
public:
    Child(int a=0,int b=0 ,int c=0,int d=0)
        :PubProperty(a),Husband(a,b),Wife(a,c){
            personProperty=d;
        };
    void changePer(int a=0){
        personProperty=a;
    };
    int getPer(){
        return personProperty;
    };
    void getAll(){
        personProperty+=Husband::getPer()+Wife::getPer()+balance;
        Husband::changePer(0);
        Wife::changePer(0);
        balance=0;
    };
    void disp(){
        cout<<"Child's Property"<<endl
        <<"==================="<<endl
        <<"parents' public:"<<balance<<endl
        <<"dad's private:"<<Husband::getPer()<<endl
        <<"mom's private:"<<Wife::getPer()<<endl
        <<"-------------------"<<endl
        <<"private:"<<getPer()<<endl
        <<"==================="<<endl<<endl;
    };
private:
    int personProperty;
};

#endif
