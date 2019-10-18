#pragma once

#include "ClientSocket.h"
// RealCreateRoomDlg 대화 상자입니다.

class RealCreateRoomDlg : public CDialog
{
	DECLARE_DYNAMIC(RealCreateRoomDlg)

public:
	RealCreateRoomDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~RealCreateRoomDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_REAL_CREATE_ROOM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedBtnRoom();
	CString m_room_name;

	CClientSocket *m_clientSocket;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

protected:
};
