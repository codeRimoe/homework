//
//  CNode.h
//  road_graph
//
//  Created by _nEgATron on 17/06/14.
//  Copyright © 2017年 _nEgATron. All rights reserved.
//

#ifndef CNODE_H
#define CNODE_H

class CEdge;
class CGraph;

class CNode{
public:
    CNode(int =0 ,int =0 ,double =0.0 ,double =0.0 );
    ~CNode();
    int getFID();
    double getX();
    double getY();
    CNode* setNext(CNode*);
    CNode* getNext();
    CNode* addEdge(CEdge*);
    CNode* setEdge(CEdge*);
    CEdge* getEdge();

    int display();
    
    double getNearestPath(CGraph*,CNode*,CEdge* &pGetPath);   //get the shortest path from this node to another node
    int printNearestPath(CGraph*,CNode*);                     //print the completed path
    int getPathGroup(CGraph*,CNode** &pNode,double* &pnDis);  //count all the shortest path begin from the node
    CEdge* oneStepTo(CNode*);    //from this node to anonther node, if only pass one road,return the road, or return NULL
 
protected:
    CNode* getNearNode(CGraph*,CNode** &pNode,double* &pnDis);
    
private:
    int mnFID,mnJoin_Count;
    double mdX,mdY;
    CNode *mpNext;
    CEdge *mpE;
};

#endif /* CNode_h */
