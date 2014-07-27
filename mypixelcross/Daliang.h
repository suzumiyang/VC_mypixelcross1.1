#pragma once
#include "afxwin.h"
#include "common.h"


// CDaliang �Ի���

class CDaliang : public CDialogEx
{
	DECLARE_DYNAMIC(CDaliang)

public:
	CDaliang(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDaliang();

// �Ի�������
	enum { IDD = IDD_DALIANG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_width;
	CEdit m_height;
	CEdit m_color;
	CEdit m_blfrom;
	CEdit m_blto;

	int i_width;
	int i_height;
	int i_colornum;
	bool israd;
	int i_buildnum;
	int i_blfrom;
	int i_blto;
	bool isbl;
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnKillfocusEditwidth();
	afx_msg void OnEnKillfocusEditheight();
	afx_msg void OnEnKillfocusEditcolor();
	afx_msg void OnEnKillfocusEditnum();
	CEdit m_buildnum;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadiblrad();
	afx_msg void OnBnClickedRadibl();
	afx_msg void OnEnKillfocusEditblfrom();
	afx_msg void OnEnKillfocusEditblto();

};
