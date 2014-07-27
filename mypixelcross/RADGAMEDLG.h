#pragma once


// CRADGAMEDLG 对话框

class CRADGAMEDLG : public CDialogEx
{
	DECLARE_DYNAMIC(CRADGAMEDLG)

public:
	CRADGAMEDLG(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRADGAMEDLG();

// 对话框数据
	enum { IDD = IDD_RADGAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnKillfocusEditwidth();
	afx_msg void OnEnKillfocusEditheight();
	afx_msg void OnEnKillfocusEditcolor();

	//数据
	int	m_width;
	int m_height;
	int m_color;
	int m_blfrom;
	int m_blto;
	virtual BOOL OnInitDialog();
	afx_msg void OnEnKillfocusEditblfrom();
	afx_msg void OnEnKillfocusEditblto();
};
