// CardGameProject.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "game_project.h"
#include "CardGameProject.h"
#include "afxdialogex.h"


// CardGameProject ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CardGameProject, CDialog)

CardGameProject::CardGameProject(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_CARDGAME, pParent)
{

}

CardGameProject::~CardGameProject()
{
}

void CardGameProject::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CardGameProject, CDialog)
END_MESSAGE_MAP()


// CardGameProject �޽��� ó�����Դϴ�.
