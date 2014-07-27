#pragma once


// CDataInput 对话框

class CDataInput : public CDialogEx
{
	DECLARE_DYNAMIC(CDataInput)

public:
	CDataInput(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDataInput();

// 对话框数据
	enum { IDD = IDD_INPUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	int m_width;
	int m_height;
	int m_pausetime;

	CString m_fulltext;
	void SetFullText(int width,int height);
	afx_msg void OnEnKillfocusInputwidth();
	afx_msg void OnEnKillfocusInputheight();
	afx_msg void OnEnKillfocusInputpausetime();
	afx_msg void OnBnClickedInputchange();
	afx_msg void OnBnClickedOk();

	afx_msg void OnBnClickedBtndef();
};
