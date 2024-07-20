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
	// 전역변수 선언
	CListBox menuLB;
	CListBox priceLB;
	CListBox orderLB;     // 주문 수량
	CFont m_font;
	CString info;         // 데이터를 담을 문자열
	CStringList infoList;
	CStringList menuList;
	CStringList priceList;
	CUIntArray orderArr;  // 수량을 담을 배열
	CUIntArray priceArr;  // 가격을 담을 배열
	CSpinButtonCtrl orderCtrl;
	BOOL basket;          // 장바구니를 다루는 FLAG

	// 가상함수 정의
	virtual BOOL OnInitDialog();

	// 메시지 핸들러 정의
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnLbnSelchangeList2();
	afx_msg void OnLbnSelchangeList3();
	afx_msg void OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedOk();
};
