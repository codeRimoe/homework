#ifndef GIS_H
#define GIS_H
#include "Compulsory.h"
class Gis:public Compulsory{
public:
    Gis(int=0,int=0,int=0,int=0,int=0,int=0);
    ~Gis();
    void setSpa(int);
    void setRS(int);
    int getSpa();
    int getRS();
    int sum();
    double avg();
    void disp();
protected:
    int spa,RS;
};

#endif
