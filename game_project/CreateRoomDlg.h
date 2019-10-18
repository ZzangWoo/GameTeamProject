#pragma once
#include "ClientSocket.h"
#include "RealCreateRoomDlg.h"
#include "afxwin.h"
#include "OthelloDlg.h"
#include "CardGameProject.h"
#include "Rock.h"

// CCreateRoomDlg ��ȭ �����Դϴ�.

class CCreateRoomDlg : public CDialog
{
	DECLARE_DYNAMIC(CCreateRoomDlg)

public:
	CCreateRoomDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CCreateRoomDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CREATEROOMDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()


public:
	CClientSocket *m_clientSocket;
	CListBox m_list_msg;
	CEdit m_edit_send;
	afx_msg void OnClickedBtnSend();
protected:
	afx_msg LRESULT OnClientRecv(WPARAM wParam, LPARAM lParam); // ���â������ ä�ø޼��� �޴� �Լ�
	afx_msg LRESULT OnClientRecvRoomList(WPARAM wParam, LPARAM lParam); // ���â���� �渮��Ʈ �޴� �Լ�
	afx_msg LRESULT OnClientRecvAllRoomList(WPARAM wParam, LPARAM lParam); // ��� �� ����Ʈ �޴� �Լ�
	afx_msg LRESULT OnClientCreateRoom(WPARAM wParam, LPARAM lParam); // �游���
	
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
//	afx_msg void OnInitMenu(CMenu* pMenu);

	CString nickName;
	afx_msg void OnClickedBtnCreateroom();
	CListBox m_list_room;
	afx_msg void OnClickedBtnOpenroom();
};
