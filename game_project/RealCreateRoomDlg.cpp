// RealCreateRoomDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "game_project.h"
#include "RealCreateRoomDlg.h"
#include "afxdialogex.h"

#include "game_projectDlg.h"
#include "CreateRoomDlg.h"
// RealCreateRoomDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(RealCreateRoomDlg, CDialog)

RealCreateRoomDlg::RealCreateRoomDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG_REAL_CREATE_ROOM, pParent)
	, m_room_name(_T(""))
{

}

RealCreateRoomDlg::~RealCreateRoomDlg()
{
}

void RealCreateRoomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ROOM_NAME, m_room_name);
}


BEGIN_MESSAGE_MAP(RealCreateRoomDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_ROOM, &RealCreateRoomDlg::OnClickedBtnRoom)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// RealCreateRoomDlg 메시지 처리기입니다.


void RealCreateRoomDlg::OnClickedBtnRoom()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);
	int nSelect = GetCheckedRadioButton(IDC_RADIO1, IDC_RADIO3);
	if (nSelect == 0) {
		AfxMessageBox(_T("게임 종류를 선택해주세요."));
		return;
	}
	if (m_room_name == "") {
		AfxMessageBox(_T("방이름을 설정해주세요."));
		return;
	}
	
	roomInfoMessage *msg = new roomInfoMessage;
	msg->id = 3000;
	msg->size = sizeof(roomInfoRecvMessage);
	msg->data.kind = nSelect;
	_tcscpy_s(msg->data.name, m_room_name);
	m_clientSocket->info.roomName = m_room_name;
	m_clientSocket->Send((char *)msg, sizeof(roomInfoMessage));
	delete msg;

	ShowWindow(SW_HIDE);
}


int RealCreateRoomDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CCreateRoomDlg* c_dlg = (CCreateRoomDlg*)GetParent();

	m_clientSocket = c_dlg->m_clientSocket;
	
	return 0;
}

