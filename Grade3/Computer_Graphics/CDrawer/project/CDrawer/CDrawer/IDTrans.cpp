// IDTrans.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CDrawer.h"
#include "IDTrans.h"
#include "afxdialogex.h"


// IDTrans �Ի���

IMPLEMENT_DYNAMIC(IDTrans, CDialogEx)

IDTrans::IDTrans(CWnd* pParent /*=NULL*/)
    : CDialogEx(IDTrans::IDD, pParent)
{

}

IDTrans::~IDTrans()
{
}

void IDTrans::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(IDTrans, CDialogEx)
END_MESSAGE_MAP()


// IDTrans ��Ϣ�������
