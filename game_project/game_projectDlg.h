
// game_projectDlg.h : 헤더 파일
//

#pragma once
#include "ClientSocket.h"
#include "afxwin.h"
#include "CreateRoomDlg.h"

// Cgame_projectDlg 대화 상자
class Cgame_projectDlg : public CDialogEx
{
// 생성입니다.
public:
	Cgame_projectDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONNECT_DLG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	
public:
	//CListBox m_list_msg;
	//CEdit m_edit_send;
	//afx_msg void OnClickedBtnSend();
	//afx_msg LRESULT OnClientRecv(WPARAM wParam, LPARAM lParam);
	CString m_serverIP;
protected:
//	afx_msg LRESULT OnClientRecv(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnClickedBtnConnect();
	CCreateRoomDlg *m_createRoomDlg;
	CString m_edit_name;
};
