
// mypixelcrossDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mypixelcross.h"
#include "mypixelcrossDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CmypixelcrossDlg �Ի���




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


// CmypixelcrossDlg ��Ϣ�������

BOOL CmypixelcrossDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	m_Menu.LoadMenu(IDR_MAINMENU);
	this->SetMenu(&m_Menu);
	m_MenuDesign.LoadMenu(IDR_MAINMENUDESIGN);
	

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	//��ʼ������
	m_selcolor = 1;
	m_missionname.Format(_T(""));
	//��ͼ�ñ�����ʼ��
	m_pDC = GetDC();
	GetClientRect(&m_rect);
    // �����ڴ��ͼ�豸��ʹ�ڴ�λͼ��DC��ؼ���DC����
    m_memDC.CreateCompatibleDC(m_pDC); 
    m_memBitmap.CreateCompatibleBitmap(m_pDC,m_rect.right,m_rect.bottom);
    m_pOldBmp = m_memDC.SelectObject(&m_memBitmap);

	isDCok = true;
	m_mode = MODEGAME;
	m_game.InitData();
	m_game.IsPuzzleCorrect();
	
	LoadMissionDef(5,5);//�չؿ�
	SetPos();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CmypixelcrossDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();

		ReDraw();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//���»���////////////////////////////////////////////////////////////////////////////////////////////////////
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
	//����
	int pwidth	= m_game.GetPuzzleWidth();
	int pheight = m_game.GetPuzzleHeight();
	//ʵ�ʳߴ�
 	int width	= m_rect.Width() - 5 ;
	int height	= m_rect.Height() - 5;
	CPoint startp;
	int size;

	startp.x = 0;
	startp.y = 0;
	size = height;

	//���û���,ˢ��
	pen.CreatePen(PS_SOLID,2, RGB(255,255,255));    
	oldpen = m_memDC.SelectObject(&pen);
	CBrush *oldbrush;

	//������	 ��ɫ
	m_memDC.Rectangle(m_tablerect[0][0].left - 2,m_tablerect[0][0].top - 2,m_tablerect[pheight - 1][pwidth - 1].right + 2,m_tablerect[pheight - 1][pwidth - 1].bottom + 2);

	//��ÿ���� ��ɫ 
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

			if(m_game.m_data.data[y][x].value == DVX)//����X
			{
				m_memDC.MoveTo(m_tablerect[y][x].left,m_tablerect[y][x].top);
				m_memDC.LineTo(m_tablerect[y][x].right,m_tablerect[y][x].bottom);

				m_memDC.MoveTo(m_tablerect[y][x].left,m_tablerect[y][x].bottom);
				m_memDC.LineTo(m_tablerect[y][x].right,m_tablerect[y][x].top);
			}

		}
	}
	
	//����ɫ�壨���3��3��
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

	//����
	m_memDC.SelectObject(oldpen);//ԭ����
	pen.DeleteObject();

	m_memDC.SelectObject(oldbrush);//ԭ��ˢ
}

void CmypixelcrossDlg::DrawChar()
{
	CFont *oldfont;
	CFont topfont;
	CFont leftfont;
	//����
	int pwidth	= m_game.GetPuzzleWidth();
	int pheight = m_game.GetPuzzleHeight();
	//ʵ�ʳߴ�
 	int width	= m_rect.Width() - 5 ;
	int height	= m_rect.Height() - 5;

	//����ģʽ
	m_memDC.SetBkMode(TRANSPARENT); 

	//��������
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


 

	//��ߵı�
	int leftx = pwidth - 1;
	for(int y = pheight - 1;y >= 0;y--)//
	{
		for(int x = pwidth - 1;x >=0 ;x--)
		{
			COLORREF fontcolor;
			CString str;
			int nvalue = m_game.m_data.yindex[y][x].value;
			if( nvalue > 0)	//��ֵ
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
	//�ϱߵı�
	int topy = pheight - 1;
	for(int x = pwidth - 1;x >=0 ;x--)//
	{
		for(int y = pheight - 1;y >= 0;y--)
		{
			COLORREF fontcolor;
			CString str;
			int nvalue = m_game.m_data.xindex[y][x].value;
			if( nvalue > 0)	//��ֵ
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
	//����
	int pwidth	= m_game.GetPuzzleWidth();
	int pheight = m_game.GetPuzzleHeight();

	//ʵ�ʳߴ�
 	int width	= m_rect.Width() - 15 ;
	int height	= m_rect.Height() - 15;

	//ÿ����ߴ�
	float nwidth  = float((width  * WINDOWBLR)/pwidth);
	float nheight = float((height * WINDOWBLR)/pheight);
	float startx  = float(width   * WINDOWBLL);
	float starty  = float(height  * WINDOWBLL);

	for(int x = 0;x < pwidth;x++)//ÿ��������
	{
		for(int y = 0;y < pheight;y++)
		{
			m_tablerect[y][x].left		= int(startx + x*nwidth + 1);
			m_tablerect[y][x].top		= int(starty + y*nheight + 1);
			m_tablerect[y][x].right		= int(m_tablerect[y][x].left + nwidth - 1);
			m_tablerect[y][x].bottom	= int(m_tablerect[y][x].top  + nheight - 1);
		}
	}

	//��ɫ��
	nwidth  = float((width  * WINDOWBLL)/3);
	nheight = float((height * WINDOWBLL)/3);
	for(int x = 0;x < 3;x++)//ÿ��������
	{
		for(int y = 0;y < 3;y++)
		{
			m_colortablerect[y][x].left		= int(x*nwidth + 1);
			m_colortablerect[y][x].top		= int(y*nheight + 1);
			m_colortablerect[y][x].right	= int(m_colortablerect[y][x].left + nwidth - 1);
			m_colortablerect[y][x].bottom	= int(m_colortablerect[y][x].top  + nheight - 1);
		}
	}

	//��ߵ���
	
	//ȡ������ֵ������
	int nleftwidth = 0;
	for(int y = 0;y < pheight;y++)//ÿ��������
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
		for(int x = 0;x < nleftwidth;x++)//ÿ��������
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
		for(int x = 0;x < pwidth;x++)//ÿ��������
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

	//�ϱߵ���

	int ntopheight = 0;
	for(int x = 0;x < pwidth;x++)//ÿ��������
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
		for(int x = 0;x < pwidth;x++)//ÿ��������
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
		for(int x = 0;x < pwidth;x++)//ÿ��������
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


//��Ϸ���
void CmypixelcrossDlg::LoadMission()//��Ϸģʽ
{
	CFile cfm;
	if(cfm.Open( m_missionname, CFile::modeRead | CFile::typeBinary ) == FALSE)
	{
		CString msg;
		msg.Format(_T("�ļ� %s ������"),m_missionname);
		MessageBox(msg);
		return;
	}
	else
		cfm.Close();
	OpenMission();
	//�������
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

	//����
	m_game.ClearData();

	//��ɫ�� 
	m_game.m_data.datacolorcnt = 0;

	m_game.m_data.datacolor.clindex[0] = RGB(0,0,0);
	//m_game.m_data.datacolor.clindex[1] = RGB(255,0,0);


	//���� ��
	for(int y = 0;y < height;y++)
	{
		for(int x = 0;x < width;x++)
		{
			m_game.m_data.xindex[y][x].colorindex = 1;
			m_game.m_data.xindex[y][x].value = 0;
		}
	}

	//���� ��
	for(int y = 0;y < height;y++)
	{
		for(int x = 0;x < width;x++)
		{
			m_game.m_data.yindex[y][x].colorindex = 1;
			m_game.m_data.yindex[y][x].value = 0;
		}
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CmypixelcrossDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//��Ϸ����Ʋ˵���ʼ/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CmypixelcrossDlg::OnUpdateMenuGame(CCmdUI *pCmdUI)
{
	m_Menu.GetSubMenu(0)->CheckMenuItem(ID_MENU_GAME	,MF_BYCOMMAND | MF_CHECKED);	//��Ϸģʽ
	m_Menu.GetSubMenu(0)->CheckMenuItem(ID_MENU_DESIGN	,MF_BYCOMMAND | MF_UNCHECKED);
	m_Menu.GetSubMenu(0)->CheckMenuItem(ID_MENU_AUTO	,MF_BYCOMMAND | MF_UNCHECKED);

	m_game.ClearData();
	m_missionname = _T("");//����ļ�������ֹ���Ᵽ��

	m_mode = MODEGAME;
	ReDraw();

	this->SetMenu(&m_Menu);

}


void CmypixelcrossDlg::OnUpdateMenuDesign(CCmdUI *pCmdUI)
{
	m_Menu.GetSubMenu(0)->CheckMenuItem(ID_MENU_GAME	,MF_BYCOMMAND | MF_UNCHECKED);	//���ģʽ
	m_Menu.GetSubMenu(0)->CheckMenuItem(ID_MENU_DESIGN	,MF_BYCOMMAND | MF_CHECKED);
	m_Menu.GetSubMenu(0)->CheckMenuItem(ID_MENU_AUTO	,MF_BYCOMMAND | MF_UNCHECKED);

	m_missionname = _T("");//����ļ�������ֹ���Ᵽ��
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


//��Ϸ�˵���ʼ/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CmypixelcrossDlg::OnUpdateMenuNewgame(CCmdUI *pCmdUI)
{
	
}


void CmypixelcrossDlg::OnUpdateMenuSomegame(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
}


void CmypixelcrossDlg::OnUpdateMenuOpengame(CCmdUI *pCmdUI)
{
		CFileDialog dlg(TRUE,											//TRUE�Ǵ������ļ��Ի���FALSE�򴴽����Ǳ����ļ��Ի��� 
                    _T(".zsd"),											//Ĭ�ϵĴ��ļ������� 
                    NULL,												//Ĭ�ϴ򿪵��ļ��� 
                    OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,				//��ֻ���ļ� 
                    _T("�ؿ��ļ�(*.zsd)|*.zsd|�����ļ� (*.*)|*.*||"),//���п��Դ򿪵��ļ����� 
					this,NULL);	

 
    if(dlg.DoModal()==IDOK)   
    { 
        m_missionname = dlg.GetPathName();////////ȡ���ļ�·�� 
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
	// TODO: �ڴ������������û����洦��������
}


void CmypixelcrossDlg::OnUpdateMenuStatus(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
}

void CmypixelcrossDlg::OnUpdateMenuSet(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
}



//��Ʋ˵���ʼ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void CmypixelcrossDlg::OnUpdateMenuOpenmission(CCmdUI *pCmdUI)
{
		CFileDialog dlg(TRUE,											//TRUE�Ǵ������ļ��Ի���FALSE�򴴽����Ǳ����ļ��Ի��� 
                    _T(".zsd"),											//Ĭ�ϵĴ��ļ������� 
                    NULL,												//Ĭ�ϴ򿪵��ļ��� 
                    OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,				//��ֻ���ļ� 
                    _T("�ؿ��ļ�(*.zsd)|*.zsd|�����ļ� (*.*)|*.*||"),//���п��Դ򿪵��ļ����� 
					this,NULL);
 
    if(dlg.DoModal()==IDOK)   
    { 
        m_missionname = dlg.GetPathName();////////ȡ���ļ�·�� 
    } 
	else
		return;
	SetActiveWindow();

	OpenMission();
	ReDraw();
}
void CmypixelcrossDlg::OpenMission()				//���ļ�������ؿ�����ƣ�
{
	CFile readTxtFile;
	if(readTxtFile.Open( m_missionname, CFile::modeRead | CFile::typeBinary ) == FALSE)
	{
		CString msg;
		msg.Format(_T("�ļ� %s ������"),m_missionname);
		MessageBox(msg);
		return;
	}
	

	//�����ϱߵ�ֵ
	for(int y = 0;y < MAXY;y++)
	{
		for(int x = 0;x < MAXX;x++)
		{
			readTxtFile.Read( &m_game.m_data.xindex[y][x].value, sizeof(int));	 
			readTxtFile.Read( &m_game.m_data.xindex[y][x].colorindex, sizeof(int));
		}
	}
	//������ߵ�ֵ
	for(int y = 0;y < MAXY;y++)
	{
		for(int x = 0;x < MAXX;x++)
		{
			readTxtFile.Read( &m_game.m_data.yindex[y][x].value, sizeof(int));	 
			readTxtFile.Read( &m_game.m_data.yindex[y][x].colorindex, sizeof(int));
		}
	}

	//�����е�ֵ
	for(int y = 0;y < MAXY;y++)
	{
		for(int x = 0;x < MAXX;x++)
		{
			readTxtFile.Read( &m_game.m_data.data[y][x].value, sizeof(int));	 
			readTxtFile.Read( &m_game.m_data.data[y][x].colorindex, sizeof(int));
		}
	}

	readTxtFile.Read( &m_game.m_data.width, sizeof(int));	//��ǰ�ؿ����
	readTxtFile.Read( &m_game.m_data.height, sizeof(int));	//��ǰ�ؿ��߶�
	readTxtFile.Read( &m_game.m_data.datacolorcnt, sizeof(int));//��ǰ��������ɫ����(����������0������ɫ��)


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

	//�����ϱߵ�ֵ
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
	//������ߵ�ֵ
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

	//�����е�ֵ
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

	int width = m_game.m_data.width;					//��ǰ�ؿ����
	writeTxtFile.Write( &width, sizeof(int));
	int height= m_game.m_data.height;					//��ǰ�ؿ��߶�
	writeTxtFile.Write( &height, sizeof(int));
	int datacolorcnt = m_game.m_data.datacolorcnt;		//��ǰ��������ɫ����(����������0������ɫ��)
	writeTxtFile.Write( &datacolorcnt, sizeof(int));	

	for(int i = 0;i < MAXCOLOR;i++)//��ɫ
	{
		writeTxtFile.Write( &m_game.m_data.datacolor.clindex[i], sizeof(COLORREF));
	}

	writeTxtFile.Close();
}

void CmypixelcrossDlg::OnMenuSavemissionas()
{
	CFileDialog dlg(false,											//TRUE�Ǵ������ļ��Ի���FALSE�򴴽����Ǳ����ļ��Ի��� 
                    _T(".zsd"),											//Ĭ�ϵĴ��ļ������� 
                    NULL,											//Ĭ�ϴ򿪵��ļ��� 
                    OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,			//��ֻ���ļ� 
                    _T("�ؿ��ļ�(*.zsd)|*.zsd|�����ļ� (*.*)|*.*||"),//���п��Դ򿪵��ļ����� 
					this,NULL);	
 
    if(dlg.DoModal()==IDOK)   
    { 
       m_missionname = dlg.GetPathName();////////ȡ���ļ�·�� 
       SaveMission();
    } 
	SetActiveWindow();

}




void CmypixelcrossDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	//���ֿ��һ�£�������Ҫ
	/*if((pRect->right - pRect->left) < WINDOWMINWIDTH || (pRect->bottom - pRect->top) < WINDOWMINHEIGHT)
	{
		pRect->right = pRect->left + WINDOWMINWIDTH;
		pRect->bottom = pRect->top + WINDOWMINHEIGHT;
	}
	bool isbigger = true;
	if(m_oldrectflg != true)	
	{
		if(pRect->right < m_oldrect.right || pRect->bottom < m_oldrect.bottom)//�жϣ��Ŵ�����С
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

	// TODO:  �ڴ������ר�õĴ�������
	isDCok = false;
	m_oldrectflg = true;
	return 0;
}


void CmypixelcrossDlg::OnLButtonDown(UINT nFlags, CPoint point)//�����ѡȡ��ɫ��Ϳɫ
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
	//�жϵ�ɫ��
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
				y = 9;//��������
				break;
			}
		}
	}

	//�ж���table
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

	CFileDialog dlg(TRUE,											//TRUE�Ǵ������ļ��Ի���FALSE�򴴽����Ǳ����ļ��Ի��� 
                    _T(".zsd"),											//Ĭ�ϵĴ��ļ������� 
                    NULL,												//Ĭ�ϴ򿪵��ļ��� 
                    OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,				//��ֻ���ļ� 
                    _T("�ؿ��ļ�(*.zsd)|*.zsd|�����ļ� (*.*)|*.*||"),//���п��Դ򿪵��ļ����� 
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
				m_missionname = dlg.GetPathName();////////ȡ���ļ�·�� 
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
			m_game.Rad();		//�������
			m_game.ComputeLT();	//��������
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



void CmypixelcrossDlg::OnRButtonDown(UINT nFlags, CPoint point)//�Ҽ�����X��ȡ��
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
		//�жϵ�ɫ��
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
					//�������д�����Եõ��Ǹ������ʱ��Ϳ���������ѡ���Լ�
					//Ҫ�õ���ɫ�ˡ�
					if (reasult == IDOK)//���������ɫ�Ի����OK��
					{    
						m_Color = colorDialog.GetColor();//�ѶԻ���ѡ�е���ɫ������m_Color    
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
		//�ж���table
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
			m_game.Rad();//������ɹؿ�
		SetPos();
		ReDraw();
	}
	else//cancel �����κβ���
	{
		return;
	}

}



void CmypixelcrossDlg::OnMenuRad()
{
	m_game.Rad();//������ɹؿ�
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
			m_game.Rad();//������ɹؿ�
		SetPos();
		ReDraw();
	}
}


void CmypixelcrossDlg::OnDaliang()	//�������ɹؿ�
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
				m_game.Rad();//������ɹؿ�
				SaveMission();

				//���
				m_game.ClearData();
			}
			MessageBox(_T("�������"));
		}
		else
		{}
		LoadMissionDef(m_game.m_data.width,m_game.m_data.height);
		SetPos();
		ReDraw();
	}
	else//cancel �����κβ���
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
		m_game.Rad();//������ɹؿ�	
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
	// TODO: �ڴ����ר�ô����/����û���
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
	//���
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
	CBitmap m_bitmap;   //����λͼ����
    CImage  m_MyImage;    //���ڶ�ȡ����ʾjpg�ȸ�ʽ��ͼ���ļ�


	//����ļ���
	//CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("ͼƬ�ļ�(*.jpg;*.jpeg;*.bmp)|*.jpg;*.jpeg;*.bmp|λͼ�ļ�(*.BMP)|*.BMP||"));
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("λͼ�ļ�(*.BMP)|*.BMP||"));
    if (IDOK==dlg.DoModal())
    {
        picstrPicPath.Format(_T("%s"),dlg.GetPathName());
        picextname = dlg.GetFileExt();             //����ѡ���ļ�����չ�ļ���
        picextname.MakeLower();        //����׺�����Сд��
    }
	else
		return;

	//���ͼƬ
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

	//����ͼƬ
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
			r = r/(swidth*sheight);//���ƽ��ֵ
			g = g/(swidth*sheight);
			b = b/(swidth*sheight);
			if(r < 50 && g < 50 && b < 50)//������ɫ��
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
				int cha = 75;	//������ɫ���ƶ�
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

//���ַ��������Ҫ����������
void CmypixelcrossDlg::SetAnaData(int n_width,int n_height,int n_time,CString n_str)
{
	m_game.m_data.width = n_width;
	m_game.m_data.height = n_height;
	m_game.m_pausetime = n_time;
	LoadMissionDef(m_game.m_data.width,m_game.m_data.height);

	//��ɫ�� 
	m_game.m_data.datacolorcnt = 1;
	m_game.m_data.datacolor.clindex[0] = RGB(0,0,0);
	m_game.m_data.datacolor.clindex[1] = RGB(255,0,0);
	
	GetDataFromStr(n_str);

	SetPos();
	ReDraw();

}

void CmypixelcrossDlg::GetDataFromStr(CString n_str)
{
	//����ı�
	CString strtmp;
	int		tmppos = 0;
	int		tmppos2;
	int		inttmp;
	CString t1 = _T("��");
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