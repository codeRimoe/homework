//
//  CNode.cpp
//  road_graph
//
//  Created by _nEgATron on 17/06/14.
//  Copyright © 2017年 _nEgATron. All rights reserved.
//

#include <iostream>
#include <cmath>
using std::cout;using std::endl;
#include "CGraph.h"
#include "CNode.h"
#include "CEdge.h"
CNode::CNode(int inFID,int inJoin_Count,double inX,double inY){
    mnFID=inFID,mnJoin_Count=inJoin_Count;
    mdX=inX,mdY=inY;
    mpNext=NULL;
    mpE=NULL;
}

CNode::~CNode(){
    CEdge *_pEdge=mpE;
    while(mpE){             //delete all the Edge(road)
        mpE=mpE->getNext();
        delete _pEdge;
        _pEdge=mpE;
    }
}

CNode* CNode::getNext(){
    return mpNext;
}

CNode* CNode::setNext(CNode* inNode){
    this->mpNext=inNode;
    return this;
}

CNode* CNode::addEdge(CEdge* inE){
    CEdge* _pE=this->mpE;
    if(_pE==NULL){
        mpE=inE;
    }
    else{
        while(_pE->getNext()!=NULL){
            _pE=_pE->getNext();
        }
        _pE->setNext(inE);
    }
    return this;
}

CNode* CNode::setEdge(CEdge* inE){
    mpE=inE;
    return this;
}
 
CEdge* CNode::getEdge(){
    return mpE;
}

int CNode::getFID(){
    return mnFID;
}

double CNode::getX(){
    return mdX;
}

double CNode::getY(){
    return mdY;
}

int CNode::display(){
    std::cout<<mnFID<<", Join Cont:"<<mnJoin_Count<<", Loc:("<<mdX<<","<<mdY<<")"<<std::endl;
    return 0;
}

int CNode::printNearestPath(CGraph* pG,CNode* pEnd){   //display the nearest path
    CEdge *pPath=NULL,*_pT=NULL;
    cout<<"====================================================="<<endl
        <<"Best Path:Total Distance="<<getNearestPath(pG, pEnd, pPath)<<endl
        <<"====================================================="<<endl;
    cout<<"From:";
    this->display();
    while(pPath){
        _pT=pPath->getNext();
        pPath->display();
        delete pPath;
        pPath=_pT;
    }
    cout<<"To:";
    pEnd->display();
    cout<<"====================================================="<<endl;
    return 0;
}

double CNode::getNearestPath(CGraph* pG,CNode* pEnd,CEdge* &pGetPath){
    //find the nearest path from the shortest path group
    CNode **pNode=NULL,*_pBreak=pEnd,*_pBF=NULL;
    double *pdDis=NULL,_dT=0;
    getPathGroup(pG,pNode,pdDis);
    _dT=pdDis[pEnd->getFID()];
    
    pGetPath=NULL,_pBF=pNode[_pBreak->getFID()];
    while((_pBreak!=this)){
        if(_pBF==pG->getHead()){
            pGetPath=NULL;
            break;
        }
        _pBF=pNode[_pBreak->getFID()];
        pGetPath=new CEdge(_pBF->oneStepTo(_pBreak),pGetPath);
        _pBreak=_pBF;
    }

    delete []pNode;
    delete []pdDis;
    return _dT;
}

int CNode::getPathGroup(CGraph* pG,CNode** &pNode,double* &pdDis){
    int nPath=0,nNode=pG->getNode();
    CNode *nANode=pG->getHead(),*_tempNode=this;
    pdDis=new double[nNode];
    pNode=new CNode*[nNode];
/* ------------------Dijkstra------------------*/
    for(int i=0;i<nNode;i++){
        pdDis[i]=0;
        pNode[i]=nANode;
    }
    pdDis[this->mnFID]=0;
    while(_tempNode){
        nPath++;
        _tempNode=_tempNode->getNearNode(pG, pNode, pdDis);
    }
    nPath--;
    return nPath;
}

inline CNode* CNode::getNearNode(CGraph* pG,CNode** &pNode,double* &pdDis){ //one loop of the refresh in Dijkstra
    int _nFID=0,_nMin=0;
    double _dLong=0;
    CEdge* _pEdge=this->getEdge();
    //refresh all the onesteptp node:if find a shorter path then refresh it
    while (_pEdge!=NULL) {
        _nFID=_pEdge->getEnd()->getFID();
        _dLong=-pdDis[this->mnFID]-_pEdge->getLong();
        if((fabs(pdDis[_nFID])<1e-7)||(pdDis[_nFID]<_dLong)){
            pdDis[_nFID]=_dLong;
            pNode[_nFID]=this;
        }
        _pEdge=_pEdge->getNext();
    }
    //find the shortest path in current array,return the shortest path,nest loop base on this path.
    for(int i=0;i<pG->getNode();i++){
        if((pdDis[i]<0)&&(pdDis[i]>pdDis[_nMin]))
            _nMin=i;
        else if((pdDis[_nMin]>0)||(fabs(pdDis[_nMin])<1e-7))
            _nMin=i;
    }
    if(pdDis[_nMin]<0){
        pdDis[_nMin]*=-1;
        return pG->search(_nMin);
    }
    else{
        return NULL;
    }
}

CEdge* CNode::oneStepTo(CNode* inNode){
    CEdge* _pE=mpE;
    while(_pE){
        if(_pE->getEnd()==inNode)  //search from start node,if find the target,break and return
            break;
        _pE=_pE->getNext();
    }
    return _pE;                    //if not found , finally return null
}
