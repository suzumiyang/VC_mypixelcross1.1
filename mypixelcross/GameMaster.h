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
	bool		m_nomorechange;//�ж��Ƿ���Ҫ����ĳ̶���
	bool		m_anaiswrong;	//��ǰ�������




	void InitData();		//��ʼ������
	void ComputeLT();		//���������ϱߵı�
	void Rad();
	bool IsPuzzleCorrect();	//�жϵ�ǰ���Ƿ���ȷ
	bool IsPuzzleSolve();	//��ǰ���Ƿ��Ѿ����

	int	 GetPuzzleWidth();
	int	 GetPuzzleHeight();
	int	 GetColorCnt();
	void GetColor(COLORREF *ncolor,int colorindex);
	void SetColor(COLORREF ncolor,int colorindex);
	void LeftClick(int x,int y,int selcolor);
	void RightClick(int x,int y);
	void ClearNotUse();
	void ClearData();

	bool Analysis();				//����������
	//�������
	void Analysis_setzero();		//�ҳ���ȫΪ�յ��У��У�������	����0001
	void Analysis_setfull();		//�ҳ���ȫ�ɿص��У��У�����ֵ	����0002
	void InitIndexInfo();			//��ʼ�� Indexinfo				����0003
	void UpdateIndexInfo(int cnt);	//���� Indexinfo				����0004
	void UpdateData(int cnt);		//���� indexinfo ���� data ֵ	����0005
	void CleanData(int cnt);		//�Ѳ����κε㷶Χ�ڵķ�����X	����0006

	//�������������+�ݹ飩
	void Analysis_IF(int cnt);		//����ĳ����ֵ�������Ƶ�		����0007

	GameMaster(void);
	~GameMaster(void);
};

