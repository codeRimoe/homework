#pragma once
#include "StdAfx.h"
#include "CLine.h"
#include <iostream>

#define LEFT_EDGE   0x1
#define RIGHT_EDGE  0x2
#define BOTTOM_EDGE 0x4
#define TOP_EDGE    0x8

#define INSIDE(a) (!a)
#define REJECT(a,b) (a&b)
#define ACCEPT(a,b) (!(a|b))

CLine::CLine() : startP(0), endP(0), color(RGB(0,0,0)) ,dc(NULL){
}



CLine::~CLine(void){
}

void CLine::setS(CPoint P){
    startP = P;
}

void CLine::setE(CPoint P){
    endP = P;
}

void CLine::setDC(CClientDC* d){
    dc = d;
}

void CLine::setColor(COLORREF c){
    color = c;
}

void CLine::setType(int i){
    this->type = i;
}

void CLine::dLine(){
    if (this->type==0)
        this->DDALine();
    else
        this->BreLine();
}

void CLine::DDALine(){
    int dx=endP.x-startP.x, dy=endP.y-startP.y, steps, k;
    float xIncrement, yIncrement, x,y;

    x=startP.x;
    y=startP.y; 
    
    if (abs(dx) > abs(dy) ) 
        steps = abs(dx);
    else 
        steps = abs(dy);

    xIncrement = dx / float(steps);
    yIncrement = dy / float(steps);

            
    dc->SetPixel ((int)(x),(int)(y),color);
    
    for( k = 0;k< steps;k++){
        x +=  xIncrement;
        y +=  yIncrement;
        dc->SetPixel ((int)(x),(int)(y),color);
    }
}

void CLine::BreLine(){
    double m, e;
    int i=0,dx=endP.x-startP.x, dy=endP.y-startP.y, x = startP.x, y = startP.y;
	int ix=1,iy=1;
	if(dx<0){
		ix=-1;
		dx=-dx;
	}
	if(dy<0){
		iy=-1;
		dy=-dy;
	}

    m = dy / (double)dx;

    if(m<1){
        e = m - 0.5;
		for ( i = 0 ; i<dx;i++){
			dc->SetPixel ((int)(x),(int)(y),color);
			if( e >= 0 ){
				y = y + iy;
				e = e - 1;
			}
			x = x + ix;
			e = e + m;
		}
    }
    else{
        m = 1 / m;
        e = m - 0.5;
        for ( i = 0 ; i<dy;i++){
			dc->SetPixel ((int)(x),(int)(y),color);
			if( e >= 0 ){
				x = x + ix;
				e = e - 1;
			}
			y = y + iy;
			e = e + m;
		}
    }
}

bool CLine::clip(CPoint UL, CPoint LR){

    unsigned char code1, code2;
    CPoint p1=this->startP,p2=this->endP;
    float m;

    while(true){
        code1 = encode(p1,UL,LR);
        code2 = encode(p2,UL,LR);
        if(ACCEPT(code1,code2)){
            this->startP = p1;
            this->endP = p2;
            return true;
        }
        else if(REJECT(code1,code2))
            return false;
        else{
            if(INSIDE(code1)){
                swapPts(p1,p2);
                swapCode(code1,code2);
            }
            if( p2.x != p1.x)
                m = (float)(p2.y - p1.y) / (p2.x - p1.x);
            if( code1 & LEFT_EDGE){
                p1.y += (UL.x - p1.x) * m;
                p1.x = UL.x;
            }
            else if( code1 & RIGHT_EDGE){
                p1.y += (LR.x - p1.x) * m;
                p1.x = LR.x;
            }
            else if(code1 & BOTTOM_EDGE){
                if( p2.x != p1.x)
                    p1.x += (UL.y - p1.y) / m;
                p1.y = UL.y;
            }
            else if(code1 & TOP_EDGE){
                if( p2.x!= p1.x)
                    p1.x += (LR.y - p1.y) /m;
                p1.y = LR.y;
            }
        }
    }

}

inline unsigned char CLine::encode(CPoint pt, CPoint UL, CPoint LR){
    unsigned char code = 0x00;
    if(pt.x < UL.x)
        code = code | LEFT_EDGE;
    if(pt.x > LR.x )
        code = code | RIGHT_EDGE;
    if(pt.y < UL.y )
        code = code | BOTTOM_EDGE;
    if(pt.y > LR.y)
        code = code | TOP_EDGE;
    return code;
}

inline void CLine::swapPts(CPoint &p1, CPoint &p2){
    CPoint tmp;
    tmp = p1;
    p1 = p2;
    p2 = tmp;
}

inline void CLine::swapCode( unsigned char &c1,unsigned char &c2){
    unsigned char tmp;
    tmp = c1;
    c1 = c2;
    c2 = tmp;
}

std::vector<std::vector<double>>CLine::getPV(){
	std::vector<std::vector<double>> ret;
	std::vector<double> tmp;
	tmp.push_back(startP.x);
	tmp.push_back(startP.y);
	tmp.push_back(1);
	ret.push_back(tmp);
	tmp[0]=endP.x;
	tmp[1]=endP.y;
	ret.push_back(tmp);
	return ret;
}

void CLine::setPV(std::vector<std::vector<double>> pv){
	startP.x=pv[0][0];
	startP.y=pv[0][1];
	endP.x=pv[1][0];
	endP.y=pv[1][1];
}
