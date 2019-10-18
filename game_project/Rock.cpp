// Rock.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "game_project.h"
#include "Rock.h"
#include "afxdialogex.h"


// Rock 대화 상자입니다.

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


// Rock 메시지 처리기입니다.
