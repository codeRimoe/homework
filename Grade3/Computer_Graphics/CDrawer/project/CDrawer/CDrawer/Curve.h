#pragma once
#include "atltypes.h"
#include <vector>
#include "CLine.h"
class CCurve{
public:
    CCurve(void);
    virtual ~CCurve(void);

public:
    void dCurve();
    void dCurve(int);
    void setColor(COLORREF);
    void addCP(CPoint);
    void drawCP(CPoint);
    void setDC(CClientDC*);
    void setType(int);
    void setAcc(int);
    void reset();
	int getType();
	void drawAll(int);
    CPoint* pick_jug(CPoint);

protected:
    void bezierP(double, int);
    void bsP(double, int);

private:
    std::vector<CPoint> CP,PList;
    int type,acc;
    CClientDC* dc;
    COLORREF color;
};

