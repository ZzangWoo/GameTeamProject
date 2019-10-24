#pragma once

#define MAX_TOTAL_CARD_COUNT 19
#define MAX_PLAY_CARD_COUNT 18

#define START 1
#define CONTINUE 2
#define SHOW_SECOND_CARD 3

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
	int roomID;
};

struct readyMessage {
	int id;
	int size;
	readyRecvMessage data;
};

struct roomInfo {
	CString roomName;
	int roomNum;
	int roomKind;
};

struct roomInfoRecvMessage {
	TCHAR name[50];
	int kind;
	bool ok;
	TCHAR ClientName[50];

};

struct roomInfoMessage {
	int id;
	int size;
	roomInfoRecvMessage data;
};

/*********** 클라이언트로 방 리스트 보낼 구조체 **********/
struct sendRoomInfoStruct {
	TCHAR roomName[100];
};

struct sendRoomInfo {
	int id;
	int size;
	sendRoomInfoStruct data;
};
/********************************************************/

/********************** 처음 접속시 방리스트 불러오기 **************************/
struct firstConnectStruct {
	bool isOnCreate;
};

struct firstConnect {
	int id;
	int size;
	firstConnectStruct data;
};
/*******************************************************************************/


/******************** 대기창 들어온 클라이언트한테만 방리스트 보내기 *******************/
struct sendAllRoomListStruct {
	TCHAR roomNameList[100];
	int roomListSize;
	int count;
};

struct sendAllRoomList {
	int id;
	int size;
	sendAllRoomListStruct data;
};
/***************************************************************************************/


/*********************** 방 목록 클릭하고 참가하기 눌렀을 때 *************************/
struct attendRoomStruct {
	int roomPosition;
	TCHAR ClientName[50];

};

struct attendRoom {
	int id;
	int size;
	attendRoomStruct data;
};
/*************************************************************************************/

/********************** 방 생성 완료후 클라이언트가 방 만들수 있게 해줌 ******************/
struct createRoomStruct {
	int kind;
	int roomID;
	int roomKind;
	TCHAR name[50];
};

struct createRoom {
	int id;
	int size;
	createRoomStruct data;
};
/*****************************************************************************************/
// 방 리스트 삭제 후 게임방에 들어가있는 클라이언트한테	보내는 구조체
struct sendRoomIDStruct {
	int roomID;
	int roomKind;
};

struct sendRoomID {
	int id;
	int size;
	sendRoomIDStruct data;
};

// 오델로 채팅 메세지
struct othelloMsgStruct{
	TCHAR msg[2000];
	int roomID;
	TCHAR name[50];
};

struct othelloMsg {
	int id;
	int size;
	othelloMsgStruct data;
};


/************************** 짝맞추기에 필요한 struct ***********************/
// 카드게임 채팅 메세지
struct cardMsgStruct {
	TCHAR msg[2000];
	int roomID;
	TCHAR name[50];
};

struct cardMsg {
	int id;
	int size;
	cardMsgStruct data;
};

struct playerStruct {
	TCHAR name[50];
};

struct playerMessage {
	int id;
	int size;
	playerStruct data;
};


// 게임시작 버튼
struct cardReadyStruct {
	int roomID;
	bool isReady;
	int roomKind;
};

struct cardReady {
	int id;
	int size;
	cardReadyStruct data;
};

// 게임시작하라는 요청
struct cardStartStruct {
	bool start;
};

struct cardStart {
	int id;
	int size;
	cardStartStruct data;
};

// 카드 섞어달라고 요청
struct cardRequestShuffleStruct {
	bool go;
	int roomID;
};

struct cardRequestShuffle {
	int id;
	int size;
	cardRequestShuffleStruct data;
};

// 섞은 카드 저장
struct randomCardsStruct {
	char m_card_table[MAX_PLAY_CARD_COUNT * 2];
};

struct randomCards {
	int id;
	int size;
	randomCardsStruct data;
};
/***************************************************************************/

//가위바위보 선택지
struct choiceStruct {
	int choice;
	int roomID;
	//int roomKind;
};
struct choiceMessage {
	int id;
	int size;
	choiceStruct data;
};

//오델로 맵보내기 
struct mapStruct {
	int roomID;
	int map[8][8];
};

struct mapMessage {
	int id;
	int size;
	mapStruct data;
};