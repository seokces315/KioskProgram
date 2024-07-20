// CMyDialog1.cpp : implementation file

#include "pch.h"
#include "KioskProgram.h"
#include "afxdialogex.h"
#include "CMyDialog1.h"


// CMyDialog1 dialog

IMPLEMENT_DYNAMIC(CMyDialog1, CDialog)

CMyDialog1::CMyDialog1(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MENU, pParent)
{
}

CMyDialog1::~CMyDialog1()
{
}


void CMyDialog1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, menuLB);
	DDX_Control(pDX, IDC_LIST2, priceLB);
	DDX_Control(pDX, IDC_LIST3, orderLB);
	DDX_Control(pDX, IDC_SPIN1, orderCtrl);
}


BEGIN_MESSAGE_MAP(CMyDialog1, CDialog)
	ON_WM_CTLCOLOR()
	ON_LBN_SELCHANGE(IDC_LIST1, &CMyDialog1::OnLbnSelchangeList1)
	ON_LBN_SELCHANGE(IDC_LIST2, &CMyDialog1::OnLbnSelchangeList2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CMyDialog1::OnDeltaposSpin1)
	ON_BN_CLICKED(IDC_OK, &CMyDialog1::OnBnClickedOk)
	ON_WM_MEASUREITEM()
	ON_LBN_SELCHANGE(IDC_LIST3, &CMyDialog1::OnLbnSelchangeList3)
END_MESSAGE_MAP()


// CMyDialog1 message handlers


// 다이얼로그 초기화 함수
BOOL CMyDialog1::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 폰트 설정
	m_font.CreateFont(40, 0, 0, 0,
		FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));
	menuLB.SetFont(&m_font);
	priceLB.SetFont(&m_font);
	orderLB.SetFont(&m_font);

	// 리스트 박스 초기화
	CString menu;
	CString price;
	POSITION pos = infoList.GetHeadPosition();
	int lbCnt = 0;
	while (pos != NULL) {
		info = infoList.GetNext(pos);
		
		// 문자열 분리 함수 활용
		AfxExtractSubString(menu, info, 0, ','); 
		AfxExtractSubString(price, info, 1, ',');
		menuLB.AddString(menu);
		menuList.AddTail(menu);
		priceLB.AddString(price);
		priceList.AddTail(price);
		lbCnt++;
	}

	// 가격을 담을 배열 정의
	int i = 0;
	int intPrice;
	priceArr.SetSize(lbCnt);
	pos = priceList.GetHeadPosition();
	while (pos != NULL) {
		price = priceList.GetNext(pos);
		intPrice = _ttoi(price); // CString -> UINT 변환해주는 함수 활용
		priceArr[i] = intPrice;
		i++;
	}

	// 리스트 박스 커서 초기화
	menuLB.SetCurSel(0);
	priceLB.SetCurSel(0);

	// 수량 컨트롤 위치/크기 초기화
	orderCtrl.MoveWindow(630, 337, 170, 60);

	// 수량 리스트 박스 초기화
	// 수량을 담을 배열 정의
	CString order;
	orderArr.SetSize(lbCnt);
	for (int i = 0; i < lbCnt; i++) {
		orderArr[i] = 0;
		order.Format(_T("%2d"), orderArr[i]);
		orderLB.AddString(order);
	}
	orderLB.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
}


// 대화상자의 색상과 관련된 함수
HBRUSH CMyDialog1::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// 리스트박스의 배경색 설정
	if (nCtlColor == CTLCOLOR_LISTBOX) {
		return CreateSolidBrush(RGB(250, 240, 230));
	}

	return hbr;
}


// 리스트박스의 커서 동기화 함수 정의
void CMyDialog1::OnLbnSelchangeList1()
{
	// 커서 반환
	int nIndex = menuLB.GetCurSel();
	// 다른쪽에 적용
	priceLB.SetCurSel(nIndex);
	orderLB.SetCurSel(nIndex);
}

void CMyDialog1::OnLbnSelchangeList2()
{
	// 커서 반환
	int nIndex = priceLB.GetCurSel();
	// 다른쪽에 적용
	menuLB.SetCurSel(nIndex);
	orderLB.SetCurSel(nIndex);
}

void CMyDialog1::OnLbnSelchangeList3()
{
	// 커서 반환
	int nIndex = orderLB.GetCurSel();
	// 다른쪽에 적용
	menuLB.SetCurSel(nIndex);
	priceLB.SetCurSel(nIndex);
}


// 스핀컨트롤 동작과 관련된 함수
void CMyDialog1::OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	*pResult = 0;

	// 현재 스핀컨트롤이 관장할 커서 반환
	int nIndex = menuLB.GetCurSel();
	int mtIndex = orderLB.GetCurSel();
	// 커서에 해당되는 수량 리스트박스 데이터 제거
	orderLB.DeleteString(nIndex);

	// 최대값: 9, 최소값: 0으로 스핀컨트롤 정의
	// 스핀컨트롤 동작 설정
	if ((pNMUpDown->iDelta < 0) && (orderArr[nIndex] < 9)) {
		orderArr[nIndex]++; 
	}
	else if((pNMUpDown->iDelta > 0) && (orderArr[nIndex] > 0)) {
		orderArr[nIndex]--;
	}

	// 수량 리스트박스 직전 커서 위치에 새로운 데이터 추가
	CString order;
	order.Format(_T("%2d"), orderArr[nIndex]);
	orderLB.InsertString(nIndex, order);

	orderLB.SetCurSel(mtIndex);
}


// 확인 버튼 동작 함수
void CMyDialog1::OnBnClickedOk()
{
	// 예/아니요 메시지 박스 정의
	int answer = MessageBox(_T("장바구니에 담겠습니까?\r\nWould you like to add to basket?"), _T("Message"), MB_YESNO | MB_ICONASTERISK);

	// 예를 눌렀을 시
	if (answer == IDYES) {
		// 특정 flag값 지정
		basket = 1;
		
		EndDialog(answer); // 대화상자 종료
	}
}
