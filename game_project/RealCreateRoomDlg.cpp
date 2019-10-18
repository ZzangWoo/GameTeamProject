// RealCreateRoomDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "game_project.h"
#include "RealCreateRoomDlg.h"
#include "afxdialogex.h"

#include "game_projectDlg.h"
#include "CreateRoomDlg.h"
// RealCreateRoomDlg ��ȭ �����Դϴ�.

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


// RealCreateRoomDlg �޽��� ó�����Դϴ�.


void RealCreateRoomDlg::OnClickedBtnRoom()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(true);
	int nSelect = GetCheckedRadioButton(IDC_RADIO1, IDC_RADIO3);
	if (nSelect == 0) {
		AfxMessageBox(_T("���� ������ �������ּ���."));
		return;
	}
	if (m_room_name == "") {
		AfxMessageBox(_T("���̸��� �������ּ���."));
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

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	CCreateRoomDlg* c_dlg = (CCreateRoomDlg*)GetParent();

	m_clientSocket = c_dlg->m_clientSocket;
	
	return 0;
}

