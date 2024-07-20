#pragma once
#include "afxdialogex.h"


// CMyDialog1 dialog

class CMyDialog1 : public CDialog
{
	DECLARE_DYNAMIC(CMyDialog1)

public:
	CMyDialog1(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CMyDialog1();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MENU };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	// �������� ����
	CListBox menuLB;
	CListBox priceLB;
	CListBox orderLB;     // �ֹ� ����
	CFont m_font;
	CString info;         // �����͸� ���� ���ڿ�
	CStringList infoList;
	CStringList menuList;
	CStringList priceList;
	CUIntArray orderArr;  // ������ ���� �迭
	CUIntArray priceArr;  // ������ ���� �迭
	CSpinButtonCtrl orderCtrl;
	BOOL basket;          // ��ٱ��ϸ� �ٷ�� FLAG

	// �����Լ� ����
	virtual BOOL OnInitDialog();

	// �޽��� �ڵ鷯 ����
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnLbnSelchangeList2();
	afx_msg void OnLbnSelchangeList3();
	afx_msg void OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedOk();
};
