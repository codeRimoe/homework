//#include <vector>
#include "StdAfx.h"
#include "Cut.h"


CCut::CCut(){
}


CCut::~CCut(){
}

void CCut::setUL(CPoint ul){
    this->ul = ul;
}

void CCut::setLR(CPoint lr){
    this->lr = lr;
    this->p1.SetPoint(this->ul.x,this->lr.y);
    this->p2.SetPoint(this->lr.x,this->ul.y);
}

void CCut::setDC(CClientDC* pdc){
    this->dc=pdc;
    this->_cl.setDC(pdc);
}

void CCut::dtan(){
    this->_cl.setS(ul);
    this->_cl.setE(p1);
    _cl.DDALine();
    this->_cl.setE(p2);
    _cl.DDALine();
    this->_cl.setS(lr);
    this->_cl.setE(p1);
    _cl.DDALine();
    this->_cl.setE(p2);
    _cl.DDALine();
}

void CCut::cut(std::vector <CLine> &LineList, int cEx){
    unsigned len = LineList.size();
    int mx=ul.x,my=ul.y,nx=lr.x,ny=lr.y,t=0;
    if(mx>nx)
        t=mx,mx=nx,nx=t;
    if(my>ny)
        t=my,my=ny,ny=t;
    ul.SetPoint(mx,my);
    lr.SetPoint(nx,ny);
    // before cut, set ul/lr as the min/max point.
    dc->SetROP2 (R2_NOTXORPEN); 
    if(cEx){
        std::vector <CLine> newList;
        for (unsigned i=0; i<len; i++){
            LineList[i].dLine();
            if(LineList[i].clip(ul,lr)){
                LineList[i].dLine();
                newList.push_back(LineList[i]);
            }
        }
        LineList = newList;
    }
    else{
        for (unsigned i=0; i<len; i++){
            LineList[i].dLine();
            LineList[i].clip(ul,lr);
            LineList[i].dLine();
        }
    }
}
