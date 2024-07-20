// KioskProgramView.h : interface of the CKioskProgramView class

#pragma once


class CKioskProgramView : public CView
{
protected: // create from serialization only
	CKioskProgramView() noexcept;
	DECLARE_DYNCREATE(CKioskProgramView)

// Attributes
public:
	CKioskProgramDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CKioskProgramView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	// �������� ����
	int x, y;    // Ŭ���̾�Ʈ ���� ��ǥ
	int total;   // ���� ���
	int langFlag;// ����� ���� FLAG
	CStringList menuList;
	CStringList priceList;
	CUIntArray orderArr;

	// �޽��� �ڵ鷯 ����
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in KioskProgramView.cpp
inline CKioskProgramDoc* CKioskProgramView::GetDocument() const
   { return reinterpret_cast<CKioskProgramDoc*>(m_pDocument); }
#endif
