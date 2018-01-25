//
//  CStNode.h
//  Stsys
//
//  Created by _nEgATron on 17/05/31.
//  Copyright © 2017年 _nEgATron. All rights reserved.
//

#ifndef CSTNODE_H
#define CSTNODE_H

#include "CStudent.h"

class CStNode{

public:
    CStNode(bool);
    CStNode(int=0,int=0,int=0,int=0,int=0,string="",string="",CStNode* =NULL,CStNode* =NULL);
    ~CStNode();

public:
    CStNode* setPara(CStNode* =NULL,CStNode* =NULL);
    CStNode* setPre(CStNode*);   //set previous Student Node.
    CStNode* getPre();            //get previous Student Node.
    CStNode* setNext(CStNode*);  //set next Student Node.
    CStNode* getNext();           //get next Student Node.
    CStudent* setSt(CStudent*);         //set para:Student
    CStudent* getSt();         //get para:Student
    
private:
    CStudent* mpSt;
    CStNode* pre;
    CStNode* next;
};

#endif
