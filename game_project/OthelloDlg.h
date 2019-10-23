#pragma once

#include "ClientSocket.h"
#include "afxwin.h"
// COthelloDlg 대화 상자입니다.

class COthelloDlg : public CDialog
{
	DECLARE_DYNAMIC(COthelloDlg)

public:
	COthelloDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~COthelloDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OTHELLO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	CClientSocket *m_clientSocket;
	bool m_turn;
	UINT m_1_count;
	UINT m_2_count;
	CBitmap m_bitmap[2];
	int m_count;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClickedBtnPass();
	void DrawLine();
	int DrawStone(int x, int y);
	int** m_map;
	int* judgeStoneX(int x, int y);
	int* judgeStoneY(int x, int y);
	int** judgeStoneXY(int x, int y);
	void ChangeStoneX(int x1, int x2, int y);
	void ChangeStoneY(int x, int y1, int y2);
	void ChangeStoneXY(int x1, int x2, int y1, int y2);
	void SetCount();
	afx_msg void OnPaint();
	CString m_player1;
	CString m_player2;
	afx_msg void OnClickedBtnSend();
	CEdit m_edit_msg;
	CListBox m_llist_msg;
protected:
	afx_msg LRESULT OnClientOthelloMsgRecv(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnClientRecvRoomIDToCard(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnDestroy();
	HWND p_hWnd;
};
