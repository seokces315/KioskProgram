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
	// 전역변수 선언
	int x, y;    // 클라이언트 영역 좌표
	int total;   // 최종 결과
	int langFlag;// 언어팩 관련 FLAG
	CStringList menuList;
	CStringList priceList;
	CUIntArray orderArr;

	// 메시지 핸들러 정의
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in KioskProgramView.cpp
inline CKioskProgramDoc* CKioskProgramView::GetDocument() const
   { return reinterpret_cast<CKioskProgramDoc*>(m_pDocument); }
#endif
