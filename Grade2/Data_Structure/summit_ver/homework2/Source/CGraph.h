//
//  CGraph.hpp
//  road_graph
//
//  Created by _nEgATron on 17/06/14.
//  Copyright © 2017年 _nEgATron. All rights reserved.
//

#ifndef CGRAPH_H
#define CGRAPH_H

#include <string>
#include "CNode.h"
using  std::string;

class CGraph{
public:
    CGraph();
    ~CGraph();
    int readData(string,string,string="ErrPoi.csv"); //read data from csv
    int saveData(string);                            //save road data FID,length,betweeness
    int display();
    int getNode();       //return the number of Node
    int getBTN();        //the total number of Nearest Path
    CNode* getHead();
    CNode* search(int);              //find node by FID
    CNode* search(double,double);    //find node by X,Y
    int beTwNess(CNode***,double**); //find node by FID
    int comStruct(double ,string);
    int mark(int,int,double,int*);
    
private:
    int mnNode,mnEdge,mnBTN; //the total number
    CNode* mpHead;           //the head pointer
    CNode** searchNode;      //a search List for search a Node , sorted with FID
};

#endif /* CGraph_h */
