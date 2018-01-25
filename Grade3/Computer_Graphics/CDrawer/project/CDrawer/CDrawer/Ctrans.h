#pragma once
#include "atltypes.h"
#include <vector>
#include "CLine.h"

class Ctrans{
public:
    Ctrans();
    virtual ~Ctrans();

public:
    void setUL(CPoint);
    void setLR(CPoint);
    void setDC(CClientDC*);
    void setM(std::vector<CPoint>);
	void setType(int);
	void setTtype(int);
	int getType();
	int getTtype();
    void dtan();
    void trans(std::vector<CLine>*);

protected:
    std::vector<double> tran(std::vector<double>);
	double contD2(CPoint,CPoint);
	void tantrans();
	void linetrans(std::vector<CLine>*);

private:
	int type,ttype;
    std::vector<std::vector<double>> PList;
    std::vector<COLORREF> ColorList;
    double matrix[3][3];
    CPoint ul,lr;
    CPoint p1,p2;
    CLine _cl;
    CClientDC* dc;
};

