//
//  main.cpp
//  Stsys
//
//  Created by _nEgATron on 17/05/31.
//  Copyright © 2017年 _nEgATron. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <String>
using std::string;
using std::cout;using std::endl;using std::cin;
#include "CStList.h"
#include "CStNode.h"

int Mread(CStList* head){
    string stInData;
    system("clear");
    cout<<"================================="<<endl
        <<" *   Read data from CSV File   * "<<endl
        <<"================================="<<endl
        <<"Please input data path:"<<endl;
    cin.sync();
    cin.clear();
    cin>>stInData;
    
    clock_t cont_time=clock();
    
    head->readData(stInData);   //"/Users/_nA/Github/code/Stsys/Stsys/testdata/test1.csv"
    
    cont_time=clock()-cont_time;
    cout<<"Run time:"<<cont_time<<"ms\nInput anything to continue:"<<endl;
    string stIN;
    cin.sync();
    cin.clear();
    cin>>stIN;
    
    return 0;
}
int Msort(CStList* head){
    int _nM=1,_nFea=5;
    system("clear");
    cout<<"================================="<<endl
        <<" *            Sort             * "<<endl
        <<"================================="<<endl
        <<"Please input sort method:"<<endl
        <<"1.Quick Sort"<<endl
        <<"2.Bubble Sort"<<endl
        <<"Input:";
    cin.sync();
    cin.clear();
    cin>>_nM;
    if((_nM!=1)&&(_nM!=2))
        return 1;
    system("clear");
    cout<<"================================="<<endl
        <<" *            Sort             * "<<endl
        <<"================================="<<endl
        <<"Sort based on:"<<endl
        <<"1.FID"<<endl
        <<"2.Sex"<<endl
        <<"3.Subject1"<<endl
        <<"4.Subject2"<<endl
        <<"5.Subject3"<<endl
        <<"6.Avg"<<endl
        <<"7.Student ID"<<endl
        <<"8.Name"<<endl
        <<"Input:";
    cin.sync();
    cin.clear();
    cin>>_nFea;
    
    clock_t cont_time=clock();
    
    if(_nM==1)
        head->sortList(_nFea-1);
    else if(_nM==2)
        head->sortList0(_nFea-1);
    
    cont_time=clock()-cont_time;
    cout<<"Run time:"<<cont_time<<"ms\nInput anything to continue:"<<endl;
    string stIN;
    cin.sync();
    cin.clear();
    cin>>stIN;
    
    return 0;
}
int Msearch(CStList* head){
    int _nM=1;
    CStNode *_pSt;
    string _stKey="";
    system("clear");
    cout<<"================================="<<endl
        <<" *    Search With StudentID    * "<<endl
    <<"================================="<<endl
    <<"Please input search method:"<<endl
    <<"1.Block Search"<<endl
    <<"2.Sequential Search"<<endl
    <<"Input:";
    cin.sync();
    cin.clear();
    cin>>_nM;
    if((_nM!=1)&&(_nM!=2))
        return 1;
    system("clear");
    cout<<"================================="<<endl
    <<" *    Search With StudentID    * "<<endl
    <<"================================="<<endl
    <<"Please input search method:";
    cin.sync();
    cin.clear();
    cin>>_stKey;
    
    clock_t cont_time=clock();
    
    if(_nM==1)
        _pSt=head->searchList(_stKey);
    else if(_nM==2)
        _pSt=head->searchList0(_stKey);
    
    cont_time=clock()-cont_time;
    cout<<"Run time:"<<cont_time<<"ms\nInput anything to continue:"<<endl;
    string stIN;
    cin.sync();
    cin.clear();
    cin>>stIN;
    
    if(_pSt)_pSt->getSt()->display();
    cout<<"Input anything back to menu:";
    cin.sync();
    cin.clear();
    cin>>_stKey;
    return 0;
}
int menu(CStList* head){
    system("clear");
    int _nInput=-1;
    string _temp="";
    clock_t cont_time=clock();
    cout<<"================================="<<endl
    <<" *  Student Management System  * "<<endl
    <<"================================="<<endl
    <<"Menu:"<<endl
    <<"1.Read data from csv"<<endl
    <<"2.Show Data"<<endl
    <<"3.Sort"<<endl
    <<"4.Search with ID"<<endl
    <<"0.exit"<<endl
    <<"Input:";
    cin.sync();
    cin.clear();
    cin>>_nInput;
    while((_nInput<0)||(_nInput>4)){
        cout<<"Error input:Please input int from 0 to 4.\nInput:";
        cin>>_nInput;
    }
    switch (_nInput) {
        case 1:
            Mread(head);
            break;
        case 2:
            system("claer");
            
            cont_time=clock();
            
            head->display();
            
            cont_time=clock()-cont_time;
            cout<<"Run time:"<<cont_time<<"ms\nInput anything to continue:"<<endl;
            
            cout<<"Input anything back to menu:";
            cin>>_temp;
            break;
        case 3:
            Msort(head);
            break;
        case 4:
            Msearch(head);
            break;
        default:
            return 1;
            break;
    }
    return 0;
}

int main(int argc, const char * argv[]) {
    CStList head;
    while (1){
        if(menu(&head))break;
    }
    
// /*this part of code is used for making up some random data.*/
// /* ***************************** */
//    srand((unsigned)time(0));
//    std::ofstream fout;
//    fout.open("/Users/_nA/Github/code/Stsys/Stsys/test05.csv",std::ios::out);
//    int i=1;
//    while(i<301){
//        int nFID=i,nSex=rand()%2,nM1=50+rand()%51,nM2=60+rand()%41,nM3=70+rand()%31;
//        string stName="",stID="";
//        int temp=rand()%5+4;
//        stName+=(char)(65+rand()%26);
//        stID+=(char)(97+rand()%3);
//        for(int ii=0;ii<temp;ii++){
//            stName+=(char)(97+rand()%26);
//        }
//        for(int ii=0;ii<10;ii++){
//            stID+=(char)(48+rand()%10);
//        }
//        fout<<nFID<<','<<nSex<<','<<nM1<<','<<nM2<<','<<nM3<<','<<stID<<','<<stName<<std::endl;
//        i++;
//    }
//    fout.close();
// /* ***************************** */
    
    return 0;
}
