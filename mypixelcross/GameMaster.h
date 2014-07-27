#pragma once

#include "common.h"


class GameMaster
{
public:
	GameData	m_data;
	int			m_num;
	int			m_blfrom;
	int			m_blto;
	bool		m_isbl;
	CString		m_analog;
	int			m_pausetime;
	bool		m_nomorechange;//判断是否到需要假设的程度了
	bool		m_anaiswrong;	//当前假设错了




	void InitData();		//初始化数据
	void ComputeLT();		//计算左侧和上边的表
	void Rad();
	bool IsPuzzleCorrect();	//判断当前关是否正确
	bool IsPuzzleSolve();	//当前关是否已经解决

	int	 GetPuzzleWidth();
	int	 GetPuzzleHeight();
	int	 GetColorCnt();
	void GetColor(COLORREF *ncolor,int colorindex);
	void SetColor(COLORREF ncolor,int colorindex);
	void LeftClick(int x,int y,int selcolor);
	void RightClick(int x,int y);
	void ClearNotUse();
	void ClearData();

	bool Analysis();				//主分析函数
	//常规分析
	void Analysis_setzero();		//找出完全为空的行（列），付空	函数0001
	void Analysis_setfull();		//找出完全可控的行（列），付值	函数0002
	void InitIndexInfo();			//初始化 Indexinfo				函数0003
	void UpdateIndexInfo(int cnt);	//更新 Indexinfo				函数0004
	void UpdateData(int cnt);		//根据 indexinfo 更新 data 值	函数0005
	void CleanData(int cnt);		//把不再任何点范围内的方格置X	函数0006

	//假设分析（迭代+递归）
	void Analysis_IF(int cnt);		//假设某格有值，继续推导		函数0007

	GameMaster(void);
	~GameMaster(void);
};

