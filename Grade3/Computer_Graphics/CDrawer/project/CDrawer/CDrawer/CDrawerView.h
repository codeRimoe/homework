
// CDrawerView.h : CCDrawerView 类的接口
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
protected: // 仅从序列化创建
    CCDrawerView();
    DECLARE_DYNCREATE(CCDrawerView)

// 特性
public:
    CCDrawerDoc* GetDocument() const;

// 操作
public:

// 重写
public:
    virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
    virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
    virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
    virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
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

// 生成的消息映射函数
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

#ifndef _DEBUG  // CDrawerView.cpp 中的调试版本
inline CCDrawerDoc* CCDrawerView::GetDocument() const
   { return reinterpret_cast<CCDrawerDoc*>(m_pDocument); }
#endif

