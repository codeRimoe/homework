#pragma once
#include <vector>
#include "StdAfx.h"
#include "CLine.h"

class CCut{
public:
    CCut();
    virtual ~CCut();

private:
    CPoint ul,lr;
    CPoint p1,p2;
    CLine _cl;
    CClientDC* dc;

public:
    void setUL(CPoint);
    void setLR(CPoint);
    void setDC(CClientDC*);
    void dtan();
    void cut(std::vector <CLine> &,int=1);

};

