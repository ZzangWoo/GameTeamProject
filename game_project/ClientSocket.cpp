// ClientSocket.cpp : implementation file
//

#include "stdafx.h"
#include "game_project.h"
#include "ClientSocket.h"


// CClientSocket

CClientSocket::CClientSocket()
{
}

CClientSocket::~CClientSocket()
{
}


// CClientSocket member functions
void CClientSocket::SetWnd(HWND hWnd)
{
	m_hWnd = hWnd;
}

void CClientSocket::OnReceive(int nErrorCode) {
	int header[2];

	Receive((char*)header, sizeof(int) * 2);

	/************** 방만들기 창 채팅 ****************/
	if (header[0] == 2) {
		msgRecvMessage* msg = new msgRecvMessage;
		ZeroMemory(msg, sizeof(msgRecvMessage));
		Receive((char*)msg, header[1]);
		SendMessage(m_hWnd, WM_CLIENT_RECV, 0, (LPARAM)msg);
		delete msg;
	}
	// 오델로 방 메세지 받는 함수
	else if (header[0] == 51) {
		othelloMsgStruct * msg = new othelloMsgStruct;
		ZeroMemory(msg, sizeof(othelloMsgStruct));
		Receive((char*)msg, header[1]);
		SendMessage(m_hWnd, WM_CLIENT_OTHELLO_MSG_RECV, 0, (LPARAM)msg);
	}
	/************************************************/
	/**************** 방 리스트 받기 ****************/
	else if (header[0] == 3001) {
		sendRoomInfoStruct* sris = new sendRoomInfoStruct;
		Receive((char*)sris, header[1]);
		SendMessage(m_hWnd, WM_CLIENT_RECV_ROOM_LIST, 0, (LPARAM)sris);
		delete sris;
	}
	/************************************************/
	/*************** 방 전체 리스트 받기 *************/
	else if (header[0] == 3002) {
		sendAllRoomListStruct* sarls = new sendAllRoomListStruct;
		Receive((char*)sarls, header[1]);
		SendMessage(m_hWnd, WM_CLIENT_RECV_ALL_ROOM_LIST, 0, (LPARAM)sarls);
		delete sarls;
	}
	/*************************************************/
	/************* 어떤 방 만들면 될지 알려줌 *********/
	else if (header[0] == 5000) {
		createRoomStruct* crs = new createRoomStruct;
		Receive((char*)crs, header[1]);
		SendMessage(m_hWnd, WM_CLIENT_CREATE_ROOM, 0, (LPARAM)crs);
		delete crs;
	}
	/**************************************************/
	/************** 카드게임 방 메세지 받는 함수 *************/
	else if (header[0] == 5001) {
		cardMsgStruct *msg = new cardMsgStruct;
		ZeroMemory(msg, sizeof(cardMsgStruct));
		Receive((char*)msg, header[1]);
		SendMessage(m_hWnd, WM_CLIENT_CARD_MSG_RECV, 0, (LPARAM)msg);

	//방참가하는 함수
	else if (header[0] == 5004) {
		createRoomStruct* crs = new createRoomStruct;
		ZeroMemory(crs, sizeof(createRoomStruct));
		Receive((char*)crs, header[1]);
		SendMessage(m_hWnd, WM_CLIENT_ATTEND_ROOM, 0, (LPARAM)crs);
		delete crs;
	}
	/*********************************************************/

	CSocket::OnReceive(nErrorCode);
}

void CClientSocket::OnClose(int nErrorCode) {
	ShutDown();
	Close();

	CSocket::OnClose(nErrorCode);

	AfxMessageBox(_T("ERROR: Disconnected from server"));
	PostQuitMessage(0);
}