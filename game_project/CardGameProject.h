#pragma once
#include "afxwin.h"


// CardGameProject ��ȭ �����Դϴ�.

class CardGameProject : public CDialog
{
	DECLARE_DYNAMIC(CardGameProject)

public:
	CardGameProject(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CardGameProject();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CARDGAME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString editPlayer1Point;
	CString editPlayer2Point;
	CEdit cardGameMsg;
	CString testEdit;
	CString remainTime;
	CListBox listMsg;
};
