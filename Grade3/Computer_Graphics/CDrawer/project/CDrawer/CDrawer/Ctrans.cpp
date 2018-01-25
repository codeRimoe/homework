#include "StdAfx.h"
#include "Ctrans.h"

Ctrans::Ctrans(void)
{
}


Ctrans::~Ctrans(void)
{
}


void Ctrans::setUL(CPoint ul){
    this->ul = ul;
}

void Ctrans::setLR(CPoint lr){
    this->lr = lr;
    this->p1.SetPoint(this->ul.x,this->lr.y);
    this->p2.SetPoint(this->lr.x,this->ul.y);
}

void Ctrans::setDC(CClientDC* pdc){
    this->dc=pdc;
    this->_cl.setDC(pdc);
}

void Ctrans::setType(int t){
    type=t;
}
void Ctrans::setTtype(int t){
	ttype=t;
}

int Ctrans::getType(){
	return type;
}

int Ctrans::getTtype(){
	return ttype;
}

void Ctrans::setM(std::vector<CPoint> ps){
	double ctheta=1, stheta=0, dx=0, dy=0, sx=1, sy=1;
	double Px=0, Py=0;
	if (type==0){
		dx=ps[1].x-ps[0].x;
		dy=ps[1].y-ps[0].y;
	}
	else if (type==1){
		double b=sqrt(contD2(ps[0],ps[1])),c=sqrt(contD2(ps[0],ps[2]));
		double c1x=ps[1].x-ps[0].x,s1y=ps[1].y-ps[0].y;
		double c2x=ps[2].x-ps[0].x,s2y=ps[2].y-ps[0].y;
		c1x/=b,s1y/=b,c2x/=c,s2y/=c;
		ctheta=c1x*c2x+s1y*s2y;
		stheta=s2y*c1x-c2x*s1y;
		Px=ps[0].x;
		Py=ps[0].y;
	}
	else if (type==2){
		double sl=sqrt(contD2(ps[0],ps[1]));
		sx=ps[2].x-ps[0].x,sy=ps[2].y-ps[0].y;
		Px=ps[0].x;
		Py=ps[0].y;
		sx/=sl;
		sy/=sl;
	}
    matrix[0][0]=sx*ctheta, matrix[0][1]=-stheta, matrix[0][2]=dx+Px*(1-sx)+Px*(1-ctheta) + Py*stheta;
    matrix[1][0]=stheta, matrix[1][1]=sy*ctheta, matrix[1][2]=dy+Py*(1-sy)+Py*(1-ctheta) - Px*stheta;
    matrix[2][0]=0, matrix[2][1]=0, matrix[2][2]=1;
}

void Ctrans::dtan(){
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


inline std::vector<double> Ctrans::tran(std::vector<double> inP){
    std::vector<double> outP;
    for(int i =0; i<3; i++){
        outP.push_back(0);
        for(int j=0; j<3; j++)
            outP[i]+=matrix[i][j]*inP[j];
    }
    return outP;
}

inline double Ctrans::contD2(CPoint a,CPoint b){
	return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}

void Ctrans::trans(std::vector<CLine>* lx){
    if(ttype==0)
		linetrans(lx);
	else
		tantrans();
}

void Ctrans::linetrans(std::vector<CLine>* lx){
	for(std::vector<CLine>::iterator iter=lx->begin();iter!=lx->end();iter++){
		dc->SetROP2 (R2_NOTXORPEN);
		iter->dLine();
		std::vector<std::vector<double>> tmp;
		tmp=iter->getPV();
        tmp[0] = tran(tmp[0]);
		tmp[1] = tran(tmp[1]);
		iter->setPV(tmp);
        iter->dLine();
	}
}

void Ctrans::tantrans(){
    int mx=ul.x,my=ul.y,nx=lr.x,ny=lr.y,t;
    if(mx>nx)
        t=mx,mx=nx,nx=t;
    if(my>ny)
        t=my,my=ny,ny=t;
    ul.SetPoint(mx,my);
    lr.SetPoint(nx,ny);
    for(int i = mx;i<=nx;i++){
        for(int j = my;j<=ny;j++){
            std::vector<double> tmp;
            COLORREF color = this->dc->GetPixel(i,j);
            tmp.push_back(i);
            tmp.push_back(j);
            tmp.push_back(1);
            this->PList.push_back(tmp);
            this->ColorList.push_back(color);
            this->dc->SetROP2 (R2_NOTXORPEN);
            this->dc->SetPixel(i,j,color);
        }
    }
    while(!PList.empty()){
        std::vector<double> tmp;
        tmp = tran(PList.back());
        PList.pop_back();
        this->dc->SetPixel(tmp[0],tmp[1],ColorList.back());
        ColorList.pop_back();
    }
}