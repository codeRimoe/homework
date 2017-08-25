#include <iostream>
using namespace std;

#include "compulsory.h"

Compulsory::Compulsory(int a,int b,int c,int d){
    setID(a),setEnglish(b),setPolitics(c),setAdvancedData(d);
}

Compulsory::~Compulsory(){
}

void Compulsory::setID(int a){
    stID=a;
}

void Compulsory::setEnglish(int a){
    english=a;
}

void Compulsory::setPolitics(int a){
    politics=a;
}

void Compulsory::setAdvancedData(int a){
    advancedData=a;
}

int Compulsory::getID(){
    return stID;
}

int Compulsory::getEnglish(){
    return english;
}

int Compulsory::getPolitics(){
    return politics;
}

int Compulsory::getAdvancedData(){
    return advancedData;
}

int Compulsory::sum(){
    return english+politics+advancedData;
}

double Compulsory:: avg(){
    return sum()/3.0;
};

void Compulsory::disp(){
    cout<<"student ID:"<<stID<<endl
        <<"===================="<<endl
        <<"Compulsory Course"<<endl
        <<"English:"<<english<<endl
        <<"Politics:"<<politics<<endl
        <<"Advanced Data:"<<advancedData<<endl
        <<"--------------------"<<endl
        <<"Sum:"<<sum()<<endl
        <<"Avg:"<<avg()<<endl;
}
