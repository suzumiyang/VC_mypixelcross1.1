#pragma once


// CRADGAMEDLG �Ի���

class CRADGAMEDLG : public CDialogEx
{
	DECLARE_DYNAMIC(CRADGAMEDLG)

public:
	CRADGAMEDLG(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRADGAMEDLG();

// �Ի�������
	enum { IDD = IDD_RADGAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnKillfocusEditwidth();
	afx_msg void OnEnKillfocusEditheight();
	afx_msg void OnEnKillfocusEditcolor();

	//����
	int	m_width;
	int m_height;
	int m_color;
	int m_blfrom;
	int m_blto;
	virtual BOOL OnInitDialog();
	afx_msg void OnEnKillfocusEditblfrom();
	afx_msg void OnEnKillfocusEditblto();
};
