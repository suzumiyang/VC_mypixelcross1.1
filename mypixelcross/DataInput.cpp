// DataInput.cpp : 实现文件
//

#include "stdafx.h"
#include "mypixelcross.h"
#include "DataInput.h"
#include "afxdialogex.h"


// CDataInput 对话框

IMPLEMENT_DYNAMIC(CDataInput, CDialogEx)

CDataInput::CDataInput(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDataInput::IDD, pParent)
{

}

CDataInput::~CDataInput()
{
}

void CDataInput::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDataInput, CDialogEx)
	ON_EN_KILLFOCUS(IDC_INPUTWIDTH, &CDataInput::OnEnKillfocusInputwidth)
	ON_EN_KILLFOCUS(IDC_INPUTHEIGHT, &CDataInput::OnEnKillfocusInputheight)
	
	ON_BN_CLICKED(IDC_INPUTCHANGE, &CDataInput::OnBnClickedInputchange)
	ON_BN_CLICKED(IDOK, &CDataInput::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTNDEF, &CDataInput::OnBnClickedBtndef)
END_MESSAGE_MAP()


// CDataInput 消息处理程序


BOOL CDataInput::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_width = 5;
	m_height = 5;
	m_pausetime = 500;

	SetDlgItemText(IDC_INPUTWIDTH,_T("5"));
	SetDlgItemText(IDC_INPUTHEIGHT,_T("5"));
	


	SetFullText(m_width,m_height);
	SetDlgItemText(IDC_EDITDATA,m_fulltext);




	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDataInput::SetFullText(int width,int height)
{
	CString tmpstr = _T("上列项：");
	CString hh = _T("\r\n");
	CString tab = _T("\t");
	tmpstr = tmpstr + hh + tab;
	for(int i = 0;i < width;i++)
	{
		CString strnum;
		strnum.Format(_T("第 %d 列"),i+1);
		tmpstr = tmpstr + strnum + tab;
	}
	tmpstr = tmpstr + hh;
	for(int y = 0;y < height;y++)
	{
		CString strnum;
		strnum.Format(_T("第 %d 行"),y+1);
		tmpstr = tmpstr + strnum;
		for(int x = 0;x < width;x++)
		{
			tmpstr = tmpstr + tab;
			tmpstr = tmpstr + _T("0");
		}
		tmpstr = tmpstr + tab + hh;
	}
	tmpstr = tmpstr + hh + _T("左列项：") + hh + tab;

	for(int i = 0;i < width;i++)
	{
		CString strnum;
		strnum.Format(_T("第 %d 列"),i+1);
		tmpstr = tmpstr + strnum + tab;
	}
	tmpstr = tmpstr + hh;
	for(int y = 0;y < height;y++)
	{
		CString strnum;
		strnum.Format(_T("第 %d 行"),y+1);
		tmpstr = tmpstr + strnum;
		for(int x = 0;x < width;x++)
		{
			tmpstr = tmpstr + tab;
			tmpstr = tmpstr + _T("0");
		}
		tmpstr = tmpstr + tab + hh;
	}

	m_fulltext = tmpstr;


}

void CDataInput::OnEnKillfocusInputwidth()
{
	CString str;
	GetDlgItemText(IDC_INPUTWIDTH,str);
	m_width = _ttoi(str.GetBuffer());
	if(m_width < 3)
	{
		m_width = 3;
		SetDlgItemText(IDC_INPUTWIDTH,_T("3"));
	}
	if(m_width > 15)
	{
		m_width = 15;
		SetDlgItemText(IDC_INPUTWIDTH,_T("15"));
	}
}


void CDataInput::OnEnKillfocusInputheight()
{
	CString str;
	GetDlgItemText(IDC_INPUTHEIGHT,str);
	m_height = _ttoi(str.GetBuffer());
	if(m_height < 3)
	{
		m_height = 3;
		SetDlgItemText(IDC_INPUTHEIGHT,_T("3"));
	}
	if(m_height > 15)
	{
		m_height = 15;
		SetDlgItemText(IDC_INPUTHEIGHT,_T("15"));
	}
}




void CDataInput::OnBnClickedInputchange()
{
	SetFullText(m_width,m_height);
	SetDlgItemText(IDC_EDITDATA,m_fulltext);
}


void CDataInput::OnBnClickedOk()
{
	GetDlgItemText(IDC_EDITDATA,m_fulltext);
	CDialogEx::OnOK();
}



void CDataInput::OnBnClickedBtndef()
{
	SetDlgItemText(IDC_INPUTHEIGHT,_T("5"));
	SetDlgItemText(IDC_INPUTWIDTH,_T("5"));	
	CString tstr = _T("上列项：\r\n\t第 1 列	第 2 列	第 3 列	第 4 列	第 5 列	\r\n第 1 行	2	2	1	1	3	\r\n第 2 行	1	0	1	1	0	\r\n第 3 行	0	0	0	0	0	\r\n第 4 行	0	0	0	0	0	\r\n第 5 行	0	0	0	0	0	\r\n\r\n左列项：\r\n\t第 1 列	第 2 列	第 3 列	第 4 列	第 5 列	\r\n第 1 行	1	1	0	0	0	\r\n第 2 行	3	1	0	0	0	\r\n第 3 行	1	2	0	0	0	\r\n第 4 行	1	0	0	0	0	\r\n第 5 行	1	1	0	0	0	\r\n");
	SetDlgItemText(IDC_EDITDATA,tstr);	
}
