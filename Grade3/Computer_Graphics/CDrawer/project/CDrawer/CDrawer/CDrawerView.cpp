
// CDrawerView.cpp : CCDrawerView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "CDrawer.h"
#endif

#include "CDrawerDoc.h"
#include "CDrawerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCDrawerView

IMPLEMENT_DYNCREATE(CCDrawerView, CView)

BEGIN_MESSAGE_MAP(CCDrawerView, CView)
    // ��׼��ӡ����
    ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCDrawerView::OnFilePrintPreview)
    ON_WM_CONTEXTMENU()
    ON_WM_RBUTTONUP()
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
    ON_COMMAND(BreL, &CCDrawerView::OnBrel)
    ON_COMMAND(DDAL, &CCDrawerView::OnDdal)
    ON_COMMAND(cenC, &CCDrawerView::Oncenc)
    ON_COMMAND(PolyC, &CCDrawerView::OnPolyc)
    ON_COMMAND(Clip, &CCDrawerView::OnClip)
    ON_COMMAND(Fill, &CCDrawerView::OnFill)
//    ON_UPDATE_COMMAND_UI(Tran, &CCDrawerView::OnUpdateTran)
//ON_UPDATE_COMMAND_UI(Tran, &CCDrawerView::OnUpdateTran)
ON_COMMAND(Tran, &CCDrawerView::OnTran)
ON_COMMAND(FG, &CCDrawerView::OnFg)
ON_COMMAND(bzC, &CCDrawerView::Onbzc)
ON_WM_RBUTTONDOWN()
ON_WM_LBUTTONDBLCLK()
ON_WM_KEYDOWN()
ON_WM_KEYUP()
ON_COMMAND(Bc, &CCDrawerView::OnBc)
ON_COMMAND(disappear, &CCDrawerView::Ondisappear)
ON_COMMAND(TransL, &CCDrawerView::OnTransl)
END_MESSAGE_MAP()

// CCDrawerView ����/����

CCDrawerView::CCDrawerView():fg_color(RGB(0,0,0)),isCtrl(false)
{
    // TODO: �ڴ˴���ӹ������
    
}

CCDrawerView::~CCDrawerView()
{
}

BOOL CCDrawerView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: �ڴ˴�ͨ���޸�
    //  CREATESTRUCT cs ���޸Ĵ��������ʽ

    return CView::PreCreateWindow(cs);
}

// CCDrawerView ����

void CCDrawerView::OnDraw(CDC* /*pDC*/)
{
    CCDrawerDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    // TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CCDrawerView ��ӡ


void CCDrawerView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
    AFXPrintPreview(this);
#endif
}

BOOL CCDrawerView::OnPreparePrinting(CPrintInfo* pInfo)
{
    // Ĭ��׼��
    return DoPreparePrinting(pInfo);
}

void CCDrawerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CCDrawerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: ��Ӵ�ӡ����е��������
}

void CCDrawerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
    ClientToScreen(&point);
    OnContextMenu(this, point);
}

void CCDrawerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
    theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCDrawerView ���

#ifdef _DEBUG
void CCDrawerView::AssertValid() const
{
    CView::AssertValid();
}

void CCDrawerView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CCDrawerDoc* CCDrawerView::GetDocument() const // �ǵ��԰汾��������
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCDrawerDoc)));
    return (CCDrawerDoc*)m_pDocument;
}
#endif //_DEBUG


// CCDrawerView ��Ϣ�������

 void draw10(CClientDC* dc,CPoint P,COLORREF color){
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

void drawL(CClientDC* dc,CPoint P0,CPoint P1,COLORREF color){
	CLine ll;
	ll.setDC(dc);
	ll.setColor(color);
	ll.setS(P0);
	ll.setE(P1);
	ll.dLine();
}

void drawMHDL(CClientDC* dc,CPoint P0,CPoint P1,COLORREF color){
	CPoint P2(P1);
	P2.x=P0.x;
	drawL(dc,P0,P2,color);
	drawL(dc,P1,P2,color);
}

void clearD(std::vector<CPoint> CP, int type, CClientDC* dc, COLORREF color){
	dc->SetROP2(R2_NOTXORPEN);
	for(std::vector<CPoint>::iterator iter=CP.begin(); iter!=CP.end(); ++iter)
		draw10(dc,*iter,color);
	drawL(dc,CP[0],CP[1],color);
	if(type==1){
	    drawL(dc,CP[0],CP[2],color);
	}
	else if(type==2){
	    drawMHDL(dc,CP[0],CP[2],color);
	}
}

void CCDrawerView::OnLButtonDown(UINT nFlags, CPoint point)
{
    // ���
    CClientDC dc(this);
    if ( MenuDrawType == 1 ) { //���߶�
        cl.setDC(&dc);
        cl.setColor(fg_color);
        if ( PressNum == 0 ) { //��һ�ΰ�����������ָ���߶ε����
            cl.setS(point); 
            cl.setE(point);
            PressNum ++; 
            SetCapture(); 
        } 
        else{ 
            cl.setE(point); //�ڶ��ΰ�����������ָ���߶ε��յ�
            //cl.dLine();
            CLine tmpc(cl);
            tmpc.setColor(fg_color);
            tmpc.dLine();
            PressNum = 0; 
            LineList.push_back(tmpc);
            //LineList.back().dLine();
            ReleaseCapture(); 

        } 
    }
    else if ( MenuDrawType == 2 ) { //��Բ
        cc.setDC(&dc);
        cc.setColor(fg_color);
        if ( PressNum == 0 ) { //��һ�ΰ�����������ָ��Բ��Բ��
            cc.setC(point);
            cc.setr(point);
            PressNum ++; 
            SetCapture(); 
        } 
        else{
            cc.setr(point); //�ڶ��ΰ�����������ָ��Բ�İ뾶
            cc.dCircle();
            PressNum = 0; 
            ReleaseCapture(); 
        } 
    }
    else if ( MenuDrawType == 3 ) { //�ü�
        tan_clip.setDC(&dc);
        if ( PressNum == 0 ) { //��һ�ΰ�����������ָ���ǵ�
            tan_clip.setUL(point);
            tan_clip.setLR(point);
            PressNum ++; 
            SetCapture(); 
        } 
        else{
            tan_clip.setLR(point); //�ڶ��ΰ�����������ָ���Խǵ�
            dc.SetROP2 (R2_NOT);
            tan_clip.dtan();
            tan_clip.cut(LineList);
            PressNum = 0; 
            ReleaseCapture(); 
        }
    }
    else if ( MenuDrawType == 4 ) { //���
        filler.setDC(&dc);
        filler.setColor(fg_color);
        filler.fill(point);
    }
    else if ( MenuDrawType == 5 ) { //�任
        transer.setDC(&dc);
		std::vector<CLine>* pL=NULL;
		if(transer.getTtype()==0)pL=&LineList;
		if ( PressNum == 0 ) { //��һ�ΰ�����������ָ���ǵ�
			transer.setUL(point);
			transer.setLR(point);
			PressNum ++; 
			SetCapture(); 
		} 
		else if ( PressNum == 1 ){
			transer.setLR(point); //�ڶ��ΰ�����������ָ���Խǵ�
			dc.SetROP2 (R2_NOTXORPEN); 
			transer.dtan();
			PressNum ++; 
			ReleaseCapture(); 
		}
		else if(PressNum==2){
			transMP.push_back(point);
			dc.SetROP2 (R2_NOTXORPEN);
			draw10(&dc, point, fg_color);
			PressNum ++; 
			transMP.push_back(transMP[0]);
		}
		else if(PressNum==3){
			transMP[1]=point;
			dc.SetROP2 (R2_NOTXORPEN);
			draw10(&dc, point, fg_color);
			//drawL(&dc,transMP[0],point,fg_color);
			if(transer.getType()==0){
				clearD(transMP,transer.getType(),&dc,fg_color);
				transer.setM(transMP);
				transer.trans(pL);
				PressNum=transer.getTtype()?0:2;
				transMP.clear();
			}
			else{
				transMP.push_back(transMP[0]);
				PressNum ++; 
			}
		}
		else{
			transMP[2]=point;
			dc.SetROP2 (R2_NOTXORPEN);
			draw10(&dc, point, fg_color);
			/*if(transer.getType()==1)
				drawL(&dc,transMP[0],point,fg_color);
			else
				drawMHDL(&dc,transMP[0],point,fg_color);*/
			clearD(transMP,transer.getType(),&dc,fg_color);
			transer.setM(transMP);
			transer.trans(pL);
			PressNum=transer.getTtype()?0:2;
			
			transMP.clear();
		}
    }
    else if ( MenuDrawType == 6 ){ //����
        ccur.setDC(&dc);
        if (curve_pick)         //throw pick up point
            curve_pick=NULL;
        else if(isCtrl)         //pick up
            curve_pick=ccur.pick_jug(point);
        else{
            ccur.addCP(point);  //add CP
			if(((ccur.getType()==1)&&(PressNum>=3))||((PressNum!=0)&&(PressNum%3==0))){
                ccur.setColor(fg_color);
                ccur.dCurve();
            }
            ++PressNum;
        }
    }
    CView::OnLButtonDown(nFlags, point);
}

void CCDrawerView::OnLButtonUp(UINT nFlags, CPoint point)
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

    CView::OnLButtonUp(nFlags, point);
}

void CCDrawerView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    CClientDC dc(this);
    // ˫��
    if ( MenuDrawType == 6 ){
        PressNum = 0;
        ccur.setColor(fg_color);
        ccur.reset();
    }
    CView::OnLButtonDblClk(nFlags, point);
}


void CCDrawerView::OnRButtonDown(UINT nFlags, CPoint point)
{
    // �һ�

    CView::OnRButtonDown(nFlags, point);
}

void CCDrawerView::OnMouseMove(UINT nFlags, CPoint point)
{
    // �ƶ����
    CClientDC dc(this); //���嵱ǰ��ͼ�豸
    dc.SetROP2 (R2_NOTXORPEN); 
    if(PressNum == 1){
        if ( MenuDrawType == 1 ){
            cl.setDC(&dc);
            cl.dLine();
            cl.setE(point);
            cl.dLine();
        }
        else if ( MenuDrawType == 2 ){
            cc.setDC(&dc);
            cc.dCircle();
            cc.setr(point);
            cc.dCircle();
        }
        else if ( MenuDrawType == 3 ){
            tan_clip.setDC(&dc);
            tan_clip.dtan();
            tan_clip.setLR(point);
            tan_clip.dtan();
        }
    }
	if ( MenuDrawType==5 ){
		if(PressNum==1){
			transer.setDC(&dc);
			transer.dtan();
			transer.setLR(point);
			transer.dtan();
		}
		else if(PressNum==3){
			drawL(&dc,transMP[0],transMP[1],fg_color);
			transMP[1]=point;
			drawL(&dc,transMP[0],transMP[1],fg_color);
		}
		else if(PressNum==4){
			if(transer.getType()==1)
			    drawL(&dc,transMP[0],transMP[2],fg_color);
			else
				drawMHDL(&dc,transMP[0],transMP[2],fg_color);
			transMP[2]=point;
			if(transer.getType()==1)
			    drawL(&dc,transMP[0],transMP[2],fg_color);
			else
				drawMHDL(&dc,transMP[0],transMP[2],fg_color);
	    }
    }
    else if (MenuDrawType == 6){
        if(curve_pick){
            ccur.dCurve();
            ccur.drawAll(0);
            curve_pick->SetPoint(point.x,point.y);
            ccur.dCurve();
            ccur.drawAll(0);
        }
    }
    CView::OnMouseMove(nFlags, point);
}

void CCDrawerView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    if(MenuDrawType==6)
		if(nChar&VK_CONTROL)
            isCtrl = true;

	if(MenuDrawType==5){
		if(nChar=='1')
		    transer.setType(0);
		else if (nChar=='2')
			transer.setType(1);
		else if (nChar=='3')
			transer.setType(2);
	}

    CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CCDrawerView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    if(nChar&VK_CONTROL){
        isCtrl = false;
    }
    CView::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CCDrawerView::OnBrel()
{
    // Bresenham�㷨���߶�
    MenuDrawType = 1; 
    PressNum = 0;
    cl.setType(1);
    cl.setColor(fg_color);
}


void CCDrawerView::OnDdal()
{
    // DDA�㷨���߶�
    MenuDrawType = 1; 
    PressNum = 0;
    cl.setType(0);
    cl.setColor(fg_color);
}


void CCDrawerView::Oncenc()
{
    // �е㷨��Բ
    MenuDrawType = 2; 
    PressNum = 0;
    cc.setType(0);
    cc.setColor(fg_color);
}


void CCDrawerView::OnPolyc()
{
    // ����αƽ���Բ
    MenuDrawType = 2; 
    PressNum = 0;
    cc.setType(1);
    cc.setColor(fg_color);
}


void CCDrawerView::OnClip()
{
    // �ü�
    MenuDrawType = 3; 
    PressNum = 0;
}


void CCDrawerView::OnFill()
{
    // ���
    MenuDrawType = 4;
    filler.setColor(fg_color);
}

void CCDrawerView::OnTran()
{
    // ��ѡ�任
    MenuDrawType = 5; 
    PressNum = 0;
	transer.setTtype(1);
	transer.setType(0);
}

void CCDrawerView::OnTransl()
{
	// ֱ�߱任
	MenuDrawType = 5; 
    PressNum = 2;
	transer.setTtype(0);
	transer.setType(0);
}


void CCDrawerView::Onbzc()
{
    // ����bezier����
    MenuDrawType = 6; 
    curve_pick=NULL;
    PressNum = 0;
    ccur.setType(0);
    ccur.setColor(fg_color);
    ccur.reset();
}

void CCDrawerView::OnBc()
{
    // TODO: �ڴ���������������
    MenuDrawType = 6; 
    curve_pick=NULL;
    PressNum = 0;
    ccur.setType(1);
    ccur.setColor(fg_color);
    ccur.reset();
}

 bool pinPoly (int px, int py, std::vector<CPoint> pts, int n){
     int ncross=0,pty=0;  
     CPoint p0(px,py);
     CPoint p1,p2;
     for (int i = 0; i<n-1;i++ ) {
         p1 = pts[i];
         p2 = pts[i+1];
         if (((p0.x >= p1.x ) && (p0.x < p2.x )) || ( (p0.x >= p2.x ) && (p0.x < p1.x) )) {
             pty = p1.y + (p0.x -p1.x) *(p2.y -p1.y)/(p2.x -p1.x);
             if (pty > p0.y)
                ncross++;
        }
     }
     p1 = pts[n-1];
     p2 = pts[0];
     if (((p0.x >= p1.x ) && (p0.x < p2.x )) |( (p0.x >= p2.x ) && (p0.x < p1.x) )) {
         pty = p1.y + (p0.x -p1.x) *(p2.y -p1.y)/(p2.x -p1.x);
             if (pty > p0.y)
                  ncross++;
     }
     return ((ncross >0)&&((ncross%2)==1));
}


void CCDrawerView::Ondisappear()
{
	// ����ʾ��
    //int a[4][3]={{50,0,200},{50,250,200},{170,250,200},{170,0,200}}, //  0, 0, 1, 200
    //    b[4][3]={{0,90,100},{0,170,100},{220,170,100},{220,90,100}}, //  0, 0, 1, 100
    //    c[3][3]={{100,120,250},{200,220,50},{250,70,50}};            //  3, 1, 2, -920
	/*
	std::vector<std::vector<int>> a,b,c;
	std::vector<int> tmp;
	for(int i=0;i<3;++i)
		tmp.push_back(0);
	for(int i=0;i<4;++i){
	    a.push_back(tmp);
		b.push_back(tmp);
		if(i<3)
			c.push_back(tmp);
	}
	a[0][0]=50, a[0][1]=0,  a[0][2]=200;
	a[1][0]=50, a[1][1]=250,a[1][2]=200;
	a[2][0]=170,a[2][1]=250,a[2][2]=200;
	a[3][0]=170,a[3][1]=0,  a[3][2]=200;

	b[0][0]=0,  a[0][1]=90, a[0][2]=100;
	b[1][0]=0,  a[1][1]=170,a[1][2]=100;
	b[2][0]=220,a[2][1]=170,a[2][2]=100;
	b[3][0]=220,a[3][1]=90, a[3][2]=100;

	c[0][0]=100,c[0][1]=120,c[0][2]=250;
	c[1][0]=200,c[1][1]=220,c[1][2]=50;
	c[2][0]=150,c[2][1]=70, c[2][2]=50;
	*/
	std::vector<CPoint> a,b,c;

	a.push_back(CPoint(50,0));
	a.push_back(CPoint(50,250));
	a.push_back(CPoint(170,250));
	a.push_back(CPoint(170,0));

	b.push_back(CPoint(0,90));
	b.push_back(CPoint(0,170));
	b.push_back(CPoint(220,170));
	b.push_back(CPoint(220,90));

	c.push_back(CPoint(100,120));
	c.push_back(CPoint(200,220));
	c.push_back(CPoint(250,70));

    int bias_x=50,bias_y=30;
    int max_x=250,max_y=250;//,mz=50;
	//int color_buffer[250][250]={0};//,z_buffer[250][250]={mz};
	CClientDC dc(this);
	COLORREF color1=RGB(255,0,0),color2=RGB(0,255,0),color3=RGB(0,0,255);
    for (int i=0;i<max_y;i++){
        for(int j=0;j<max_x;j++){
            int z1=200,z2=100,z3=(3*i+j-920)/(-2);
			bool in1=pinPoly(i,j,a,4),in2=pinPoly(i,j,b,4),in3=pinPoly(i,j,c,3);
			z1*=in1;
			z2*=in2;
			z3*=in3;			
			if(in1||in2||in3){
				if(z1>z2){
					if(z1>z3)
						dc.SetPixel(i+bias_x,j+bias_y,color1);//z1
					else
						dc.SetPixel(i+bias_x,j+bias_y,color3);//z3
				}
				else{
					if(z2>z3)
						dc.SetPixel(i+bias_x,j+bias_y,color2);//z2
					else
						dc.SetPixel(i+bias_x,j+bias_y,color3);//z3
				}
			}
			/*
			if(in1){
				if((in3)&&(z3>z1)){
					dc.SetPixel(i+bias_x,j+bias_y,color3);//z3
				}
				else{
					dc.SetPixel(i+bias_x,j+bias_y,color1);//z1
				}
			}
			else if(in2){
				if((in3)&&(z3>z2)){
					dc.SetPixel(i+bias_x,j+bias_y,color3);//z3
				}
				else{
					dc.SetPixel(i+bias_x,j+bias_y,color2);//z2
				}
			}
			else if(in3){
				dc.SetPixel(i+bias_x,j+bias_y,color3);//z3
			}
			*/
        }
    }

}


void CCDrawerView::OnFg()
{
    // �ı�ǰ��ɫ
    CColorDialog colorDlg(fg_color);         // ������ɫ�Ի��򣬴����ʼ��ɫֵ   
    if (IDOK == colorDlg.DoModal())          // ��ʾ��ɫ�Ի��򣬲��ж��Ƿ����ˡ�ȷ����   
    {   
        fg_color = colorDlg.GetColor();      // ��ȡ��ɫ�Ի�����ѡ�����ɫֵ
    }  
}
