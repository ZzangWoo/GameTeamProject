#pragma once

#include "ClientSocket.h"
// COthelloDlg ��ȭ �����Դϴ�.

class COthelloDlg : public CDialog
{
	DECLARE_DYNAMIC(COthelloDlg)

public:
	COthelloDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~COthelloDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OTHELLODLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
};
