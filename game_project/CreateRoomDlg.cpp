// CreateRoomDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "game_project.h"
#include "CreateRoomDlg.h"
#include "afxdialogex.h"
#include "game_projectDlg.h"

// CCreateRoomDlg 대화 상자입니다.
#define PORT 9999
IMPLEMENT_DYNAMIC(CCreateRoomDlg, CDialog)

CCreateRoomDlg::CCreateRoomDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_CREATEROOMDLG, pParent)
	, nickName(_T(""))
{

}

CCreateRoomDlg::~CCreateRoomDlg()
{
}

void CCreateRoomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MSG, m_list_msg);
	DDX_Control(pDX, IDC_EDIT_MSG, m_edit_send);
	DDX_Control(pDX, IDC_LIST_ROOM, m_list_room);
}


BEGIN_MESSAGE_MAP(CCreateRoomDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_SEND, &CCreateRoomDlg::OnClickedBtnSend)
	ON_MESSAGE(WM_CLIENT_RECV, &CCreateRoomDlg::OnClientRecv)
	ON_MESSAGE(WM_CLIENT_RECV_ROOM_LIST, &CCreateRoomDlg::OnClientRecvRoomList)
	ON_MESSAGE(WM_CLIENT_RECV_ALL_ROOM_LIST, &CCreateRoomDlg::OnClientRecvAllRoomList)
	ON_MESSAGE(WM_CLIENT_CREATE_ROOM, &CCreateRoomDlg::OnClientCreateRoom)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BTN_CREATEROOM, &CCreateRoomDlg::OnClickedBtnCreateroom)
	ON_BN_CLICKED(IDC_BTN_OPENROOM, &CCreateRoomDlg::OnClickedBtnOpenroom)
	ON_MESSAGE(WM_CLIENT_ATTEND_ROOM, &CCreateRoomDlg::OnClientAttendRoom)
END_MESSAGE_MAP()


// CCreateRoomDlg 메시지 처리기입니다.

void CCreateRoomDlg::OnClickedBtnSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	UpdateData(TRUE);

	m_edit_send.GetWindowTextW(str);

	msgMessage* msg = new msgMessage;
	msg->id = 2;
	msg->size = sizeof(msgRecvMessage);
	_tcscpy_s(msg->data.name, nickName);
	_tcscpy_s(msg->data.str, str);

	m_clientSocket->Send((char *)msg, sizeof(msgMessage));
	m_edit_send.SetWindowTextW(_T(""));
	delete msg;

	UpdateData(FALSE);
}

int CCreateRoomDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	Cgame_projectDlg *p_dlg = (Cgame_projectDlg*)GetParent();

	m_clientSocket = new CClientSocket;
	m_clientSocket->SetWnd(m_hWnd);
	m_clientSocket->Create();
	if (m_clientSocket->Connect(p_dlg->m_serverIP, PORT) == FALSE) {
		AfxMessageBox(_T("ERROR: Failed connected server!!"));
		PostQuitMessage(0);
	}
	nickName = p_dlg->m_edit_name;
	m_clientSocket->nickname = p_dlg->m_edit_name;
	//p_dlg->ShowWindow(SW_ERASE);

	/********************** 처음 접속시 방리스트 불러오기 **************************/
	firstConnect* fc = new firstConnect;
	fc->id = 3002;
	fc->size = sizeof(firstConnectStruct);
	fc->data.isOnCreate = true;

	m_clientSocket->Send((char*)fc, sizeof(firstConnect));
	/*******************************************************************************/

	return 0;
}

afx_msg LRESULT CCreateRoomDlg::OnClientRecv(WPARAM wParam, LPARAM lParam)
{
	msgRecvMessage* msg = (msgRecvMessage*)lParam;
	CString strTmp = _T("");
	strTmp.Format(_T("[%s]:%s"), msg->name, msg->str);

	m_list_msg.InsertString(-1, strTmp);
	m_list_msg.SetCurSel(m_list_msg.GetCount() - 1);

	return 0;
}


afx_msg LRESULT CCreateRoomDlg::OnClientRecvRoomList(WPARAM wParam, LPARAM lParam) {
	sendRoomInfoStruct* sris = (sendRoomInfoStruct*)lParam;

	m_clientSocket->info.roomName = sris->roomName;

	m_list_room.InsertString(-1, sris->roomName);
	m_list_room.SetCurSel(m_list_room.GetCount() - 1);

	return 0;
}

afx_msg LRESULT CCreateRoomDlg::OnClientRecvAllRoomList(WPARAM wParam, LPARAM lParam) {
	sendAllRoomListStruct* sarls = (sendAllRoomListStruct*)lParam;

	CString str;
	str.Format(_T("%s"), sarls->roomNameList);
	m_list_room.InsertString(-1, str);
	m_list_room.SetCurSel(m_list_room.GetCount() - 1);
	

	/*if (sarls->roomNameList != NULL) {
		m_list_room.InsertString(-1, sarls->roomNameList[0]);
	}*/
	 
	return 0;
}

afx_msg LRESULT CCreateRoomDlg::OnClientCreateRoom(WPARAM wParam, LPARAM lParam) {
	createRoomStruct* crs = (createRoomStruct*)lParam;
	m_clientSocket->info.roomNum = crs->roomID;
	m_clientSocket->info.roomName = crs->name;
	if (crs->kind == 1004) { // 오델로
		COthelloDlg* dlg = new COthelloDlg;
		dlg->DoModal();
		/*dlg->Create(IDD_OTHELLO, this);
		dlg->ShowWindow(SW_SHOW);*/
	}
	else if (crs->kind == 1005) { // 오목

	}
	else if (crs->kind == 1006) { // 짝맞추기
		CardGameProject* dlg = new CardGameProject;
		dlg->Create(IDD_CARDGAME, this);
		dlg->ShowWindow(SW_SHOW);
	}

	return 0;
}


void CCreateRoomDlg::OnClickedBtnCreateroom()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	RealCreateRoomDlg* dlg = new RealCreateRoomDlg;
	dlg->Create(IDD_DIALOG_REAL_CREATE_ROOM, this);
	dlg->ShowWindow(SW_SHOW);
}


void CCreateRoomDlg::OnClickedBtnOpenroom()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int currentRoomPosition = m_list_room.GetCurSel();

	attendRoom* ar = new attendRoom;
	ar->id = 4000;
	ar->size = sizeof(attendRoomStruct);
	ar->data.roomPosition = currentRoomPosition;

	m_clientSocket->Send((char*)ar, sizeof(attendRoom));

}


afx_msg LRESULT CCreateRoomDlg::OnClientAttendRoom(WPARAM wParam, LPARAM lParam)
{
	createRoomStruct* crs = (createRoomStruct*)lParam;
	m_clientSocket->info.roomNum = crs->roomID;
	m_clientSocket->info.roomName = crs->name;
	if (crs->kind == 1004) { // 오델로
		COthelloDlg* dlg = new COthelloDlg;
		dlg->DoModal();
		/*dlg->Create(IDD_OTHELLO, this);
		dlg->ShowWindow(SW_SHOW);*/
	}
	else if (crs->kind == 1005) { // 오목

	}
	else if (crs->kind == 1006) { // 짝맞추기
		CardGameProject* dlg = new CardGameProject;
		dlg->Create(IDD_CARDGAME, this);
		dlg->ShowWindow(SW_SHOW);
	}
	return 0;
}
