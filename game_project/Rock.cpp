// Rock.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "game_project.h"
#include "Rock.h"
#include "afxdialogex.h"
#include "OthelloDlg.h"
#include "CardGameProject.h"

// Rock ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(Rock, CDialog)

Rock::Rock(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_ROCK, pParent)
{

}

Rock::~Rock()
{
}

void Rock::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Rock, CDialog)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON_PAPER, &Rock::OnClickedButtonPaper)
	ON_BN_CLICKED(IDC_BUTTON_ROCK, &Rock::OnClickedButtonRock)
	ON_BN_CLICKED(IDC_BUTTON_SCISSOR, &Rock::OnClickedButtonScissor)
END_MESSAGE_MAP()


// Rock �޽��� ó�����Դϴ�.


int Rock::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	CWnd * pWnd = GetParent();
	//�θ� ���������� �˻�
	if (pWnd->IsKindOf(RUNTIME_CLASS(COthelloDlg))) {
		COthelloDlg *p_dlg = (COthelloDlg*)GetParent();
		m_clientSocket = p_dlg->m_clientSocket;
	}
	//�θ� ī��������� �˻�
	else if (pWnd->IsKindOf(RUNTIME_CLASS(CardGameProject))) {
		CardGameProject *p_dlg = (CardGameProject*)GetParent();
		m_clientSocket = p_dlg->m_clientSocket;
	}

	return 0;
}

void Rock::OnImagePrint(int choice, int x, int y) {
	//srand(time(NULL));
	CImage img;
	CClientDC dc(this);
	if (choice == 1) {
		img.Load(_T("r.jpg"));
		img.BitBlt(dc.m_hDC, x, y);
	}
	else if (choice == 2) {
		img.Load(_T("s.jpg"));
		img.BitBlt(dc.m_hDC, x, y);
	}
	else if (choice == 3) {
		img.Load(_T("p.jpg"));
		img.BitBlt(dc.m_hDC, x, y);
	}
	//�̹��� �ı��ϱ�
	//img.Destroy();
	//������ ���ΰ�ħ
}


void Rock::OnClickedButtonPaper()
{
	// TODO: Add your control notification handler code here
	m_choice = 3;
	UpdateData(FALSE);
	OnImagePrint(m_choice, 170, 70);


	choiceMessage* temp = new choiceMessage;
	temp->id = 401;
	temp->size = sizeof(choiceMessage);
	temp->data.choice = m_choice;
	temp->data.roomID = m_clientSocket->info.roomNum;

	/*��Ʈ��*/

	m_clientSocket->Send((char *)temp, sizeof(choiceMessage) * 2);

	delete temp;
}


void Rock::OnClickedButtonRock()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);


	m_choice = 1;
	UpdateData(FALSE);

	OnImagePrint(m_choice, 170, 70);

	choiceMessage* temp = new choiceMessage;
	temp->id = 401;
	temp->size = sizeof(choiceStruct);
	temp->data.choice = m_choice;
	temp->data.roomID = m_clientSocket->info.roomNum;
	/*��Ʈ��*/

	m_clientSocket->Send((char *)temp, sizeof(choiceMessage) * 2);
	delete temp;
}


void Rock::OnClickedButtonScissor()
{
	// TODO: Add your control notification handler code here
	m_choice = 2;
	UpdateData(FALSE);
	OnImagePrint(m_choice, 170, 70);

	choiceMessage* temp = new choiceMessage;
	temp->id = 401;
	temp->size = sizeof(choiceStruct);
	temp->data.choice = m_choice;
	temp->data.roomID = m_clientSocket->info.roomNum;
	/*��Ʈ��*/

	m_clientSocket->Send((char *)temp, sizeof(choiceMessage) * 2);
	delete temp;
}
