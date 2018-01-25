//
//  CEdge.hpp
//  road_graph
//
//  Created by _nEgATron on 17/06/14.
//  Copyright © 2017年 _nEgATron. All rights reserved.
//

#ifndef CEDGE_H
#define CEDGE_H

#include <iostream>
class CNode;
class CEdge{
public:
    CEdge(int =0 ,double =0.0 ,CNode* =NULL );
    CEdge(CEdge*,CEdge*);
    ~CEdge();
    CEdge* getNext();
    CEdge* setNext(CEdge*);
    CNode* getEnd();
    double getLong();
    int getFID();
    int display();
    double getBTN();
    double addBTN(int);
    double setBTN(int);
    
private:
    int mnFID;
    double mdLength,mnBTN;
    CNode *mpEnd;
    CEdge *mpNext;
    
};

#endif /* CEdge_h */
