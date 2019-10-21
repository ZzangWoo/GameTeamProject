#pragma once
#include "structCollection.h"

// CClientSocket command target
#define WM_CLIENT_RECV WM_USER+1

#define WM_CLIENT_OTHELLO_MSG_RECV WM_USER+51

#define WM_CLIENT_RECV_ROOM_LIST WM_USER+3001
#define WM_CLIENT_RECV_ALL_ROOM_LIST WM_USER+3002
#define WM_CLIENT_CREATE_ROOM WM_USER+5000
#define WM_CLIENT_CARD_MSG_RECV WM_USER+5001

#define WM_CLIENT_ATTEND_ROOM WM_USER+5004

class CClientSocket : public CSocket
{
public:
	CClientSocket();
	virtual ~CClientSocket();
	void SetWnd(HWND hWnd);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	HWND m_hWnd;
	CString nickname;
	roomInfo info;
};


