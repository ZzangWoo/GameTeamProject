
// game_projectDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "game_project.h"
#include "game_projectDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define PORT 9999
// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.
#include "OthelloDlg.h"

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnBtnPass();
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
protected:
//	afx_msg LRESULT OnClientRemoveGameroom(WPARAM wParam, LPARAM lParam);
public:
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_COMMAND(IDC_BTN_PASS, &CAboutDlg::OnBtnPass)
//ON_WM_CREATE()
//ON_MESSAGE(WM_CLIENT_REMOVE_GAMEROOM, &CAboutDlg::OnClientRemoveGameroom)
//ON_WM_CREATE()
END_MESSAGE_MAP()


// Cgame_projectDlg 대화 상자



Cgame_projectDlg::Cgame_projectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CONNECT_DLG, pParent)
	, m_serverIP(_T(""))
	, m_edit_name(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_createRoomDlg = NULL;
}

void Cgame_projectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_IP, m_serverIP);
	DDX_Text(pDX, IDC_EDIT_NAME, m_edit_name);
}

BEGIN_MESSAGE_MAP(Cgame_projectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_CONNECT, &Cgame_projectDlg::OnClickedBtnConnect)
END_MESSAGE_MAP()


// Cgame_projectDlg 메시지 처리기

BOOL Cgame_projectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void Cgame_projectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void Cgame_projectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR Cgame_projectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Cgame_projectDlg::OnClickedBtnConnect()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_serverIP == "") {
		AfxMessageBox(_T("ip를 입력해주세요."));
		return;
	}
	if (m_edit_name == "")
		m_edit_name.Format(_T("%d"),m_hWnd);

	CCreateRoomDlg* dlg = new CCreateRoomDlg;
	dlg->Create(IDD_CREATEROOMDLG, this);
	dlg->ShowWindow(SW_SHOW);

	//IP번호 입력하면 버튼기능 막기 
	CButton* pBtn = (CButton*)GetDlgItem(IDC_BTN_CONNECT);
	pBtn->EnableWindow(FALSE);
	//this->OnClose(); // 왜 안닫히고 지랄이야 시벌롬이
}
