// Rock.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "game_project.h"
#include "Rock.h"
#include "afxdialogex.h"


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
END_MESSAGE_MAP()


// Rock �޽��� ó�����Դϴ�.
