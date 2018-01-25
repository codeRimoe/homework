#pragma once
#include "atltypes.h"
#include<vector>


class CLine{
public:
    CLine();
    virtual ~CLine();

public:
    void dLine();
    void DDALine();
    void BreLine();
    bool clip(CPoint UL, CPoint LR);
    void setColor(COLORREF);
    void setS(CPoint);
    void setE(CPoint);
    void setDC(CClientDC*);
    void setType(int);
	std::vector<std::vector<double>> getPV();      //for trans
	void setPV(std::vector<std::vector<double>>); //for trans

protected:
    unsigned char encode(CPoint, CPoint, CPoint);
    void swapPts(CPoint&, CPoint&);
    void swapCode(unsigned char&, unsigned char&);

private:
    CPoint startP;
    CPoint endP;
    int type;
    CClientDC* dc;
    COLORREF color;
};

