// OthelloDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "game_project.h"
#include "OthelloDlg.h"
#include "afxdialogex.h"

#include "Rock.h"
#include "game_projectDlg.h"
#define PORT 9999
// COthelloDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(COthelloDlg, CDialog)

COthelloDlg::COthelloDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_OTHELLO, pParent)
	, m_turn(false)
	, m_count(0)
	, m_1_count(2)
	, m_2_count(2)
	, m_player1(_T(""))
	, m_player2(_T("player2\n기다리는 중"))
	, m_stone_color(0)
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
	DDX_Text(pDX, IDC_STATIC1, m_player1);
	DDX_Text(pDX, IDC_STATIC2, m_player2);
	DDX_Control(pDX, IDC_EDIT_OTHELLO_MSG, m_edit_msg);
	DDX_Control(pDX, IDC_LIST_OTHELLO_MSG, m_llist_msg);
}


BEGIN_MESSAGE_MAP(COthelloDlg, CDialog)
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BTN_PASS, &COthelloDlg::OnClickedBtnPass)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_OTHELLO_SEND, &COthelloDlg::OnClickedBtnSend)
	ON_MESSAGE(WM_CLIENT_OTHELLO_MSG_RECV, &COthelloDlg::OnClientOthelloMsgRecv)
	ON_MESSAGE(WM_CLIENT_RECV_ROOM_ID_TO_CARD, &COthelloDlg::OnClientRecvRoomIDToCard)
	ON_WM_DESTROY()
	ON_MESSAGE(WM_CLIENT_PLAYER_NAME, &COthelloDlg::OnClientPlayerName)
	ON_BN_CLICKED(IDC_BTN_READY, &COthelloDlg::OnClickedBtnReady)
	ON_MESSAGE(WM_CLIENT_OTHELLO_ALL_READY, &COthelloDlg::OnClientOthelloAllReady)
	ON_MESSAGE(WM_CLIENT_RSP_RESULT, &COthelloDlg::OnClientRspResult)
END_MESSAGE_MAP()


// COthelloDlg 메시지 처리기입니다.


void COthelloDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (point.x > 420 || point.x < 10 || point.y>420 || point.y < 10) {
		AfxMessageBox(_T("보드 위를 클릭해주세요."), MB_ICONWARNING);
		return;
	}
	int m_x = (point.x - 20) / 50, m_y = (point.y - 20) / 50;
	if (m_map[m_y][m_x] != 0) {
		AfxMessageBox(_T("이미 둔 곳 입니다."));
		return;
	}

	int* pointX, *pointY, **pointXY;
	pointX = judgeStoneX(m_x, m_y);
	pointY = judgeStoneY(m_x, m_y);
	pointXY = judgeStoneXY(m_x, m_y);
	if (pointX[0] == -1 & pointX[1] == -1 & pointY[0] == -1 & pointY[1] == -1 &
		pointXY[0][0] == -1 & pointXY[1][0] == -1 & pointXY[2][0] == -1 & pointXY[3][0] == -1) {
		AfxMessageBox(_T("잘못된 선택입니다."), MB_ICONWARNING);
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

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CCreateRoomDlg *p_dlg = (CCreateRoomDlg*)GetParent();

	m_clientSocket = p_dlg->m_clientSocket;
	m_player1 = m_clientSocket->nickname;
	p_hWnd = m_clientSocket->m_hWnd;
	m_clientSocket->SetWnd(this->GetSafeHwnd());
	// OOO님이 입장하셨습니다
	CString str = _T("");
	str.Format(_T("[%s]님이 입장하셨습니다."), p_dlg->nickName);

	othelloMsg *msg = new othelloMsg;
	msg->id = 50;
	msg->size = sizeof(othelloMsgStruct);
	_tcscpy_s(msg->data.msg, str);
	_tcscpy_s(msg->data.name, m_clientSocket->nickname);
	msg->data.roomID = m_clientSocket->info.roomNum;
	m_clientSocket->Send((char*)msg, sizeof(othelloMsg));
	delete msg;

	SetWindowText(m_clientSocket->info.roomName);

	m_bitmap[0].LoadBitmap(IDB_RED);
	m_bitmap[1].LoadBitmap(IDB_YELLOW);

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

	return 0;
}


void COthelloDlg::OnClickedBtnPass()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_turn = !m_turn;
}


void COthelloDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.
	DrawLine();

	/*CFont font;
	font.CreateFontW(50, 20, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("고딕"));
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

void COthelloDlg::OnClickedBtnSend()
{
	// TODO: Add your control notification handler code here
	CString str;
	UpdateData(TRUE);
	m_edit_msg.GetWindowTextW(str);

	othelloMsg *msg = new othelloMsg;
	msg->id = 50;
	msg->size = sizeof(msgRecvMessage);
	_tcscpy_s(msg->data.msg, str);
	_tcscpy_s(msg->data.name, m_player1);
	msg->data.roomID= m_clientSocket->info.roomNum;
	m_clientSocket->Send((char*)msg, sizeof(msgMessage) * 2);

	m_edit_msg.SetWindowTextW(_T(""));
	UpdateData(FALSE);

	delete msg;
}


afx_msg LRESULT COthelloDlg::OnClientOthelloMsgRecv(WPARAM wParam, LPARAM lParam)
{
	othelloMsgStruct* msg = (othelloMsgStruct*)lParam;
	
	m_llist_msg.InsertString(-1, msg->msg);
	m_llist_msg.SetCurSel(m_llist_msg.GetCount() - 1);

	return 0;
}

afx_msg LRESULT COthelloDlg::OnClientRecvRoomIDToCard(WPARAM wParam, LPARAM lParam) {
	//AfxMessageBox(_T("들어옴"));
	int deletedRoomID = (int)lParam;

	if (m_clientSocket->info.roomNum > deletedRoomID) {
		m_clientSocket->info.roomNum--;
	}

	return 0;
}


void COthelloDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
	createRoom *msg = new createRoom;
	msg->id = 5005;
	msg->size = sizeof(createRoomStruct);
	msg->data.roomID = m_clientSocket->info.roomNum;
	m_clientSocket->SetWnd(p_hWnd);
	m_clientSocket->Send((char*)msg, sizeof(createRoom));
	delete msg;
}


afx_msg LRESULT COthelloDlg::OnClientPlayerName(WPARAM wParam, LPARAM lParam)
{
	CString p2 = (LPCTSTR)lParam;
	m_player2 = p2;
	UpdateData(FALSE);
	return 0;
}


void COthelloDlg::OnClickedBtnReady()
{
	// TODO: Add your control notification handler code here
	if (m_player2 != _T("player2\n기다리는 중")) {
		readyMessage *msg = new readyMessage;
		msg->id = 3;
		msg->size = sizeof(readyRecvMessage);
		msg->data.roomID = m_clientSocket->info.roomNum;
		m_clientSocket->Send((char*)msg, sizeof(readyRecvMessage));
		delete msg;
		CButton* pBtn = (CButton*)GetDlgItem(IDC_BTN_READY);
		pBtn->EnableWindow(FALSE);
	}
	else
		AfxMessageBox(_T("플레이어를 기다리는 중입니다."));
}


afx_msg LRESULT COthelloDlg::OnClientOthelloAllReady(WPARAM wParam, LPARAM lParam)
{
	r_dlg = new Rock();
	r_dlg->DoModal();
	return 0;
}


afx_msg LRESULT COthelloDlg::OnClientRspResult(WPARAM wParam, LPARAM lParam)
{
	int choice = (int)lParam;
	CString str;

	if (choice == 0) {
		str.Format(_T("비겼습니다! 다시 해주세요!"));

	}
	else if (choice == -1) {
		r_dlg->EndDialog(IDOK);
		str.Format(_T("이겼습니다. 먼저 시작합니다."));
		m_turn = true;
		m_stone_color = 0;
	}
	else {
		r_dlg->EndDialog(IDOK);
		str.Format(_T("졌습니다. %s님이 먼저 시작합니다."), m_player2);
		m_stone_color = 1;
	}
	AfxMessageBox(str);
	return 0;
}
