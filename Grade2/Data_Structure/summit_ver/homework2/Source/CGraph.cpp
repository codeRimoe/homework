//
//  CGraph.cpp
//  road_graph
//
//  Created by _nEgATron on 17/06/14.
//  Copyright © 2017年 _nEgATron. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

#include "CNode.h"
#include "CEdge.h"
#include "CGraph.h"

using std::string;using std::cout;

CGraph::CGraph(){
    mnNode=0,mnEdge=0;
    mpHead=new CNode(-1,-1,-1,-1);
}
CGraph::~CGraph(){
    CNode *_pNode=mpHead;
    while(mpHead){
        mpHead=mpHead->getNext();
        delete _pNode;
        _pNode=mpHead;
    }
    delete []searchNode;
}


int CGraph::readData(string inFile1,string inFile2,string outErr){
    std::ofstream rec;
    rec.open(outErr,std::ios::out);
    std::ifstream fin;
    fin.open(inFile1,std::ios::in);                       //open File
    if(!fin){
        cout<<"Error! File is not found!";               //return tips when file not found
        return 1;
    }
    
    int inFID=-1,inJoin_Count=-1;
    double inX=0,inY=0;
    string stIn;
    CNode *_pTemp=mpHead,*_pTempEnd=NULL;
    while(!fin.eof()){                                   //break when eof
        if(inJoin_Count>0){
            mnNode++;
            _pTemp->setNext(new CNode(inFID,inJoin_Count,inX,inY));  //add node when read a record.
            _pTemp=_pTemp->getNext();
        }
        getline(fin,stIn);                               //recieve one line string from file
        for(int i=0;stIn[i];i++)
            if(stIn[i]==',')stIn[i]=' ';                 //csv replace ',' with ' '.               ***********
        std::stringstream ss(stIn);                      //change string to stringstre             ***********
        ss>>inFID>>inX>>inY>>inJoin_Count;               //use >> operator input from stringstream ***********
    }
    fin.close();                                         //close file
    
    
    searchNode=new CNode*[mnNode];
    _pTemp=mpHead->getNext();
    for(int i=0;i<mnNode;i++){
        searchNode[i]=_pTemp;
        _pTemp=_pTemp->getNext();
    }
    
    
    
    fin.open(inFile2,std::ios::in);                       //open File
    if(!fin){
        cout<<"Error! File is not found!";               //return tips when file not found
        return 1;
    }
    
    int inOneWay=-1;
    double inLength=0,inEX=0,inEY=0;
    
    while(!fin.eof()){//break when eof
        _pTemp=search(inX, inY),_pTempEnd=search(inEX, inEY);
        if(_pTemp&&_pTempEnd){
            if(inOneWay>=0){
                mnEdge++;
                _pTemp->addEdge(new CEdge(inFID,inLength,_pTempEnd));  //add node when read a record.
            }
            if(inOneWay==0){
                mnEdge++;
                _pTempEnd->addEdge(new CEdge(inFID,inLength,_pTemp));  //add node when read a record.
            }
        }
        else
            rec<<inFID<<","<<inOneWay<<","<<inLength<<","<<inX<<","<<inY<<","<<inEX<<","<<inEY<<std::endl;
        getline(fin,stIn);                               //recieve one line string from file
        for(int i=0;stIn[i];i++)
            if(stIn[i]==',')stIn[i]=' ';                 //csv replace ',' with ' '.               ***********
        std::stringstream ss(stIn);                      //change string to stringstre             ***********
        ss>>inFID>>inOneWay>>inLength>>inX>>inY>>inEX>>inEY;
    }
    fin.close();                                         //close file
    rec.close();
    return 0;
}

int CGraph::saveData(string outFile){
    CEdge *_pE=NULL;
    std::ofstream rec;
    rec.open(outFile,std::ios::out);
    cout<<"FID,length(m),betweenNess"<<std::endl;
    for(int i=0;i<this->mnNode;i++)
        for(int j=0;j<this->mnNode;j++){
            if((_pE=this->search(i)->oneStepTo(this->search(j))))
                rec<<_pE->getFID()<<','<<_pE->getLong()<<','<<_pE->getBTN()/this->getBTN()<<std::endl;
        }
    rec.close();
    return 0;
}


int CGraph::getNode(){
    return this->mnNode;
}

int CGraph::getBTN(){
    return mnBTN;
}

CNode* CGraph::getHead(){
    return this->mpHead;
}

int CGraph::display(){
    CNode *_pTemp=mpHead->getNext();
    CEdge *_pETemp=NULL;
    while(_pTemp!=NULL){
        _pTemp->display();
        _pETemp=_pTemp->getEdge();
        while(_pETemp!=NULL){
            _pETemp->display();
            _pETemp=_pETemp->getNext();
        }
        _pTemp=_pTemp->getNext();
    }
    cout<<mnNode<<std::endl<<mnEdge;
    return 0;
}

CNode* CGraph::search(int inFID){
    return searchNode[inFID];     //search the Node by FID
}


CNode* CGraph::search(double inX,double inY){
    CNode* _ptemp=mpHead;
    while(_ptemp){
        if((fabs(_ptemp->getX()-inX)<1e-7)&&(fabs(_ptemp->getY()-inY)<1e-7))
            break;
        _ptemp=_ptemp->getNext();
    }
    return _ptemp;
}

int CGraph::beTwNess(CNode*** pNode,double** pdDis){
    if(this->getBTN()!=0){
        std::cout<<"Betweenness has been counted."<<std::endl;
        return this->getBTN();
    }
    int _i=0,_j=0,_nPathNum=0,**_pCont=NULL,_nCont=0,_nN=0;
    double _dTDis=0;
    CNode *_pN=this->getHead()->getNext();
    CEdge *_pE=NULL;
    _pCont=new int*[mnNode];
    pNode=new CNode**[mnNode];          //build a matrix between each 2 Node
    pdDis=new double*[mnNode];          //matrix pNode used to record midNode
    for(;_i<mnNode;_i++){               //matrix pdDis uesd to record the length of path
        pNode[_i]=new CNode*[mnNode];
        pdDis[_i]=new double[mnNode];
        _pCont[_i]=new int[mnNode];
        for(_j=0;_j<mnNode;_j++){
            pNode[_i][_j]=NULL;
            pdDis[_i][_j]=0;
            _pCont[_i][_j]=0;
        }
    }
    /* -----------------------------Floyd-----------------------------  */
    //initial the matrix : record the oneStep road
    _i=0,_j=0;
    while(_pN){
        _pE=_pN->getEdge();
        while (_pE) {
            _i=_pN->getFID();
            _j=_pE->getEnd()->getFID();
            if(_i!=_j){
                pNode[_i][_j]=_pN;
                pdDis[_i][_j]+=_pE->getLong();
                _pCont[_i][_j]=1;
            }
            _pE=_pE->getNext();
        }
        _pN=_pN->getNext();
    }
    //refresh the matrix : if the new path(pass one point) is shorter, change the path
    for(int _k=0;_k<mnNode;_k++){
        for(_i=0;_i<mnNode;_i++){
            for(_j=0;_j<mnNode;_j++){
                if((pdDis[_i][_k]>1e-7)&&(pdDis[_k][_j]>1e-7)){
                    _dTDis=pdDis[_i][_k]+pdDis[_k][_j];
                    if(fabs(pdDis[_i][_j])<1e-7){
                        _pCont[_i][_j]=1;
                        pNode[_i][_j]=search(_k);
                        pdDis[_i][_j]=_dTDis;
                    }
                    if(_dTDis<pdDis[_i][_j]){
                        pNode[_i][_j]=search(_k);
                        pdDis[_i][_j]=_dTDis;
                    }
                }
            }
        }
    }
    /* -----------------------------Floyd-----------------------------  */
    
    //count the total number of the path
    for(_i=0;_i<mnNode;_i++)
        for(_j=0;_j<mnNode;_j++)
            _nCont+=_pCont[_i][_j];
    _nPathNum=_nCont;
    //count the betweenness of each edge(rode).
    while(_nCont){                               //end loop until _nCont = 0;
        for(_i=0;_i<mnNode;_i++)
            for(_j=0;_j<mnNode;_j++)
                if(_pCont[_i][_j]){
                    _nN=pNode[_i][_j]->getFID();
                    if(_nN==_i){                 //if only one road from _i to _j, BTN change
                        search(_i)->oneStepTo(search(_j))->addBTN(_pCont[_i][_j]);
                        _nCont-=_pCont[_i][_j];
                    }
                    else{                        //if more than one road, split into 2 path
                        _pCont[_i][_nN]+=_pCont[_i][_j];
                        _pCont[_nN][_j]+=_pCont[_i][_j];
                        _nCont+=_pCont[_i][_j];
                    }
                    _pCont[_i][_j]=0;
                }
    }
    this->mnBTN=_nPathNum;
    //delete _pCont
    for(_i=0;_i<mnNode;_i++)
        if(_pCont[_i])delete[] _pCont[_i];
    if(_pCont)delete _pCont;
    return _nPathNum;
}


int CGraph::mark(int FID,int nM,double dThreshold,int *nMark){
    CEdge *_pE=NULL;
    int _tFID=0;
    if((this->search(FID)!=NULL)&&(nMark[FID]==0)){
        nMark[FID]=nM;
        _pE=this->search(FID)->getEdge();
        while(_pE){                                      //mark the node by the conected road
            if(_pE->getBTN()/this->getBTN()<dThreshold){ //if betweenness bigger than threshold, cut it
                _tFID=_pE->getEnd()->getFID();
                mark(_tFID,nM,dThreshold,nMark);         //mark the same class index
            }
            _pE=_pE->getNext();
        }
    }
    return 0;
}

int CGraph::comStruct(double dThreshold,string outFile){
    int *_nMark=new int[this->mnNode](),_nTMark=1;
    std::ofstream rec;
    rec.open(outFile,std::ios::out);
    for(int _i=0;_i<this->mnNode;_i++){
        if(this->search(_i)){
            if(_nMark[_i]==0){
                mark(_i,_nTMark,dThreshold,_nMark);     //mark the connected node into same class index
               _nTMark++;
            }
            rec<<_i<<','<<_nMark[_i]<<std::endl;
        }
    }
    rec.close();
    return 0;
}
