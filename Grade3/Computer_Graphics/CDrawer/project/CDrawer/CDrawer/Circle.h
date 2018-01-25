#pragma once
#include "atltypes.h"
#include "CLine.h"

class CCircle
{
public:
    CCircle();
    virtual ~CCircle();

public:
    void dCircle();
    void MPCircle();
    void PolyCircle();
    void setColor(COLORREF);
    void setC(CPoint);
    void setr(double);
    void setr(CPoint);
    void setDC(CClientDC*);
    void setType(int);

protected:
    void dcP(int,int);
    void dcPs(int,int);
    void dPoly(double);
    void dL(CPoint,CPoint);
    void dLs(CPoint,CPoint);

private:
    CLine line;
    CPoint cP;
    double r;
    int type;
    CClientDC* dc;
    COLORREF color;
};

