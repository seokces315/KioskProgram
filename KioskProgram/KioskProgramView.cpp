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

// 매크로 정의
// 리소스 ID를 활용
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
	// 생성자에서 초기화할 변수
	x = 10;
	y = 1010;
	total = 0;
	langFlag = 0;

	// 수량을 담을 배열의 크기를 리소스 ID를 활용해 정의
	orderArr.SetSize(N);
	// 수량을 담을 배열의 각 요소를 0으로 초기화
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
	// 사용할 객체 선언
	CKioskProgramDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CClientDC dc(this);
	dc.SetBkMode(TRANSPARENT); // 배경 모드 설정

	// 제목 설정
	pDoc->SetTitle(_T("MFC Project"));

	// 배경 비트맵 출력
	CBitmap bgi;
	bgi.LoadBitmapW(IDB_BGI);
	BITMAP bgiInfo;
	bgi.GetBitmap(&bgiInfo);
	
	CDC dcmem1;
	dcmem1.CreateCompatibleDC(&dc);
	dcmem1.SelectObject(&bgi);

	dc.StretchBlt(0, 0, bgiInfo.bmWidth * 0.64, bgiInfo.bmHeight * 0.70,
		&dcmem1, 0, 0, bgiInfo.bmWidth, bgiInfo.bmHeight, SRCCOPY);

	// 메뉴판 컨트롤/대화상자를 여는 버튼 그리기
	CFont gothic1;
	gothic1.CreateFont(45, 0, 0, 0,
		FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));
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
		dc.TextOutW(420, 370, _T("메인 메뉴"));
		dc.TextOutW(760, 370, _T("세트 메뉴"));
		dc.TextOutW(405, 560, _T("사이드 메뉴"));
		dc.TextOutW(795, 560, _T("주류"));
	}
	else {
		dc.TextOutW(400, 370, _T("Main Menu"));
		dc.TextOutW(755, 370, _T("Set Menu"));
		dc.TextOutW(405, 560, _T("Side Menu"));
		dc.TextOutW(775, 560, _T("Drinks"));
	}

	// 장바구니 영역 화면에 출력
	dc.RoundRect(2, 930, 900, 1310, 75, 75);

	CFont gothic2;
	gothic2.CreateFont(50, 0, 0, 0,
		FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));
	dc.SelectObject(gothic2);
	dc.SetTextColor(RGB(150, 75, 0));
	if(!langFlag) {
		dc.TextOutW(375, 940, CString(_T("장바구니")));
	}
	else {
		dc.TextOutW(395, 940, CString(_T("Basket")));

	}
	CPen brown1(PS_SOLID, 2.5, RGB(150, 75, 0));
	dc.SelectObject(brown1);
	dc.MoveTo(300, 1000);
	dc.LineTo(600, 1000);

	// 장바구니 아이콘
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

	// 결제 버튼 화면에 출력
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
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));
	dc.SelectObject(gothic3);
	dc.Rectangle(940, 1090, 1240, 1150);
	dc.SetTextColor(RGB(255, 255, 255));
	if (!langFlag) {
		dc.TextOutW(995, 960, CString(_T("전체 주문 금액")));
		dc.TextOutW(1155, 1020, CString(_T("원")));
		dc.TextOutW(1027, 1100, CString(_T("결제 버튼")));
	}
	else {
		dc.TextOutW(990, 960, CString(_T("Total Amount")));
		dc.TextOutW(1155, 1020, CString(_T("Won")));
		dc.TextOutW(1030, 1100, CString(_T("Payment")));
	}

	// 장바구니 초기화 버튼 화면에 출력
	dc.SelectObject(null);
	CBrush bnb3(RGB(150, 75, 0));
	dc.SelectObject(bnb3);
	dc.RoundRect(920, 1170, 1260, 1295, 50, 50);
	if (!langFlag) {
		dc.TextOutW(983, 1210, CString(_T("장바구니 초기화")));
	}
	else {
		dc.TextOutW(1000, 1210, CString(_T("Reset Basket")));
	}

	// 언어팩 관력 버튼 만들기
	CFont gothic4;
	gothic4.CreateFont(35, 0, 0, 0,
		FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));
	dc.SelectObject(gothic4);

	CRgn kor;
	CRgn eng;
	CBrush langBrush(RGB(0, 0, 215));
	kor.CreateRoundRectRgn(1175, 15, 1260, 100, 60, 60);
	eng.CreateRoundRectRgn(1175, 115, 1260, 200, 60, 60);
	dc.FillRgn(&kor, &langBrush);
	dc.FillRgn(&eng, &langBrush);
	if (!langFlag) {
		dc.TextOutW(1177, 37, CString(_T("한국어")));
		dc.TextOutW(1190, 137, CString(_T("영어")));
	}
	else {
		dc.TextOutW(1174, 37, CString(_T("Korean")));
		dc.TextOutW(1174, 137, CString(_T("English")));
	}


	// 종료 버튼 만들기
	CRgn exit;
	exit.CreateRoundRectRgn(15, 15, 100, 100, 60, 60);
	CBrush exBrush(RGB(175, 0, 0));
	dc.FillRgn(&exit, &exBrush);
	if (!langFlag) {
		dc.TextOutW(30, 37, CString(_T("종료!")));
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


// 커서 위치에 따른 화면출력 변경 함수
BOOL CKioskProgramView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// 사용할 변수 선언
	CClientDC dc(this);
	dc.SetBkMode(TRANSPARENT);

	// 커서 위치 반환
	CPoint point;
	::GetCursorPos(&point);
	ScreenToClient(&point);

	// 커서가 동작할 리전 정의
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

	// 사용할 폰트 정의
	CFont gothic1;
	gothic1.CreateFont(35, 0, 0, 0,
		FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));
	CFont gothic2;
	gothic2.CreateFont(40, 0, 0, 0,
		FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));
	CFont gothic3;
	gothic3.CreateFont(45, 0, 0, 0,
		FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));

	// 리전에 커서가 있다면 손가락 모양으로 변경
	if (rgn1.PtInRegion(point) || rgn2.PtInRegion(point) || rgn3.PtInRegion(point) ||
		rgn4.PtInRegion(point) || rgn5.PtInRegion(point) || rgn6.PtInRegion(point) ||
		rgn7.PtInRegion(point) || rgn8.PtInRegion(point) || rgn9.PtInRegion(point)) {
		::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_HAND));
	}
	else {
		::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	}

	// 각 리전별로 커서의 위치에 따른 동작
	if (!langFlag) {
		if (rgn1.PtInRegion(point)) {
			dc.SelectObject(gothic1);
			dc.SetTextColor(RGB(0, 0, 0));
			dc.TextOutW(30, 37, CString(_T("종료!")));
		}
		else {
			dc.SelectObject(gothic1);
			dc.SetTextColor(RGB(255, 255, 255));
			dc.TextOutW(30, 37, CString(_T("종료!")));
		}
		if (rgn2.PtInRegion(point)) {
			dc.SelectObject(gothic2);
			dc.SetTextColor(RGB(0, 0, 0));
			dc.TextOutW(983, 1210, CString(_T("장바구니 초기화")));
		}
		else {
			dc.SelectObject(gothic2);
			dc.SetTextColor(RGB(255, 255, 255));
			dc.TextOutW(983, 1210, CString(_T("장바구니 초기화")));
		}
		if (rgn3.PtInRegion(point)) {
			dc.SelectObject(gothic2);
			dc.SetTextColor(RGB(250, 250, 10));
			dc.TextOutW(1027, 1100, CString(_T("결제 버튼")));
		}
		else {
			CString answer;
			dc.SelectObject(gothic2);
			dc.SetTextColor(RGB(255, 255, 255));
			dc.TextOutW(1027, 1100, CString(_T("결제 버튼")));
		}
		if (rgn4.PtInRegion(point)) {
			dc.SelectObject(gothic3);
			dc.SetTextColor(RGB(150, 75, 0));
			dc.TextOutW(420, 370, _T("메인 메뉴"));
		}
		else {
			dc.SelectObject(gothic3);
			dc.SetTextColor(RGB(0, 0, 0));
			dc.TextOutW(420, 370, _T("메인 메뉴"));
		}
		if (rgn5.PtInRegion(point)) {
			dc.SelectObject(gothic3);
			dc.SetTextColor(RGB(150, 75, 0));
			dc.TextOutW(760, 370, _T("세트 메뉴"));
		}
		else {
			dc.SelectObject(gothic3);
			dc.SetTextColor(RGB(0, 0, 0));
			dc.TextOutW(760, 370, _T("세트 메뉴"));
		}
		if (rgn6.PtInRegion(point)) {
			dc.SelectObject(gothic3);
			dc.SetTextColor(RGB(150, 75, 0));
			dc.TextOutW(405, 560, _T("사이드 메뉴"));
		}
		else {
			dc.SelectObject(gothic3);
			dc.SetTextColor(RGB(0, 0, 0));
			dc.TextOutW(405, 560, _T("사이드 메뉴"));
		}
		if (rgn7.PtInRegion(point)) {
			dc.SelectObject(gothic3);
			dc.SetTextColor(RGB(150, 75, 0));
			dc.TextOutW(795, 560, _T("주류"));
		}
		else {
			dc.SelectObject(gothic3);
			dc.SetTextColor(RGB(0, 0, 0));
			dc.TextOutW(795, 560, _T("주류"));
		}
		if (rgn8.PtInRegion(point)) {
			dc.SelectObject(gothic1);
			dc.SetTextColor(RGB(0, 0, 0));
			dc.TextOutW(1177, 37, CString(_T("한국어")));
		}
		else {
			dc.SelectObject(gothic1);
			dc.SetTextColor(RGB(255, 255, 255));
			dc.TextOutW(1177, 37, CString(_T("한국어")));
		}
		if (rgn9.PtInRegion(point)) {
			dc.SelectObject(gothic1);
			dc.SetTextColor(RGB(0, 0, 0));
			dc.TextOutW(1190, 137, CString(_T("영어")));
		}
		else {
			dc.SelectObject(gothic1);
			dc.SetTextColor(RGB(255, 255, 255));
			dc.TextOutW(1190, 137, CString(_T("영어")));
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
	// 사용할 변수 선언
	CClientDC dc(this);
	dc.SetBkMode(TRANSPARENT);
	CPen null(PS_NULL, 0, RGB(0, 0, 0));
	CPen yellow(PS_SOLID, 2.5, RGB(250, 250, 10));
	CBrush bnb(RGB(225, 80, 55));
	CFont gothic1;
	gothic1.CreateFont(45, 0, 0, 0,
		FW_DEMIBOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));
	CFont gothic2;
	gothic2.CreateFont(40, 0, 0, 0,
		FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));

	// 버튼의 리전 설정
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

	// 종료 버튼을 누르면 프로그램을 종료하도록 함
	if (rgn1.PtInRegion(point)) {
		AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_APP_EXIT, NULL);
	}

	// 장바구니 초기화 버튼을 누르면 장바구니 초기화
	if (rgn2.PtInRegion(point)) {
		// 생성자의 지역변수
		x = 10;
		y = 1010;
		total = 0;
		
		menuList.RemoveAll();
		priceList.RemoveAll();
		for (int i = 0; i < orderArr.GetCount(); i++) {
			orderArr[i] = 0;
		}

		// 화면 갱신
		Invalidate();
	}

	// 결제 버튼을 누르면 결제창 출력
	if (rgn3.PtInRegion(point)) {
		// 예/아니요 메시지 박스 정의
		int answer; 
		if (!langFlag) {
			answer = MessageBox(_T("결제를 진행하시겠습니까?"), _T("안내 메시지"), MB_YESNO | MB_ICONASTERISK);
		}
		else {
			answer = MessageBox(_T("Would you like to proceed with payment?"), _T("Message"), MB_YESNO | MB_ICONASTERISK);
		}

		// 예를 눌렀을 시
		if (answer == IDYES) {
			// 장바구니가 비었을 때
			if (total == 0) {
				if (!langFlag) {
					MessageBox(_T("장바구니가 비어있습니다."), _T("안내 메시지"), MB_ICONERROR);
				}
				else {
					MessageBox(_T("Basket is empty!"), _T("Message"), MB_ICONERROR);
				}
			}
			else {

				// 지역 변수 선언
				CString msg = _T("");
				CString info;
				CString menu;
				CString price;
				int order;
				POSITION menuPos = menuList.GetHeadPosition();
				POSITION pricePos = priceList.GetHeadPosition();

				// while-loop문 작성
				// 반복을 통해 주문 정보를 메시지박스로 전달
				int i = 0;
				while (menuPos != NULL) {
					// 주문 정보 반환
					menu = menuList.GetNext(menuPos);
					price = priceList.GetNext(pricePos);
					order = orderArr[i];

					// 정보 포매팅
					info.Format(_T("%s %-5s %-d\r\n"), menu.Trim(), price, order); // 공백 제거

					// 수량이 0이라면 정보를 전달하지 않음
					i++;
					if (order == 0) {
						continue;
					}

					// 출력할 메시지에 정보 추가
					msg += info;
				}

				// 결제할 최종 금액을 메시지 박스에 전달
				CString account;
				if (!langFlag) {
					account.Format(_T("\r\n               총합 = %d원"), total);
				}
				else {
					account.Format(_T("\r\n               Total = %d Won"), total);
				}
				msg += account;
				
				// 메시지 박스 출력
				if (!langFlag) {
					MessageBox(msg, _T("결제 내역"), MB_ICONINFORMATION);
				}
				else {
					MessageBox(msg, _T("Payment List"), MB_ICONINFORMATION);
				}

				// 모든 동작이 끝나면 변수 초기화
				x = 10;
				y = 1010;
				total = 0;

				menuList.RemoveAll();
				priceList.RemoveAll();
				for (int i = 0; i < orderArr.GetCount(); i++) {
					orderArr[i] = 0;
				}

				// 화면 갱신
				Invalidate();

			}
		}
	}

	// 메뉴판 버튼을 누르면 메뉴판 출력
	// 텍스트 파일을 담을 객체 선언
	CStdioFile iFile;
	setlocale(LC_ALL, "korean"); // 한글 깨짐 방지
	
	// 대화상자 객체 선언
	CMyDialog1 dlg1;
	
	// 조건 분기
	if ((rgn4.PtInRegion(point)) || (rgn5.PtInRegion(point)) || (rgn6.PtInRegion(point)) || (rgn7.PtInRegion(point))) {
		
		// 지역 변수 선언
		int bmp;

		// 메뉴판 종류에 따른 조건 분기
		if(rgn4.PtInRegion(point)) {

			// 메인 메뉴를 담는 메뉴판
			if (!langFlag) {
				iFile.Open(_T("res\\메인 메뉴.txt"), CFile::modeRead);
			}
			else {
				iFile.Open(_T("res\\mainMenu.txt"), CFile::modeRead);
			}

			bmp = 312;
		}
		else if (rgn5.PtInRegion(point)) {

			// 세트 메뉴를 담는 메뉴판
			if (!langFlag) {
				iFile.Open(_T("res\\세트 메뉴.txt"), CFile::modeRead);
			}
			else {
				iFile.Open(_T("res\\setMenu.txt"), CFile::modeRead);
			}

			bmp = 317;
		}
		else if (rgn6.PtInRegion(point)) {

			// 사이드 메뉴를 담는 메뉴판
			if (!langFlag) {
				iFile.Open(_T("res\\사이드 메뉴.txt"), CFile::modeRead);
			}
			else {
				iFile.Open(_T("res\\sideMenu.txt"), CFile::modeRead);
			}

			bmp = 321;
		}
		else if (rgn7.PtInRegion(point)) {

			// 주류를 담는 메뉴판
			if (!langFlag) {
				iFile.Open(_T("res\\주류.txt"), CFile::modeRead);
			}
			else {
				iFile.Open(_T("res\\juices.txt"), CFile::modeRead);
			}

			bmp = 327;
		}

		// 파일을 한줄씩 읽어 대화상자 객체에 저장
		while (iFile.ReadString(dlg1.info)) {
			dlg1.infoList.AddTail(dlg1.info);
		}

		// 모드형 대화상자
		dlg1.DoModal();

		// 장바구니 FLAG가 참일 때 조건 분기
		if (dlg1.basket) {

			// 지역변수 선언
			CString menu;
			CString price;
			POSITION menuPos = dlg1.menuList.GetHeadPosition();
			POSITION pricePos = dlg1.priceList.GetHeadPosition();
			// 메뉴판 중복과 관련된 변수
			int accMenu;
			int flag = 0;
			int cnt = 0;
			
			for (int i = 0; i < dlg1.menuList.GetCount(); i++) {
			// 비트맵 관련 객체 선언
				CBitmap basket;
				BITMAP bktInfo;
				CDC dcmem;
				dcmem.CreateCompatibleDC(&dc);
				
				// 리소스 ID 관리 필요
				// switch문에서 리소스 ID로 비트맵 선택
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

				// 메뉴판을 장바구니에 전달
				menu = dlg1.menuList.GetNext(menuPos);
				price = dlg1.priceList.GetNext(pricePos);

				// 메뉴판이 중복되면 더이상 전달하지 않음
				if (menuList.Find(menu) == NULL) { // 메뉴가 더 특수함
					menuList.AddTail(menu);
					priceList.AddTail(price);
					flag = 1;
				}
				cnt++;

				// 이중 for문 작성
				// 수량을 장바구니에 전달
				flag == 1 ? accMenu = menuList.GetCount() : accMenu = cnt; // 메뉴판 중복에 따라 수량 리스트 분기
				for (int j = 0; j < dlg1.orderArr[i]; j++) {
					// 비트맵 출력할 공간이 없을 시 -> 장바구니 가득찬 것으로 간주
					if ((x + bktInfo.bmWidth * 0.2 > 890) && (y == 1150)) {
						if (!langFlag) {
							MessageBox(_T("장바구니가 가득 찼습니다!"), _T("안내 메시지"), MB_ICONERROR);
						}
						else {
							MessageBox(_T("Basket is full!"), _T("Message"), MB_ICONERROR);
						}
						goto jump;
					}
					// 첫 번째 줄이 가득 차면 비트맵 줄바꿈을 해줌
					else if (x + bktInfo.bmWidth * 0.2 > 890) {
						x = 10;
						y = 1150;
					}

					// 각 수량마다 비트맵 장바구니에 출력
					dc.StretchBlt(x, y, bktInfo.bmWidth * 0.20, bktInfo.bmHeight * 0.25,
						&dcmem, 0, 0, bktInfo.bmWidth, bktInfo.bmHeight, SRCCOPY);
					// 출력 후 다음 위치로 이동
					x += bktInfo.bmWidth * 0.20 + 25;
					// 최종 결과에 반영
					total += dlg1.priceArr[i];
					// 장바구니 전달할 수량 증가
					orderArr[accMenu - 1]++;
				}
			}

			jump :

				// 결제창에서 동작에 의해 변경된 사항을 갱신
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
					dc.TextOutW(995, 960, CString(_T("전체 주문 금액")));
					dc.TextOutW(1155, 1020, CString(_T("원")));
				}
				else {
					dc.TextOutW(990, 960, CString(_T("Total Amount")));
					dc.TextOutW(1155, 1020, CString(_T("Won")));
				}

				dc.SelectObject(yellow);
				dc.Rectangle(940, 1090, 1240, 1150);
				if (!langFlag) {
					dc.TextOutW(1027, 1100, CString(_T("결제 버튼")));
				}
				else {
					dc.TextOutW(1030, 1100, CString(_T("Payment")));
				}

		}
	}

	// 언어팩 관련 버튼
	// 버튼을 누르면 언어 스위칭 + 화면 갱신
	if (rgn8.PtInRegion(point)) {
	langFlag = 0;

	// 변수 초기화
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

	// 변수 초기화
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
