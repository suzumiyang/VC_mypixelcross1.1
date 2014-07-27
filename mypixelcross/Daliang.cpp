// Daliang.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mypixelcross.h"
#include "Daliang.h"
#include "afxdialogex.h"


// CDaliang �Ի���

IMPLEMENT_DYNAMIC(CDaliang, CDialogEx)

CDaliang::CDaliang(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDaliang::IDD, pParent)
{

}

CDaliang::~CDaliang()
{
}

void CDaliang::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDITWIDTH, m_width);
	DDX_Control(pDX, IDC_EDITHEIGHT, m_height);
	DDX_Control(pDX, IDC_EDITCOLOR, m_color);
	DDX_Control(pDX, IDC_EDITNUM, m_buildnum);
	DDX_Control(pDX, IDC_EDITBLFROM, m_blfrom);
	DDX_Control(pDX, IDC_EDITBLTO, m_blto);
}


BEGIN_MESSAGE_MAP(CDaliang, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDaliang::OnBnClickedOk)
	ON_EN_KILLFOCUS(IDC_EDITWIDTH, &CDaliang::OnEnKillfocusEditwidth)
	ON_EN_KILLFOCUS(IDC_EDITHEIGHT, &CDaliang::OnEnKillfocusEditheight)
	ON_EN_KILLFOCUS(IDC_EDITCOLOR, &CDaliang::OnEnKillfocusEditcolor)
	ON_EN_KILLFOCUS(IDC_EDITNUM, &CDaliang::OnEnKillfocusEditnum)
	ON_BN_CLICKED(IDC_RADIBLRAD, &CDaliang::OnBnClickedRadiblrad)
	ON_BN_CLICKED(IDC_RADIBL, &CDaliang::OnBnClickedRadibl)
	ON_EN_KILLFOCUS(IDC_EDITBLFROM, &CDaliang::OnEnKillfocusEditblfrom)
	ON_EN_KILLFOCUS(IDC_EDITBLTO, &CDaliang::OnEnKillfocusEditblto)
END_MESSAGE_MAP()


// CDaliang ��Ϣ�������


void CDaliang::OnBnClickedOk()
{
	
	CDialogEx::OnOK();
}


void CDaliang::OnEnKillfocusEditwidth()
{
	CString str;
	m_width.GetWindowTextW(str);
	i_width = _ttoi(str.GetBuffer());
	if(i_width < 3)
	{
		i_width = 3;
		m_width.SetWindowTextW(_T("3"));
	}
	if(i_width > MAXX)
	{
		i_width = MAXX;
		m_width.SetWindowTextW(_T("30"));
	}
}


void CDaliang::OnEnKillfocusEditheight()
{
	CString str;
	m_height.GetWindowTextW(str);
	i_height = _ttoi(str.GetBuffer());
	if(i_height < 3)
	{
		i_height = 3;
		m_height.SetWindowTextW(_T("3"));
	}
	if(i_height > 30)
	{
		i_height = 30;
		m_height.SetWindowTextW(_T("30"));
	}
}

void CDaliang::OnEnKillfocusEditcolor()
{
	CString str;
	m_color.GetWindowTextW(str);
	i_colornum = _ttoi(str.GetBuffer());
	if(i_colornum < 1)
	{
		i_colornum = 1;
		m_color.SetWindowTextW(_T("1"));
	}
	if(i_colornum > 9)
	{
		i_colornum = 9;
		m_color.SetWindowTextW(_T("9"));
	}
}


void CDaliang::OnEnKillfocusEditnum()
{
	CString str;
	m_buildnum.GetWindowTextW(str);
	i_buildnum = _ttoi(str.GetBuffer());
	if(i_buildnum < 1)
	{
		i_buildnum = 1;
		m_buildnum.SetWindowTextW(_T("1"));
	}
}


BOOL CDaliang::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CButton* cchk;
	cchk=(CButton*)GetDlgItem(IDC_RADIBLRAD);
	cchk->SetCheck(1);
	israd = true;
	isbl = false;
	i_blfrom = 10;
	i_blto   = 100;


	i_width = 3;
	i_height = 3;
	i_colornum = 1;
	i_buildnum = 1;

	m_width.SetWindowTextW(_T("3"));
	m_height.SetWindowTextW(_T("3"));
	m_color.SetWindowTextW(_T("1"));
	m_buildnum.SetWindowTextW(_T("1"));

	m_blfrom.SetWindowTextW(_T("10"));
	m_blto.SetWindowTextW(_T("100"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDaliang::OnBnClickedRadiblrad()
{
	isbl = false;//���ñ���

	CButton* cchk;//������һ����ť
	cchk=(CButton*)GetDlgItem(IDC_RADIBL);
	cchk->SetCheck(0);
	
	//�������������
	m_blfrom.SetReadOnly(true);
	m_blto.SetReadOnly(true);
	
}


void CDaliang::OnBnClickedRadibl()
{
	isbl = true;//���ñ���

	CButton* cchk;//������һ����ť
	cchk=(CButton*)GetDlgItem(IDC_RADIBLRAD);
	cchk->SetCheck(0);
	
	//�������������
	m_blfrom.SetReadOnly(false);
	m_blto.SetReadOnly(false);
	
}


void CDaliang::OnEnKillfocusEditblfrom()
{
	CString str;
	m_blfrom.GetWindowTextW(str);
	i_blfrom = _ttoi(str.GetBuffer());
	if(i_blfrom < 10)	//���С��1��Ϊ1
	{
		i_blfrom = 10;
		m_blfrom.SetWindowTextW(_T("10"));
	}
		
	CString str2;		//�������to��Ϊto
	m_blto.GetWindowTextW(str2);
	int tto = _ttoi(str2.GetBuffer());
	if(i_blfrom > tto)
	{
		i_blfrom = tto;
		m_blfrom.SetWindowTextW(str2);
	}
}


void CDaliang::OnEnKillfocusEditblto()
{
	CString str;
	m_blto.GetWindowTextW(str);
	i_blto = _ttoi(str.GetBuffer());
	if(i_blto > 100)	//�������100��Ϊ100
	{
		i_blto = 100;
		m_blto.SetWindowTextW(_T("100"));
	}
		
	CString str2;		//���С��to��Ϊto
	m_blfrom.GetWindowTextW(str2);
	int tto = _ttoi(str2.GetBuffer());
	if(i_blto < tto)
	{
		i_blto = tto;
		m_blto.SetWindowTextW(str2);
	}
}
