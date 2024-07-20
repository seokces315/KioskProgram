// KioskProgramView.cpp : implementation of the CKioskProgramView class

#include "pch.h"
#include "framework.h"

#ifndef SHARED_HANDLERS
#include "KioskProgram.h"
#endif

#include "KioskProgramDoc.h"
#include "KioskProgramView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "CMyDialog1.h"
#include <locale.h>

// ��ũ�� ����
// ���ҽ� ID�� Ȱ��
#define N (IDB_ORANGEJUICE - IDB_CHICKEN + 1)

// CKioskProgramView

IMPLEMENT_DYNCREATE(CKioskProgramView, CView)

BEGIN_MESSAGE_MAP(CKioskProgramView, CView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CKioskProgramView construction/destruction

CKioskProgramView::CKioskProgramView() noexcept
{
	// �����ڿ��� �ʱ�ȭ�� ����
	x = 10;
	y = 1010;
	total = 0;
	langFlag = 0;

	// ������ ���� �迭�� ũ�⸦ ���ҽ� ID�� Ȱ���� ����
	orderArr.SetSize(N);
	// ������ ���� �迭�� �� ��Ҹ� 0���� �ʱ�ȭ
	for (int i = 0; i < orderArr.GetCount(); i++) {
		orderArr[i] = 0;
	}
}

CKioskProgramView::~CKioskProgramView()
{
}

BOOL CKioskProgramView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}


// CKioskProgramView drawing

void CKioskProgramView::OnDraw(CDC* /*pDC*/)
{
	// ����� ��ü ����
	CKioskProgramDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CClientDC dc(this);
	dc.SetBkMode(TRANSPARENT); // ��� ��� ����

	// ���� ����
	pDoc->SetTitle(_T("MFC Project"));

	// ��� ��Ʈ�� ���
	CBitmap bgi;
	bgi.LoadBitmapW(IDB_BGI);
	BITMAP bgiInfo;
	bgi.GetBitmap(&bgiInfo);
	
	CDC dcmem1;
	dcmem1.CreateCompatibleDC(&dc);
	dcmem1.SelectObject(&bgi);

	dc.StretchBlt(0, 0, bgiInfo.bmWidth * 0.64, bgiInfo.bmHeight * 0.70,
		&dcmem1, 0, 0, bgiInfo.bmWidth, bgiInfo.bmHeight, SRCCOPY);

	// �޴��� ��Ʈ��/��ȭ���ڸ� ���� ��ư �׸���
	CFont gothic1;
	gothic1.CreateFont(45, 0, 0, 0,
		FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("���� ���"));
	dc.SelectObject(gothic1);
	CPen null(PS_NULL, 0, RGB(0, 0, 0));
	dc.SelectObject(null);
	CBrush bnb1(RGB(255, 228, 201));
	dc.SelectObject(bnb1);
	dc.SetTextColor(RGB(0, 0, 0));
	dc.RoundRect(325, 300, 650, 480, 60, 60);
	dc.RoundRect(665, 300, 990, 480, 60, 60);
	dc.RoundRect(325, 495, 650, 675, 60, 60);
	dc.RoundRect(665, 495, 990, 675, 60, 60);
	if (!langFlag) {
		dc.TextOutW(420, 370, _T("���� �޴�"));
		dc.TextOutW(760, 370, _T("��Ʈ �޴�"));
		dc.TextOutW(405, 560, _T("���̵� �޴�"));
		dc.TextOutW(795, 560, _T("�ַ�"));
	}
	else {
		dc.TextOutW(400, 370, _T("Main Menu"));
		dc.TextOutW(755, 370, _T("Set Menu"));
		dc.TextOutW(405, 560, _T("Side Menu"));
		dc.TextOutW(775, 560, _T("Drinks"));
	}

	// ��ٱ��� ���� ȭ�鿡 ���
	dc.RoundRect(2, 930, 900, 1310, 75, 75);

	CFont gothic2;
	gothic2.CreateFont(50, 0, 0, 0,
		FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("���� ���"));
	dc.SelectObject(gothic2);
	dc.SetTextColor(RGB(150, 75, 0));
	if(!langFlag) {
		dc.TextOutW(375, 940, CString(_T("��ٱ���")));
	}
	else {
		dc.TextOutW(395, 940, CString(_T("Basket")));

	}
	CPen brown1(PS_SOLID, 2.5, RGB(150, 75, 0));
	dc.SelectObject(brown1);
	dc.MoveTo(300, 1000);
	dc.LineTo(600, 1000);

	// ��ٱ��� ������
	CBitmap basket;
	basket.LoadBitmapW(IDB_BASKET);
	BITMAP bktInfo;
	basket.GetBitmap(&bktInfo);

	CDC dcmem2;
	dcmem2.CreateCompatibleDC(&dc);
	dcmem2.SelectObject(&basket);

	dc.StretchBlt(530, 930, bktInfo.bmWidth * 0.1, bktInfo.bmHeight * 0.1,
		&dcmem2, 0, 0, bktInfo.bmWidth, bktInfo.bmHeight, SRCCOPY);
	dc.StretchBlt(297, 930, bktInfo.bmWidth * 0.1, bktInfo.bmHeight * 0.1,
		&dcmem2, 0, 0, bktInfo.bmWidth, bktInfo.bmHeight, SRCCOPY);

	// ���� ��ư ȭ�鿡 ���
	dc.SelectObject(null);
	CBrush bnb2(RGB(225, 80, 55));
	dc.SelectObject(bnb2);
	dc.RoundRect(920, 945, 1260, 1160, 50, 50);

	CPen yellow1(PS_SOLID, 2.5, RGB(250, 250, 10));
	dc.SelectObject(yellow1);
	dc.MoveTo(1027, 1060);
	dc.LineTo(1153, 1060);

	CFont gothic3;
	gothic3.CreateFont(40, 0, 0, 0,
		FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("���� ���"));
	dc.SelectObject(gothic3);
	dc.Rectangle(940, 1090, 1240, 1150);
	dc.SetTextColor(RGB(255, 255, 255));
	if (!langFlag) {
		dc.TextOutW(995, 960, CString(_T("��ü �ֹ� �ݾ�")));
		dc.TextOutW(1155, 1020, CString(_T("��")));
		dc.TextOutW(1027, 1100, CString(_T("���� ��ư")));
	}
	else {
		dc.TextOutW(990, 960, CString(_T("Total Amount")));
		dc.TextOutW(1155, 1020, CString(_T("Won")));
		dc.TextOutW(1030, 1100, CString(_T("Payment")));
	}

	// ��ٱ��� �ʱ�ȭ ��ư ȭ�鿡 ���
	dc.SelectObject(null);
	CBrush bnb3(RGB(150, 75, 0));
	dc.SelectObject(bnb3);
	dc.RoundRect(920, 1170, 1260, 1295, 50, 50);
	if (!langFlag) {
		dc.TextOutW(983, 1210, CString(_T("��ٱ��� �ʱ�ȭ")));
	}
	else {
		dc.TextOutW(1000, 1210, CString(_T("Reset Basket")));
	}

	// ����� ���� ��ư �����
	CFont gothic4;
	gothic4.CreateFont(35, 0, 0, 0,
		FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("���� ���"));
	dc.SelectObject(gothic4);

	CRgn kor;
	CRgn eng;
	CBrush langBrush(RGB(0, 0, 215));
	kor.CreateRoundRectRgn(1175, 15, 1260, 100, 60, 60);
	eng.CreateRoundRectRgn(1175, 115, 1260, 200, 60, 60);
	dc.FillRgn(&kor, &langBrush);
	dc.FillRgn(&eng, &langBrush);
	if (!langFlag) {
		dc.TextOutW(1177, 37, CString(_T("�ѱ���")));
		dc.TextOutW(1190, 137, CString(_T("����")));
	}
	else {
		dc.TextOutW(1174, 37, CString(_T("Korean")));
		dc.TextOutW(1174, 137, CString(_T("English")));
	}


	// ���� ��ư �����
	CRgn exit;
	exit.CreateRoundRectRgn(15, 15, 100, 100, 60, 60);
	CBrush exBrush(RGB(175, 0, 0));
	dc.FillRgn(&exit, &exBrush);
	if (!langFlag) {
		dc.TextOutW(30, 37, CString(_T("����!")));
	}
	else {
		dc.TextOutW(33, 37, CString(_T("Exit!")));
	}
}


// CKioskProgramView printing

BOOL CKioskProgramView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CKioskProgramView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CKioskProgramView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}


// CKioskProgramView diagnostics

#ifdef _DEBUG
void CKioskProgramView::AssertValid() const
{
	CView::AssertValid();
}

void CKioskProgramView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKioskProgramDoc* CKioskProgramView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKioskProgramDoc)));
	return (CKioskProgramDoc*)m_pDocument;
}
#endif //_DEBUG


// CKioskProgramView message handlers


// Ŀ�� ��ġ�� ���� ȭ����� ���� �Լ�
BOOL CKioskProgramView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// ����� ���� ����
	CClientDC dc(this);
	dc.SetBkMode(TRANSPARENT);

	// Ŀ�� ��ġ ��ȯ
	CPoint point;
	::GetCursorPos(&point);
	ScreenToClient(&point);

	// Ŀ���� ������ ���� ����
	CRgn rgn1, rgn2, rgn3, rgn4, rgn5, rgn6, rgn7, rgn8, rgn9;
	rgn1.CreateRoundRectRgn(15, 15, 100, 100, 60, 60);
	rgn2.CreateRoundRectRgn(920, 1170, 1260, 1295, 50, 50);
	rgn3.CreateRectRgn(940, 1090, 1240, 1150);
	rgn4.CreateRoundRectRgn(325, 300, 650, 480, 60, 60);
	rgn5.CreateRoundRectRgn(665, 300, 990, 480, 60, 60);
	rgn6.CreateRoundRectRgn(325, 495, 650, 675, 60, 60);
	rgn7.CreateRoundRectRgn(665, 495, 990, 675, 60, 60);
	rgn8.CreateRoundRectRgn(1175, 15, 1260, 100, 60, 60);
	rgn9.CreateRoundRectRgn(1175, 115, 1260, 200, 60, 60);

	// ����� ��Ʈ ����
	CFont gothic1;
	gothic1.CreateFont(35, 0, 0, 0,
		FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("���� ���"));
	CFont gothic2;
	gothic2.CreateFont(40, 0, 0, 0,
		FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("���� ���"));
	CFont gothic3;
	gothic3.CreateFont(45, 0, 0, 0,
		FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("���� ���"));

	// ������ Ŀ���� �ִٸ� �հ��� ������� ����
	if (rgn1.PtInRegion(point) || rgn2.PtInRegion(point) || rgn3.PtInRegion(point) ||
		rgn4.PtInRegion(point) || rgn5.PtInRegion(point) || rgn6.PtInRegion(point) ||
		rgn7.PtInRegion(point) || rgn8.PtInRegion(point) || rgn9.PtInRegion(point)) {
		::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_HAND));
	}
	else {
		::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	}

	// �� �������� Ŀ���� ��ġ�� ���� ����
	if (!langFlag) {
		if (rgn1.PtInRegion(point)) {
			dc.SelectObject(gothic1);
			dc.SetTextColor(RGB(0, 0, 0));
			dc.TextOutW(30, 37, CString(_T("����!")));
		}
		else {
			dc.SelectObject(gothic1);
			dc.SetTextColor(RGB(255, 255, 255));
			dc.TextOutW(30, 37, CString(_T("����!")));
		}
		if (rgn2.PtInRegion(point)) {
			dc.SelectObject(gothic2);
			dc.SetTextColor(RGB(0, 0, 0));
			dc.TextOutW(983, 1210, CString(_T("��ٱ��� �ʱ�ȭ")));
		}
		else {
			dc.SelectObject(gothic2);
			dc.SetTextColor(RGB(255, 255, 255));
			dc.TextOutW(983, 1210, CString(_T("��ٱ��� �ʱ�ȭ")));
		}
		if (rgn3.PtInRegion(point)) {
			dc.SelectObject(gothic2);
			dc.SetTextColor(RGB(250, 250, 10));
			dc.TextOutW(1027, 1100, CString(_T("���� ��ư")));
		}
		else {
			CString answer;
			dc.SelectObject(gothic2);
			dc.SetTextColor(RGB(255, 255, 255));
			dc.TextOutW(1027, 1100, CString(_T("���� ��ư")));
		}
		if (rgn4.PtInRegion(point)) {
			dc.SelectObject(gothic3);
			dc.SetTextColor(RGB(150, 75, 0));
			dc.TextOutW(420, 370, _T("���� �޴�"));
		}
		else {
			dc.SelectObject(gothic3);
			dc.SetTextColor(RGB(0, 0, 0));
			dc.TextOutW(420, 370, _T("���� �޴�"));
		}
		if (rgn5.PtInRegion(point)) {
			dc.SelectObject(gothic3);
			dc.SetTextColor(RGB(150, 75, 0));
			dc.TextOutW(760, 370, _T("��Ʈ �޴�"));
		}
		else {
			dc.SelectObject(gothic3);
			dc.SetTextColor(RGB(0, 0, 0));
			dc.TextOutW(760, 370, _T("��Ʈ �޴�"));
		}
		if (rgn6.PtInRegion(point)) {
			dc.SelectObject(gothic3);
			dc.SetTextColor(RGB(150, 75, 0));
			dc.TextOutW(405, 560, _T("���̵� �޴�"));
		}
		else {
			dc.SelectObject(gothic3);
			dc.SetTextColor(RGB(0, 0, 0));
			dc.TextOutW(405, 560, _T("���̵� �޴�"));
		}
		if (rgn7.PtInRegion(point)) {
			dc.SelectObject(gothic3);
			dc.SetTextColor(RGB(150, 75, 0));
			dc.TextOutW(795, 560, _T("�ַ�"));
		}
		else {
			dc.SelectObject(gothic3);
			dc.SetTextColor(RGB(0, 0, 0));
			dc.TextOutW(795, 560, _T("�ַ�"));
		}
		if (rgn8.PtInRegion(point)) {
			dc.SelectObject(gothic1);
			dc.SetTextColor(RGB(0, 0, 0));
			dc.TextOutW(1177, 37, CString(_T("�ѱ���")));
		}
		else {
			dc.SelectObject(gothic1);
			dc.SetTextColor(RGB(255, 255, 255));
			dc.TextOutW(1177, 37, CString(_T("�ѱ���")));
		}
		if (rgn9.PtInRegion(point)) {
			dc.SelectObject(gothic1);
			dc.SetTextColor(RGB(0, 0, 0));
			dc.TextOutW(1190, 137, CString(_T("����")));
		}
		else {
			dc.SelectObject(gothic1);
			dc.SetTextColor(RGB(255, 255, 255));
			dc.TextOutW(1190, 137, CString(_T("����")));
		}
	}
	else {
		if (rgn1.PtInRegion(point)) {
			dc.SelectObject(gothic1);
			dc.SetTextColor(RGB(0, 0, 0));
			dc.TextOutW(33, 37, CString(_T("Exit!")));
		}
		else {
			dc.SelectObject(gothic1);
			dc.SetTextColor(RGB(255, 255, 255));
			dc.TextOutW(33, 37, CString(_T("Exit!")));
		}
		if (rgn2.PtInRegion(point)) {
			dc.SelectObject(gothic2);
			dc.SetTextColor(RGB(0, 0, 0));
			dc.TextOutW(1000, 1210, CString(_T("Reset Basket")));
		}
		else {
			dc.SelectObject(gothic2);
			dc.SetTextColor(RGB(255, 255, 255));
			dc.TextOutW(1000, 1210, CString(_T("Reset Basket")));
		}
		if (rgn3.PtInRegion(point)) {
			dc.SelectObject(gothic2);
			dc.SetTextColor(RGB(250, 250, 10));
			dc.TextOutW(1030, 1100, CString(_T("Payment")));
		}
		else {
			CString answer;
			dc.SelectObject(gothic2);
			dc.SetTextColor(RGB(255, 255, 255));
			dc.TextOutW(1030, 1100, CString(_T("Payment")));
		}
		if (rgn4.PtInRegion(point)) {
			dc.SelectObject(gothic3);
			dc.SetTextColor(RGB(150, 75, 0));
			dc.TextOutW(400, 370, _T("Main Menu"));
		}
		else {
			dc.SelectObject(gothic3);
			dc.SetTextColor(RGB(0, 0, 0));
			dc.TextOutW(400, 370, _T("Main Menu"));
		}
		if (rgn5.PtInRegion(point)) {
			dc.SelectObject(gothic3);
			dc.SetTextColor(RGB(150, 75, 0));
			dc.TextOutW(755, 370, _T("Set Menu"));
		}
		else {
			dc.SelectObject(gothic3);
			dc.SetTextColor(RGB(0, 0, 0));
			dc.TextOutW(755, 370, _T("Set Menu"));
		}
		if (rgn6.PtInRegion(point)) {
			dc.SelectObject(gothic3);
			dc.SetTextColor(RGB(150, 75, 0));
			dc.TextOutW(405, 560, _T("Side Menu"));
		}
		else {
			dc.SelectObject(gothic3);
			dc.SetTextColor(RGB(0, 0, 0));
			dc.TextOutW(405, 560, _T("Side Menu"));
		}
		if (rgn7.PtInRegion(point)) {
			dc.SelectObject(gothic3);
			dc.SetTextColor(RGB(150, 75, 0));
			dc.TextOutW(775, 560, _T("Drinks"));
		}
		else {
			dc.SelectObject(gothic3);
			dc.SetTextColor(RGB(0, 0, 0));
			dc.TextOutW(775, 560, _T("Drinks"));
		}
		if (rgn8.PtInRegion(point)) {
			dc.SelectObject(gothic1);
			dc.SetTextColor(RGB(0, 0, 0));
			dc.TextOutW(1174, 37, CString(_T("Korean")));
		}
		else {
			dc.SelectObject(gothic1);
			dc.SetTextColor(RGB(255, 255, 255));
			dc.TextOutW(1174, 37, CString(_T("Korean")));
		}
		if (rgn9.PtInRegion(point)) {
			dc.SelectObject(gothic1);
			dc.SetTextColor(RGB(0, 0, 0));
			dc.TextOutW(1174, 137, CString(_T("English")));
		}
		else {
			dc.SelectObject(gothic1);
			dc.SetTextColor(RGB(255, 255, 255));
			dc.TextOutW(1174, 137, CString(_T("English")));
		}

	}

	return TRUE;

	return CView::OnSetCursor(pWnd, nHitTest, message);
}


void CKioskProgramView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// ����� ���� ����
	CClientDC dc(this);
	dc.SetBkMode(TRANSPARENT);
	CPen null(PS_NULL, 0, RGB(0, 0, 0));
	CPen yellow(PS_SOLID, 2.5, RGB(250, 250, 10));
	CBrush bnb(RGB(225, 80, 55));
	CFont gothic1;
	gothic1.CreateFont(45, 0, 0, 0,
		FW_DEMIBOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("���� ���"));
	CFont gothic2;
	gothic2.CreateFont(40, 0, 0, 0,
		FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("���� ���"));

	// ��ư�� ���� ����
	CRgn rgn1, rgn2, rgn3, rgn4, rgn5, rgn6, rgn7, rgn8, rgn9;
	rgn1.CreateRoundRectRgn(15, 15, 100, 100, 60, 60);
	rgn2.CreateRoundRectRgn(920, 1170, 1260, 1295, 50, 50);
	rgn3.CreateRectRgn(940, 1090, 1240, 1150);
	rgn4.CreateRoundRectRgn(325, 300, 650, 480, 60, 60);
	rgn5.CreateRoundRectRgn(665, 300, 990, 480, 60, 60);
	rgn6.CreateRoundRectRgn(325, 495, 650, 675, 60, 60);
	rgn7.CreateRoundRectRgn(665, 495, 990, 675, 60, 60);
	rgn8.CreateRoundRectRgn(1175, 15, 1260, 100, 60, 60);
	rgn9.CreateRoundRectRgn(1175, 115, 1260, 200, 60, 60);

	// ���� ��ư�� ������ ���α׷��� �����ϵ��� ��
	if (rgn1.PtInRegion(point)) {
		AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_APP_EXIT, NULL);
	}

	// ��ٱ��� �ʱ�ȭ ��ư�� ������ ��ٱ��� �ʱ�ȭ
	if (rgn2.PtInRegion(point)) {
		// �������� ��������
		x = 10;
		y = 1010;
		total = 0;
		
		menuList.RemoveAll();
		priceList.RemoveAll();
		for (int i = 0; i < orderArr.GetCount(); i++) {
			orderArr[i] = 0;
		}

		// ȭ�� ����
		Invalidate();
	}

	// ���� ��ư�� ������ ����â ���
	if (rgn3.PtInRegion(point)) {
		// ��/�ƴϿ� �޽��� �ڽ� ����
		int answer; 
		if (!langFlag) {
			answer = MessageBox(_T("������ �����Ͻðڽ��ϱ�?"), _T("�ȳ� �޽���"), MB_YESNO | MB_ICONASTERISK);
		}
		else {
			answer = MessageBox(_T("Would you like to proceed with payment?"), _T("Message"), MB_YESNO | MB_ICONASTERISK);
		}

		// ���� ������ ��
		if (answer == IDYES) {
			// ��ٱ��ϰ� ����� ��
			if (total == 0) {
				if (!langFlag) {
					MessageBox(_T("��ٱ��ϰ� ����ֽ��ϴ�."), _T("�ȳ� �޽���"), MB_ICONERROR);
				}
				else {
					MessageBox(_T("Basket is empty!"), _T("Message"), MB_ICONERROR);
				}
			}
			else {

				// ���� ���� ����
				CString msg = _T("");
				CString info;
				CString menu;
				CString price;
				int order;
				POSITION menuPos = menuList.GetHeadPosition();
				POSITION pricePos = priceList.GetHeadPosition();

				// while-loop�� �ۼ�
				// �ݺ��� ���� �ֹ� ������ �޽����ڽ��� ����
				int i = 0;
				while (menuPos != NULL) {
					// �ֹ� ���� ��ȯ
					menu = menuList.GetNext(menuPos);
					price = priceList.GetNext(pricePos);
					order = orderArr[i];

					// ���� ������
					info.Format(_T("%s %-5s %-d\r\n"), menu.Trim(), price, order); // ���� ����

					// ������ 0�̶�� ������ �������� ����
					i++;
					if (order == 0) {
						continue;
					}

					// ����� �޽����� ���� �߰�
					msg += info;
				}

				// ������ ���� �ݾ��� �޽��� �ڽ��� ����
				CString account;
				if (!langFlag) {
					account.Format(_T("\r\n               ���� = %d��"), total);
				}
				else {
					account.Format(_T("\r\n               Total = %d Won"), total);
				}
				msg += account;
				
				// �޽��� �ڽ� ���
				if (!langFlag) {
					MessageBox(msg, _T("���� ����"), MB_ICONINFORMATION);
				}
				else {
					MessageBox(msg, _T("Payment List"), MB_ICONINFORMATION);
				}

				// ��� ������ ������ ���� �ʱ�ȭ
				x = 10;
				y = 1010;
				total = 0;

				menuList.RemoveAll();
				priceList.RemoveAll();
				for (int i = 0; i < orderArr.GetCount(); i++) {
					orderArr[i] = 0;
				}

				// ȭ�� ����
				Invalidate();

			}
		}
	}

	// �޴��� ��ư�� ������ �޴��� ���
	// �ؽ�Ʈ ������ ���� ��ü ����
	CStdioFile iFile;
	setlocale(LC_ALL, "korean"); // �ѱ� ���� ����
	
	// ��ȭ���� ��ü ����
	CMyDialog1 dlg1;
	
	// ���� �б�
	if ((rgn4.PtInRegion(point)) || (rgn5.PtInRegion(point)) || (rgn6.PtInRegion(point)) || (rgn7.PtInRegion(point))) {
		
		// ���� ���� ����
		int bmp;

		// �޴��� ������ ���� ���� �б�
		if(rgn4.PtInRegion(point)) {

			// ���� �޴��� ��� �޴���
			if (!langFlag) {
				iFile.Open(_T("res\\���� �޴�.txt"), CFile::modeRead);
			}
			else {
				iFile.Open(_T("res\\mainMenu.txt"), CFile::modeRead);
			}

			bmp = 312;
		}
		else if (rgn5.PtInRegion(point)) {

			// ��Ʈ �޴��� ��� �޴���
			if (!langFlag) {
				iFile.Open(_T("res\\��Ʈ �޴�.txt"), CFile::modeRead);
			}
			else {
				iFile.Open(_T("res\\setMenu.txt"), CFile::modeRead);
			}

			bmp = 317;
		}
		else if (rgn6.PtInRegion(point)) {

			// ���̵� �޴��� ��� �޴���
			if (!langFlag) {
				iFile.Open(_T("res\\���̵� �޴�.txt"), CFile::modeRead);
			}
			else {
				iFile.Open(_T("res\\sideMenu.txt"), CFile::modeRead);
			}

			bmp = 321;
		}
		else if (rgn7.PtInRegion(point)) {

			// �ַ��� ��� �޴���
			if (!langFlag) {
				iFile.Open(_T("res\\�ַ�.txt"), CFile::modeRead);
			}
			else {
				iFile.Open(_T("res\\juices.txt"), CFile::modeRead);
			}

			bmp = 327;
		}

		// ������ ���پ� �о� ��ȭ���� ��ü�� ����
		while (iFile.ReadString(dlg1.info)) {
			dlg1.infoList.AddTail(dlg1.info);
		}

		// ����� ��ȭ����
		dlg1.DoModal();

		// ��ٱ��� FLAG�� ���� �� ���� �б�
		if (dlg1.basket) {

			// �������� ����
			CString menu;
			CString price;
			POSITION menuPos = dlg1.menuList.GetHeadPosition();
			POSITION pricePos = dlg1.priceList.GetHeadPosition();
			// �޴��� �ߺ��� ���õ� ����
			int accMenu;
			int flag = 0;
			int cnt = 0;
			
			for (int i = 0; i < dlg1.menuList.GetCount(); i++) {
			// ��Ʈ�� ���� ��ü ����
				CBitmap basket;
				BITMAP bktInfo;
				CDC dcmem;
				dcmem.CreateCompatibleDC(&dc);
				
				// ���ҽ� ID ���� �ʿ�
				// switch������ ���ҽ� ID�� ��Ʈ�� ����
				bmp++;
				switch(bmp) {
				case IDB_CHICKEN :
					basket.LoadBitmapW(IDB_CHICKEN);
					basket.GetBitmap(&bktInfo);
					break;
				case IDB_PIZZA:
					basket.LoadBitmapW(IDB_PIZZA);
					basket.GetBitmap(&bktInfo);
					break;
				case IDB_HAMBURGER:
					basket.LoadBitmapW(IDB_HAMBURGER);
					basket.GetBitmap(&bktInfo);
					break;
				case IDB_HOTDOG:
					basket.LoadBitmapW(IDB_HOTDOG);
					basket.GetBitmap(&bktInfo);
					break;
				case IDB_SANDWICH:
					basket.LoadBitmapW(IDB_SANDWICH);
					basket.GetBitmap(&bktInfo);
					break;
				case IDB_CHICKCHILI:
					basket.LoadBitmapW(IDB_CHICKCHILI);
					basket.GetBitmap(&bktInfo);
					break;
				case IDB_PIZZAGARLIC:
					basket.LoadBitmapW(IDB_PIZZAGARLIC);
					basket.GetBitmap(&bktInfo);
					break;
				case IDB_PIZZAPASTA:
					basket.LoadBitmapW(IDB_PIZZAPASTA);
					basket.GetBitmap(&bktInfo);
					break;
				case IDB_HAMBURGERSET:
					basket.LoadBitmapW(IDB_HAMBURGERSET);
					basket.GetBitmap(&bktInfo);
					break;
				case IDB_CHILISAUCE:
					basket.LoadBitmapW(IDB_CHILISAUCE);
					basket.GetBitmap(&bktInfo);
					break;
				case IDB_GARLICSAUCE:
					basket.LoadBitmapW(IDB_GARLICSAUCE);
					basket.GetBitmap(&bktInfo);
					break;
				case IDB_SPAGHETTI:
					basket.LoadBitmapW(IDB_SPAGHETTI);
					basket.GetBitmap(&bktInfo);
					break;
				case IDB_FRENCHFRIES:
					basket.LoadBitmapW(IDB_FRENCHFRIES);
					basket.GetBitmap(&bktInfo);
					break;
				case IDB_CHEESEBALL:
					basket.LoadBitmapW(IDB_CHEESEBALL);
					basket.GetBitmap(&bktInfo);
					break;
				case IDB_CORNSALAD:
					basket.LoadBitmapW(IDB_CORNSALAD);
					basket.GetBitmap(&bktInfo);
					break;
				case IDB_COKE:
					basket.LoadBitmapW(IDB_COKE);
					basket.GetBitmap(&bktInfo);
					break;
				case IDB_CIDER:
					basket.LoadBitmapW(IDB_CIDER);
					basket.GetBitmap(&bktInfo);
					break;
				case IDB_FANTA:
					basket.LoadBitmapW(IDB_FANTA);
					basket.GetBitmap(&bktInfo);
					break;
				case IDB_MIRANDA:
					basket.LoadBitmapW(IDB_MIRANDA);
					basket.GetBitmap(&bktInfo);
					break;
				case IDB_ORANGEJUICE:
					basket.LoadBitmapW(IDB_ORANGEJUICE);
					basket.GetBitmap(&bktInfo);
					break;
				}

				dcmem.SelectObject(&basket);

				// �޴����� ��ٱ��Ͽ� ����
				menu = dlg1.menuList.GetNext(menuPos);
				price = dlg1.priceList.GetNext(pricePos);

				// �޴����� �ߺ��Ǹ� ���̻� �������� ����
				if (menuList.Find(menu) == NULL) { // �޴��� �� Ư����
					menuList.AddTail(menu);
					priceList.AddTail(price);
					flag = 1;
				}
				cnt++;

				// ���� for�� �ۼ�
				// ������ ��ٱ��Ͽ� ����
				flag == 1 ? accMenu = menuList.GetCount() : accMenu = cnt; // �޴��� �ߺ��� ���� ���� ����Ʈ �б�
				for (int j = 0; j < dlg1.orderArr[i]; j++) {
					// ��Ʈ�� ����� ������ ���� �� -> ��ٱ��� ������ ������ ����
					if ((x + bktInfo.bmWidth * 0.2 > 890) && (y == 1150)) {
						if (!langFlag) {
							MessageBox(_T("��ٱ��ϰ� ���� á���ϴ�!"), _T("�ȳ� �޽���"), MB_ICONERROR);
						}
						else {
							MessageBox(_T("Basket is full!"), _T("Message"), MB_ICONERROR);
						}
						goto jump;
					}
					// ù ��° ���� ���� ���� ��Ʈ�� �ٹٲ��� ����
					else if (x + bktInfo.bmWidth * 0.2 > 890) {
						x = 10;
						y = 1150;
					}

					// �� �������� ��Ʈ�� ��ٱ��Ͽ� ���
					dc.StretchBlt(x, y, bktInfo.bmWidth * 0.20, bktInfo.bmHeight * 0.25,
						&dcmem, 0, 0, bktInfo.bmWidth, bktInfo.bmHeight, SRCCOPY);
					// ��� �� ���� ��ġ�� �̵�
					x += bktInfo.bmWidth * 0.20 + 25;
					// ���� ����� �ݿ�
					total += dlg1.priceArr[i];
					// ��ٱ��� ������ ���� ����
					orderArr[accMenu - 1]++;
				}
			}

			jump :

				// ����â���� ���ۿ� ���� ����� ������ ����
				dc.SelectObject(null);
				dc.SelectObject(bnb);
				dc.RoundRect(920, 945, 1260, 1160, 50, 50);

				CString account;
				account.Format(_T("%6d"), total);
				dc.SelectObject(gothic1);
				dc.SetTextColor(RGB(250, 250, 10));
				dc.TextOutW(1033, 1010, account);
				dc.SelectObject(yellow);
				dc.MoveTo(1027, 1060);
				dc.LineTo(1153, 1060);

				dc.SelectObject(gothic2);
				dc.SetTextColor(RGB(255, 255, 255));
				if (!langFlag) {
					dc.TextOutW(995, 960, CString(_T("��ü �ֹ� �ݾ�")));
					dc.TextOutW(1155, 1020, CString(_T("��")));
				}
				else {
					dc.TextOutW(990, 960, CString(_T("Total Amount")));
					dc.TextOutW(1155, 1020, CString(_T("Won")));
				}

				dc.SelectObject(yellow);
				dc.Rectangle(940, 1090, 1240, 1150);
				if (!langFlag) {
					dc.TextOutW(1027, 1100, CString(_T("���� ��ư")));
				}
				else {
					dc.TextOutW(1030, 1100, CString(_T("Payment")));
				}

		}
	}

	// ����� ���� ��ư
	// ��ư�� ������ ��� ����Ī + ȭ�� ����
	if (rgn8.PtInRegion(point)) {
	langFlag = 0;

	// ���� �ʱ�ȭ
	x = 10;
	y = 1010;
	total = 0;

	menuList.RemoveAll();
	priceList.RemoveAll();
	for (int i = 0; i < orderArr.GetCount(); i++) {
		orderArr[i] = 0;
	}

	Invalidate();
	}

	if (rgn9.PtInRegion(point)) {
	langFlag = 1;

	// ���� �ʱ�ȭ
	x = 10;
	y = 1010;
	total = 0;

	menuList.RemoveAll();
	priceList.RemoveAll();
	for (int i = 0; i < orderArr.GetCount(); i++) {
		orderArr[i] = 0;
	}

	Invalidate();
	}

	CView::OnLButtonDown(nFlags, point);
}
