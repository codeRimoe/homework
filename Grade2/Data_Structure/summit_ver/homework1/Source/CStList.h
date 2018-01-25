//
//  CStList.h
//  Stsys
//
//  Created by _nEgATron on 17/05/31.
//  Copyright © 2017年 _nEgATron. All rights reserved.
//

#ifndef CSTLIST_H
#define CSTLIST_H

#include <fstream>

#include "CStNode.h"

struct SIndex{
    SIndex(string inValue="",CStNode *inSt=NULL,SIndex *inIndex=NULL){
        mValue=inValue,mStudent=inSt,next=inIndex;
    }
    string mValue;
    CStNode *mStudent;
    SIndex *next;
};//use as the index for block search.

class CStList{
    
public:
    CStList();
    ~CStList();
    
    int getLength();              //get the length of the List.
    
    CStList& readData(string);    //read data from document.
    CStList& display();           //display List.
    CStList* sortList(int=0);     //sort List (QuickSort)
    CStList* sortList0(int=0);    //sort List (Bubble)
    CStNode* searchList(string);  //search by block index
    CStNode* searchList0(string); //search in order
    CStList& addNode(int=0,int=0,int=0,int=0,int=0,string="",string="");  //add Node to the List;
    
    void test();
    
protected:
    
    CStList& insertNode(CStNode*,CStNode*);
    CStList& removeNode(CStNode*);
    CStList& delNode(CStNode*);
    CStList& swapNode(CStNode*,CStNode*);
    CStList& swapSt(CStNode*,CStNode*);
    int getBlock(string);
    int distoryList();
    CStList* sortList(CStNode*,CStNode*,int=0);
    CStList* sortList0(CStNode*,CStNode*,int=0);
    CStNode* searchList0(string,SIndex*);
    
private:
    int mnLength;
    CStNode *head;
    SIndex mIndex[6];
};

#endif
