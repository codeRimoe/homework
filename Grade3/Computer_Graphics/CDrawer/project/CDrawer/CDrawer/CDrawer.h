
// CDrawer.h : CDrawer Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
    #error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CCDrawerApp:
// �йش����ʵ�֣������ CDrawer.cpp
//

class CCDrawerApp : public CWinAppEx
{
public:
    CCDrawerApp();


// ��д
public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();

// ʵ��
    UINT  m_nAppLook;
    BOOL  m_bHiColorIcons;

    virtual void PreLoadState();
    virtual void LoadCustomState();
    virtual void SaveCustomState();

    afx_msg void OnAppAbout();
    DECLARE_MESSAGE_MAP()
};

extern CCDrawerApp theApp;