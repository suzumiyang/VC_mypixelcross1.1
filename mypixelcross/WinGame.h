#pragma once
#include "common.h"

// CWinGame �Ի���

class CWinGame : public CDialogEx
{
	DECLARE_DYNAMIC(CWinGame)

public:
	CWinGame(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWinGame();

// �Ի�������
	enum { IDD = IDD_WIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnreplay();
	afx_msg void OnBnClickedBtnopen();
	afx_msg void OnBnClickedBtnrad();

	int btnindex;
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
};
