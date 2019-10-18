#pragma once

struct msgRecvMessage {
	TCHAR name[50];
	TCHAR str[2000];
};

struct msgMessage {
	int id;
	int size;
	msgRecvMessage data;
};

struct readyRecvMessage {
	int ready;
};

struct readyMessage {
	int id;
	int size;
	readyRecvMessage data;
};

struct roomInfo {
	CString roomName;
	int roomNum;
};

struct roomInfoRecvMessage {
	TCHAR name[50];
	int kind;
	bool ok;
};

struct roomInfoMessage {
	int id;
	int size;
	roomInfoRecvMessage data;
};

/*********** Ŭ���̾�Ʈ�� �� ����Ʈ ���� ����ü **********/
struct sendRoomInfoStruct {
	TCHAR roomName[100];
};

struct sendRoomInfo {
	int id;
	int size;
	sendRoomInfoStruct data;
};
/********************************************************/

/********************** ó�� ���ӽ� �渮��Ʈ �ҷ����� **************************/
struct firstConnectStruct {
	bool isOnCreate;
};

struct firstConnect {
	int id;
	int size;
	firstConnectStruct data;
};
/*******************************************************************************/


/******************** ���â ���� Ŭ���̾�Ʈ���׸� �渮��Ʈ ������ *******************/
struct sendAllRoomListStruct {
	TCHAR roomNameList[100];
	int roomListSize;
};

struct sendAllRoomList {
	int id;
	int size;
	sendAllRoomListStruct data;
};
/***************************************************************************************/


/*********************** �� ��� Ŭ���ϰ� �����ϱ� ������ �� *************************/
struct attendRoomStruct {
	int roomPosition;
};

struct attendRoom {
	int id;
	int size;
	attendRoomStruct data;
};
/*************************************************************************************/

/********************** �� ���� �Ϸ��� Ŭ���̾�Ʈ�� �� ����� �ְ� ���� ******************/
struct createRoomStruct {
	int kind;
};

struct createRoom {
	int id;
	int size;
	createRoomStruct data;
};
/*****************************************************************************************/