#pragma once

#include "common.h"

// CNewMission 对话框

class CNewMission : public CDialogEx
{
	DECLARE_DYNAMIC(CNewMission)

public:
	CNewMission(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CNewMission();

	//数据
	int	m_width;
	int m_height;
	bool m_israd;


// 对话框数据
	enum { IDD = IDD_RAD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheckrad();
	virtual BOOL OnInitDialog();
	afx_msg void OnEnKillfocusEditwidth();
	afx_msg void OnEnKillfocusEditheight();
};
