// WinGame.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mypixelcross.h"
#include "WinGame.h"
#include "afxdialogex.h"


// CWinGame �Ի���

IMPLEMENT_DYNAMIC(CWinGame, CDialogEx)

CWinGame::CWinGame(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWinGame::IDD, pParent)
{

}

CWinGame::~CWinGame()
{
}

void CWinGame::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWinGame, CDialogEx)
	ON_BN_CLICKED(IDC_BTNREPLAY, &CWinGame::OnBnClickedBtnreplay)
	ON_BN_CLICKED(IDC_BTNOPEN, &CWinGame::OnBnClickedBtnopen)
	ON_BN_CLICKED(IDC_BTNRAD, &CWinGame::OnBnClickedBtnrad)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CWinGame ��Ϣ�������


void CWinGame::OnBnClickedBtnreplay()
{
	btnindex = BTNREPLAY;
	CDialogEx::OnOK();
}


void CWinGame::OnBnClickedBtnopen()
{
	btnindex = BTNOPEN;
	CDialogEx::OnOK();
}


void CWinGame::OnBnClickedBtnrad()
{
	btnindex = BTNRAD;
	CDialogEx::OnOK();
}


BOOL CWinGame::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	btnindex = BTNNO;

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CWinGame::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnClose();
}
