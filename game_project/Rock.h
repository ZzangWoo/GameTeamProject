#pragma once

#include "ClientSocket.h"

// Rock 대화 상자입니다.
class COthelloDlg;
class CardGameProject;
class Rock : public CDialog
{
	DECLARE_DYNAMIC(Rock)

public:
	Rock(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Rock();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ROCK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void OnImagePrint(int choice, int x, int y);
	int m_choice;
	CClientSocket *m_clientSocket;
	afx_msg void OnClickedButtonPaper();
	afx_msg void OnClickedButtonRock();
	afx_msg void OnClickedButtonScissor();
};
