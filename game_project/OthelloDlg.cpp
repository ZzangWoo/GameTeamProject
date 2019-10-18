// OthelloDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "game_project.h"
#include "OthelloDlg.h"
#include "afxdialogex.h"

#include "game_projectDlg.h"
#define PORT 9999
// COthelloDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(COthelloDlg, CDialog)

COthelloDlg::COthelloDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_OTHELLODLG, pParent)
	, m_turn(false)
	, m_count(0)
	, m_1_count(2)
	, m_2_count(2)
{
	m_map = new int*[8];
	m_map[0] = new int[8]{ 0,0,0,0,0,0,0,0 };
	m_map[1] = new int[8]{ 0,0,0,0,0,0,0,0 };
	m_map[2] = new int[8]{ 0,0,0,0,0,0,0,0 };
	m_map[3] = new int[8]{ 0,0,0,1,2,0,0,0 };
	m_map[4] = new int[8]{ 0,0,0,2,1,0,0,0 };
	m_map[5] = new int[8]{ 0,0,0,0,0,0,0,0 };
	m_map[6] = new int[8]{ 0,0,0,0,0,0,0,0 };
	m_map[7] = new int[8]{ 0,0,0,0,0,0,0,0 };
}

COthelloDlg::~COthelloDlg()
{
}

void COthelloDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_COUNT1, m_1_count);
	DDX_Text(pDX, IDC_STATIC_COUNT2, m_2_count);
}


BEGIN_MESSAGE_MAP(COthelloDlg, CDialog)
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BTN_PASS, &COthelloDlg::OnClickedBtnPass)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// COthelloDlg �޽��� ó�����Դϴ�.


void COthelloDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (point.x > 420 || point.x < 10 || point.y>420 || point.y < 10) {
		AfxMessageBox(_T("���� ���� Ŭ�����ּ���."), MB_ICONWARNING);
		return;
	}
	int m_x = (point.x - 20) / 50, m_y = (point.y - 20) / 50;
	if (m_map[m_y][m_x] != 0) {
		AfxMessageBox(_T("�̹� �� �� �Դϴ�."));
		return;
	}

	int* pointX, *pointY, **pointXY;
	pointX = judgeStoneX(m_x, m_y);
	pointY = judgeStoneY(m_x, m_y);
	pointXY = judgeStoneXY(m_x, m_y);
	if (pointX[0] == -1 & pointX[1] == -1 & pointY[0] == -1 & pointY[1] == -1 &
		pointXY[0][0] == -1 & pointXY[1][0] == -1 & pointXY[2][0] == -1 & pointXY[3][0] == -1) {
		AfxMessageBox(_T("�߸��� �����Դϴ�."), MB_ICONWARNING);
	}
	else {
		ChangeStoneX(m_x, pointX[0], m_y);
		ChangeStoneX(m_x, pointX[1], m_y);
		ChangeStoneY(m_x, m_y, pointY[0]);
		ChangeStoneY(m_x, m_y, pointY[1]);
		ChangeStoneXY(m_x, pointXY[0][0], m_y, pointXY[0][1]);
		ChangeStoneXY(m_x, pointXY[1][0], m_y, pointXY[1][1]);
		ChangeStoneXY(m_x, pointXY[2][0], m_y, pointXY[2][1]);
		ChangeStoneXY(m_x, pointXY[3][0], m_y, pointXY[3][1]);
		DrawStone(m_x * 50 + 21, m_y * 50 + 21);
		SetCount();
		m_count++;
		m_turn = !m_turn;
		if (m_count == 61) {
			CString str;
			str.Format(_T("player1: %d player2: %d \r\n winner: %s"), m_1_count, m_2_count, (m_1_count > m_2_count ? "player1" : "player2"));
			AfxMessageBox(str, MB_OK | MB_ICONINFORMATION);
		}
	}
	CDialog::OnLButtonDown(nFlags, point);
}


int COthelloDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	Cgame_projectDlg *p_dlg = (Cgame_projectDlg*)GetParent();

	m_clientSocket = new CClientSocket;
	m_clientSocket->SetWnd(m_hWnd);
	m_clientSocket->Create();
	if (m_clientSocket->Connect(p_dlg->m_serverIP, PORT) == FALSE) {
		AfxMessageBox(_T("ERROR: Failed connected server!!"));
		PostQuitMessage(0);
	}
	p_dlg->ShowWindow(SW_HIDE);
	m_bitmap[0].LoadBitmap(IDB_RED);
	m_bitmap[1].LoadBitmap(IDB_YELLOW);
	return 0;
}


void COthelloDlg::OnClickedBtnPass()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_turn = !m_turn;
}


void COthelloDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
					   // �׸��� �޽����� ���ؼ��� CDialog::OnPaint()��(��) ȣ������ ���ʽÿ�.
	DrawLine();

	/*CFont font;
	font.CreateFontW(50, 20, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("���"));
	GetDlgItem(IDC_1_SCORE)->SetFont(&font);
	GetDlgItem(IDC_2_SCORE)->SetFont(&font);*/
	CBitmap *pOldBitmap;
	CDC   MemDC, *pDC;

	pDC = this->GetDC();
	MemDC.CreateCompatibleDC(pDC);

	pOldBitmap = MemDC.SelectObject(&m_bitmap[0]);
	pDC->BitBlt(171, 171, 48, 48, &MemDC, 0, 0, SRCCOPY);
	pDC->BitBlt(221, 221, 48, 48, &MemDC, 0, 0, SRCCOPY);
	MemDC.SelectObject(pOldBitmap);

	pOldBitmap = MemDC.SelectObject(&m_bitmap[1]);
	pDC->BitBlt(221, 171, 48, 48, &MemDC, 0, 0, SRCCOPY);
	pDC->BitBlt(171, 221, 48, 48, &MemDC, 0, 0, SRCCOPY);
	MemDC.SelectObject(pOldBitmap);
}

void COthelloDlg::DrawLine()
{
	CClientDC pDC(this);
	CRect r;
	GetClientRect(r);
	CPen myPen, *oldPen;
	myPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	oldPen = pDC.SelectObject(&myPen);

	for (int i = 0; i < 9; i++) {
		pDC.MoveTo(20, 50 * i + 20);
		pDC.LineTo(20 + 50 * 8, 50 * i + 20);
	}
	for (int i = 0; i < 9; i++) {
		pDC.MoveTo(50 * i + 20, 20);
		pDC.LineTo(50 * i + 20, 20 + 50 * 8);
	}
}

int COthelloDlg::DrawStone(int x, int y) {
	int m_x = x / 50, m_y = y / 50;

	CBitmap *pOldBitmap;
	CDC   MemDC, *pDC;

	pDC = this->GetDC();

	MemDC.CreateCompatibleDC(pDC);
	if (!m_turn) {
		pOldBitmap = MemDC.SelectObject(&m_bitmap[0]);
		m_map[m_y][m_x] = 1;
	}
	else {
		pOldBitmap = MemDC.SelectObject(&m_bitmap[1]);
		m_map[m_y][m_x] = 2;
	}
	pDC->BitBlt(x, y, 48, 48, &MemDC, 0, 0, SRCCOPY);

	MemDC.SelectObject(pOldBitmap);

	return 0;
}

int* COthelloDlg::judgeStoneX(int x, int y) {
	int t, i;
	int* pointX = new int[2]{ -1,-1 };
	if (!m_turn) t = 1;
	else t = 2;

	for (i = x - 1; i > 0; i--) {
		if (m_map[y][i] == 0) break;
		if (m_map[y][i] == t) {
			if (i == x - 1) break;
			pointX[0] = i;
			break;
		}
	}

	for (i = x + 1; i < 8; i++) {
		if (m_map[y][i] == 0)break;
		if (m_map[y][i] == t) {
			if (i == x + 1) break;
			pointX[1] = i;
			break;
		}
	}
	return pointX;
}

int* COthelloDlg::judgeStoneY(int x, int y) {
	int t, i;
	int* pointY = new int[2]{ -1,-1 };
	if (!m_turn) t = 1;
	else t = 2;

	for (i = y - 1; i > 0; i--) {
		if (m_map[i][x] == 0) break;
		if (m_map[i][x] == t) {
			if (i == y - 1) break;
			pointY[0] = i;
			break;
		}
	}

	for (i = y + 1; i < 8; i++) {
		if (m_map[i][x] == 0) break;
		if (m_map[i][x] == t) {
			if (i == y + 1) break;
			pointY[1] = i;
			break;
		}
	}
	return pointY;
}

int** COthelloDlg::judgeStoneXY(int x, int y) {
	int **pointXY = new int*[4];
	for (int a = 0; a < 4; a++) {
		pointXY[a] = new int[2]{ -1,-1 };
	}
	int t, i_x, i_y;
	if (!m_turn) t = 1;
	else t = 2;
	i_x = x - 1;
	i_y = y - 1;
	while (i_x>0 && i_y>0) {
		if (m_map[i_y][i_x] == 0)break;
		if (m_map[i_y][i_x] == t) {
			if ((i_x == x - 1) && (i_y = y - 1)) break;
			pointXY[0][0] = i_x;
			pointXY[0][1] = i_y;
			break;
		}
		i_x--; i_y--;
	}
	i_x = x - 1;
	i_y = y + 1;
	while (i_x>0 && i_y<8) {
		if (m_map[i_y][i_x] == 0)break;
		if (m_map[i_y][i_x] == t) {
			if ((i_x == x - 1) && (i_y = y + 1)) break;
			pointXY[1][0] = i_x;
			pointXY[1][1] = i_y;
			break;
		}
		i_x--; i_y++;
	}
	i_x = x + 1;
	i_y = y - 1;
	while (i_x<8 && i_y>0) {
		if (m_map[i_y][i_x] == 0)break;
		if (m_map[i_y][i_x] == t) {
			if ((i_x == x + 1) && (i_y = y - 1)) break;
			pointXY[2][0] = i_x;
			pointXY[2][1] = i_y;
			break;
		}
		i_x++; i_y--;
	}
	i_x = x + 1;
	i_y = y + 1;
	while (i_x<8 && i_y<8) {
		if (m_map[i_y][i_x] == 0)break;
		if (m_map[i_y][i_x] == t) {
			if ((i_x == x + 1) && (i_y = y + 1)) break;
			pointXY[3][0] = i_x;
			pointXY[3][1] = i_y;
			break;
		}
		i_x++; i_y++;
	}

	return pointXY;
}

void COthelloDlg::ChangeStoneX(int x1, int x2, int y) {
	if (x2 == -1) return;
	for (int i = (x1 < x2 ? x1 + 1 : x2 + 1); i <= (x1 > x2 ? x1 : x2); i++) {
		DrawStone(i * 50 + 21, y * 50 + 21);
	}
}

void COthelloDlg::ChangeStoneY(int x, int y1, int y2) {
	if (y2 == -1) return;
	for (int i = (y1 < y2 ? y1 + 1 : y2 + 1); i <= (y1 > y2 ? y1 : y2); i++) {
		DrawStone(x * 50 + 21, i * 50 + 21);
	}
}

void COthelloDlg::ChangeStoneXY(int x1, int x2, int y1, int y2) {
	if ((x2 == -1) & (y2 == -1)) return;
	int i_x = x1 < x2 ? x1 + 1 : x2 + 1, i_y = x1<x2 ? y1 : y2, j_x = x1 > x2 ? x1 : x2, j_y = x1 > x2 ? y1 : y2, add = i_y>j_y ? -1 : 1;

	i_y += add;
	while (i_x <= j_x && i_y <= j_x) {
		DrawStone(i_x * 50 + 21, i_y * 50 + 21);
		i_x++;
		i_y += add;
	}
}

void COthelloDlg::SetCount() {
	int cnt1 = 0, cnt2 = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (m_map[j][i] == 1) cnt1++;
			if (m_map[j][i] == 2) cnt2++;
		}
	}
	UpdateData(true);
	m_1_count = cnt1;
	m_2_count = cnt2;
	UpdateData(false);
}