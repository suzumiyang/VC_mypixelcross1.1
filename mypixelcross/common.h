#pragma once
#include <WinDef.h>

#define MAXX 30	//����ȣ���
#define MAXY 30	//���߶ȣ���
#define MAXXY 30	//MAXX,MAXY�нϴ��ֵ
#define MAXCOLOR 10


#define WINDOWMINWIDTH 320
#define WINDOWMINHEIGHT 340
#define WINDOWBLL 1/4
#define WINDOWBLR 3/4

#define DVNO  0
#define DVYES 1
#define DVX   -1

#define MODEGAME	0
#define MODEDESIGN	1
#define MODEAUTO	2

#define BTNREPLAY	0
#define BTNOPEN		1
#define BTNRAD		2
#define BTNNO		-1


typedef struct 
{
	int value;		//ֵ
	int colorindex;	//��ɫ
} Index;

typedef struct 
{
	COLORREF clindex[MAXCOLOR];				//0:��ʹ��ʱ����ɫ	1��9����ɫ1��9	
} ColorIndex;

typedef struct
{
	bool isok;							//�ô���ֵ�Ƿ��Ѿ��ҵ���ȷλ����
	int  startpos;						//���������У��У�����С���õ�λ��
	int  endpos;						//���������У��У��������õ�λ��
	int  withoutnum;					//����λ�����ų���λ��
	int  without[MAXXY];				//�ų���λ��
	int  withnum;						//����λ�������е�λ��
	int  with[MAXXY];					//���е�λ��
}Indexinfo;


typedef struct 
{
	//����
	Index xindex[MAXY][MAXX];			//�����ϱߵ�ֵ
	Index yindex[MAXY][MAXX];			//������ߵ�ֵ
	Index data[MAXY][MAXX];				//�����е�ֵ

	//�Ƶ���
	Indexinfo xindexinfo[MAXY][MAXX];	//�����ϱߵ�ֵ���Զ��Ƶ��ã�
	Indexinfo yindexinfo[MAXY][MAXX];	//������ߵ�ֵ���Զ��Ƶ��ã�

	//����
	int width;							//��ǰ�ؿ����
	int height;							//��ǰ�ؿ��߶�
	int tempdatacnt;					//��ʹ�õ���ʱ���ݸ���
	ColorIndex datacolor;				//��ɫ����
	int datacolorcnt;					//��ǰ��������ɫ����(����������0������ɫ��)

	//ͳ����
	int alldatacnt[MAXCOLOR];			//��ǰ�����и�����ɫ����
	int bakdatacnt[MAXCOLOR];			//���ֲ��ָ�����ɫ������IsPuzzleCorrect �м��㣩
	
} GameData;
