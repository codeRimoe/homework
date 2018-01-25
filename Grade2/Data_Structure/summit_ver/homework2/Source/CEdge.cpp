//
//  CEdge.cpp
//  road_graph
//
//  Created by _nEgATron on 17/06/14.
//  Copyright © 2017年 _nEgATron. All rights reserved.
//

#include <iostream>

#include "CEdge.h"
#include "CNode.h"

CEdge::CEdge(int inFID,double inLength,CNode* inEnd){
    mnFID=inFID;
    mdLength=inLength;
    mpEnd=inEnd;
    mpNext=NULL;
    mnBTN=0;
}

CEdge::CEdge(CEdge* inE,CEdge* nextE){
    mnFID=inE->getFID();
    mdLength=inE->getLong();
    mpEnd=inE->getEnd();
    mpNext=nextE;
}

CEdge::~CEdge(){
    
}

int CEdge::display(){
    std::cout<<" -(Road ID: "<<mnFID<<",Length: "<<mdLength<<")=>"<<mpEnd->getFID()<<"("<<mpEnd->getX()<<","<<mpEnd->getY()<<")"<<std::endl;
    return 0;
}

int CEdge::getFID(){
    return mnFID;
}

CNode* CEdge::getEnd(){
    return this->mpEnd;
}

CEdge* CEdge::getNext(){
    return this->mpNext;
}

double CEdge::getLong(){
    return mdLength;
}

double CEdge::getBTN(){
    return mnBTN;
}

double CEdge::addBTN(int nAddNum){
    mnBTN+=nAddNum;
    return mnBTN;
}

double CEdge::setBTN(int inPath){
    mnBTN/=inPath;
    return mnBTN;
}

CEdge* CEdge::setNext(CEdge * inE){
    mpNext=inE;
    return this;
}
