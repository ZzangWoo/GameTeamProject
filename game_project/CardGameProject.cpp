// CardGameProject.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "game_project.h"
#include "CardGameProject.h"
#include "afxdialogex.h"

#include "game_projectDlg.h"


// CardGameProject 대화 상자입니다.

IMPLEMENT_DYNAMIC(CardGameProject, CDialog)

CardGameProject::CardGameProject(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_CARDGAME, pParent)
	, editPlayer1Point(_T(""))
	, editPlayer2Point(_T(""))
	, testEdit(_T(""))
	, remainTime(_T(""))
{

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
}


BEGIN_MESSAGE_MAP(CardGameProject, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CardGameProject::OnClickedButtonSend)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CardGameProject 메시지 처리기입니다.


void CardGameProject::OnClickedButtonSend()
{
	CString str;
	UpdateData(TRUE);
	cardGameMsg.GetWindowTextW(str);

	cardMsg* cm = new cardMsg;
	cm->id = 5000;
	
}


int CardGameProject::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CCreateRoomDlg *p_dlg = (CCreateRoomDlg*)GetParent();

	m_clientSocket = p_dlg->m_clientSocket;
	//player1Name.SetWindowTextW(m_clientSocket->nickname);
	CString str = m_clientSocket->nickname;
	AfxMessageBox(str);

	return 0;
}
