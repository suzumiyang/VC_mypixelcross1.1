#pragma once

#include "common.h"

// CNewMission �Ի���

class CNewMission : public CDialogEx
{
	DECLARE_DYNAMIC(CNewMission)

public:
	CNewMission(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNewMission();

	//����
	int	m_width;
	int m_height;
	bool m_israd;


// �Ի�������
	enum { IDD = IDD_RAD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheckrad();
	virtual BOOL OnInitDialog();
	afx_msg void OnEnKillfocusEditwidth();
	afx_msg void OnEnKillfocusEditheight();
};
