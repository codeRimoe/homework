#pragma once
#include "atltypes.h"
#include <stack>

class CFill    {
public:
    CFill();
    virtual ~CFill();

public:
    void fill(CPoint);
    void setColor(COLORREF);
    void setDC(CClientDC*);

private:
    CClientDC* dc;
    COLORREF color;
    std::stack<CPoint> fill_pix;
};

