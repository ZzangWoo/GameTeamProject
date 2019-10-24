#pragma once
#include "ClientSocket.h"
#include "afxwin.h"


// CardGameProject 대화 상자입니다.
class Rock;
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
	CClientSocket *m_clientSocket;
	CString editPlayer1Point;
	CString editPlayer2Point;
	CEdit cardGameMsg;
	CString testEdit;
	CString remainTime;
	CListBox listMsg;
	afx_msg void OnClickedButtonSend();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
//	CStatic player1Name;
//	CStatic player2Name;

protected:
	afx_msg LRESULT OnClientCardMsgRecv(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnClientCardStart(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnClientRecvRoomIDToCard(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnClientRspResult(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnClientPlayerName(WPARAM wParam, LPARAM lParam);
public:
	CString nickName;
	afx_msg void OnClickedStartButton();
	bool isReady;
	CButton startButton;
	afx_msg void OnDestroy();
	HWND p_hWnd;
	afx_msg void OnClickedCardExitButton();
	int roomKind;
//	CString m_player1;
//	CString m_player2;
	Rock* r_dlg;
	CString m_player1;
	CString m_player2;
};
