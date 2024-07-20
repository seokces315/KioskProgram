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


// ���̾�α� �ʱ�ȭ �Լ�
BOOL CMyDialog1::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��Ʈ ����
	m_font.CreateFont(40, 0, 0, 0,
		FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("���� ���"));
	menuLB.SetFont(&m_font);
	priceLB.SetFont(&m_font);
	orderLB.SetFont(&m_font);

	// ����Ʈ �ڽ� �ʱ�ȭ
	CString menu;
	CString price;
	POSITION pos = infoList.GetHeadPosition();
	int lbCnt = 0;
	while (pos != NULL) {
		info = infoList.GetNext(pos);
		
		// ���ڿ� �и� �Լ� Ȱ��
		AfxExtractSubString(menu, info, 0, ','); 
		AfxExtractSubString(price, info, 1, ',');
		menuLB.AddString(menu);
		menuList.AddTail(menu);
		priceLB.AddString(price);
		priceList.AddTail(price);
		lbCnt++;
	}

	// ������ ���� �迭 ����
	int i = 0;
	int intPrice;
	priceArr.SetSize(lbCnt);
	pos = priceList.GetHeadPosition();
	while (pos != NULL) {
		price = priceList.GetNext(pos);
		intPrice = _ttoi(price); // CString -> UINT ��ȯ���ִ� �Լ� Ȱ��
		priceArr[i] = intPrice;
		i++;
	}

	// ����Ʈ �ڽ� Ŀ�� �ʱ�ȭ
	menuLB.SetCurSel(0);
	priceLB.SetCurSel(0);

	// ���� ��Ʈ�� ��ġ/ũ�� �ʱ�ȭ
	orderCtrl.MoveWindow(630, 337, 170, 60);

	// ���� ����Ʈ �ڽ� �ʱ�ȭ
	// ������ ���� �迭 ����
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


// ��ȭ������ ����� ���õ� �Լ�
HBRUSH CMyDialog1::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// ����Ʈ�ڽ��� ���� ����
	if (nCtlColor == CTLCOLOR_LISTBOX) {
		return CreateSolidBrush(RGB(250, 240, 230));
	}

	return hbr;
}


// ����Ʈ�ڽ��� Ŀ�� ����ȭ �Լ� ����
void CMyDialog1::OnLbnSelchangeList1()
{
	// Ŀ�� ��ȯ
	int nIndex = menuLB.GetCurSel();
	// �ٸ��ʿ� ����
	priceLB.SetCurSel(nIndex);
	orderLB.SetCurSel(nIndex);
}

void CMyDialog1::OnLbnSelchangeList2()
{
	// Ŀ�� ��ȯ
	int nIndex = priceLB.GetCurSel();
	// �ٸ��ʿ� ����
	menuLB.SetCurSel(nIndex);
	orderLB.SetCurSel(nIndex);
}

void CMyDialog1::OnLbnSelchangeList3()
{
	// Ŀ�� ��ȯ
	int nIndex = orderLB.GetCurSel();
	// �ٸ��ʿ� ����
	menuLB.SetCurSel(nIndex);
	priceLB.SetCurSel(nIndex);
}


// ������Ʈ�� ���۰� ���õ� �Լ�
void CMyDialog1::OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	*pResult = 0;

	// ���� ������Ʈ���� ������ Ŀ�� ��ȯ
	int nIndex = menuLB.GetCurSel();
	int mtIndex = orderLB.GetCurSel();
	// Ŀ���� �ش�Ǵ� ���� ����Ʈ�ڽ� ������ ����
	orderLB.DeleteString(nIndex);

	// �ִ밪: 9, �ּҰ�: 0���� ������Ʈ�� ����
	// ������Ʈ�� ���� ����
	if ((pNMUpDown->iDelta < 0) && (orderArr[nIndex] < 9)) {
		orderArr[nIndex]++; 
	}
	else if((pNMUpDown->iDelta > 0) && (orderArr[nIndex] > 0)) {
		orderArr[nIndex]--;
	}

	// ���� ����Ʈ�ڽ� ���� Ŀ�� ��ġ�� ���ο� ������ �߰�
	CString order;
	order.Format(_T("%2d"), orderArr[nIndex]);
	orderLB.InsertString(nIndex, order);

	orderLB.SetCurSel(mtIndex);
}


// Ȯ�� ��ư ���� �Լ�
void CMyDialog1::OnBnClickedOk()
{
	// ��/�ƴϿ� �޽��� �ڽ� ����
	int answer = MessageBox(_T("��ٱ��Ͽ� ��ڽ��ϱ�?\r\nWould you like to add to basket?"), _T("Message"), MB_YESNO | MB_ICONASTERISK);

	// ���� ������ ��
	if (answer == IDYES) {
		// Ư�� flag�� ����
		basket = 1;
		
		EndDialog(answer); // ��ȭ���� ����
	}
}
