//
//  CStudent.cpp
//  Student_system
//
//  Created by _nEgATron on 17/06/11.
//  Copyright © 2017年 _nEgATron. All rights reserved.
//

#include <String>
#include <iostream>
using std::string;
using std::cin;using std::cout;using std::endl;

#include "CStudent.h"

CStudent::CStudent(int inID,int inSex,int inM1,int inM2,int inM3,string stID,string stName){
    this->setPara(inID,inSex,inM1,inM2,inM3,stID,stName);
}

CStudent::~CStudent(){
    
}


CStudent* CStudent::setPara(int inID,int inSex,int inM1,int inM2,int inM3,string stID,string stName){
    this->mnFID=inID;
    this->mnSex=inSex;
    this->mnMark[0]=inM1;
    this->mnMark[1]=inM2;
    this->mnMark[2]=inM3;
    this->mstrID=stID;
    this->mstrName=stName;
    return this;
}

int CStudent::getIntPara(int paraID){
    switch (paraID) {
        case 0:return mnFID;break;
        case 1:return mnSex;break;
        case 2:
        case 3:
        case 4:return mnMark[paraID-2];
        default:return -1;
            break;
    }
}

string CStudent::getStringPara(int paraID){
    switch (paraID) {
        case 0:return mstrID;break;
        case 1:return mstrName;break;
        default:return "-1:error input";
            break;
    }
}

double CStudent::contAvg(){
    return (this->mnMark[0]+this->mnMark[1]+this->mnMark[2])/3;
}

bool CStudent::compare(CStudent* pInSt,int inPara){
    if(inPara>7)return false;
    else if(inPara>5){
        inPara-=6;
        return (this->getStringPara(inPara)>pInSt->getStringPara(inPara));
    }
    else if (inPara==5)
        return (this->contAvg()>pInSt->contAvg());
    else if(inPara>=0)
        return (this->getIntPara(inPara)>pInSt->getIntPara(inPara));
    else return false;
}

CStudent* CStudent::display(){
    
    cout<<"====================="<<endl
    <<" Student Information"<<endl
    <<"====================="<<endl
    <<"FID:"<<this->mnFID<<endl
    <<"St.ID:"<<this->mstrID<<endl
    <<"Name:"<<this->mstrName<<endl
    <<"Sex:"<<(this->mnSex==0?"Male":"Female")<<endl
    <<"Mark:"<<this->mnMark[0]<<","
    <<this->mnMark[1]<<","
    <<this->mnMark[2]<<endl
    <<"Avg:"<<this->contAvg()<<endl<<endl;
    return this;
}
