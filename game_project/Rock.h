#pragma once


// Rock ��ȭ �����Դϴ�.

class Rock : public CDialog
{
	DECLARE_DYNAMIC(Rock)

public:
	Rock(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Rock();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ROCK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
