
// mypixelcrossDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mypixelcross.h"
#include "mypixelcrossDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	
END_MESSAGE_MAP()


// CmypixelcrossDlg 对话框




CmypixelcrossDlg::CmypixelcrossDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CmypixelcrossDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmypixelcrossDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CmypixelcrossDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_UPDATE_COMMAND_UI(ID_MENU_GAME, &CmypixelcrossDlg::OnUpdateMenuGame)
	ON_UPDATE_COMMAND_UI(ID_MENU_DESIGN, &CmypixelcrossDlg::OnUpdateMenuDesign)
	ON_UPDATE_COMMAND_UI(ID_MENU_NEWGAME, &CmypixelcrossDlg::OnUpdateMenuNewgame)
	ON_UPDATE_COMMAND_UI(ID_MENU_SOMEGAME, &CmypixelcrossDlg::OnUpdateMenuSomegame)
	ON_UPDATE_COMMAND_UI(ID_MENU_OPENGAME, &CmypixelcrossDlg::OnUpdateMenuOpengame)
	ON_UPDATE_COMMAND_UI(ID_MENU_RESTART, &CmypixelcrossDlg::OnUpdateMenuRestart)
	ON_UPDATE_COMMAND_UI(ID_MENU_STATUS, &CmypixelcrossDlg::OnUpdateMenuStatus)
	ON_UPDATE_COMMAND_UI(ID_MENU_OPENMISSION, &CmypixelcrossDlg::OnUpdateMenuOpenmission)
	ON_UPDATE_COMMAND_UI(ID_MENU_SET, &CmypixelcrossDlg::OnUpdateMenuSet)
	ON_UPDATE_COMMAND_UI(ID_MENU_AUTO, &CmypixelcrossDlg::OnUpdateMenuAuto)
	ON_WM_SIZING()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOVE()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_MENU_SAVEMISSIONAS, &CmypixelcrossDlg::OnMenuSavemissionas)
	ON_COMMAND(ID_MENU_NEWMISSION, &CmypixelcrossDlg::OnMenuNewmission)
	ON_COMMAND(ID_MENU_RAD, &CmypixelcrossDlg::OnMenuRad)
	ON_COMMAND(ID_MENU_CHANGESIZE, &CmypixelcrossDlg::OnMenuChangesize)
	ON_COMMAND(ID_DALIANG, &CmypixelcrossDlg::OnDaliang)
	ON_COMMAND(ID_MENU_SOMEGAME, &CmypixelcrossDlg::OnMenuSomegame)
	ON_COMMAND(ID_MENU_SAVEMISSION, &CmypixelcrossDlg::OnMenuSavemission)
	ON_COMMAND(ID_MENU_RESTART, &CmypixelcrossDlg::OnMenuRestart)
	ON_COMMAND(ID_MENU_PIC, &CmypixelcrossDlg::OnMenuPic)
END_MESSAGE_MAP()


// CmypixelcrossDlg 消息处理程序

BOOL CmypixelcrossDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	m_Menu.LoadMenu(IDR_MAINMENU);
	this->SetMenu(&m_Menu);
	m_MenuDesign.LoadMenu(IDR_MAINMENUDESIGN);
	

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//初始化变量
	m_selcolor = 1;
	m_missionname.Format(_T(""));
	//绘图用变量初始化
	m_pDC = GetDC();
	GetClientRect(&m_rect);
    // 创建内存绘图设备，使内存位图的DC与控件的DC关联
    m_memDC.CreateCompatibleDC(m_pDC); 
    m_memBitmap.CreateCompatibleBitmap(m_pDC,m_rect.right,m_rect.bottom);
    m_pOldBmp = m_memDC.SelectObject(&m_memBitmap);

	isDCok = true;
	m_mode = MODEGAME;
	m_game.InitData();
	m_game.IsPuzzleCorrect();
	
	LoadMissionDef(5,5);//空关卡
	SetPos();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CmypixelcrossDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CmypixelcrossDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();

		ReDraw();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//更新画面////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CmypixelcrossDlg::ReDraw()
{
	if(isDCok == false)
		return;
	GetClientRect(&m_rect);
	int width = m_rect.Width();
	int height = m_rect.Height();

	m_memBitmap.DeleteObject();
	m_memBitmap.CreateCompatibleBitmap(m_pDC,width,height);
	m_memDC.SelectObject(&m_memBitmap);


	DrawDataTable();
	if(m_mode == MODEGAME ||m_mode == MODEAUTO)
		DrawChar();
 
	m_pDC->BitBlt(m_rect.left,m_rect.top,m_rect.right,m_rect.bottom,&m_memDC,0,0,SRCCOPY); 
}

void CmypixelcrossDlg::DrawDataTable()
{
	CPen pen,*oldpen;
	//格数
	int pwidth	= m_game.GetPuzzleWidth();
	int pheight = m_game.GetPuzzleHeight();
	//实际尺寸
 	int width	= m_rect.Width() - 5 ;
	int height	= m_rect.Height() - 5;
	CPoint startp;
	int size;

	startp.x = 0;
	startp.y = 0;
	size = height;

	//设置画笔,刷子
	pen.CreatePen(PS_SOLID,2, RGB(255,255,255));    
	oldpen = m_memDC.SelectObject(&pen);
	CBrush *oldbrush;

	//画背景	 白色
	m_memDC.Rectangle(m_tablerect[0][0].left - 2,m_tablerect[0][0].top - 2,m_tablerect[pheight - 1][pwidth - 1].right + 2,m_tablerect[pheight - 1][pwidth - 1].bottom + 2);

	//画每个格 黑色 
	for(int x = 0;x < pwidth;x++)//
	{
		for(int y = 0;y < pheight;y++)
		{
			COLORREF brushcolor;
			if(m_game.m_data.data[y][x].value ==DVYES)
			{
				int colorindex = m_game.m_data.data[y][x].colorindex;
				m_game.GetColor(&brushcolor,colorindex);
			}
			else 
				brushcolor = RGB(0,0,0);

			CBrush newbrush(brushcolor);
			oldbrush = m_memDC.SelectObject(&newbrush);
			m_memDC.Rectangle(&m_tablerect[y][x]);
			m_memDC.SelectObject(oldbrush);
			newbrush.DeleteObject();

			if(m_game.m_data.data[y][x].value == DVX)//画个X
			{
				m_memDC.MoveTo(m_tablerect[y][x].left,m_tablerect[y][x].top);
				m_memDC.LineTo(m_tablerect[y][x].right,m_tablerect[y][x].bottom);

				m_memDC.MoveTo(m_tablerect[y][x].left,m_tablerect[y][x].bottom);
				m_memDC.LineTo(m_tablerect[y][x].right,m_tablerect[y][x].top);
			}

		}
	}
	
	//画调色板（最大3×3）
	int colorpos = 1;
	for(int y = 0;y < 3;y++)
	{
		for(int x = 0;x < 3;x++)
		{
			COLORREF brushcolor;
			if (colorpos <= m_game.GetColorCnt())
			{
				m_game.GetColor(&brushcolor,colorpos);
				colorpos++;
			}
			else
			{
				brushcolor = RGB(0,0,0);
			}

			CBrush newbrush(brushcolor);
			oldbrush = m_memDC.SelectObject(&newbrush);
			m_memDC.Rectangle(&m_colortablerect[y][x]);
			m_memDC.SelectObject(oldbrush);
			newbrush.DeleteObject();
		}
	}

	//结束
	m_memDC.SelectObject(oldpen);//原画笔
	pen.DeleteObject();

	m_memDC.SelectObject(oldbrush);//原笔刷
}

void CmypixelcrossDlg::DrawChar()
{
	CFont *oldfont;
	CFont topfont;
	CFont leftfont;
	//格数
	int pwidth	= m_game.GetPuzzleWidth();
	int pheight = m_game.GetPuzzleHeight();
	//实际尺寸
 	int width	= m_rect.Width() - 5 ;
	int height	= m_rect.Height() - 5;

	//设置模式
	m_memDC.SetBkMode(TRANSPARENT); 

	//设置字体
	leftfont.CreateFont(
    //m_leftfont[0][0].Height(), // nHeight
    //m_leftfont[0][0].Width()/2,  // nWidth
	0,							// nHeight
	0,							// nWidth
    0,                         // nEscapement
    0,                         // nOrientation
    FW_BOLD,                   // nWeight
    FALSE,                     // bItalic
    FALSE,                     // bUnderline
    0,                         // cStrikeOut
    ANSI_CHARSET,              // nCharSet
    OUT_DEFAULT_PRECIS,        // nOutPrecision
    CLIP_DEFAULT_PRECIS,       // nClipPrecision
    DEFAULT_QUALITY,           // nQuality
    DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
    _T("Arial"));                 // lpszFacename
	

	topfont.CreateFont(
    //m_topfont[0][0].Height(),  // nHeight
    //m_topfont[0][0].Width()/2, // nWidth
	0,							// nHeight
	0,							// nWidth
    0,                         // nEscapement
    0,                         // nOrientation
    FW_BOLD,                   // nWeight
    FALSE,                     // bItalic
    FALSE,                     // bUnderline
    0,                         // cStrikeOut
    ANSI_CHARSET,              // nCharSet
    OUT_DEFAULT_PRECIS,        // nOutPrecision
    CLIP_DEFAULT_PRECIS,       // nClipPrecision
    DEFAULT_QUALITY,           // nQuality
    DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
    _T("Arial"));              // lpszFacename

	oldfont = m_memDC.SelectObject(&leftfont);


 

	//左边的表
	int leftx = pwidth - 1;
	for(int y = pheight - 1;y >= 0;y--)//
	{
		for(int x = pwidth - 1;x >=0 ;x--)
		{
			COLORREF fontcolor;
			CString str;
			int nvalue = m_game.m_data.yindex[y][x].value;
			if( nvalue > 0)	//有值
			{
				str.Format(_T("%d"),nvalue);       
				int colorindex = m_game.m_data.yindex[y][x].colorindex;
				m_game.GetColor(&fontcolor,colorindex);
			}
			else
				continue;
			m_memDC.SetTextColor(fontcolor);
			m_memDC.DrawText(str,&m_leftfont[y][leftx], DT_CENTER | DT_SINGLELINE|DT_VCENTER);
			leftx--;
		}
		if(leftx == pwidth - 1)
		{
			CString str;
			str.Format(_T("%d"),0); 
			COLORREF fontcolor=RGB(255,255,255);
			m_memDC.SetTextColor(fontcolor);
			m_memDC.DrawText(str,&m_leftfont[y][pwidth - 1], DT_CENTER | DT_SINGLELINE|DT_VCENTER);
		}
		leftx = pwidth - 1;
	}

	m_memDC.SelectObject(&topfont);
	//上边的表
	int topy = pheight - 1;
	for(int x = pwidth - 1;x >=0 ;x--)//
	{
		for(int y = pheight - 1;y >= 0;y--)
		{
			COLORREF fontcolor;
			CString str;
			int nvalue = m_game.m_data.xindex[y][x].value;
			if( nvalue > 0)	//有值
			{
				str.Format(_T("%d"),nvalue);       
				int colorindex = m_game.m_data.xindex[y][x].colorindex;
				m_game.GetColor(&fontcolor,colorindex);
			}
			else
				continue;
			m_memDC.SetTextColor(fontcolor);

			m_memDC.DrawText(str,&m_topfont[topy][x], DT_CENTER | DT_SINGLELINE|DT_VCENTER );
			topy--;
		}
		if(topy == pheight - 1)
		{
			CString str;
			str.Format(_T("%d"),0); 
			COLORREF fontcolor=RGB(255,255,255);
			m_memDC.SetTextColor(fontcolor);
			m_memDC.DrawText(str,&m_topfont[pheight - 1][x], DT_CENTER | DT_SINGLELINE|DT_VCENTER);
		}
		topy = pheight - 1;
	}

	m_memDC.SelectObject(oldfont);
	topfont.DeleteObject();
	leftfont.DeleteObject();
}

void CmypixelcrossDlg::SetPos()
{
	//main table
	//格数
	int pwidth	= m_game.GetPuzzleWidth();
	int pheight = m_game.GetPuzzleHeight();

	//实际尺寸
 	int width	= m_rect.Width() - 15 ;
	int height	= m_rect.Height() - 15;

	//每个格尺寸
	float nwidth  = float((width  * WINDOWBLR)/pwidth);
	float nheight = float((height * WINDOWBLR)/pheight);
	float startx  = float(width   * WINDOWBLL);
	float starty  = float(height  * WINDOWBLL);

	for(int x = 0;x < pwidth;x++)//每个格坐标
	{
		for(int y = 0;y < pheight;y++)
		{
			m_tablerect[y][x].left		= int(startx + x*nwidth + 1);
			m_tablerect[y][x].top		= int(starty + y*nheight + 1);
			m_tablerect[y][x].right		= int(m_tablerect[y][x].left + nwidth - 1);
			m_tablerect[y][x].bottom	= int(m_tablerect[y][x].top  + nheight - 1);
		}
	}

	//调色板
	nwidth  = float((width  * WINDOWBLL)/3);
	nheight = float((height * WINDOWBLL)/3);
	for(int x = 0;x < 3;x++)//每个格坐标
	{
		for(int y = 0;y < 3;y++)
		{
			m_colortablerect[y][x].left		= int(x*nwidth + 1);
			m_colortablerect[y][x].top		= int(y*nheight + 1);
			m_colortablerect[y][x].right	= int(m_colortablerect[y][x].left + nwidth - 1);
			m_colortablerect[y][x].bottom	= int(m_colortablerect[y][x].top  + nheight - 1);
		}
	}

	//左边的字
	
	//取得左边字的最大宽度
	int nleftwidth = 0;
	for(int y = 0;y < pheight;y++)//每个格坐标
	{
		int twidth = 0;
		for(int x = 0;x < pwidth;x++)
		{
			if(m_game.m_data.yindex[y][x].value > 0)
				twidth++;
		}
		if(nleftwidth < twidth)
			nleftwidth = twidth;
	}

	if(nleftwidth != 0)
	{
		nwidth  = float((width  * WINDOWBLL)/nleftwidth);
		nheight = float((height * WINDOWBLR)/pheight);
		startx  = 0;
		starty  = float(height  * WINDOWBLL);
		for(int x = 0;x < nleftwidth;x++)//每个格坐标
		{
			for(int y = 0;y < pheight;y++)
			{
				m_leftfont[y][pwidth - x - 1].left	= int(width * WINDOWBLL - (x+1)*nwidth + 1);

				m_leftfont[y][pwidth - x- 1].right	= int(m_leftfont[y][pwidth - x - 1].left + nwidth - 1);
				m_leftfont[y][pwidth - x- 1].top	= int(starty + y*nheight + 1);
				m_leftfont[y][pwidth - x- 1].bottom	= int(m_leftfont[y][pwidth - x- 1].top  + nheight - 1);
			}
		}
	}
	else
	{
		nwidth  = float((width  * WINDOWBLL)/pwidth);
		nheight = float((height * WINDOWBLR)/pheight);
		startx  = 0;
		starty  = float(height  * WINDOWBLL);
		for(int x = 0;x < pwidth;x++)//每个格坐标
		{
			for(int y = 0;y < pheight;y++)
			{
				m_leftfont[y][x].left	= int(startx + x*nwidth + 1);
				m_leftfont[y][x].top	= int(starty + y*nheight + 1);
				m_leftfont[y][x].right	= int(m_leftfont[y][x].left + nwidth - 1);
				m_leftfont[y][x].bottom	= int(m_leftfont[y][x].top  + nheight - 1);
			}
		}
	}

	//上边的字

	int ntopheight = 0;
	for(int x = 0;x < pwidth;x++)//每个格坐标
	{
		int theight = 0;
		for(int y = 0;y < pheight;y++)
		{
			if(m_game.m_data.xindex[y][x].value > 0)
				theight++;
		}
		if(ntopheight < theight)
			ntopheight = theight;
	}

	if(ntopheight!=0)
	{
		nwidth  = float((width  * WINDOWBLR)/pwidth);
		nheight = float((height * WINDOWBLL)/ntopheight);
		startx  = float(width   * WINDOWBLL);
		starty  = 0;
		for(int x = 0;x < pwidth;x++)//每个格坐标
		{
			for(int y = 0;y < ntopheight;y++)
			{
				m_topfont[pheight - y - 1][x].top		= int(height * WINDOWBLL - (y+1)*nheight + 1);

				m_topfont[pheight - y - 1][x].bottom	= int(m_topfont[pheight - y - 1][x].top  + nheight - 1);
				m_topfont[pheight - y - 1][x].left	= int(startx + x*nwidth + 1);
				m_topfont[pheight - y - 1][x].right	= int(m_topfont[pheight - y - 1][x].left + nwidth - 1);
			}
		}
	}
	else
	{
		nwidth  = float((width  * WINDOWBLR)/pwidth);
		nheight = float((height * WINDOWBLL)/pheight);
		startx  = float(width   * WINDOWBLL);
		starty  = 0;
		for(int x = 0;x < pwidth;x++)//每个格坐标
		{
			for(int y = 0;y < pheight;y++)
			{
				m_topfont[y][x].left	= int(startx + x*nwidth + 1);
				m_topfont[y][x].top		= int(starty + y*nheight + 1);
				m_topfont[y][x].right	= int(m_topfont[y][x].left + nwidth - 1);
				m_topfont[y][x].bottom	= int(m_topfont[y][x].top  + nheight - 1);
			}
		}
	}
}


//游戏相关
void CmypixelcrossDlg::LoadMission()//游戏模式
{
	CFile cfm;
	if(cfm.Open( m_missionname, CFile::modeRead | CFile::typeBinary ) == FALSE)
	{
		CString msg;
		msg.Format(_T("文件 %s 不存在"),m_missionname);
		MessageBox(msg);
		return;
	}
	else
		cfm.Close();
	OpenMission();
	//清空数据
	for(int y = 0;y < MAXY;y++)
	{
		for(int x = 0;x < MAXX;x++)
		{
			m_game.m_data.data[y][x].value = 0;
			m_game.m_data.data[y][x].colorindex = 0;
		}
	}

	SetPos();
	ReDraw();

	
}

void CmypixelcrossDlg::LoadMissionDef(int width,int height)
{
	m_game.m_data.width = width;
	m_game.m_data.height = height;

	//数据
	m_game.ClearData();

	//调色板 
	m_game.m_data.datacolorcnt = 0;

	m_game.m_data.datacolor.clindex[0] = RGB(0,0,0);
	//m_game.m_data.datacolor.clindex[1] = RGB(255,0,0);


	//数据 上
	for(int y = 0;y < height;y++)
	{
		for(int x = 0;x < width;x++)
		{
			m_game.m_data.xindex[y][x].colorindex = 1;
			m_game.m_data.xindex[y][x].value = 0;
		}
	}

	//数据 左
	for(int y = 0;y < height;y++)
	{
		for(int x = 0;x < width;x++)
		{
			m_game.m_data.yindex[y][x].colorindex = 1;
			m_game.m_data.yindex[y][x].value = 0;
		}
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CmypixelcrossDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//游戏，设计菜单开始/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CmypixelcrossDlg::OnUpdateMenuGame(CCmdUI *pCmdUI)
{
	m_Menu.GetSubMenu(0)->CheckMenuItem(ID_MENU_GAME	,MF_BYCOMMAND | MF_CHECKED);	//游戏模式
	m_Menu.GetSubMenu(0)->CheckMenuItem(ID_MENU_DESIGN	,MF_BYCOMMAND | MF_UNCHECKED);
	m_Menu.GetSubMenu(0)->CheckMenuItem(ID_MENU_AUTO	,MF_BYCOMMAND | MF_UNCHECKED);

	m_game.ClearData();
	m_missionname = _T("");//清空文件名，防止意外保存

	m_mode = MODEGAME;
	ReDraw();

	this->SetMenu(&m_Menu);

}


void CmypixelcrossDlg::OnUpdateMenuDesign(CCmdUI *pCmdUI)
{
	m_Menu.GetSubMenu(0)->CheckMenuItem(ID_MENU_GAME	,MF_BYCOMMAND | MF_UNCHECKED);	//设计模式
	m_Menu.GetSubMenu(0)->CheckMenuItem(ID_MENU_DESIGN	,MF_BYCOMMAND | MF_CHECKED);
	m_Menu.GetSubMenu(0)->CheckMenuItem(ID_MENU_AUTO	,MF_BYCOMMAND | MF_UNCHECKED);

	m_missionname = _T("");//清空文件名，防止意外保存
	m_game.ClearData();
	m_mode = MODEDESIGN;
	ReDraw();

	this->SetMenu(&m_MenuDesign);

}

void CmypixelcrossDlg::OnUpdateMenuAuto(CCmdUI *pCmdUI)
{
	m_Menu.GetSubMenu(0)->CheckMenuItem(ID_MENU_GAME	,MF_BYCOMMAND | MF_UNCHECKED);	
	m_Menu.GetSubMenu(0)->CheckMenuItem(ID_MENU_DESIGN	,MF_BYCOMMAND | MF_UNCHECKED);
	m_Menu.GetSubMenu(0)->CheckMenuItem(ID_MENU_AUTO	,MF_BYCOMMAND | MF_CHECKED);

	m_mode = MODEAUTO;
	ReDraw();

	this->SetMenu(&m_MenuDesign);


	CDataInput cdi;

	if(cdi.DoModal() == IDOK)
	{
		SetAnaData(cdi.m_width,cdi.m_height,cdi.m_pausetime,cdi.m_fulltext);
	}
	else
	{
		return;
	}
}


//游戏菜单开始/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CmypixelcrossDlg::OnUpdateMenuNewgame(CCmdUI *pCmdUI)
{
	
}


void CmypixelcrossDlg::OnUpdateMenuSomegame(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}


void CmypixelcrossDlg::OnUpdateMenuOpengame(CCmdUI *pCmdUI)
{
		CFileDialog dlg(TRUE,											//TRUE是创建打开文件对话框，FALSE则创建的是保存文件对话框 
                    _T(".zsd"),											//默认的打开文件的类型 
                    NULL,												//默认打开的文件名 
                    OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,				//打开只读文件 
                    _T("关卡文件(*.zsd)|*.zsd|所有文件 (*.*)|*.*||"),//所有可以打开的文件类型 
					this,NULL);	

 
    if(dlg.DoModal()==IDOK)   
    { 
        m_missionname = dlg.GetPathName();////////取出文件路径 
    } 
	else
		return;
	this->SetFocus();
	LoadMission();
	m_game.IsPuzzleCorrect();
	SetPos();
	ReDraw();
}


void CmypixelcrossDlg::OnUpdateMenuRestart(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}


void CmypixelcrossDlg::OnUpdateMenuStatus(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}

void CmypixelcrossDlg::OnUpdateMenuSet(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}



//设计菜单开始////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void CmypixelcrossDlg::OnUpdateMenuOpenmission(CCmdUI *pCmdUI)
{
		CFileDialog dlg(TRUE,											//TRUE是创建打开文件对话框，FALSE则创建的是保存文件对话框 
                    _T(".zsd"),											//默认的打开文件的类型 
                    NULL,												//默认打开的文件名 
                    OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,				//打开只读文件 
                    _T("关卡文件(*.zsd)|*.zsd|所有文件 (*.*)|*.*||"),//所有可以打开的文件类型 
					this,NULL);
 
    if(dlg.DoModal()==IDOK)   
    { 
        m_missionname = dlg.GetPathName();////////取出文件路径 
    } 
	else
		return;
	SetActiveWindow();

	OpenMission();
	ReDraw();
}
void CmypixelcrossDlg::OpenMission()				//从文件中载入关卡（设计）
{
	CFile readTxtFile;
	if(readTxtFile.Open( m_missionname, CFile::modeRead | CFile::typeBinary ) == FALSE)
	{
		CString msg;
		msg.Format(_T("文件 %s 不存在"),m_missionname);
		MessageBox(msg);
		return;
	}
	

	//矩阵上边的值
	for(int y = 0;y < MAXY;y++)
	{
		for(int x = 0;x < MAXX;x++)
		{
			readTxtFile.Read( &m_game.m_data.xindex[y][x].value, sizeof(int));	 
			readTxtFile.Read( &m_game.m_data.xindex[y][x].colorindex, sizeof(int));
		}
	}
	//矩阵左边的值
	for(int y = 0;y < MAXY;y++)
	{
		for(int x = 0;x < MAXX;x++)
		{
			readTxtFile.Read( &m_game.m_data.yindex[y][x].value, sizeof(int));	 
			readTxtFile.Read( &m_game.m_data.yindex[y][x].colorindex, sizeof(int));
		}
	}

	//矩阵中的值
	for(int y = 0;y < MAXY;y++)
	{
		for(int x = 0;x < MAXX;x++)
		{
			readTxtFile.Read( &m_game.m_data.data[y][x].value, sizeof(int));	 
			readTxtFile.Read( &m_game.m_data.data[y][x].colorindex, sizeof(int));
		}
	}

	readTxtFile.Read( &m_game.m_data.width, sizeof(int));	//当前关卡宽度
	readTxtFile.Read( &m_game.m_data.height, sizeof(int));	//当前关卡高度
	readTxtFile.Read( &m_game.m_data.datacolorcnt, sizeof(int));//当前索引中颜色个数(不包括索引0（无颜色）)


	for(int i = 0;i < MAXCOLOR;i++)
	{
		readTxtFile.Read( &m_game.m_data.datacolor.clindex[i], sizeof(COLORREF));
	}
	readTxtFile.Close();
}


void CmypixelcrossDlg::SaveMission()
{
	CFile writeTxtFile( m_missionname, CFile::modeWrite | CFile::typeBinary|CFile::modeCreate );

	m_game.ComputeLT();

	//矩阵上边的值
	for(int y = 0;y < MAXY;y++)
	{
		for(int x = 0;x < MAXX;x++)
		{
			int value		= m_game.m_data.xindex[y][x].value;	 
			int colorindex	= m_game.m_data.xindex[y][x].colorindex;
			writeTxtFile.Write( &value, sizeof(int));
			writeTxtFile.Write( &colorindex, sizeof(int));
		}
	}
	//矩阵左边的值
	for(int y = 0;y < MAXY;y++)
	{
		for(int x = 0;x < MAXX;x++)
		{
			int value		= m_game.m_data.yindex[y][x].value;	 
			int colorindex	= m_game.m_data.yindex[y][x].colorindex;
			writeTxtFile.Write( &value, sizeof(int));
			writeTxtFile.Write( &colorindex, sizeof(int));
		}
	}

	//矩阵中的值
	for(int y = 0;y < MAXY;y++)
	{
		for(int x = 0;x < MAXX;x++)
		{
			int value		= m_game.m_data.data[y][x].value;	 
			int colorindex	= m_game.m_data.data[y][x].colorindex;
			writeTxtFile.Write( &value, sizeof(int));
			writeTxtFile.Write( &colorindex, sizeof(int));
		}
	}

	int width = m_game.m_data.width;					//当前关卡宽度
	writeTxtFile.Write( &width, sizeof(int));
	int height= m_game.m_data.height;					//当前关卡高度
	writeTxtFile.Write( &height, sizeof(int));
	int datacolorcnt = m_game.m_data.datacolorcnt;		//当前索引中颜色个数(不包括索引0（无颜色）)
	writeTxtFile.Write( &datacolorcnt, sizeof(int));	

	for(int i = 0;i < MAXCOLOR;i++)//颜色
	{
		writeTxtFile.Write( &m_game.m_data.datacolor.clindex[i], sizeof(COLORREF));
	}

	writeTxtFile.Close();
}

void CmypixelcrossDlg::OnMenuSavemissionas()
{
	CFileDialog dlg(false,											//TRUE是创建打开文件对话框，FALSE则创建的是保存文件对话框 
                    _T(".zsd"),											//默认的打开文件的类型 
                    NULL,											//默认打开的文件名 
                    OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,			//打开只读文件 
                    _T("关卡文件(*.zsd)|*.zsd|所有文件 (*.*)|*.*||"),//所有可以打开的文件类型 
					this,NULL);	
 
    if(dlg.DoModal()==IDOK)   
    { 
       m_missionname = dlg.GetPathName();////////取出文件路径 
       SaveMission();
    } 
	SetActiveWindow();

}




void CmypixelcrossDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	//保持宽高一致，不再需要
	/*if((pRect->right - pRect->left) < WINDOWMINWIDTH || (pRect->bottom - pRect->top) < WINDOWMINHEIGHT)
	{
		pRect->right = pRect->left + WINDOWMINWIDTH;
		pRect->bottom = pRect->top + WINDOWMINHEIGHT;
	}
	bool isbigger = true;
	if(m_oldrectflg != true)	
	{
		if(pRect->right < m_oldrect.right || pRect->bottom < m_oldrect.bottom)//判断，放大还是缩小
			isbigger = false;
		if(isbigger == true)
		{
			if(pRect->right - pRect->left >  pRect->bottom - pRect->top )
				pRect->bottom = pRect->top + (pRect->right - pRect->left) + 20;//20:menu
			else
				pRect->right = pRect->left + (pRect->bottom - pRect->top) - 20;
		}
		else
		{
			if(pRect->right - pRect->left <  pRect->bottom - pRect->top )
				pRect->bottom = pRect->top + (pRect->right - pRect->left) + 20;
			else
				pRect->right = pRect->left + (pRect->bottom - pRect->top) - 20;
		}
	}

	m_oldrect.left		= pRect->left;
	m_oldrect.right		= pRect->right;
	m_oldrect.top		= pRect->top;
	m_oldrect.bottom	= pRect->bottom;
	m_oldrectflg		= false;*/


	CDialogEx::OnSizing(fwSide, pRect);
	
}


void CmypixelcrossDlg::OnSize(UINT nType, int cx, int cy)
{
	if(isDCok != false)
		SetPos();
	CDialogEx::OnSize(nType, cx, cy);
	ReDraw();
}


int CmypixelcrossDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	isDCok = false;
	m_oldrectflg = true;
	return 0;
}


void CmypixelcrossDlg::OnLButtonDown(UINT nFlags, CPoint point)//左键，选取颜色或涂色
{
	LClick(point);
	ReDraw();
	if(m_game.IsPuzzleSolve()== true)
	{
		AfterGameFinished();
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CmypixelcrossDlg::LClick(CPoint point)
{
	//判断调色板
	int tnum =1; ;
	for(int y = 0;y < 3;y++)
	{
		for(int x = 0;x < 3;x++)
		{
			if(point.x >= m_colortablerect[y][x].left && point.x <= m_colortablerect[y][x].right && point.y >= m_colortablerect[y][x].top && point.y <= m_colortablerect[y][x].bottom)
			{
				m_selcolor = y * 3 + x + 1;

				return;
			}
			
			tnum++;
			if(tnum > m_game.GetColorCnt())
			{
				y = 9;//跳到最外
				break;
			}
		}
	}

	//判断主table
	int pwidth	= m_game.GetPuzzleWidth();
	int pheight = m_game.GetPuzzleHeight();

	for(int y = 0;y < pheight;y++)
	{
		for(int x = 0;x < pwidth;x++)
		{
			if(point.x >= m_tablerect[y][x].left && point.x <= m_tablerect[y][x].right && point.y >= m_tablerect[y][x].top && point.y <= m_tablerect[y][x].bottom)
			{
				m_game.LeftClick(x,y,m_selcolor);
				return;
			}
		}
	}
}

void CmypixelcrossDlg::AfterGameFinished()
{
	m_game.ClearNotUse();
	ReDraw();
	CWinGame wg;
	wg.DoModal();

	CFileDialog dlg(TRUE,											//TRUE是创建打开文件对话框，FALSE则创建的是保存文件对话框 
                    _T(".zsd"),											//默认的打开文件的类型 
                    NULL,												//默认打开的文件名 
                    OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,				//打开只读文件 
                    _T("关卡文件(*.zsd)|*.zsd|所有文件 (*.*)|*.*||"),//所有可以打开的文件类型 
					this,NULL);	

	switch(wg.btnindex)
	{
	case BTNREPLAY:
			for(int y = 0;y < m_game.m_data.height;y++)
			{
				for(int x = 0;x < m_game.m_data.width;x++)
				{
					m_game.m_data.data[y][x].colorindex = 1;
					m_game.m_data.data[y][x].value = 0;
				}
			}
			break;
	case BTNOPEN:
			
			if(dlg.DoModal()==IDOK)   
			{ 
				m_missionname = dlg.GetPathName();////////取出文件路径 
			} 
			else
				return;
			this->SetFocus();
			LoadMission();
			m_game.IsPuzzleCorrect();
			SetPos();
			ReDraw();
			break;
	case BTNRAD:
			m_game.Rad();		//随机生成
			m_game.ComputeLT();	//计算行列
			m_game.IsPuzzleCorrect();
			m_game.ClearData();
			break;
	case BTNNO:
			break;
	}
	SetPos();
	ReDraw();
}


void CmypixelcrossDlg::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);

	ReDraw();
}



void CmypixelcrossDlg::OnRButtonDown(UINT nFlags, CPoint point)//右键，画X或取消
{
	RClick(point);
	ReDraw();
	if(m_game.IsPuzzleSolve()== true)
	{
		AfterGameFinished();
	}
	CDialogEx::OnRButtonDown(nFlags, point);
}

void CmypixelcrossDlg::RClick(CPoint point)
{
	if(m_mode == MODEDESIGN)
	{
		//判断调色板
		int tnum =1; ;
		for(int y = 0;y < 3;y++)
		{
			for(int x = 0;x < 3;x++)
			{
				if(point.x >= m_colortablerect[y][x].left && point.x <= m_colortablerect[y][x].right && point.y >= m_colortablerect[y][x].top && point.y <= m_colortablerect[y][x].bottom)
				{
					m_selcolor = y * 3 + x + 1;

					CColorDialog colorDialog;
					COLORREF m_Color;
					int reasult = colorDialog.DoModal();
					//用这两行代码可以得到那个框框。这时候就可以在上面选择自己
					//要用的颜色了。
					if (reasult == IDOK)//如果按下颜色对话框的OK键
					{    
						m_Color = colorDialog.GetColor();//把对话框选中的颜色给变量m_Color    
						m_game.SetColor(m_Color,tnum);
					}

					return;
				}
			
				tnum++;
			}
		}
	}
	else if(m_mode == MODEGAME)
	{
		//判断主table
		int pwidth	= m_game.GetPuzzleWidth();
		int pheight = m_game.GetPuzzleHeight();

		for(int y = 0;y < pheight;y++)
		{
			for(int x = 0;x < pwidth;x++)
			{
				if(point.x >= m_tablerect[y][x].left && point.x <= m_tablerect[y][x].right && point.y >= m_tablerect[y][x].top && point.y <= m_tablerect[y][x].bottom)
				{
					m_game.RightClick(x,y);
					y = 99;
					break;
				}
			}
		}
	}
}



void CmypixelcrossDlg::OnMenuNewmission()
{
	CNewMission cnm;	//C New Mission....not other cnm...
	if(cnm.DoModal() == IDOK)
	{
		m_game.m_data.width = cnm.m_width;
		m_game.m_data.height = cnm.m_height;
		LoadMissionDef(m_game.m_data.width,m_game.m_data.height);
		bool israd = cnm.m_israd;
		if(israd == true)
			m_game.Rad();//随机生成关卡
		SetPos();
		ReDraw();
	}
	else//cancel 不做任何操作
	{
		return;
	}

}



void CmypixelcrossDlg::OnMenuRad()
{
	m_game.Rad();//随机生成关卡
	ReDraw();
}


void CmypixelcrossDlg::OnMenuChangesize()
{
	CNewMission cnm;	//C New Mission....not other cnm...
	if(cnm.DoModal() == IDOK)
	{
		m_game.m_data.width = cnm.m_width;
		m_game.m_data.height = cnm.m_height;
		bool israd = cnm.m_israd;
		if(israd == true)
			m_game.Rad();//随机生成关卡
		SetPos();
		ReDraw();
	}
}


void CmypixelcrossDlg::OnDaliang()	//大量生成关卡
{
	CDaliang cdl;
	CTime nowtime;     
	nowtime = CTime::GetCurrentTime();     
	CString nt;
	

	if(cdl.DoModal() == IDOK)
	{
		LoadMissionDef(m_game.m_data.width,m_game.m_data.height);

		m_game.m_data.width			= cdl.i_width;
		m_game.m_data.height		= cdl.i_height;
		m_game.m_data.datacolorcnt	= cdl.i_colornum;
		m_game.m_blfrom				= cdl.i_blfrom;
		m_game.m_blto				= cdl.i_blto;
		m_game.m_isbl				= cdl.isbl;

		m_game.m_data.datacolor.clindex[0] = RGB(0	,0	,0	);
		m_game.m_data.datacolor.clindex[1] = RGB(255,0	,0	);
		m_game.m_data.datacolor.clindex[2] = RGB(0	,255,0	);
		m_game.m_data.datacolor.clindex[3] = RGB(0	,0	,255);
		m_game.m_data.datacolor.clindex[4] = RGB(255,0	,255);
		m_game.m_data.datacolor.clindex[5] = RGB(255,255,0	);
		m_game.m_data.datacolor.clindex[6] = RGB(0	,255,255);
		m_game.m_data.datacolor.clindex[7] = RGB(255,128,128);
		m_game.m_data.datacolor.clindex[8] = RGB(0	,128,128);
		m_game.m_data.datacolor.clindex[9] = RGB(128,0	,128);
		for(int i = m_game.m_data.datacolorcnt + 1;i < MAXCOLOR;i++)
		{
			m_game.m_data.datacolor.clindex[i] = RGB(0,0,0);
		}

		
		int num = cdl.i_buildnum;
		bool israd = cdl.israd;
		if(israd == true)
		{
			for(int i = 0;i < num;i++)
			{
				nt.Format(_T("%d%d%d%d.zsd"),nowtime.GetYear(),nowtime.GetMonth(),nowtime.GetDay(),i);
				m_missionname = nt;
				m_game.Rad();//随机生成关卡
				SaveMission();

				//清空
				m_game.ClearData();
			}
			MessageBox(_T("生成完毕"));
		}
		else
		{}
		LoadMissionDef(m_game.m_data.width,m_game.m_data.height);
		SetPos();
		ReDraw();
	}
	else//cancel 不做任何操作
	{
		return;
	}
	
}


void CmypixelcrossDlg::OnMenuSomegame()
{
	CRADGAMEDLG crg;
	if(crg.DoModal() == IDOK)
	{
		LoadMissionDef(m_game.m_data.width,m_game.m_data.height);

		m_game.m_data.width			= crg.m_width;
		m_game.m_data.height		= crg.m_height;
		m_game.m_data.datacolorcnt	= crg.m_color;
		m_game.m_blfrom				= crg.m_blfrom;
		m_game.m_blto				= crg.m_blto;
		m_game.m_isbl				= true;

		m_game.m_data.datacolor.clindex[0] = RGB(0	,0	,0	);
		m_game.m_data.datacolor.clindex[1] = RGB(255,0	,0	);
		m_game.m_data.datacolor.clindex[2] = RGB(0	,255,0	);
		m_game.m_data.datacolor.clindex[3] = RGB(0	,0	,255);
		m_game.m_data.datacolor.clindex[4] = RGB(255,0	,255);
		m_game.m_data.datacolor.clindex[5] = RGB(255,255,0	);
		m_game.m_data.datacolor.clindex[6] = RGB(0	,255,255);
		m_game.m_data.datacolor.clindex[7] = RGB(255,128,128);
		m_game.m_data.datacolor.clindex[8] = RGB(0	,128,128);
		m_game.m_data.datacolor.clindex[9] = RGB(128,0,128);
		for(int i = m_game.m_data.datacolorcnt + 1;i < MAXCOLOR;i++)
		{
			m_game.m_data.datacolor.clindex[i] = RGB(0,0,0);
		}
		m_game.Rad();//随机生成关卡	
		m_game.ComputeLT();
		m_game.IsPuzzleCorrect();
		m_game.ClearData();
		SetPos();
		ReDraw();


	}
	else
		return;
	

}


void CmypixelcrossDlg::OnMenuSavemission()
{
	if(m_missionname.GetLength()<1)
		OnMenuSavemissionas();
	SaveMission();
}


BOOL CmypixelcrossDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg -> message == WM_KEYDOWN)
	{
		if(pMsg -> wParam == VK_ESCAPE)
			return TRUE;
		if(pMsg -> wParam == VK_RETURN)
			return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CmypixelcrossDlg::OnMenuRestart()
{
	//清空
	for(int y = 0;y < m_game.m_data.height;y++)
	{
		for(int x = 0;x < m_game.m_data.width;x++)
		{
			m_game.m_data.data[y][x].colorindex = 1;
			m_game.m_data.data[y][x].value = 0;
		}
	}
	ReDraw();
}




void CmypixelcrossDlg::OnMenuPic()
{
	CBitmap m_bitmap;   //创建位图对象
    CImage  m_MyImage;    //用于读取与显示jpg等格式的图像文件


	//获得文件名
	//CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("图片文件(*.jpg;*.jpeg;*.bmp)|*.jpg;*.jpeg;*.bmp|位图文件(*.BMP)|*.BMP||"));
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("位图文件(*.BMP)|*.BMP||"));
    if (IDOK==dlg.DoModal())
    {
        picstrPicPath.Format(_T("%s"),dlg.GetPathName());
        picextname = dlg.GetFileExt();             //返回选定文件的扩展文件名
        picextname.MakeLower();        //将后缀名变成小写的
    }
	else
		return;

	//获得图片
    HBITMAP hBitmap=(HBITMAP)LoadImage(NULL,picstrPicPath,IMAGE_BITMAP,0,0,LR_CREATEDIBSECTION|LR_DEFAULTSIZE|LR_LOADFROMFILE);
	m_bitmap.Detach();
	m_bitmap.Attach(hBitmap);

	CRect rect;
	GetClientRect(&rect);

	CDC dcImage;
	if (!dcImage.CreateCompatibleDC(m_pDC))
	{
		return;
	}
	BITMAP bm;
	m_bitmap.GetBitmap(&bm);
	dcImage.SelectObject(&m_bitmap);

	//分析图片
	int width = m_game.m_data.width;
	int height = m_game.m_data.height;
	double r,g,b;
	int npos = 1;
	for(int y = 0;y < height;y++)
	{
		for(int x = 0;x < width;x++)
		{
			r =	g = b = 0;
			int swidth = bm.bmWidth/width;
			int sheight = bm.bmHeight/height;
			for(int sy = 0;sy < sheight;sy++)
			{
				for(int sx = 0;sx < swidth;sx++)
				{
					COLORREF cl = dcImage.GetPixel(x*bm.bmWidth/width + sx,y*bm.bmHeight/height +sy);
					r += GetRValue(cl);
					g += GetGValue(cl);
					b += GetBValue(cl);
				}
			}
			r = r/(swidth*sheight);//获得平均值
			g = g/(swidth*sheight);
			b = b/(swidth*sheight);
			if(r < 50 && g < 50 && b < 50)//按背景色算
			{
				m_game.m_data.data[y][x].value = DVNO;
				continue;
			}


			bool findcolor = false;
			int nfindcolor= 0;
			for(int ncolor = 1;ncolor < npos;ncolor++)
			{
				double nr,ng,nb;
				nr = GetRValue(m_game.m_data.datacolor.clindex[ncolor]);
				ng = GetGValue(m_game.m_data.datacolor.clindex[ncolor]);
				nb = GetBValue(m_game.m_data.datacolor.clindex[ncolor]);
				int cha = 75;	//控制颜色相似度
				int cha2 = cha * -1;
				if(r - nr > cha2 && r - nr < cha && g - ng > cha2 && g - ng < cha && b - nb > cha2 && b - nb < cha)
				{
					r = nr;
					g = ng;
					b = nb;
					findcolor = true;
					nfindcolor = ncolor;
					break;
				}
			}
			if(findcolor == false)
			{
				m_game.m_data.datacolor.clindex[npos] = RGB(r	,g	,b	);
				nfindcolor = npos;
				m_game.m_data.datacolorcnt = npos;
				if(npos++ > 9)
					npos = 9;
			}
			m_game.m_data.data[y][x].value = DVYES;
			m_game.m_data.data[y][x].colorindex = nfindcolor;
		}
	}
	ReDraw();

}

//从字符串获得需要分析的数据
void CmypixelcrossDlg::SetAnaData(int n_width,int n_height,int n_time,CString n_str)
{
	m_game.m_data.width = n_width;
	m_game.m_data.height = n_height;
	m_game.m_pausetime = n_time;
	LoadMissionDef(m_game.m_data.width,m_game.m_data.height);

	//调色板 
	m_game.m_data.datacolorcnt = 1;
	m_game.m_data.datacolor.clindex[0] = RGB(0,0,0);
	m_game.m_data.datacolor.clindex[1] = RGB(255,0,0);
	
	GetDataFromStr(n_str);

	SetPos();
	ReDraw();

}

void CmypixelcrossDlg::GetDataFromStr(CString n_str)
{
	//上面的表
	CString strtmp;
	int		tmppos = 0;
	int		tmppos2;
	int		inttmp;
	CString t1 = _T("行");
	CString tab = _T("\t");
	int width = m_game.m_data.width;
	int height = m_game.m_data.height;
	tmppos = n_str.Find(t1,0)+ 2;
	for(int y = 0;y < height;y++)
	{
		for(int x = 0;x < width;x++)
		{
			tmppos2 = n_str.Find(tab,tmppos);
			strtmp = n_str.Mid(tmppos,tmppos2 - tmppos);
			inttmp = _ttoi(strtmp.GetBuffer());
			m_game.m_data.xindex[y][x].value = inttmp;
			m_game.m_data.xindex[y][x].colorindex = 1;
			tmppos = tmppos2+1;
		}
		tmppos = n_str.Find(t1,tmppos2)+ 2;
	}

	for(int y = 0;y < height;y++)
	{
		for(int x = 0;x < width;x++)
		{
			tmppos2 = n_str.Find(tab,tmppos);
			strtmp = n_str.Mid(tmppos,tmppos2 - tmppos);
			inttmp = _ttoi(strtmp.GetBuffer());
			m_game.m_data.yindex[y][x].value = inttmp;
			m_game.m_data.yindex[y][x].colorindex = 1;
			tmppos = tmppos2+1;
		}
		tmppos = n_str.Find(t1,tmppos2)+ 2;
	}
	
}