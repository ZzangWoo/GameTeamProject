#pragma once
#include "afxwin.h"


// CardGameProject 대화 상자입니다.

class CardGameProject : public CDialog
{
	DECLARE_DYNAMIC(CardGameProject)

public:
	CardGameProject(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CardGameProject();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CARDGAME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString editPlayer1Point;
	CString editPlayer2Point;
	CEdit cardGameMsg;
	CString testEdit;
	CString remainTime;
	CListBox listMsg;
};
