// IDTrans.cpp : 实现文件
//

#include "stdafx.h"
#include "CDrawer.h"
#include "IDTrans.h"
#include "afxdialogex.h"


// IDTrans 对话框

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


// IDTrans 消息处理程序
