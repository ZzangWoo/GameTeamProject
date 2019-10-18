#pragma once
#include "ClientSocket.h"
#include "RealCreateRoomDlg.h"
#include "afxwin.h"
#include "OthelloDlg.h"
#include "CardGameProject.h"
#include "Rock.h"

// CCreateRoomDlg 대화 상자입니다.

class CCreateRoomDlg : public CDialog
{
	DECLARE_DYNAMIC(CCreateRoomDlg)

public:
	CCreateRoomDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCreateRoomDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CREATEROOMDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()


public:
	CClientSocket *m_clientSocket;
	CListBox m_list_msg;
	CEdit m_edit_send;
	afx_msg void OnClickedBtnSend();
protected:
	afx_msg LRESULT OnClientRecv(WPARAM wParam, LPARAM lParam); // 대기창에서의 채팅메세지 받는 함수
	afx_msg LRESULT OnClientRecvRoomList(WPARAM wParam, LPARAM lParam); // 대기창에서 방리스트 받는 함수
	afx_msg LRESULT OnClientRecvAllRoomList(WPARAM wParam, LPARAM lParam); // 모든 방 리스트 받는 함수
	afx_msg LRESULT OnClientCreateRoom(WPARAM wParam, LPARAM lParam); // 방만들기
	
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
//	afx_msg void OnInitMenu(CMenu* pMenu);

	CString nickName;
	afx_msg void OnClickedBtnCreateroom();
	CListBox m_list_room;
	afx_msg void OnClickedBtnOpenroom();
};
