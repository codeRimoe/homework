
// CDrawerDoc.cpp : CCDrawerDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "CDrawer.h"
#endif

#include "CDrawerDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCDrawerDoc

IMPLEMENT_DYNCREATE(CCDrawerDoc, CDocument)

BEGIN_MESSAGE_MAP(CCDrawerDoc, CDocument)
END_MESSAGE_MAP()


// CCDrawerDoc ����/����

CCDrawerDoc::CCDrawerDoc()
{
    // TODO: �ڴ����һ���Թ������

}

CCDrawerDoc::~CCDrawerDoc()
{
}

BOOL CCDrawerDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;

    // TODO: �ڴ�������³�ʼ������
    // (SDI �ĵ������ø��ĵ�)

    return TRUE;
}




// CCDrawerDoc ���л�

void CCDrawerDoc::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        // TODO: �ڴ���Ӵ洢����
    }
    else
    {
        // TODO: �ڴ���Ӽ��ش���
    }
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CCDrawerDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
    // �޸Ĵ˴����Ի����ĵ�����
    dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

    CString strText = _T("TODO: implement thumbnail drawing here");
    LOGFONT lf;

    CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
    pDefaultGUIFont->GetLogFont(&lf);
    lf.lfHeight = 36;

    CFont fontDraw;
    fontDraw.CreateFontIndirect(&lf);

    CFont* pOldFont = dc.SelectObject(&fontDraw);
    dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
    dc.SelectObject(pOldFont);
}

// ������������֧��
void CCDrawerDoc::InitializeSearchContent()
{
    CString strSearchContent;
    // ���ĵ����������������ݡ�
    // ���ݲ���Ӧ�ɡ�;���ָ�

    // ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
    SetSearchContent(strSearchContent);
}

void CCDrawerDoc::SetSearchContent(const CString& value)
{
    if (value.IsEmpty())
    {
        RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
    }
    else
    {
        CMFCFilterChunkValueImpl *pChunk = NULL;
        ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
        if (pChunk != NULL)
        {
            pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
            SetChunkValue(pChunk);
        }
    }
}

#endif // SHARED_HANDLERS

// CCDrawerDoc ���

#ifdef _DEBUG
void CCDrawerDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void CCDrawerDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif //_DEBUG


// CCDrawerDoc ����
