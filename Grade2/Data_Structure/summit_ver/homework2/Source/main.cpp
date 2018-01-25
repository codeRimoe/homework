//
//  main.cpp
//  road_graph
//
//  Created by _nEgATron on 17/06/12.
//  Copyright © 2017年 _nEgATron. All rights reserved.
//

#include <iostream>

#include <fstream>
#include <sstream>

#include <cmath>
#include "CGraph.h"
#include "CNode.h"
#include "CEdge.h"

using std::cout;using std::endl;using std::cin;

int main(int argc, const char * argv[]) {
    int nInput=4,nIDStart=0,nIDEnd=0;
    clock_t tick=clock();
    CGraph graph;
    CNode ***pNode=NULL;
    double **pdDis=NULL,_th=0;
    string sNodeFile="/Users/_nA/Downloads/15级数据结构作业/data/Node.csv",sRoadFile="/Users/_nA/Downloads/15级数据结构作业/data/road.csv",sErrFile="/Users/_nA/Github/code/road_graph/road_graph/errroad.csv",sSaveFile="/Users/_nA/Github/code/road_graph/road_graph/BTN.csv";
    cout<<"Please input the file path of NodeFile:";
    cin>>sNodeFile;
    cout<<"Please input the file path of RoadFile:";
    cin>>sRoadFile;
    cout<<"Please input the file path of ErrorFile(going to save):";
    cin>>sErrFile;
//    sNodeFile="/Users/_nA/Downloads/15级数据结构作业/data/node.csv";
//    sRoadFile="/Users/_nA/Downloads/15级数据结构作业/data/road.csv";
//    sErrFile="/Users/_nA/Github/code/road_graph/road_graph/errroad.csv";
    graph.readData(sNodeFile,sRoadFile,sErrFile);
    while(nInput){
        cout << "Input number to operate!"<<endl
             << "1.display the network of the roas."<<endl
             << "2.count the shorest path from one node to another."<<endl
             << "3.count the betweeness."<<endl
             << "4.community structure split."<<endl
             << "0.exit"<<endl
             << "Input:";
        std::cin >> nInput;
        tick=clock();
        switch (nInput) {
            case 1:
                graph.display();
                break;
            case 2:
                cout<<"Start From(Input FID):"<<endl;
                cin>>nIDStart;
                cout<<"Go To(Input FID):"<<endl;
                cin>>nIDEnd;
                graph.search(nIDStart)->printNearestPath(&graph, graph.search(nIDEnd));
                break;
            case 3:
                cout<<"Please input the file path of betweeness File(going to save):";
                cin>>sSaveFile;
                graph.beTwNess(pNode, pdDis);
                graph.saveData(sSaveFile);
                break;
            case 4:
                cout<<"Please input the file path of betweeness File(going to save):";
                cin>>sSaveFile;
                cout<<"Please input dThreshold:"<<endl;
                cin>>_th;
                graph.beTwNess(pNode, pdDis);
                graph.comStruct(_th, sSaveFile);
                break;
            default:break;
        }
        std::cout<<"\nTime:"<<(clock()-tick)/1.0/CLOCKS_PER_SEC<<std::endl;
        if(pdDis){
            for(int _i=0;_i<graph.getNode();_i++)
                if(pdDis[_i])delete[] pdDis[_i];
            delete []pdDis;
        }
        if(pNode){
            for(int _i=0;_i<graph.getNode();_i++)
                if(pNode[_i])delete[] pNode[_i];
            delete []pNode;
        }
    }


    return 0;
}
