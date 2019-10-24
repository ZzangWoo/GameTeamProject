// CardGameProject.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "game_project.h"
#include "CardGameProject.h"
#include "afxdialogex.h"

#include "Rock.h"
#include "game_projectDlg.h"

#include "atlimage.h"



// CardGameProject ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CardGameProject, CDialog)

CardGameProject::CardGameProject(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_CARDGAME, pParent)
	, editPlayer1Point(_T(""))
	, editPlayer2Point(_T(""))
	, testEdit(_T(""))
	, remainTime(_T(""))
	, m_player1(_T(""))
	, m_player2(_T(""))
{

	nickName = _T("");
	roomKind = 0;
	//  m_player1 = _T("");
	//  m_player2 = _T("");
}

CardGameProject::~CardGameProject()
{
}

void CardGameProject::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PLAYER1_POINT, editPlayer1Point);
	DDX_Text(pDX, IDC_EDIT_PLAYER2_POINT, editPlayer2Point);
	DDX_Control(pDX, IDC_EDIT_SEND, cardGameMsg);
	DDX_Text(pDX, IDC_EDIT_TEST, testEdit);
	DDX_Text(pDX, IDC_EDIT_TIME, remainTime);
	DDX_Control(pDX, IDC_LIST_MSG, listMsg);
	//  DDX_Control(pDX, IDC_PLAYER1_NICK, player1Name);
	//  DDX_Control(pDX, IDC_PLAYER2_NICK, player2Name);
	DDX_Control(pDX, IDC_START_BUTTON, startButton);
	DDX_Text(pDX, IDC_PLAYER1_NICK, m_player1);
	DDX_Text(pDX, IDC_PLAYER2_NICK, m_player2);
}


BEGIN_MESSAGE_MAP(CardGameProject, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CardGameProject::OnClickedButtonSend)
	ON_WM_CREATE()
	ON_MESSAGE(WM_CLIENT_CARD_MSG_RECV, &CardGameProject::OnClientCardMsgRecv)
	ON_BN_CLICKED(IDC_START_BUTTON, &CardGameProject::OnClickedStartButton)
	ON_MESSAGE(WM_CLIENT_CARD_START, &CardGameProject::OnClientCardStart)
	ON_WM_DESTROY()
	ON_MESSAGE(WM_CLIENT_RECV_ROOM_ID_TO_CARD, &CardGameProject::OnClientRecvRoomIDToCard)
	ON_MESSAGE(WM_CLIENT_RSP_RESULT, &CardGameProject::OnClientRspResult)
	ON_MESSAGE(WM_CLIENT_PLAYER_NAME, &CardGameProject::OnClientPlayerName)
//	ON_WM_PAINT()
	ON_MESSAGE(WM_CLIENT_SHUFFLE_CARD_RECV, &CardGameProject::OnClientShuffleCardRecv)
//	ON_WM_PAINT()
ON_WM_PAINT()
END_MESSAGE_MAP()


// CardGameProject �޽��� ó�����Դϴ�.

int CardGameProject::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	CCreateRoomDlg *p_dlg = (CCreateRoomDlg*)GetParent();

	//m_clientSocket = new CClientSocket;
	m_clientSocket = p_dlg->m_clientSocket;
	m_player1 = m_clientSocket->nickname;
	m_player2 = _T("��ٸ�����...");

	p_hWnd = m_clientSocket->m_hWnd;
	m_clientSocket->SetWnd(this->GetSafeHwnd());
	
	// ������� ����
	roomKind = m_clientSocket->info.roomKind;

	//CString str2;
	//str2.Format(_T("%d"), roomKind);
	//AfxMessageBox(str2);

	// ������ ǥ��
	SetWindowText(m_clientSocket->info.roomName);
	
	CString str = _T("");
	str.Format(_T("[%s]���� �����ϼ̽��ϴ�."), p_dlg->nickName);

	cardMsg *msg = new cardMsg;
	msg->id = 5000;
	msg->size = sizeof(cardMsgStruct);
	_tcscpy_s(msg->data.msg, str);
	_tcscpy_s(msg->data.name, m_clientSocket->nickname);
	msg->data.roomID = m_clientSocket->info.roomNum;
	m_clientSocket->Send((char*)msg, sizeof(cardMsg));

	CString test = _T("");
	test.Format(_T("%s"), msg->data.msg);
	
	//AfxMessageBox(test);

	//listMsg.SetWindowTextW(_T(""));
	//UpdateData(FALSE);

	delete msg;

	//AfxMessageBox(test);

	//listMsg.InsertString(-1, str);
	//listMsg.SetCurSel(listMsg.GetCount() - 1);

	/****************** ī�� �̹��� �ε� *******************/
	CString cardImage;
	for (int i = 0; i < MAX_TOTAL_CARD_COUNT; i++) {
		cardImage.Format(_T("%d.jpg"), i);
		m_card_image[i].Load(cardImage);
	}
	/*******************************************************/

	CDC		MemDC, *pDC;
	pDC = this->GetDC();
	MemDC.CreateCompatibleDC(pDC);

	return 0;
}

afx_msg LRESULT CardGameProject::OnClientCardMsgRecv(WPARAM wParam, LPARAM lParam)
{
	cardMsgStruct* msg = (cardMsgStruct*)lParam;

	listMsg.InsertString(-1, msg->msg);
	listMsg.SetCurSel(listMsg.GetCount() - 1);

	return 0;
}

// �޼���������
void CardGameProject::OnClickedButtonSend()
{
	CString str;
	UpdateData(TRUE);
	cardGameMsg.GetWindowTextW(str);

	cardMsg* msg = new cardMsg;
	msg->id = 5000;
	msg->size = sizeof(cardMsgStruct);
	_tcscpy_s(msg->data.msg, str);
	_tcscpy_s(msg->data.name, m_clientSocket->nickname);
	msg->data.roomID = m_clientSocket->info.roomNum;

	m_clientSocket->Send((char*)msg, sizeof(cardMsgStruct));

	cardGameMsg.SetWindowTextW(_T(""));
	
	delete msg;
	
	UpdateData(FALSE);
}

// �غ��ư ������ ��
void CardGameProject::OnClickedStartButton()
{
	if (isReady == FALSE) {
		startButton.SetWindowTextW(_T("����"));

		cardReady* cr = new cardReady;
		cr->id = 5400;
		cr->size = sizeof(cardReadyStruct);
		cr->data.roomID = m_clientSocket->info.roomNum;
		cr->data.isReady = TRUE;
		cr->data.roomKind = 1006;
		m_clientSocket->Send((char*)cr, sizeof(cardReady));
		delete cr;

		isReady = TRUE;
		isStart = TRUE;
	}
	else {
		AfxMessageBox(_T("�̹� �غ�Ǿ����ϴ�"));
	}
}

// ���ӽ���
afx_msg LRESULT CardGameProject::OnClientCardStart(WPARAM wParam, LPARAM lParam) {
	cardStartStruct* css = (cardStartStruct*)lParam;
	
	if (css->start == TRUE) {
		//AfxMessageBox(_T("���������� ����!!!"));
		r_dlg = new Rock();
		r_dlg->DoModal();
	}

	return 0;
}

afx_msg LRESULT CardGameProject::OnClientRecvRoomIDToCard(WPARAM wParam, LPARAM lParam) {
	//AfxMessageBox(_T("����"));
	int deletedRoomID = (int)lParam;

	if (m_clientSocket->info.roomNum > deletedRoomID) {
		m_clientSocket->info.roomNum--;
	}

	return 0;
}

void CardGameProject::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	createRoom* msg = new createRoom;
	msg->id = 5005;
	msg->size = sizeof(createRoomStruct);
	msg->data.roomID = m_clientSocket->info.roomNum;
	msg->data.roomKind = roomKind;
	m_clientSocket->SetWnd(p_hWnd);
	m_clientSocket->Send((char*)msg, sizeof(createRoom));	
	delete msg;
}

afx_msg LRESULT CardGameProject::OnClientRspResult(WPARAM wParam, LPARAM lParam)
{
	int choice = (int)lParam;
	CString str;

	if (choice == 0) {
		AfxMessageBox(_T("�����ϴ�."));
		return 0;
	}
	else if (choice == -1) {
		r_dlg->EndDialog(IDOK);
		str.Format(_T("�̰���ϴ�. ���� �����մϴ�."));
	}
	else {
		r_dlg->EndDialog(IDOK);
		str.Format(_T("�����ϴ�. %s���� ���� �����մϴ�."), m_player2);
	}

	listMsg.InsertString(-1, str);
	listMsg.SetCurSel(listMsg.GetCount() - 1);

	//Invalidate();
	draw();

	return 0;
}

afx_msg LRESULT CardGameProject::OnClientPlayerName(WPARAM wParam, LPARAM lParam)
{
	CString p2 = (LPCTSTR)lParam;
	m_player2 = p2;
	UpdateData(FALSE);
	return 0;
}

afx_msg LRESULT CardGameProject::OnClientShuffleCardRecv(WPARAM wParam, LPARAM lParam) {
	cardArr = (char*)lParam;

	/*CString str;
	str.Format(_T("%d"), cardArr[2]);
	AfxMessageBox(str);*/

	cardState = true;

	//Invalidate();

	return 0;
}

void CardGameProject::OnClickedCardExitButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//CardGameProject* dlg = new CardGameProject;
	//dlg->DestroyWindow();
	//DestroyWindow();
}

void CardGameProject::draw() {
	CPaintDC doc(CWnd::FromHandle(m_hWnd));
	CPaintDC dcc(this);
	

	if (isStart) {
		CDC		MemDC, *pDC;
		pDC = this->GetDC();
		MemDC.CreateCompatibleDC(pDC);
		CClientDC dc(this);
		//m_card_image[1].BitBlt(dc, 280, 456);
		int index;
		for (int i = 0; i < MAX_PLAY_CARD_COUNT * 2; i++) {
			if (cardArr[i] == -1) continue;
			if (cardState == false) index = 0;
			else index = cardArr[i] + 1;

			m_card_image[index].BitBlt(dc, (i % 6) * 56, (i / 6) * 76);
		}
	}
}

void CardGameProject::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
					   // �׸��� �޽����� ���ؼ��� CDialog::OnPaint()��(��) ȣ������ ���ʽÿ�.

	

	if (isStart) {
		CDC		MemDC, *pDC;
		pDC = this->GetDC();
		MemDC.CreateCompatibleDC(pDC);

		int index;
		for (int i = 0; i < MAX_PLAY_CARD_COUNT * 2; i++) {
			if (cardArr[i] == -1) continue;
			if (cardState == false) index = 0;
			else index = cardArr[i] + 1;

			m_card_image[index].BitBlt(dc, (i % 6) * 56, (i / 6) * 76);
		}
	}

	
}
