
// mypixelcross.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CmypixelcrossApp:
// �йش����ʵ�֣������ mypixelcross.cpp
//

class CmypixelcrossApp : public CWinApp
{
public:
	CmypixelcrossApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CmypixelcrossApp theApp;