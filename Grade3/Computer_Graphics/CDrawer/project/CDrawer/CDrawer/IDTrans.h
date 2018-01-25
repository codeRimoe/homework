#pragma once


// IDTrans 对话框

class IDTrans : public CDialogEx
{
    DECLARE_DYNAMIC(IDTrans)

public:
    IDTrans(CWnd* pParent = NULL);   // 标准构造函数
    virtual ~IDTrans();

// 对话框数据
    enum { IDD = IDD_TRANS };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    DECLARE_MESSAGE_MAP()
};
