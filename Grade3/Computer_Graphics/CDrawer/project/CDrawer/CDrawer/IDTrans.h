#pragma once


// IDTrans �Ի���

class IDTrans : public CDialogEx
{
    DECLARE_DYNAMIC(IDTrans)

public:
    IDTrans(CWnd* pParent = NULL);   // ��׼���캯��
    virtual ~IDTrans();

// �Ի�������
    enum { IDD = IDD_TRANS };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

    DECLARE_MESSAGE_MAP()
};
