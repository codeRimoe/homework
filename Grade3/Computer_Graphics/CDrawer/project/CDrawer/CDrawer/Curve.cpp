#include "StdAfx.h"
#include "Curve.h"
#include "CLine.h"
#include <vector>

CCurve::CCurve(void): color(RGB(0,0,0)) ,dc(NULL), acc(20){
}


CCurve::~CCurve(void){
}

void CCurve::addCP(CPoint P){
	CLine l;
	l.setColor(color);
    l.setDC(dc);
    l.setType(1);
	l.setS(P);
	if(!CP.empty()){
		l.setE(CP.back());
		l.dLine();
	}
    CP.push_back(P);
    this->drawCP(P);
}

inline void CCurve::drawCP(CPoint P){
    dc->SetPixel(P,color);
    dc->SetPixel(P.x-1,P.y,color);
    dc->SetPixel(P.x,P.y-1,color);
    dc->SetPixel(P.x+1,P.y,color);
    dc->SetPixel(P.x,P.y+1,color);
    dc->SetPixel(P.x-2,P.y,color);
    dc->SetPixel(P.x,P.y-2,color);
    dc->SetPixel(P.x+2,P.y,color);
    dc->SetPixel(P.x,P.y+2,color);
}

void CCurve::setDC(CClientDC* d){
    dc = d;
}

void CCurve::setColor(COLORREF c){
    color = c;
}

void CCurve::setType(int i){
    this->type = i;
}

void CCurve::setAcc(int i){
    acc = i;
}

int CCurve::getType(){
    return type;
}

inline void CCurve::drawAll(int type){
	CLine l;
	l.setColor(color);
    l.setDC(dc);
    l.setType(1);
    for(std::vector<CPoint>::iterator it=CP.begin();it!=CP.end();){
        CPoint P=*it++;
		this->drawCP(P);
        l.setS(P);
		if(it!=CP.end()){
			l.setE(*it);
			dc->SetROP2(R2_NOTXORPEN);
			l.dLine();
	    }
    }
}

void CCurve::reset(){
    if(CP.empty())return;
    dc->SetROP2(R2_NOTXORPEN);
    drawAll(0);
    // clear the curve
    for(int i=0;i<CP.size()/3;i++){
        dCurve(3*(i+1));
    }
    dc->SetROP2(R2_NOTXORPEN);
    // re-draw the curve with pen
    for(int i=0;i<CP.size()/3;i++){
        dCurve(3*(i+1));
    }
    PList.clear();
    CP.clear();
}

CPoint* CCurve::pick_jug(CPoint curP){
    for(std::vector<CPoint>::iterator it=CP.begin();it!=CP.end();++it){
        int dx=curP.x-it->x,dy=curP.y-it->y;
        dx*=dx,dy*=dy;
        if((dx+dy)<5)
            return &(*it);
    }
    return NULL;
}

void CCurve::dCurve(){
    if (type==0)
        for(int i=0;i<CP.size()/3;i++)
            dCurve(3*(i+1));
    else
        for(int i=3;i<CP.size();i++)
            dCurve(i);
}

void CCurve::dCurve(int ip){
    CLine l;
    double t=0;
    l.setColor(color);
    l.setDC(dc);
    l.setType(0);
    PList.clear();
    for(int i=0; i<=acc;++i){
        if (type==0)
            bezierP(t, ip);
        else
            bsP(t, ip);
        t+=1.0/acc;
    }
    for(std::vector<CPoint>::iterator it=PList.begin(); it!=PList.end();){
        l.setS(*it);
        ++it;
        if(it!=PList.end()){
            l.setE(*it);
            l.dLine();
            dc->SetPixel(*it,color);
        }
    }
}

inline void CCurve::bezierP(double t, int i){
    CPoint tp(0);
    tp.x=(1-t)*(1-t)*(1-t)*CP[i-3].x;
    tp.x+=3*t*(1-t)*(1-t)*CP[i-2].x;
    tp.x+=3*t*t*(1-t)*CP[i-1].x;
    tp.x+=t*t*t*CP[i].x;
    tp.y=(1-t)*(1-t)*(1-t)*CP[i-3].y;
    tp.y+=3*t*(1-t)*(1-t)*CP[i-2].y;
    tp.y+=3*t*t*(1-t)*CP[i-1].y;
    tp.y+=t*t*t*CP[i].y;
    PList.push_back(tp);
}

void CCurve::bsP(double t, int i){
    CPoint tp(0);
    tp.x=(-t*t*t+3*t*t-3*t+1)*CP[i-3].x;
    tp.x+=(3*t*t*t-6*t*t+4)*CP[i-2].x;
    tp.x+=(-3*t*t*t+3*t*t+3*t+1)*CP[i-1].x;
    tp.x+=t*t*t*CP[i].x;
    tp.x/=6;
    tp.y=(-t*t*t+3*t*t-3*t+1)*CP[i-3].y;
    tp.y+=(3*t*t*t-6*t*t+4)*CP[i-2].y;
    tp.y+=(-3*t*t*t+3*t*t+3*t+1)*CP[i-1].y;
    tp.y+=t*t*t*CP[i].y;
    tp.y/=6;
    PList.push_back(tp);
}

