
// CDrawerView.h : CCDrawerView ��Ľӿ�
//

#pragma once

#include <vector>
#include "CLine.h"
#include "Circle.h"
#include "Cut.h"
#include "Fill.h"
#include "Ctrans.h"
#include "Curve.h"

class CCDrawerView : public CView
{
protected: // �������л�����
    CCDrawerView();
    DECLARE_DYNCREATE(CCDrawerView)

// ����
public:
    CCDrawerDoc* GetDocument() const;

// ����
public:

// ��д
public:
    virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
    virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
    virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
    virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
    virtual ~CCDrawerView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    int MenuDrawType, PressNum;
    bool isCtrl;
    CPoint* curve_pick;
    std::vector <CLine> LineList;
	std::vector <CPoint> transMP;
    std::vector <COLORREF> LineColor;
    COLORREF fg_color;
    CLine cl;
    CCurve ccur;
    CCircle cc;
    CCut tan_clip;
    CFill filler;
    Ctrans transer;

// ���ɵ���Ϣӳ�亯��
protected:
    afx_msg void OnFilePrintPreview();
    afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnBrel();
    afx_msg void OnDdal();
    afx_msg void Oncenc();
    afx_msg void OnPolyc();
    afx_msg void OnClip();
    afx_msg void OnFill();
    afx_msg void OnTran();
    afx_msg void OnFg();
    afx_msg void Onbzc();
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnBc();
    afx_msg void Ondisappear();
	afx_msg void OnTransl();
};

#ifndef _DEBUG  // CDrawerView.cpp �еĵ��԰汾
inline CCDrawerDoc* CCDrawerView::GetDocument() const
   { return reinterpret_cast<CCDrawerDoc*>(m_pDocument); }
#endif

