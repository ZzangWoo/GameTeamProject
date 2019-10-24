// CardGameProject.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "game_project.h"
#include "CardGameProject.h"
#include "afxdialogex.h"

#include "game_projectDlg.h"
#include "Rock.h"


// CardGameProject 대화 상자입니다.

IMPLEMENT_DYNAMIC(CardGameProject, CDialog)

CardGameProject::CardGameProject(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_CARDGAME, pParent)
	, editPlayer1Point(_T(""))
	, editPlayer2Point(_T(""))
	, testEdit(_T(""))
	, remainTime(_T(""))
{

	nickName = _T("");
	roomKind = 0;
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
	DDX_Control(pDX, IDC_PLAYER1_NICK, player1Name);
	DDX_Control(pDX, IDC_PLAYER2_NICK, player2Name);
	DDX_Control(pDX, IDC_START_BUTTON, startButton);
}


BEGIN_MESSAGE_MAP(CardGameProject, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CardGameProject::OnClickedButtonSend)
	ON_WM_CREATE()
	ON_MESSAGE(WM_CLIENT_CARD_MSG_RECV, &CardGameProject::OnClientCardMsgRecv)
	ON_BN_CLICKED(IDC_START_BUTTON, &CardGameProject::OnClickedStartButton)
	ON_MESSAGE(WM_CLIENT_CARD_START, &CardGameProject::OnClientCardStart)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CARD_EXIT_BUTTON, &CardGameProject::OnClickedCardExitButton)
	ON_MESSAGE(WM_CLIENT_RECV_ROOM_ID_TO_CARD, &CardGameProject::OnClientRecvRoomIDToCard)
END_MESSAGE_MAP()


// CardGameProject 메시지 처리기입니다.

int CardGameProject::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CCreateRoomDlg *p_dlg = (CCreateRoomDlg*)GetParent();

	//m_clientSocket = new CClientSocket;
	m_clientSocket = p_dlg->m_clientSocket;
	p_hWnd = m_clientSocket->m_hWnd;
	m_clientSocket->SetWnd(this->GetSafeHwnd());
	
	// 어떤방인지 설정
	roomKind = m_clientSocket->info.roomKind;

	//CString str2;
	//str2.Format(_T("%d"), roomKind);
	//AfxMessageBox(str2);

	// 방제목 표시
	SetWindowText(m_clientSocket->info.roomName);
	
	CString str = _T("");
	str.Format(_T("[%s]님이 입장하셨습니다."), p_dlg->nickName);

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

	return 0;
}

afx_msg LRESULT CardGameProject::OnClientCardMsgRecv(WPARAM wParam, LPARAM lParam)
{
	cardMsgStruct* msg = (cardMsgStruct*)lParam;

	listMsg.InsertString(-1, msg->msg);
	listMsg.SetCurSel(listMsg.GetCount() - 1);

	return 0;
}

// 메세지보내기
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

// 준비버튼 눌렀을 때
void CardGameProject::OnClickedStartButton()
{
	if (isReady == FALSE) {
		startButton.SetWindowTextW(_T("시작"));

		cardReady* cr = new cardReady;
		cr->id = 5400;
		cr->size = sizeof(cardReadyStruct);
		cr->data.roomID = m_clientSocket->info.roomNum;
		cr->data.isReady = TRUE;
		m_clientSocket->Send((char*)cr, sizeof(cardReady));
		delete cr;

		isReady = TRUE;
	}
	else {
		AfxMessageBox(_T("이미 준비되었습니다"));
	}
}

// 게임시작
afx_msg LRESULT CardGameProject::OnClientCardStart(WPARAM wParam, LPARAM lParam) {
	cardStartStruct* css = (cardStartStruct*)lParam;

	if (css->start == TRUE) {
		//AfxMessageBox(_T("가위바위보 등장!!!"));
		Rock* dlg = new Rock;
		dlg->DoModal();
	}

	return 0;
}

afx_msg LRESULT CardGameProject::OnClientRecvRoomIDToCard(WPARAM wParam, LPARAM lParam) {
	//AfxMessageBox(_T("들어옴"));
	int deletedRoomID = (int)lParam;

	if (m_clientSocket->info.roomNum > deletedRoomID) {
		m_clientSocket->info.roomNum--;
	}

	return 0;
}

void CardGameProject::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	createRoom* msg = new createRoom;
	msg->id = 5005;
	msg->size = sizeof(createRoomStruct);
	msg->data.roomID = m_clientSocket->info.roomNum;
	msg->data.roomKind = roomKind;
	m_clientSocket->SetWnd(p_hWnd);
	m_clientSocket->Send((char*)msg, sizeof(createRoom));	
	delete msg;
}


void CardGameProject::OnClickedCardExitButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CardGameProject* dlg = new CardGameProject;
	//dlg->DestroyWindow();
	//DestroyWindow();
}
