
// mypixelcrossDlg.h : ͷ�ļ�
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

// CmypixelcrossDlg �Ի���
class CmypixelcrossDlg : public CDialogEx
{
// ����
public:
	CmypixelcrossDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MYPIXELCROSS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	CMenu m_Menu;
	CMenu m_MenuDesign;

	// ���ɵ���Ϣӳ�亯��
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
	//////////////////�Լ���
	////����

	//��ͼ��
	CRect		m_rect;         // �洢��ͼ�ؼ��Ļ�ͼ����
    CDC			*m_pDC;         // �ؼ�����Ļ��ͼ�豸ָ��
    CDC			m_memDC;        // �ڴ��ͼ�豸
    CBitmap		m_memBitmap;	// �����ڴ��ͼ��λͼ  
    CBitmap		*m_pOldBmp;		// ���ݾɵ�λͼָ�� 
    CWnd		*m_pWnd;		// ��ͼ�ؼ���ָ��
	//flg
	bool		isDCok;			// DC�Ƿ��Ѿ�׼����

	//��Ϸ
	GameMaster  m_game;
	int			m_selcolor;		//��ǰ
	int			m_mode;
	CString		m_missionname;

	//ͼƬ
	CString		picstrPicPath;
    CString		picextname;

	//�ߴ�
	CRect		m_oldrect;
	bool		m_oldrectflg;
	CRect		m_tablerect[MAXX][MAXY];	//main table
	CRect		m_colortablerect[3][3];		//��ɫ��
	CRect		m_leftfont[MAXX][MAXY];		//��ߵ���
	CRect		m_topfont[MAXX][MAXY];		//�ϱߵ���
	////����
	void ReDraw();
	void DrawDataTable();
	void DrawChar();
	void SetPos();
	void LoadMission();							//���ļ�������ؿ�����Ϸ��
	void LoadMissionDef(int width,int height);	//����ؿ����հ׹ؿ���
	void LClick(CPoint point);
	void RClick(CPoint point);
	void AfterGameFinished();
	void OpenMission();				//���ļ�������ؿ�����ƣ�
	void SaveMission();				//����ؿ�
	void SetAnaData(int n_width,int n_height,int n_time,CString n_str);	//���ַ��������Ҫ����������
	void GetDataFromStr(CString n_str);

	afx_msg void OnDaliang();
	afx_msg void OnMenuSomegame();
	afx_msg void OnMenuSavemission();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnMenuRestart();
	afx_msg void OnMenuPic();
};
