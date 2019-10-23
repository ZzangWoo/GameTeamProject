#pragma once

#include "ClientSocket.h"

// Rock ��ȭ �����Դϴ�.
class COthelloDlg;
class CardGameProject;
class Rock : public CDialog
{
	DECLARE_DYNAMIC(Rock)

public:
	Rock(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Rock();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ROCK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
