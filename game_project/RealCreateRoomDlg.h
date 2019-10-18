#pragma once

#include "ClientSocket.h"
// RealCreateRoomDlg ��ȭ �����Դϴ�.

class RealCreateRoomDlg : public CDialog
{
	DECLARE_DYNAMIC(RealCreateRoomDlg)

public:
	RealCreateRoomDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~RealCreateRoomDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_REAL_CREATE_ROOM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedBtnRoom();
	CString m_room_name;

	CClientSocket *m_clientSocket;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

protected:
};
