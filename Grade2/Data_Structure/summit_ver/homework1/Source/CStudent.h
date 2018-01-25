//
//  CStudent.h
//  Student_system
//
//  Created by _nEgATron on 17/06/11.
//  Copyright © 2017年 _nEgATron. All rights reserved.
//

#ifndef CSTUDENT_H
#define CSTUDENT_H

#include <String>
using std::string;

class CStudent{
    
public:
    CStudent(int=0,int=0,int=0,int=0,int=0,string="",string="");
    ~CStudent();
    
public:
    CStudent* setPara(int=0,int=0,int=0,int=0,int=0,string="",string="");
    int getIntPara(int=0);         //get para:0-FID 1-Sex 3-Mark1 4-Mark2 5-Mark3 (error return -1:error input)
    string getStringPara(int=0);   //get para:0-StID 1-Name(error return "-1:error input")
    double contAvg();              //cont Avg Mark.
    bool compare(CStudent*,int);  //compare 2 Student Class. a.compare(b)return true when a>b.
    CStudent* display();           //To display the info.
    
private:
    int mnFID,mnSex,mnMark[3];
    string mstrID,mstrName;
};

#endif /* CStudent_h */
