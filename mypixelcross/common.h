#pragma once
#include <WinDef.h>

#define MAXX 30	//最大宽度（格）
#define MAXY 30	//最大高度（格）
#define MAXXY 30	//MAXX,MAXY中较大的值
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
	int value;		//值
	int colorindex;	//颜色
} Index;

typedef struct 
{
	COLORREF clindex[MAXCOLOR];				//0:不使用时的颜色	1～9：颜色1～9	
} ColorIndex;

typedef struct
{
	bool isok;							//该处的值是否已经找到正确位置了
	int  startpos;						//在所处的行（列）中最小可用的位置
	int  endpos;						//在所处的行（列）中最大可用的位置
	int  withoutnum;					//可用位置中排除的位置
	int  without[MAXXY];				//排除的位置
	int  withnum;						//可用位置中已有的位置
	int  with[MAXXY];					//已有的位置
}Indexinfo;


typedef struct 
{
	//数据
	Index xindex[MAXY][MAXX];			//矩阵上边的值
	Index yindex[MAXY][MAXX];			//矩阵左边的值
	Index data[MAXY][MAXX];				//矩阵中的值

	//推导用
	Indexinfo xindexinfo[MAXY][MAXX];	//矩阵上边的值（自动推导用）
	Indexinfo yindexinfo[MAXY][MAXX];	//矩阵左边的值（自动推导用）

	//其他
	int width;							//当前关卡宽度
	int height;							//当前关卡高度
	int tempdatacnt;					//已使用的临时数据个数
	ColorIndex datacolor;				//颜色索引
	int datacolorcnt;					//当前索引中颜色个数(不包括索引0（无颜色）)

	//统计用
	int alldatacnt[MAXCOLOR];			//当前矩阵中各个颜色个数
	int bakdatacnt[MAXCOLOR];			//数字部分各个颜色个数（IsPuzzleCorrect 中计算）
	
} GameData;
