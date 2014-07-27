// NewMission.cpp : 实现文件
//

#include "stdafx.h"
#include "mypixelcross.h"
#include "NewMission.h"
#include "afxdialogex.h"


// CNewMission 对话框

IMPLEMENT_DYNAMIC(CNewMission, CDialogEx)

CNewMission::CNewMission(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNewMission::IDD, pParent)
{

}

CNewMission::~CNewMission()
{
}

void CNewMission::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNewMission, CDialogEx)
	ON_BN_CLICKED(IDC_CHECKRAD, &CNewMission::OnBnClickedCheckrad)
	ON_EN_KILLFOCUS(IDC_EDITWIDTH, &CNewMission::OnEnKillfocusEditwidth)
	ON_EN_KILLFOCUS(IDC_EDITHEIGHT, &CNewMission::OnEnKillfocusEditheight)
END_MESSAGE_MAP()


// CNewMission 消息处理程序



void CNewMission::OnBnClickedCheckrad()
{
	CButton* cchk;
	cchk=(CButton*)GetDlgItem(IDC_CHECKRAD);
	if(cchk->GetCheck()==1)
		m_israd = true;
	else
		m_israd = false;
}


BOOL CNewMission::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_width = 5;
	m_height = 5;
	m_israd = false;
	SetDlgItemText(IDC_EDITWIDTH,_T("5"));
	SetDlgItemText(IDC_EDITHEIGHT,_T("5"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CNewMission::OnEnKillfocusEditwidth()
{
	CString str;
	GetDlgItemText(IDC_EDITWIDTH,str);
	m_width = _ttoi(str.GetBuffer());
	if(m_width < 3)
	{
		m_width = 3;
		SetDlgItemText(IDC_EDITWIDTH,_T("3"));
	}
	if(m_width > MAXX)
	{
		m_width = MAXX;
		SetDlgItemText(IDC_EDITWIDTH,_T("30"));
	}
}


void CNewMission::OnEnKillfocusEditheight()
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
