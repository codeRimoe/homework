#include "StdAfx.h"
#include "Circle.h"
#include "CLine.h"
#include <Cmath>

CCircle::CCircle() : cP(0), r(0), color(RGB(0,0,0)) ,dc(NULL){
    line.setType(0);
}


CCircle::~CCircle(){
}

void CCircle::setColor(COLORREF c){
    color = c;
    line.setColor(c);
}

void CCircle::setC(CPoint P){
    cP = P;
}

void CCircle::setr(double inr){
    r = inr;
}

void CCircle::setr(CPoint p){
    int dx = p.x - cP.x, dy = p.y - cP.y;
    double r2 = sqrt(double(dx * dx + dy *dy));
    this->setr(r2);
}

void CCircle::setDC(CClientDC* d){
    dc = d;
    line.setDC(d);
}

void CCircle::setType(int i){
    this->type = i;
}

void CCircle::dcP(int x,int y){
    dc->SetPixel(cP.x+x,cP.y+y,color);
}

void CCircle::dcPs(int x,int y){
    dcP(x,y);
    dcP(-x,y);
    dcP(x,-y);
    dcP(-x,-y);
    dcP(y,x);
    dcP(-y,x);
    dcP(y,-x);
    dcP(-y,-x);
}

void CCircle::dL(CPoint sP, CPoint eP){
    line.setS(sP+cP);
    line.setE(eP+cP);
    line.dLine();
}

void CCircle::dLs(CPoint sP, CPoint eP){
    long t = 0;
    dL(sP,eP);
    /*dL(-sP,-eP);

    sP.x+=sP.y;
    sP.y-=sP.x;
    sP.x+=sP.y;

    eP.x+=eP.y;
    eP.y-=eP.x;
    eP.x+=eP.y;

    dL(sP,eP);
    dL(-sP,-eP);*/
}

void CCircle::dPoly(double d){
    const double PI=3.14159;
    int n = 2 * PI / d;
    CPoint sP,eP;
    eP.x = 0;
    eP.y = r;
    for(int i=1;i<=n;++i){
        sP = eP;
        eP.x = r * sin(i*d);
        eP.y = r * cos(i*d);
        dLs(sP,eP);
    }
    sP = eP;
    eP.x = 0;
    eP.y = r;
    dLs(sP,eP);
}


void CCircle::dCircle(){
    if (this->type==0)
        this->MPCircle();
    else
        this->PolyCircle();
}


void CCircle::MPCircle(){
    
    int x=0, y=r;
    double e=1-r;
    dcPs(x,y);//做对称处理
    while(x<=y){    
        if(e<0)
            e+=2*x+3;
        else{ 
            e+=2*(x-y)+5;
            y--;
        }
        x++;
        dcPs(x,y); //做对称处理
    }
}

void CCircle::PolyCircle(){
    double d = 1e-4;
    double alpha = 2 * acos(1-d);
    dPoly(alpha);
}
