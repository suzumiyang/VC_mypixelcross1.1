#pragma once
#include "common.h"

// CWinGame 对话框

class CWinGame : public CDialogEx
{
	DECLARE_DYNAMIC(CWinGame)

public:
	CWinGame(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWinGame();

// 对话框数据
	enum { IDD = IDD_WIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnreplay();
	afx_msg void OnBnClickedBtnopen();
	afx_msg void OnBnClickedBtnrad();

	int btnindex;
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
};
