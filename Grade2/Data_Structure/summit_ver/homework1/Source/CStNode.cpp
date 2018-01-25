//
//  CStNode.cpp
//  Stsys
//
//  Created by _nEgATron on 17/05/31.
//  Copyright © 2017年 _nEgATron. All rights reserved.
//

#include <String>
#include <iostream>
using std::string;
using std::cin;using std::cout;using std::endl;

#include "CStNode.h"

CStNode::CStNode(bool){
    this->mpSt=NULL;
    this->setPara(NULL,NULL);
}

CStNode::CStNode(int inID,int inSex,int inM1,int inM2,int inM3,string stID,string stName,CStNode* inPre,CStNode* inNext){
    this->mpSt=new CStudent(inID,inSex,inM1,inM2,inM3,stID,stName);
    this->setPara(inPre,inNext);
}

CStNode::~CStNode(){
    delete this->mpSt;
}


CStNode* CStNode::setPara(CStNode* inPre,CStNode* inNext){
    this->pre=inPre;
    this->next=inNext;
    return this;
}

CStNode* CStNode::setPre(CStNode* inPre){
    this->pre=inPre;
    return this;
}

CStNode* CStNode::setNext(CStNode* inNext){
    this->next=inNext;
    return this;
}

CStudent* CStNode::setSt(CStudent *inSt){
    this->mpSt=inSt;
    return this->mpSt;
}

CStNode* CStNode::getPre(){
    return this->pre;
}

CStNode* CStNode::getNext(){
    return this->next;
}

CStudent* CStNode::getSt(){
    return this->mpSt;
}
