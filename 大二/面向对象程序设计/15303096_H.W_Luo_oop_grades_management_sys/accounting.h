#ifndef ACCOUNTING_H
#define ACCOUNTING_H
#include "Compulsory.h"
class Accounting:public Compulsory{
public:
    Accounting(int=0,int=0,int=0,int=0,int=0,int=0);
    ~Accounting();
    void setAcc(int);
    void setEco(int);
    int getAcc();
    int getEco();
    int sum();
    double avg();
    void disp();
protected:
    int acc,eco;
};

#endif
