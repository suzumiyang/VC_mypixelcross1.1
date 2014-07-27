
// mypixelcrossDlg.h : 头文件
//

#pragma once

#include "common.h"
#include "GameMaster.h"
#include "NewMission.h"
#include "WinGame.h"
#include "RADGAMEDLG.h"
#include "Daliang.h"
#include "DataInput.h"
#include <afxdlgs.h> 

// CmypixelcrossDlg 对话框
class CmypixelcrossDlg : public CDialogEx
{
// 构造
public:
	CmypixelcrossDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MYPIXELCROSS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CMenu m_Menu;
	CMenu m_MenuDesign;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnMainShow();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnUpdateMenuGame(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuDesign(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuNewgame(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuSomegame(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuOpengame(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuRestart(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuStatus(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuOpenmission(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuSet(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuAuto(CCmdUI *pCmdUI);

	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMenuSavemissionas();
	afx_msg void OnMenuNewmission();
	afx_msg void OnMenuRad();
	afx_msg void OnMenuChangesize();
	//////////////////自己的
	////变量

	//绘图用
	CRect		m_rect;         // 存储绘图控件的绘图区域
    CDC			*m_pDC;         // 控件的屏幕绘图设备指针
    CDC			m_memDC;        // 内存绘图设备
    CBitmap		m_memBitmap;	// 用于内存绘图的位图  
    CBitmap		*m_pOldBmp;		// 备份旧的位图指针 
    CWnd		*m_pWnd;		// 绘图控件的指针
	//flg
	bool		isDCok;			// DC是否已经准备好

	//游戏
	GameMaster  m_game;
	int			m_selcolor;		//当前
	int			m_mode;
	CString		m_missionname;

	//图片
	CString		picstrPicPath;
    CString		picextname;

	//尺寸
	CRect		m_oldrect;
	bool		m_oldrectflg;
	CRect		m_tablerect[MAXX][MAXY];	//main table
	CRect		m_colortablerect[3][3];		//调色板
	CRect		m_leftfont[MAXX][MAXY];		//左边的字
	CRect		m_topfont[MAXX][MAXY];		//上边的字
	////函数
	void ReDraw();
	void DrawDataTable();
	void DrawChar();
	void SetPos();
	void LoadMission();							//从文件中载入关卡（游戏）
	void LoadMissionDef(int width,int height);	//载入关卡（空白关卡）
	void LClick(CPoint point);
	void RClick(CPoint point);
	void AfterGameFinished();
	void OpenMission();				//从文件中载入关卡（设计）
	void SaveMission();				//保存关卡
	void SetAnaData(int n_width,int n_height,int n_time,CString n_str);	//从字符串获得需要分析的数据
	void GetDataFromStr(CString n_str);

	afx_msg void OnDaliang();
	afx_msg void OnMenuSomegame();
	afx_msg void OnMenuSavemission();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnMenuRestart();
	afx_msg void OnMenuPic();
};
