// RADGAMEDLG.cpp : 实现文件
//

#include "stdafx.h"
#include "mypixelcross.h"
#include "RADGAMEDLG.h"
#include "afxdialogex.h"


// CRADGAMEDLG 对话框

IMPLEMENT_DYNAMIC(CRADGAMEDLG, CDialogEx)

CRADGAMEDLG::CRADGAMEDLG(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRADGAMEDLG::IDD, pParent)
{

}

CRADGAMEDLG::~CRADGAMEDLG()
{
}

void CRADGAMEDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRADGAMEDLG, CDialogEx)
	ON_EN_KILLFOCUS(IDC_EDITWIDTH, &CRADGAMEDLG::OnEnKillfocusEditwidth)
	ON_EN_KILLFOCUS(IDC_EDITHEIGHT, &CRADGAMEDLG::OnEnKillfocusEditheight)
	ON_EN_KILLFOCUS(IDC_EDITCOLOR, &CRADGAMEDLG::OnEnKillfocusEditcolor)
	ON_EN_KILLFOCUS(IDC_EDITBLFROM, &CRADGAMEDLG::OnEnKillfocusEditblfrom)
	ON_EN_KILLFOCUS(IDC_EDITBLTO, &CRADGAMEDLG::OnEnKillfocusEditblto)
END_MESSAGE_MAP()


// CRADGAMEDLG 消息处理程序


void CRADGAMEDLG::OnEnKillfocusEditwidth()
{
	CString str;
	GetDlgItemText(IDC_EDITWIDTH,str);
	m_width = _ttoi(str.GetBuffer());
	if(m_width < 3)
	{
		m_width = 3;
		SetDlgItemText(IDC_EDITWIDTH,_T("3"));
	}
	if(m_width > 30)
	{
		m_width = 30;
		SetDlgItemText(IDC_EDITWIDTH,_T("30"));
	}
}


void CRADGAMEDLG::OnEnKillfocusEditheight()
{
	CString str;
	GetDlgItemText(IDC_EDITHEIGHT,str);
	m_height = _ttoi(str.GetBuffer());
	if(m_height < 3)
	{
		m_height = 3;
		SetDlgItemText(IDC_EDITHEIGHT,_T("3"));
	}
	if(m_height > 30)
	{
		m_height = 30;
		SetDlgItemText(IDC_EDITHEIGHT,_T("30"));
	}
}


void CRADGAMEDLG::OnEnKillfocusEditcolor()
{
	CString str;
	GetDlgItemText(IDC_EDITCOLOR,str);
	m_color = _ttoi(str.GetBuffer());
	if(m_color < 1)
	{
		m_color = 1;
		SetDlgItemText(IDC_EDITCOLOR,_T("1"));
	}
	if(m_color > 9)
	{
		m_color = 9;
		SetDlgItemText(IDC_EDITCOLOR,_T("9"));
	}
}


BOOL CRADGAMEDLG::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_width = 5;
	m_height = 5;
	m_color = 1;
	m_blfrom = 10;
	m_blto   = 100;
	SetDlgItemText(IDC_EDITWIDTH,_T("5"));
	SetDlgItemText(IDC_EDITHEIGHT,_T("5"));
	SetDlgItemText(IDC_EDITCOLOR,_T("1"));
	SetDlgItemText(IDC_EDITBLFROM,_T("10"));
	SetDlgItemText(IDC_EDITBLTO,_T("70"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CRADGAMEDLG::OnEnKillfocusEditblfrom()
{
	CString str;
	GetDlgItemText(IDC_EDITBLFROM,str);
	m_blfrom = _ttoi(str.GetBuffer());
	if(m_blfrom < 10)
	{
		m_blfrom = 10;
		SetDlgItemText(IDC_EDITBLFROM,_T("10"));
	}

	CString str2;
	GetDlgItemText(IDC_EDITBLTO,str2);

	if(m_blfrom > m_blto)
	{
		m_blfrom = m_blto;
		SetDlgItemText(IDC_EDITBLFROM,str2);
	}
}


void CRADGAMEDLG::OnEnKillfocusEditblto()
{
	CString str;
	GetDlgItemText(IDC_EDITBLTO,str);
	m_blto = _ttoi(str.GetBuffer());

	if(m_blto > 70)
	{
		m_blto = 70;
		SetDlgItemText(IDC_EDITBLTO,_T("70"));
	}

	CString str2;
	GetDlgItemText(IDC_EDITBLFROM,str2);

	if(m_blto < m_blfrom)
	{
		m_blto = m_blfrom;
		SetDlgItemText(IDC_EDITBLTO,str2);
	}
}
