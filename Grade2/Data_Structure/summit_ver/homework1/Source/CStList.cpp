//
//  CStList.cpp
//  Stsys
//
//  Created by _nEgATron on 17/05/31.
//  Copyright © 2017年 _nEgATron. All rights reserved.
//

#include <String>
#include <iostream>
#include <fstream>
#include <sstream>
using std::string;
using std::cin;using std::cout;using std::endl;

#include "CStList.h"

/*---------------------------------------------------*/

CStList::CStList(){
    //initialize
    this->mnLength=0;
    this->head=new CStNode(false);
    this->head->setPre(this->head);
    
    //setup block search index.
    this->mIndex[0].mValue="a0000000000";
    this->mIndex[1].mValue="a5000000000";
    this->mIndex[2].mValue="b0000000000";
    this->mIndex[3].mValue="b5000000000";
    this->mIndex[4].mValue="c0000000000";
    this->mIndex[5].mValue="c5000000000";
}

CStList::~CStList(){
    this->distoryList();
}

/*---------------------------------------------------*/

CStList& CStList::readData(string inFile){
    std::ifstream fin;
    fin.open(inFile,std::ios::in);                       //open File
    if(!fin){
        cout<<"Error! File is not found!";               //return tips when file not found
        return *this;
    }
    
    int nFID=0,nSex=0,nM1=0,nM2=0,nM3=0;
    string stIn="",stName="",stID="";
    
    while(!fin.eof()){                                   //break when eof
        if(nFID>0){
            addNode(nFID,nSex,nM1,nM2,nM3,stID,stName);  //add node when read a record.
        }
        getline(fin,stIn);                               //recieve one line string from file
        for(int i=0;stIn[i];i++)
            if(stIn[i]==',')stIn[i]=' ';                 //csv replace ',' with ' '.               ***********
        std::stringstream ss(stIn);                      //change string to stringstre             ***********
        ss>>nFID>>nSex>>nM1>>nM2>>nM3>>stID>>stName;     //use >> operator input from stringstream ***********
    }
    fin.close();                                         //close file
    return *this;
}

int CStList::getLength(){
    return this->mnLength;
}

CStList& CStList::display(){
    CStNode* _pTemp=this->head->getNext();
    while(_pTemp){
        _pTemp->getSt()->display();
        _pTemp=_pTemp->getNext();
    }
    return *this;
}

/*---------------------------------------------------*///Core Algorithms:Sort

CStList* CStList::sortList(int inPara){
    return sortList(this->head->getNext(), this->head->getPre(),inPara);
}

CStList* CStList::sortList0(int inPara){
    return sortList0(this->head->getNext(), this->head->getPre(),inPara);
}

CStList* CStList::sortList(CStNode* pHead,CStNode* pTail,int inPara){       /* ******Qucik Sort****** */
    if(pHead==pTail)return this;
    CStudent *_pTemp=pHead->getSt();                                        //record the leftest axis' value
    CStNode *_pLow=pHead,*_pHigh=pTail;                                     //set pLow,pHigh
    while (_pLow!=_pHigh) {                                                 //break when pHigh meets pLow
        while((_pLow!=_pHigh)&&(_pTemp->compare(_pHigh->getSt(),inPara)))   //pHigh move
            _pHigh=_pHigh->getPre();
        swapSt(_pLow, _pHigh);                                              //swap when pLow bigger than axis
        while((_pLow!=_pHigh)&&(!(_pTemp->compare(_pLow->getSt(),inPara)))) //pLow move
            _pLow=_pLow->getNext();
        swapSt(_pLow, _pHigh);                                              //swap when pLow smaller than axis
    }
    _pLow->setSt(_pTemp);                                                   //put left axis' value back
    if(_pLow!=pHead)
        sortList(pHead, _pLow->getPre(),inPara);
    if(_pHigh!=pTail)
        sortList(_pHigh->getNext(), pTail,inPara);                          //iterate left part and right part
    return this;
}

CStList* CStList::sortList0(CStNode* pHead,CStNode* pTail,int inPara){       /* ******Bubble Sort****** */
    CStNode *_pTemp=pTail,*_pMove=NULL;                                      /*    use for compare..    */
    while(_pTemp!=pHead){
        _pMove=pHead;
        while(_pMove!=_pTemp){
            if(!_pMove->getSt()->compare(_pMove->getNext()->getSt(),inPara))
                swapSt(_pMove, _pMove->getNext());
            _pMove=_pMove->getNext();
        }
        _pTemp=_pTemp->getPre();
    }
    return this;
}

/*---------------------------------------------------*///Core Algorithms:Search

CStNode* CStList::searchList(string keySt){
    int _nTemp=getBlock(keySt);
    return searchList0(keySt, &mIndex[_nTemp]);
}

CStNode* CStList::searchList0(string keySt){
    CStNode *_pTemp=head->getNext();
    while(_pTemp->getSt()->getStringPara(0)!=keySt){
        _pTemp=_pTemp->getNext();
        if(_pTemp==NULL){
            cout<<"Student Record not Found."<<endl;
            return NULL;
        }
    }
    return _pTemp;
}

CStNode* CStList::searchList0(string keySt,SIndex *head){
    SIndex *_pTemp=head->next;
    while(_pTemp->mValue!=keySt){
        _pTemp=_pTemp->next;
        if(_pTemp==NULL){
            cout<<"Student Record not Found."<<endl;
            return NULL;
        }
    }
    return _pTemp->mStudent;
}

/*---------------------------------------------------*/

/* **************************** */
// these are auxiliary functions.
// addNode;     append Node.
// insertNode;  insert Node.
// removeNode;  remove but NOT DELETE the Node.
// delNode;     DELETE the Node.
// swapNode;    change the location of 2 Nodes.
// swapSt;      swap the CStudent*(pointer) only.
// getBlock;    return the block Area of input CStudent.
// destoryList; delete all the Node.
/* **************************** */

CStList& CStList::addNode(int inID,int inSex,int inM1,int inM2,int inM3,string stID,string stName){
    CStNode* _ptemp=this->head->getPre();
    
    _ptemp->setNext(new CStNode(inID,inSex,inM1,inM2,inM3,stID,stName,_ptemp));
    this->head->setPre(_ptemp->getNext());
    
    int _nTemp=this->getBlock(_ptemp->getNext()->getSt()->getStringPara(0));
    SIndex* _ptemp2=this->mIndex[_nTemp].next;
    this->mIndex[_nTemp].next=new SIndex(stID,_ptemp->getNext(),_ptemp2);
    
    this->mnLength++;
    return *this;
}

CStList& CStList::insertNode(CStNode* lastNode,CStNode* inNode){
    inNode->setNext(lastNode->getNext())->setPre(lastNode);
    lastNode->getNext()->setPre(inNode);
    lastNode->setNext(inNode);
    this->mnLength++;
    return *this;
}

CStList& CStList::removeNode(CStNode* moveNode){
    moveNode->getPre()->setNext(moveNode->getNext());
    if(moveNode->getNext())moveNode->getNext()->setPre(moveNode->getPre());
    this->mnLength--;
    return *this;
}

CStList& CStList::delNode(CStNode* moveNode){
    removeNode(moveNode);
    delete moveNode;
    moveNode=NULL;
    return *this;
}

CStList& CStList::swapNode(CStNode* node1,CStNode* node2){
    CStNode *_ptemp=node1->getPre();
    this->removeNode(node1);
    this->insertNode(node2, node1);
    this->removeNode(node2);
    this->insertNode(_ptemp, node2);
    return *this;
}

CStList& CStList::swapSt(CStNode *node1, CStNode *node2){
    CStudent *_pTemp=node1->getSt();
    node1->setSt(node2->getSt());
    node2->setSt(_pTemp);
    return *this;
}

int CStList::getBlock(string inSt){
    int _nTemp=0;
    while(inSt >= this->mIndex[_nTemp].mValue){
        _nTemp++;
    }
    _nTemp--;
    if(_nTemp<0)_nTemp=0;
    return _nTemp;
}

int CStList::distoryList(){
    while(this->head->getNext()){
        delNode(this->head->getNext());
    }
    return 0;
}
