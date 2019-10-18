#pragma once


// Rock 대화 상자입니다.

class Rock : public CDialog
{
	DECLARE_DYNAMIC(Rock)

public:
	Rock(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Rock();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ROCK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
