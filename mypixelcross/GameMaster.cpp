#include "StdAfx.h"
#include "GameMaster.h"
#include <time.h>

GameMaster::GameMaster(void)
{
	InitData();
	srand( (unsigned)time( NULL ) );
}


GameMaster::~GameMaster(void)
{
}

void GameMaster::InitData()		//初始化数据
{
	for(int y = 0;y < MAXY;y++)
	{
		for(int x = 0;x < MAXX;x++)
		{
			//value
			m_data.data[y][x].value			= 0;
			m_data.xindex[y][x].value		= 0;
			m_data.yindex[y][x].value		= 0;

			//color
			m_data.data[y][x].colorindex	= 0;
			m_data.xindex[y][x].colorindex	= 0;
			m_data.yindex[y][x].colorindex	= 0;
		}
	}
	m_data.height = 0;
	m_data.width  = 0;
	m_data.datacolorcnt = 0;
	m_data.tempdatacnt = 0;
	for(int i = 1;i < MAXCOLOR;i++)
	{
		m_data.alldatacnt[i] = 0;
		m_data.bakdatacnt[i] = 0;
	}
}
bool GameMaster::IsPuzzleCorrect()	//判断当前关是否正确 正确：返回TRUE 错误：返回FALSE
{
	int xnum[9];
	int ynum[9];
	int allcnt = 0;
	for(int ncolor = 1;ncolor <= m_data.datacolorcnt;ncolor++)
	{
		xnum[ncolor] = 0;
		ynum[ncolor] = 0;
		for(int y = 0;y < m_data.height;y++)
		{
			for(int x = 0;x < m_data.width;x++)
			{
				//判断上方数字指定颜色总数
				if(m_data.xindex[y][x].colorindex == ncolor && m_data.xindex[y][x].value > 0)
					xnum[ncolor] += m_data.xindex[y][x].value;
				else if(m_data.xindex[y][x].colorindex > m_data.datacolorcnt)	//使用未指定颜色
					return false;

				//判断左方数字指定颜色总数
				if(m_data.yindex[y][x].colorindex == ncolor && m_data.yindex[y][x].value > 0)
					ynum[ncolor] += m_data.yindex[y][x].value;
				else if(m_data.yindex[y][x].colorindex > m_data.datacolorcnt)	//使用未指定颜色
					return false;
			}
		}
		if(xnum[ncolor]!= ynum[ncolor])	//相同颜色数量不等，返回错误
			return false;
		if(xnum[ncolor] > 0)
			allcnt = 1;	//有值
		m_data.bakdatacnt[ncolor] = xnum[ncolor];
	}
	if(allcnt == 0)	//没有值
		return false;
	return true;

}
/////**************数字，上对齐，左对齐
bool GameMaster::IsPuzzleSolve()	//当前关是否已经解决	解决：返回TRUE	未解决：返回FALSE 
{
	//1：判断各个颜色数是否相等，不相等直接返回FALSE
	//获得当前游戏中颜色总数
	for(int i = 1;i < MAXCOLOR;i++)
	{
		m_data.alldatacnt[i] = 0;
	}
	for(int y = 0;y < m_data.height;y++)
	{
		for(int x = 0;x < m_data.width;x++)
		{
			if(m_data.data[y][x].value==DVYES)
			{
				int index = m_data.data[y][x].colorindex;
				m_data.alldatacnt[index]++;
			}
		}
	}

	for(int i = 1;i <= m_data.datacolorcnt;i++)
	{
		if(m_data.alldatacnt[i] !=m_data.bakdatacnt[i])
			return false;
	}

	//2:判断位置+颜色是否正确
	//判断纵向
	for(int x = 0;x < m_data.width;x++)	//xpos
	{
		int xy = 0;		//上面值的index
		int datacnt = 0;//个数
		int firstdata=0;
		int oldcolor = -1;
		for(int temp = 0;temp < m_data.height;temp++)
		{
			if(m_data.data[temp][x].value == DVYES)
			{
				firstdata = temp;
				oldcolor = m_data.data[firstdata][x].colorindex;	//当前颜色
				break;
			}
		}
		for(int y = firstdata;y < m_data.height;y++)//ypos
		{
			if(m_data.data[y][x].value == DVYES && m_data.data[y][x].colorindex == oldcolor)	//如果有值而且为当前颜色
				datacnt++;
			else//如果没值或者颜色改变
			{
				if(datacnt != m_data.xindex[xy][x].value || oldcolor != m_data.xindex[xy][x].colorindex)//与指定值不同
					return false;
				else
				{
					xy++;//下一个总数
					datacnt = 0;
				}
				//寻找新点
				while(m_data.data[y][x].value != DVYES && y < m_data.height)
					y++;
				if(y < m_data.height)//标记新点
				{
					oldcolor = m_data.data[y][x].colorindex;
					y--;
				}
			}//判断变化结束
		}//y循环结束
		if(datacnt > 0)
		{
			if(datacnt != m_data.xindex[xy][x].value || oldcolor != m_data.xindex[xy][x].colorindex)//与指定值不同
				return false;
		}
	}//x循环结束

	//判断横向
	for(int y = 0;y < m_data.height;y++)	//xpos
	{
		int xy = 0;		//上面值的index
		int datacnt   = 0;//个数
		int firstdata =0;
		int oldcolor = -1;
		for(int temp = 0;temp < m_data.width;temp++)
		{
			if(m_data.data[y][temp].value == DVYES)
			{
				firstdata = temp;
				oldcolor = m_data.data[y][firstdata].colorindex;	//当前颜色
				break;
			}
		}
		
		for(int x = firstdata;x < m_data.width;x++)//ypos
		{
			if(m_data.data[y][x].value == DVYES && m_data.data[y][x].colorindex == oldcolor)	//如果有值而且为当前颜色
				datacnt++;
			else//如果没值或者颜色改变
			{
				if(datacnt != m_data.yindex[y][xy].value || oldcolor != m_data.yindex[y][xy].colorindex)//与指定值不同
					return false;
				else
				{
					xy++;//下一个总数
					datacnt = 0;
				}
				//寻找新点
				while(m_data.data[y][x].value != DVYES && x < m_data.width)
					x++;
				if(x < m_data.width)//标记新点
				{
					oldcolor = m_data.data[y][x].colorindex;
					x--;
				}
			}//判断变化结束
		}//x循环结束
		if(datacnt > 0)
		{
			if(datacnt != m_data.yindex[y][xy].value || oldcolor != m_data.yindex[y][xy].colorindex)//与指定值不同
				return false;
		}
	}//y循环结束

	return true;
}


int	 GameMaster::GetPuzzleWidth()
{
	return m_data.width;
}
int	 GameMaster::GetPuzzleHeight()
{
	return m_data.height;
}

int	 GameMaster::GetColorCnt()
{
	return m_data.datacolorcnt;
}

void GameMaster::GetColor(COLORREF *ncolor,int colorindex)
{
	 *ncolor = m_data.datacolor.clindex[colorindex];
}

void GameMaster::LeftClick(int x,int y,int selcolor)
{
	if(m_data.data[y][x].value != DVNO)
		m_data.data[y][x].value = DVNO;
	else
	{
		m_data.data[y][x].value = DVYES;
		m_data.data[y][x].colorindex = selcolor;
	}
}

void GameMaster::RightClick(int x,int y)
{
	if(m_data.data[y][x].value != DVNO)
		m_data.data[y][x].value = DVNO;
	else
	{
		m_data.data[y][x].value = DVX;
	}
}

void GameMaster::SetColor(COLORREF ncolor,int colorindex)
{
	if(m_data.datacolorcnt < colorindex)
	{
		colorindex = m_data.datacolorcnt + 1;	//只增加一个
		m_data.datacolorcnt++;
	}

	m_data.datacolor.clindex[colorindex] = ncolor;
	
}


void GameMaster::ComputeLT()		//计算左侧和上边的表
{
	//纵向生成
	for(int x = 0;x < m_data.width;x++)	//xpos
	{
		int xy = 0;		//上面值的index
		int datacnt = 0;//个数
		int firstdata=0;
		int oldcolor = -1;
		for(int y = 0;y < m_data.height;y++)//清空
		{
			m_data.xindex[y][x].value = 0;
			m_data.xindex[y][x].colorindex = 0;
		}
		for(int temp = 0;temp < m_data.height;temp++)//寻找第一个值
		{
			if(m_data.data[temp][x].value == DVYES)
			{
				firstdata = temp;
				oldcolor = m_data.data[firstdata][x].colorindex;	//当前颜色
				break;
			}
		}
		for(int y = firstdata;y < m_data.height;y++)//ypos
		{
			if(m_data.data[y][x].value == DVYES && m_data.data[y][x].colorindex == oldcolor)	//如果有值而且为当前颜色
				datacnt++;
			else//如果没值或者颜色改变
			{
				m_data.xindex[xy][x].value = datacnt;
				m_data.xindex[xy][x].colorindex = oldcolor;
				xy++;
				datacnt = 0;
				//寻找新点
				while(m_data.data[y][x].value != DVYES && y < m_data.height)
					y++;
				if(y < m_data.height)//标记新点
				{
					
					oldcolor = m_data.data[y][x].colorindex;
					y--;
				}
			}//判断变化结束
		}//y循环结束
		if(datacnt > 0)//末端
		{
			m_data.xindex[xy][x].value = datacnt;
			m_data.xindex[xy][x].colorindex = oldcolor;
		}
	}//x循环结束

	//横向生成
	for(int y = 0;y < m_data.height;y++)	//xpos
	{
		int xy = 0;		//上面值的index
		int datacnt = 0;//个数
		int firstdata=0;
		int oldcolor = -1;

		for(int x = 0;x < m_data.width;x++)//清空
		{
			m_data.yindex[y][x].value = 0;
			m_data.yindex[y][x].colorindex = 0;
		}
		for(int temp = 0;temp < m_data.width;temp++)
		{
			if(m_data.data[y][temp].value == DVYES)
			{
				firstdata = temp;
				oldcolor = m_data.data[y][firstdata].colorindex;	//当前颜色
				break;
			}
		}
		
		for(int x = firstdata;x < m_data.width;x++)//ypos
		{
			if(m_data.data[y][x].value == DVYES && m_data.data[y][x].colorindex == oldcolor)	//如果有值而且为当前颜色
				datacnt++;
			else//如果没值或者颜色改变
			{
				m_data.yindex[y][xy].value = datacnt;
				m_data.yindex[y][xy].colorindex = oldcolor;
				xy++;
				datacnt = 0;
				//寻找新点
				while(m_data.data[y][x].value != DVYES && x < m_data.width)
					x++;
				if(x < m_data.width)//标记新点
				{
					
					oldcolor = m_data.data[y][x].colorindex;
					x--;
				}
			}//判断变化结束
		}//x循环结束
		if(datacnt > 0)//末端
		{
			m_data.yindex[y][xy].value = datacnt;
			m_data.yindex[y][xy].colorindex = oldcolor;
		}
	}//y循环结束

}
void GameMaster::Rad()
{
	ClearData();

	int numofdata;
	if(m_isbl == false)
		numofdata= rand()%(m_data.width * m_data.height);//随机生成个数
	else
	{
		int allnum = m_data.width * m_data.height;
		if(m_blto > m_blfrom)
			numofdata = rand() % ( allnum * m_blto / 100 - allnum * m_blfrom / 100 ) + m_blfrom;//按比率生成个数
		else
			numofdata = allnum * m_blto / 100;//固定
	}
	//if(numofdata < 5 )
	//	numofdata = rand()%(m_data.width * m_data.height);//重新生成

	for(int i = 0;i < numofdata;i++)
	{
		bool isok=false;
		int tempx;
		int tempy;
		int tempcolor;
		
		while(isok== false)
		{
			tempx = rand()%m_data.width;
			tempy = rand()%m_data.height;
			tempcolor = rand()%m_data.datacolorcnt + 1;
			if(m_data.data[tempy][tempx].value == DVNO)
			{
				m_data.data[tempy][tempx].value = DVYES;
				m_data.data[tempy][tempx].colorindex = tempcolor;
				isok = true;
			}
		}
	}
}

void GameMaster::ClearNotUse()
{
	for(int y = 0;y <m_data.height;y++)
	{
		for(int x = 0;x <m_data.width;x++)
		{
			if(m_data.data[y][x].value == DVX)
				m_data.data[y][x].value = DVNO;
		}
	}
}

void GameMaster::ClearData()
{
	for(int y = 0;y <m_data.height;y++)
	{
		for(int x = 0;x <m_data.width;x++)
		{
			m_data.data[y][x].value = DVNO;
		}
	}
}

//ans start	函数0000
bool GameMaster::Analysis()
{
	//列出函数功能
	CString pmemo;
	pmemo.Format(_T("函数0001:寻找列表中行（列）全为0的项目，并将该行（列）所有位置置X\n"));
	OutputDebugString(pmemo);
	pmemo.Format(_T("函数0002:寻找列表中行（列）全可预测的项目，并将该行（列）每个位置赋上预测值\n"));
	OutputDebugString(pmemo);
	pmemo.Format(_T("函数0003:初始化每一个非0的INDEX的可能位置\n"));
	OutputDebugString(pmemo);
	pmemo.Format(_T("函数0004:根据每一个位置更新每一个非0，非完成的INDEX的可能位置\n"));
	OutputDebugString(pmemo);
	pmemo.Format(_T("函数0005:根据每一个INDEX的信息更新位置\n"));
	OutputDebugString(pmemo);
	pmemo.Format(_T("函数0006:判断某一位置是否不被所有index使用，如果是，置X\n"));
	OutputDebugString(pmemo);

	//列出函数功能 结束
	if(IsPuzzleCorrect()== false)
		return false;
	Analysis_setzero();
	bool ismisok = IsPuzzleSolve();
	InitIndexInfo();
	Analysis_setfull();
	m_nomorechange = false;
	int nloop = 1;
	while(!ismisok && !m_nomorechange)
	{
		CString tstr;
		tstr.Format(_T("函数 0000 第 %d 遍开始\n"),nloop);
		OutputDebugString(tstr);

		m_nomorechange = true;
		UpdateIndexInfo(nloop);//0004
		UpdateData(nloop);	//0005
		ismisok = IsPuzzleSolve();
		nloop++;
	}
	if(ismisok == false)//未解开，开始假设
	{
		CString tstr;
		tstr.Format(_T("函数 0000 循环结束，谜题还没解开，假设开始\n"),nloop);
		OutputDebugString(tstr);

		//假设开始
		nloop = 0;
		Analysis_IF(nloop);
		ismisok = IsPuzzleSolve();

		tstr.Format(_T("函数 0000 假设结束\n"));
		OutputDebugString(tstr);
	}

	return ismisok;
}

//找出完全为空的行（列），付空	函数0001
void GameMaster::Analysis_setzero()
{
	int width = m_data.width;
	int height = m_data.height;
	int tmax = 0;
	//上面
	for(int x = 0;x < width;x++)
	{
		for(int y = 0;y < height;y++)
		{
			tmax += m_data.xindex[y][x].value;
			if(tmax > 0)
				break;
		}
		if(tmax == 0)//该列无值
		{
			CString tstr;
			tstr.Format(_T("函数 0001：因为：第 %d 列内容全为0，"),x+1);
			for(int y = 0;y < height;y++)
			{
				m_data.data[y][x].value = DVX;
				m_data.data[y][x].colorindex = 1;
				CString tstr2;
				tstr2.Format(_T("所以：位置 x = %d , y = %d 一定为空"),x+1,y+1);
				CString tstr3;
				tstr3 = tstr + tstr2 + _T("\n");
				OutputDebugString(tstr3);
				//TRACE(tstr3);
			}
		}
		tmax = 0;
	}
	//左边
	for(int y = 0;y < height;y++)
	{
		for(int x = 0;x < width;x++)
		{
			tmax += m_data.yindex[y][x].value;
			if(tmax > 0)
				break;
		}
		if(tmax == 0)//该列无值
		{
			CString tstr;
			tstr.Format(_T("函数 0001：因为：第 %d 行内容全为0，"),y+1);
			for(int x = 0;x < width;x++)
			{
				m_data.data[y][x].value = DVX;
				m_data.data[y][x].colorindex = 1;
				CString tstr2;
				tstr2.Format(_T("所以：位置 x = %d , y = %d 一定为空"),x+1,y+1);
				CString tstr3;
				tstr3 = tstr + tstr2 + _T("\n");
				OutputDebugString(tstr3);
			}
		}
		tmax = 0;
	}
}

//找出完全可控的行（列），付值	函数0002
void GameMaster::Analysis_setfull()
{
	int width = m_data.width;
	int height = m_data.height;
	int tmax = 0;
	bool isbegin = false;
	//上面
	for(int x = 0;x < width;x++)
	{
		for(int y = 0;y < height;y++)
		{
			tmax += m_data.xindex[y][x].value;
			if(tmax > 0 && isbegin == false)
			{
				isbegin = true;
			}
			if(isbegin == true && y<height - 1 && m_data.xindex[y][x].value > 0 && m_data.xindex[y+1][x].value > 0)	//没两个数字间会空一个格，所以最后一个数字后不空.  防止上对齐
				tmax++;
		}
		if(tmax == height)//该列可控
		{
			CString tstr;
			tstr.Format(_T("函数 0002：因为：第 %d 列内容完全可控，"),x+1);
			int ty = 0;
			for(int y = 0;y < height;y++)
			{
				int tnum = m_data.xindex[y][x].value;
				if(tnum ==0)//忽略0项
					continue;
				for(int ti = 0;ti < tnum;ti++)
				{
					m_data.data[ty][x].value = DVYES;
					m_data.data[ty++][x].colorindex = 1;
					CString tstr2;
					tstr2.Format(_T("所以：位置 x = %d , y = %d 一定有值"),x+1,ty);
					CString tstr3;
					tstr3 = tstr + tstr2 + _T("\n");
					OutputDebugString(tstr3);
				}
				if(ty < height)
				{
					m_data.data[ty][x].value = DVX;
					m_data.data[ty++][x].colorindex = 1;
					CString tstr2;
					tstr2.Format(_T("所以：位置 x = %d , y = %d 一定为空"),x+1,ty);
					CString tstr3;
					tstr3 = tstr + tstr2 + _T("\n");
					OutputDebugString(tstr3);
				}
			}
		}
		tmax = 0;
		isbegin = false;
	}
	//左边
	tmax = 0;
	isbegin = false;
	for(int y = 0;y < height;y++)
	{
		for(int x = 0;x < width;x++)
		{
			tmax += m_data.yindex[y][x].value;
			if(tmax > 0&& isbegin == false)
			{
				isbegin = true;
			}
			if(isbegin == true && x<width - 1 && m_data.yindex[y][x].value > 0 && m_data.yindex[y][x+1].value > 0)	//没两个数字间会空一个格，所以最后一个数字后不空.  防止左对齐
				tmax++;
		}
		if(tmax == width)//该列可控
		{
			CString tstr;
			int tx = 0;
			tstr.Format(_T("函数 0002：因为：第 %d 行内容完全可控，"),y+1);
			for(int x = 0;x < width;x++)
			{
				int tnum = m_data.yindex[y][x].value;
				if(tnum ==0)//忽略0项
					continue;
				for(int ti = 0;ti < tnum;ti++)
				{
					m_data.data[y][tx].value = DVYES;
					m_data.data[y][tx++].colorindex = 1;
					CString tstr2;
					tstr2.Format(_T("所以：位置 x = %d , y = %d 一定有值"),tx,y + 1);
					CString tstr3;
					tstr3 = tstr + tstr2 + _T("\n");
					OutputDebugString(tstr3);
				}
				if(tx < width)
				{
					m_data.data[y][tx].value = DVX;
					m_data.data[y][tx++].colorindex = 1;
					CString tstr2;
					tstr2.Format(_T("所以：位置 x = %d , y = %d 一定为空"),tx,y + 1);
					CString tstr3;
					tstr3 = tstr + tstr2 + _T("\n");
					OutputDebugString(tstr3);
				}
			}
		}
		tmax = 0;
		isbegin = false;
	}
}


//初始化 Indexinfo	函数0003
void GameMaster::InitIndexInfo()
{
	int width = m_data.width;
	int height = m_data.height;
	int tmax = 0;
	//上面
	for(int x = 0;x < width;x++)
	{
		for(int y = 0;y < height;y++)
		{
			if(m_data.xindex[y][x].value > 0)
			{
				m_data.xindexinfo[y][x].isok = false;
				//设置开始位置
				int tsnum = 0;
				for(int i = 0;i < y;i++)
				{
					if(m_data.xindex[i][x].value > 0)
					{
						tsnum += m_data.xindex[i][x].value;
						tsnum ++;
					}
				}
				m_data.xindexinfo[y][x].startpos = tsnum;

				//设置结束位置
				int tenum = 0;
				for(int i = y + 1;i < height;i++)
				{
					if(m_data.xindex[i][x].value > 0)
					{
						tenum += m_data.xindex[i][x].value;
						tenum ++;
					}
				}
				m_data.xindexinfo[y][x].endpos =height - tenum - 1;

				CString tstr;
				tstr.Format(_T("函数 0003：坐标信息（上）：位置 第 %d 列，第 %d 行可用范围为 %d 行到 %d行\n"),x + 1,y + 1,m_data.xindexinfo[y][x].startpos + 1,m_data.xindexinfo[y][x].endpos + 1);
				OutputDebugString(tstr);

				m_data.xindexinfo[y][x].withoutnum = 0;
				m_data.xindexinfo[y][x].withnum = 0;
			}
			else
				m_data.xindexinfo[y][x].isok = true;
		}
	}

	//左面
	for(int y = 0;y < height;y++)
	{
		for(int x = 0;x < width;x++)
		{
			if(m_data.yindex[y][x].value > 0)
			{
				m_data.yindexinfo[y][x].isok = false;
				//设置开始位置
				int tsnum = 0;
				for(int i = 0;i < x;i++)
				{
					if(m_data.yindex[y][i].value > 0)
					{
						tsnum += m_data.yindex[y][i].value;
						tsnum ++;
					}
				}
				m_data.yindexinfo[y][x].startpos = tsnum;

				//设置结束位置
				int tenum = 0;
				for(int i = x + 1;i < width;i++)
				{
					if(m_data.yindex[y][i].value > 0)
					{
						tenum += m_data.yindex[y][i].value;
						tenum ++;
					}
				}
				m_data.yindexinfo[y][x].endpos =width - tenum - 1;

				CString tstr;
				tstr.Format(_T("函数 0003：坐标信息（左）：位置 第 %d 行，第 %d 列可用范围为 %d 列到 %d列\n"),y + 1,x + 1,m_data.yindexinfo[y][x].startpos + 1,m_data.yindexinfo[y][x].endpos + 1);
				OutputDebugString(tstr);

				m_data.yindexinfo[y][x].withoutnum = 0;
				m_data.yindexinfo[y][x].withnum = 0;
			}
			else
				m_data.yindexinfo[y][x].isok = true;
		}
	}
}

//更新 Indexinfo		函数0004
void GameMaster::UpdateIndexInfo(int cnt)
{
	int width = m_data.width;
	int height = m_data.height;
	int tmax = 0;

	for(int dy = 0;dy < height;dy++)
	{
		for(int dx = 0;dx < width;dx++)
		{
			if(m_data.data[dy][dx].value != DVNO )//DVYES or DVX
			{
				//上面(只看当前列)
				for(int y = 0;y < height;y++)
				{
					if(m_data.xindexinfo[y][dx].isok == false )//只看未解决的
					{
						if(m_data.xindexinfo[y][dx].startpos <= dy && m_data.xindexinfo[y][dx].endpos >= dy)//可能范围内
						{
							if(m_data.data[dy][dx].value == DVYES)
							{
								bool isfound = false;
								for(int i = 0 ;i < m_data.xindexinfo[y][dx].withnum;i++)
								{
									if(m_data.xindexinfo[y][dx].with[i]==dy)//已在列表中，不需要更新
										isfound = true;
								}
								if(isfound == false)//不在列表中，需要添加
								{
									//20131022 start
									//判断其他点是否在用
									bool isotheruse = false;
									for(int ty = 0; ty < height;ty++)
									{
										if(m_data.xindexinfo[ty][dx].isok == true || ty == y)//排除已经ok的点（包括无值的点）和当前点
											continue;
										if(m_data.xindexinfo[ty][dx].startpos<= dy && m_data.xindexinfo[ty][dx].endpos>=dy )
											isotheruse = true;//有别的点在用当前点
									}
									//20131022 end

									if(isotheruse == false)//不和其他点公用此点时才添加
									{
										m_data.xindexinfo[y][dx].with[m_data.xindexinfo[y][dx].withnum] = dy;
										m_data.xindexinfo[y][dx].withnum++;	//计数+1
										CString tstr;
										tstr.Format(_T("函数 0004 第 %d 遍：坐标信息（上）：位置 第 %d 列，第 %d 行确认位置添加： %d 行\n"),cnt,dx + 1,y + 1,dy + 1);
										OutputDebugString(tstr);
									}

									if(m_data.xindexinfo[y][dx].withnum > m_data.xindex[y][dx].value)//如果已知点大于值
									{
										m_anaiswrong = true;//出错
										return;
									}
								}
							}
							else	//DVX
							{
								bool isfound = false;
								for(int i = 0 ;i < m_data.xindexinfo[y][dx].withoutnum;i++)
								{
									if(m_data.xindexinfo[y][dx].without[i]==dy)//已在列表中，不需要更新
										isfound = true;
								}
								if(isfound == false)//不在列表中，需要添加
								{
									m_data.xindexinfo[y][dx].without[m_data.xindexinfo[y][dx].withoutnum] = dy;
									m_data.xindexinfo[y][dx].withoutnum++;	//计数+1

									CString tstr;
									tstr.Format(_T("函数 0004 第 %d 遍：坐标信息（上）：位置 第 %d 列，第 %d 行否定位置添加： %d 行\n"),cnt,dx + 1,y + 1,dy + 1);
									OutputDebugString(tstr);
								}
							}//if(m_data.data[dy][dx].value == DVYES)

						}//if(m_data.xindexinfo[y][dx].startpos <= dy && m_data.xindexinfo[y][dx].endpos >= dy)//可能范围内
					}//if(m_data.xindexinfo[y][dx].isok == false )//只看未解决的
				}//for(int y = 0;y < height;y++)

				//左面(只看一行)
				for(int x = 0;x < width;x++)
				{
					if(m_data.yindexinfo[dy][x].isok == false )//只看未解决的
					{
						if(m_data.yindexinfo[dy][x].startpos <= dx && m_data.yindexinfo[dy][x].endpos >= dx)//可能范围内
						{
							if(m_data.data[dy][dx].value == DVYES)
							{
								bool isfound = false;
								for(int i = 0 ;i < m_data.yindexinfo[dy][x].withnum;i++)
								{
									if(m_data.yindexinfo[dy][x].with[i]==dx)//已在列表中，不需要更新
										isfound = true;
								}
								if(isfound == false)//不在列表中，需要添加
								{
									//20131022 start
									//判断其他点是否在用
									bool isotheruse = false;
									for(int tx = 0; tx < width;tx++)
									{
										if(m_data.xindexinfo[dy][tx].isok == true || tx == x)//排除已经ok的点（包括无值的点）和当前点
											continue;
										if(m_data.xindexinfo[dy][tx].startpos<= dx && m_data.xindexinfo[dy][tx].endpos>=dx )
											isotheruse = true;//有别的点在用当前点
									}
									//20131022 end

									if(isotheruse == false)//不和其他点公用此点时才添加
									{
										m_data.yindexinfo[dy][x].with[m_data.yindexinfo[dy][x].withnum] = dx;
										m_data.yindexinfo[dy][x].withnum++;	//计数+1
										CString tstr;
										tstr.Format(_T("函数 0004 第 %d 遍：坐标信息（左）：位置 第 %d 行，第 %d 列确认位置添加： %d 列\n"),cnt,dy + 1,x + 1,dx + 1);
										OutputDebugString(tstr);
									}

									if(m_data.yindexinfo[dy][x].withnum > m_data.yindex[dy][x].value)//如果已知点大于值
									{
										m_anaiswrong = true;//出错
										return;
									}
								}
							}
							else	//DVX
							{
								bool isfound = false;
								for(int i = 0 ;i < m_data.yindexinfo[dy][x].withoutnum;i++)
								{
									if(m_data.yindexinfo[dy][x].without[i]==dx)//已在列表中，不需要更新
										isfound = true;
								}
								if(isfound == false)//不在列表中，需要添加
								{
									m_data.yindexinfo[dy][x].without[m_data.yindexinfo[dy][x].withoutnum] = dx;
									m_data.yindexinfo[dy][x].withoutnum++;	//计数+1
									CString tstr;
									tstr.Format(_T("函数 0004 第 %d 遍：坐标信息（左）：位置 第 %d 行，第 %d 列否定位置添加： %d 列\n"),cnt,dy + 1,x + 1,dx + 1);
									OutputDebugString(tstr);
								}
							}//if(m_data.data[dy][dx].value == DVYES)

						}//if(m_data.yindexinfo[dy][x].startpos <= dx && m_data.yindexinfo[dy][x].endpos >= dx)//可能范围内
					}//if(m_data.yindexinfo[dy][x].isok == false )//只看未解决的
				}//for(int x = 0;x < width;x++)
			}//if(m_data.data[dy][dx].value != DVNO )//DVYES or DVX
		}
	}

	for(int dy = 0;dy < height;dy++)
	{
		for(int dx = 0;dx < width;dx++)
		{
			if(m_data.xindexinfo[dy][dx].isok==false)
			{
				if(m_data.xindexinfo[dy][dx].endpos - m_data.xindexinfo[dy][dx].startpos < m_data.xindex[dy][dx].value)
				{
					m_anaiswrong = true;
					return;
				}
			}
			if(m_data.yindexinfo[dy][dx].isok==false)
			{
				if(m_data.yindexinfo[dy][dx].endpos - m_data.yindexinfo[dy][dx].startpos < m_data.yindex[dy][dx].value)
				{
					m_anaiswrong = true;
					return;
				}
			}
		}
	}

}

//根据 indexinfo 更新 data 值	函数0005
void GameMaster::UpdateData(int cnt)
{
	int width = m_data.width;
	int height = m_data.height;

	//上面
	for(int x = 0;x < width;x++)
	{
		for(int y = 0;y < height;y++)
		{
			if(m_data.xindexinfo[y][x].isok == true)
				continue;
			//判断范围是否可缩小
			for(int i = 0;i < m_data.xindexinfo[y][x].withnum;i++)//判断确认位置
			{
				int pos = m_data.xindexinfo[y][x].with[i];
				//判断是否在其他点的可能范围内
				bool isotheruse = false;
				for(int dy = 0; dy < height;dy++)
				{
					if(m_data.xindexinfo[dy][x].isok == true || dy == y)//排除已经ok的点（包括无值的点）和当前点
						continue;
					for(int tnum = 0;tnum < m_data.xindexinfo[dy][x].withnum;tnum++)
					{
						int tpos = m_data.xindexinfo[dy][x].with[tnum];
						if(tpos == pos)
							isotheruse = true;//有别的点在用当前点
					}
				}//for(int dy = 0; dy < height;dy++)
				
				if(isotheruse == true)//如果有别的点在用，忽略
					continue;

				// 缩小范围
				// 例子（横向为例）
				// 长度：3
				// 位置：0	1	2	3	4	5	6	7	8	9
				//          |                   |
				//        start                end
				//当位置5确认有值时，可能值为3～5，4～6，5～7，因为7 > end值(6)，所以5～7舍去，实际范围变为3~6
				if((pos - m_data.xindex[y][x].value + 1) > m_data.xindexinfo[y][x].startpos)
				{
					m_data.xindexinfo[y][x].startpos = pos - m_data.xindex[y][x].value + 1;
					m_nomorechange = false;
				}

				if((pos + m_data.xindex[y][x].value - 1)>=0 &&(pos + m_data.xindex[y][x].value - 1) < m_data.xindexinfo[y][x].endpos)
				{
					CString tstr;
					tstr.Format(_T("函数 0005 第 %d 遍：坐标信息（上）：位置 第 %d 列，第 %d 行结束位置由 %d 变成 %d\n"),cnt,x + 1,y + 1,m_data.xindexinfo[y][x].endpos + 1,pos + m_data.xindex[y][x].value);
					OutputDebugString(tstr);
					m_data.xindexinfo[y][x].endpos = pos + m_data.xindex[y][x].value - 1;
					m_nomorechange = false;
				}
			}//判断确认位置


			for(int i = 0;i < m_data.xindexinfo[y][x].withoutnum;i++)//判断否认位置
			{
				// 例子（横向为例）
				// 长度：3
				// 位置：0	1	2	3	4	5	6	7	8	9
				//          |                   |
				//        start                end
				//当位置4确认无值时，可用范围变为1～3和5～6，实际范围变为1~3
				int pos = m_data.xindexinfo[y][x].without[i];
				if((m_data.xindexinfo[y][x].endpos - pos) >= 0 && (m_data.xindexinfo[y][x].endpos - pos) < m_data.xindex[y][x].value)//按上例：  if(6 - 4 < 3)
				{
					m_data.xindexinfo[y][x].endpos = pos - 1;						//          end = 3
					m_nomorechange = false;
				}
				if((pos - m_data.xindexinfo[y][x].startpos) >= 0 && (pos - m_data.xindexinfo[y][x].startpos)< m_data.xindex[y][x].value)
				{
					CString tstr;
					tstr.Format(_T("函数 0005 第 %d 遍：坐标信息（上）：位置 第 %d 列，第 %d 行开始位置由 %d 变成 %d\n"),cnt,x + 1,y + 1,m_data.xindexinfo[y][x].startpos + 1,pos + 2);
					OutputDebugString(tstr);

					m_data.xindexinfo[y][x].startpos = pos + 1;
					m_nomorechange = false;
				}

			}//判断否认位置
			CString tstr;
			tstr.Format(_T("函数 0005 第 %d 遍：坐标信息（上）：位置 第 %d 列，第 %d 行范围： %d 行 ～ %d 行\n"),cnt,x + 1,y + 1,m_data.xindexinfo[y][x].startpos + 1,m_data.xindexinfo[y][x].endpos + 1);
			OutputDebugString(tstr);

			//判断范围内是否部分或完全可控
			int nlen = m_data.xindexinfo[y][x].endpos - m_data.xindexinfo[y][x].startpos + 1;
			// 完全可控例子（横向为例）
			// 长度：6
			// 位置：0	1	2	3	4	5	6	7	8	9
			//          |                   |
			//        start                end
			if(nlen == m_data.xindex[y][x].value)//完全可控
			{
				for(int i = m_data.xindexinfo[y][x].startpos;i <= m_data.xindexinfo[y][x].endpos;i++)
				{
					if(m_data.data[i][x].value == DVNO)
					{
						m_data.data[i][x].colorindex = 1;
						m_data.data[i][x].value = DVYES;
						m_nomorechange = false;
						CString tstr;
						tstr.Format(_T("函数 0005 第 %d 遍：坐标信息（上）：位置 第 %d 列，第 %d 行完全可控：所以 %d 列，%d 行 必有值\n"),cnt,x + 1,y + 1,x + 1,i + 1);
						OutputDebugString(tstr);
					}
					else if(m_data.data[i][x].value == DVX)	//假设与现有冲突，失败
					{
						m_anaiswrong = true;
						return;
					}
				}
				m_data.xindexinfo[y][x].isok = true;
				//zzy add 20131023 start
				if(m_data.xindexinfo[y][x].startpos - 1 >=0)
				{
					if(m_data.data[m_data.xindexinfo[y][x].startpos - 1][x].value==DVYES)
					{
						m_anaiswrong = true;
						return;
					}
					m_data.data[m_data.xindexinfo[y][x].startpos - 1][x].value = DVX;
				}
				if(m_data.xindexinfo[y][x].endpos + 1 < height)
				{
					if(m_data.data[m_data.xindexinfo[y][x].endpos + 1][x].value==DVYES)
					{
						m_anaiswrong = true;
						return;
					}
					m_data.data[m_data.xindexinfo[y][x].endpos + 1][x].value = DVX;
				}
				//zzy add 20131023 end
			}
			else if(m_data.xindex[y][x].value == m_data.xindexinfo[y][x].withnum)//另一种完全可控 已知肯定项=项总数
			{
				m_data.xindexinfo[y][x].isok = true;
				//范围内其他项设为X
				for(int i = m_data.xindexinfo[y][x].startpos;i <=m_data.xindexinfo[y][x].endpos;i++)
				{
					if(m_data.data[i][x].value==DVYES)
						continue;

					//判断其他点是否在用
					bool isotheruse = false;
					for(int dy = 0; dy < height;dy++)
					{
						if(m_data.xindexinfo[dy][x].isok == true || dy == y)//排除已经ok的点（包括无值的点）和当前点
							continue;
						if(m_data.xindexinfo[dy][x].startpos<= i && m_data.xindexinfo[dy][x].endpos>=i )
							isotheruse = true;//有别的点在用当前点
						
					}//for(int dy = 0; dy < height;dy++)

					if(isotheruse == false)
					{
						m_data.data[i][x].value=DVX;
						CString tstr;
						tstr.Format(_T("函数 0005 第 %d 遍：坐标信息（上）：位置 第 %d 列，第 %d 行完全可控：所以 %d 列，%d 行 必无值\n"),cnt,x + 1,y + 1,x + 1,i + 1);
						OutputDebugString(tstr);
						m_nomorechange = false;
					}
				}

				//zzy add 20131023 start

				if(m_data.data[m_data.xindexinfo[y][x].startpos][x].value == DVYES)
				{
					if(m_data.xindexinfo[y][x].startpos - 1 >=0)
					{
						if(m_data.data[m_data.xindexinfo[y][x].startpos - 1][x].value==DVYES)
						{
							m_anaiswrong = true;
							return;
						}
						m_data.data[m_data.xindexinfo[y][x].startpos - 1][x].value = DVX;
					}
				}

				if(m_data.data[m_data.xindexinfo[y][x].endpos][x].value == DVYES)
				{
					if(m_data.xindexinfo[y][x].endpos + 1 < height)
					{
						if(m_data.data[m_data.xindexinfo[y][x].endpos + 1][x].value==DVYES)
						{
							m_anaiswrong = true;
							return;
						}
						m_data.data[m_data.xindexinfo[y][x].endpos + 1][x].value = DVX;
					}
				}
				//zzy add 20131023 end
			}
			else if(m_data.xindex[y][x].value * 2 > nlen)//部分可控
			{
				// 部分可控例子（横向为例）
				// 长度：4
				// 位置：0	1	2	3	4	5	6	7	8	9
				//         |                    |
				//       start                 end
				//最左时值为1～4，最右时值为3～6，所以3，4两点一定有值
				for(int i = 0;i <(m_data.xindex[y][x].value * 2 - nlen);i++)//按上例  for(int i = 0;i < (4*2 - 6);i++)	//i:0~1
				{
					int pos = m_data.xindexinfo[y][x].startpos + (nlen - m_data.xindex[y][x].value)+ i;//按上例  pos = 1 + (6 - 4) + i  = 3 + i	//pos :3~4
					
					
					if( pos >= 0 && pos<= height &&m_data.data[pos][x].value == DVNO)
					{
						m_data.data[pos][x].colorindex = 1;
						m_data.data[pos][x].value = DVYES;
						m_nomorechange = false;
						CString tstr;
						tstr.Format(_T("函数 0005 第 %d 遍：坐标信息（上）：位置 第 %d 列，第 %d 行部分可控：所以 %d 列，%d 行 必有值\n"),cnt,x + 1,y + 1,x + 1,pos + 1);
						OutputDebugString(tstr);
					}
					else if(m_data.data[pos][x].value == DVX)	//假设与现有冲突，失败
					{
						m_anaiswrong = true;
						return;
					}
				}//for end
			}//if~else if end(完全，部分可控判断)
		}//y循环结束
	}//x循环结束
	CleanData(cnt);//刷新不用格
	//上面表结束
	/////////////////////////////////////////////////////////////////////////////////////////////
	//左边的表
	for(int y = 0;y < height;y++)
	{
		for(int x = 0;x < width;x++)
		{
			if(m_data.yindexinfo[y][x].isok == true)
				continue;
			//判断范围是否可缩小
			for(int i = 0;i < m_data.yindexinfo[y][x].withnum;i++)//判断确认位置
			{
				int pos = m_data.yindexinfo[y][x].with[i];
				//判断是否在其他点的可能范围内
				bool isotheruse = false;
				for(int dx = 0; dx < width;dx++)
				{
					if(m_data.yindexinfo[y][dx].isok == true || dx == x)//排除已经ok的点（包括无值的点）和当前点
						continue;
					for(int tnum = 0;tnum < m_data.yindexinfo[y][dx].withnum;tnum++)
					{
						int tpos = m_data.yindexinfo[y][dx].with[tnum];
						if(tpos == pos)
							isotheruse = true;//有别的点在用当前点
					}
				}//for(int dx = 0; dx < width;dx++)
				
				if(isotheruse == true)//如果有别的点在用，忽略
					continue;

				// 缩小范围
				// 例子（横向为例）
				// 长度：3
				// 位置：0	1	2	3	4	5	6	7	8	9
				//         |                    |
				//        start                end
				//当位置5确认有值时，可能值为3～5，4～6，5～7，因为7 > end值(6)，所以5～7舍去，实际范围变为3~6
				if((pos - m_data.yindex[y][x].value + 1) > m_data.yindexinfo[y][x].startpos)
				{
					m_data.yindexinfo[y][x].startpos = pos - m_data.yindex[y][x].value + 1;
					m_nomorechange = false;
				}

				if((pos + m_data.yindex[y][x].value - 1)>= 0 && ((pos + m_data.yindex[y][x].value - 1)) < m_data.yindexinfo[y][x].endpos)
				{
					CString tstr;
					tstr.Format(_T("函数 0005 第 %d 遍：坐标信息（左）：位置 第 %d 列，第 %d 行结束位置由 %d 变成 %d\n"),cnt,x + 1,y + 1,m_data.yindexinfo[y][x].endpos + 1,pos + m_data.yindex[y][x].value);
					OutputDebugString(tstr);

					m_data.yindexinfo[y][x].endpos = pos + m_data.yindex[y][x].value - 1;
					m_nomorechange = false;
				}
			}//判断确认位置


			for(int i = 0;i < m_data.yindexinfo[y][x].withoutnum;i++)//判断否认位置
			{
				// 例子（横向为例）
				// 长度：3
				// 位置：0	1	2	3	4	5	6	7	8	9
				//         |                    |
				//        start                end
				//当位置4确认无值时，可用范围变为1～3和5～6，实际范围变为1~3
				int pos = m_data.yindexinfo[y][x].without[i];
				if((m_data.yindexinfo[y][x].endpos - pos)>=0 && (m_data.yindexinfo[y][x].endpos - pos) < m_data.yindex[y][x].value)//按上例：  if(6 - 4 < 3)
				{
					m_data.yindexinfo[y][x].endpos = pos - 1;						//          end = 3
					m_nomorechange = false;
				}
				if((pos - m_data.yindexinfo[y][x].startpos) >=0 && (pos - m_data.yindexinfo[y][x].startpos) < m_data.yindex[y][x].value)
				{
					CString tstr;
					tstr.Format(_T("函数 0005 第 %d 遍：坐标信息（左）：位置 第 %d 列，第 %d 行开始位置由 %d 变成 %d\n"),cnt,x + 1,y + 1,m_data.yindexinfo[y][x].startpos,pos + 2);
					OutputDebugString(tstr);

					m_data.yindexinfo[y][x].startpos = pos + 1;
					m_nomorechange = false;
				}

			}//判断否认位置
			CString tstr;
			tstr.Format(_T("函数 0005 第 %d 遍：坐标信息（左）：位置 第 %d 行，第 %d 列范围： %d 列 ～ %d 列\n"),cnt,y + 1,x + 1,m_data.yindexinfo[y][x].startpos + 1,m_data.yindexinfo[y][x].endpos + 1);
			OutputDebugString(tstr);

			//判断范围内是否部分或完全可控
			int nlen = m_data.yindexinfo[y][x].endpos - m_data.yindexinfo[y][x].startpos + 1;
			// 完全可控例子（横向为例）
			// 长度：6
			// 位置：0	1	2	3	4	5	6	7	8	9
			//          |                   |
			//        start                end
			if(nlen == m_data.yindex[y][x].value)//完全可控
			{
				for(int i = m_data.yindexinfo[y][x].startpos;i <= m_data.yindexinfo[y][x].endpos;i++)
				{
					if(m_data.data[y][i].value == DVNO)
					{
						m_data.data[y][i].colorindex = 1;
						m_data.data[y][i].value = DVYES;
						CString tstr;
						tstr.Format(_T("函数 0005 第 %d 遍：坐标信息（左）：位置 第 %d 行，第 %d 列完全可控：所以 %d 行，%d 列 必有值\n"),cnt,y + 1,x + 1,y + 1,i + 1);
						OutputDebugString(tstr);
						m_nomorechange = false;
					}
					else if(m_data.data[y][i].value == DVX)	//假设与现有冲突，失败
					{
						m_anaiswrong = true;
						return;
					}
				}
				
				m_data.yindexinfo[y][x].isok = true;


				//zzy add 20131023 start
				if(m_data.yindexinfo[y][x].startpos - 1 >=0)
				{
					if(m_data.data[y][m_data.yindexinfo[y][x].startpos - 1].value==DVYES)
					{
						m_anaiswrong = true;
						return;
					}
					m_data.data[y][m_data.yindexinfo[y][x].startpos - 1].value = DVX;
				}
				if(m_data.yindexinfo[y][x].endpos + 1 < width)
				{
					if(m_data.data[y][m_data.yindexinfo[y][x].endpos + 1].value==DVYES)
					{
						m_anaiswrong = true;
						return;
					}
					m_data.data[y][m_data.yindexinfo[y][x].endpos + 1].value = DVX;
				}
				//zzy add 20131023 end
			}
			else if(m_data.yindex[y][x].value == m_data.yindexinfo[y][x].withnum)//另一种完全可控 已知肯定项=项总数
			{
				m_data.yindexinfo[y][x].isok = true;
				//范围内其他项设为X
				for(int i = m_data.yindexinfo[y][x].startpos;i <=m_data.yindexinfo[y][x].endpos;i++)
				{
					if(m_data.data[y][i].value==DVYES)
						continue;

					//判断其他点是否在用
					bool isotheruse = false;
					for(int dx = 0; dx < width;dx++)
					{
						if(m_data.yindexinfo[y][dx].isok == true || dx == x)//排除已经ok的点（包括无值的点）和当前点
							continue;
						if(m_data.yindexinfo[y][dx].startpos<= i && m_data.yindexinfo[y][dx].endpos>=i )
							isotheruse = true;//有别的点在用当前点
						
					}//for(int dx = 0; dx < width;dx++)

					if(isotheruse == false)
					{
						m_data.data[y][i].value=DVX;
						CString tstr;
						tstr.Format(_T("函数 0005 第 %d 遍：坐标信息（左）：位置 第 %d 列，第 %d 行完全可控：所以 %d 列，%d 行 必无值\n"),cnt,x + 1,y + 1,x + 1,i + 1);
						OutputDebugString(tstr);
						m_nomorechange = false;
					}
				}


				//zzy add 20131023 start

				if(m_data.data[y][m_data.yindexinfo[y][x].startpos].value == DVYES)
				{
					if(m_data.yindexinfo[y][x].startpos - 1 >=0)
					{
						if(m_data.data[y][m_data.yindexinfo[y][x].startpos - 1].value==DVYES)
						{
							m_anaiswrong = true;
							return;
						}
						m_data.data[y][m_data.yindexinfo[y][x].startpos - 1].value = DVX;
					}
				}

				if(m_data.data[y][m_data.xindexinfo[y][x].endpos].value == DVYES)
				{
					if(m_data.yindexinfo[y][x].endpos + 1 < width)
					{
						if(m_data.data[y][m_data.yindexinfo[y][x].endpos + 1].value==DVYES)
						{
							m_anaiswrong = true;
							return;
						}
						m_data.data[y][m_data.yindexinfo[y][x].endpos + 1].value = DVX;
					}
				}
				//zzy add 20131023 end
			}
			else if(m_data.yindex[y][x].value * 2 > nlen)//部分可控
			{
				// 部分可控例子（横向为例）
				// 长度：4
				// 位置：0	1	2	3	4	5	6	7	8	9
				//          |                   |
				//        start                end
				//最左时值为1～4，最右时值为3～6，所以3，4两点一定有值
				for(int i = 0;i <(m_data.yindex[y][x].value * 2 - nlen);i++)//按上例  for(int i = 0;i < (4*2 - 6);i++)	//i:0~1
				{
					int pos = m_data.yindexinfo[y][x].startpos + (nlen - m_data.yindex[y][x].value)+ i;//按上例  pos = 1 + (6 - 4) + i  = 3 + i	//pos :3~4
					if(pos >= 0 && pos <= width && m_data.data[y][pos].value != DVNO)
					{
						m_data.data[y][pos].colorindex = 1;
						m_data.data[y][pos].value = DVYES;
						m_nomorechange = false;
						CString tstr;
						tstr.Format(_T("函数 0005 第 %d 遍：坐标信息（左）：位置 第 %d 行，第 %d 列部分可控：所以 %d 行，%d 列 必有值\n"),cnt,y + 1,x + 1,y + 1,pos + 1);
						OutputDebugString(tstr);
					}
					else if(m_data.data[y][pos].value == DVX)	//假设与现有冲突，失败
					{
						m_anaiswrong = true;
						return;
					}
				}//for end
			}//if~else if end(完全，部分可控判断)
		}//x循环结束
	}//y循环结束
	CleanData(cnt);//刷新不用格
	//左面表结束

}


//把不再任何点范围内的方格置X	函数0006	

void GameMaster::CleanData(int cnt)
{
	int width = m_data.width;
	int height = m_data.height;
	for(int y = 0;y < height;y++)
	{
		for(int x = 0;x < width;x++)
		{
			bool isyused = false;
			bool isxused = false;
			if(m_data.data[y][x].value == DVNO)
			{
				//纵向
				for(int dy = 0;dy < height;dy++)
				{
					if(m_data.xindexinfo[dy][x].isok == true)
						continue;
					if(m_data.xindexinfo[dy][x].startpos <= y && m_data.xindexinfo[dy][x].endpos >= y)
						isyused = true;
				}

				//横向 
				for(int dx = 0;dx < width;dx++)
				{
					if(m_data.yindexinfo[y][dx].isok == true)
						continue;
					if(m_data.yindexinfo[y][dx].startpos <= x && m_data.yindexinfo[y][dx].endpos >= x)
						isxused = true;
				}

				if(isyused == false || isxused == false)//横向和纵向有一个不用的，则为空
				{
					if(m_data.data[y][x].value != DVX)
					{
						m_data.data[y][x].value = DVX;
						m_nomorechange = false;
						CString tstr;
						tstr.Format(_T("函数 0006 第 %d 遍：因为无人使用：位置 第 %d 行，第 %d 列必无值\n"),cnt,y + 1,x + 1);
						OutputDebugString(tstr);
					}

					//更新另一个表
					if(isyused == true)//纵向（上方表）中有使用
					{
						for(int dy = 0;dy < height;dy++)//再来次
						{
							if(m_data.xindexinfo[dy][x].isok == true)
								continue;
							if(m_data.xindexinfo[dy][x].startpos <= y && m_data.xindexinfo[dy][x].endpos >= y)
							{
								bool isinwithout = false;
								for(int i = 0;i < m_data.xindexinfo[dy][x].withoutnum;i++)
								{
									if(m_data.xindexinfo[dy][x].without[i]== y)
									{
										isinwithout = true;
										continue;
									}//end if
								}//end for(int i = 0;i < m_data.xindexinfo[dy][x].withoutnum;i++)

								if(isinwithout == false)//添加到 without 列表
								{
									m_data.xindexinfo[dy][x].without[m_data.xindexinfo[dy][x].withoutnum] = y;
									m_data.xindexinfo[dy][x].withoutnum++;

									CString tstr;
									tstr.Format(_T("函数 0006 第 %d 遍：坐标信息（上）：位置 第 %d 列，第 %d 行否定位置添加： %d 行\n"),cnt,x + 1,dy + 1,y + 1);
									OutputDebugString(tstr);
								}

							}//end if(m_data.xindexinfo[dy][x].startpos <= y && m_data.xindexinfo[dy][x].endpos >= y)
						}// end for(int dy = 0;dy < height;dy++)//再来次
					}//end if(isyused == true)//纵向（上方表）中有使用

					if(isxused == true)//横向（左方表）中有使用
					{
						for(int dx = 0;dx < width;dx++)//再来次
						{
							if(m_data.yindexinfo[y][dx].isok == true)
								continue;
							if(m_data.yindexinfo[y][dx].startpos <= x && m_data.yindexinfo[y][dx].endpos >= x)
							{
								bool isinwithout = false;
								for(int i = 0;i < m_data.yindexinfo[y][dx].withoutnum;i++)
								{
									if(m_data.yindexinfo[y][dx].without[i]== x)
									{
										isinwithout = true;
										continue;
									}//end if
								}//end for(int i = 0;i < m_data.yindexinfo[y][dx].withoutnum;i++)

								if(isinwithout == false)//添加到 without 列表
								{
									m_data.yindexinfo[y][dx].without[m_data.yindexinfo[y][dx].withoutnum] = x;
									m_data.yindexinfo[y][dx].withoutnum++;

									CString tstr;
									tstr.Format(_T("函数 0006 第 %d 遍：坐标信息（左）：位置 第 %d 行，第 %d 列否定位置添加： %d 列\n"),cnt,y + 1,dx + 1,x + 1);
									OutputDebugString(tstr);
								}

							}//end if(m_data.yindexinfo[y][dx].startpos <= x && m_data.yindexinfo[y][dx].endpos >= x)
						}// end for(int dx = 0;dx < width;dx++)//再来次
					}//end if(isxused == true)//纵向（上方表）中有使用
				}
			}
		}
	}
}


//假设某格有值，继续推导		函数0007
void GameMaster::Analysis_IF(int cnt)
{

	int width = GetPuzzleWidth();
	int height = GetPuzzleHeight();
	//备份数据
	//Index tempdata[MAXY][MAXX];		//临时备份用数据（自动推导用）
	//Indexinfo xinfot[MAXY][MAXX];	//矩阵上边的值（自动推导备份用）
	//Indexinfo yinfot[MAXY][MAXX];	//矩阵左边的值（自动推导备份用）

	//再大就出错了……
	Index tempdata[15][15];		//临时备份用数据（自动推导用）
	Indexinfo xinfot[15][15];	//矩阵上边的值（自动推导备份用）
	Indexinfo yinfot[15][15];	//矩阵左边的值（自动推导备份用）


	CString ustr;
	ustr.Format(_T("当前层数为：%d\n"),cnt);
	if(cnt == 20)
	{
		int lsdjfjshjakjsdfnlasdhjf = 0;
	}
	OutputDebugString(ustr);
	ustr.Format(_T("当前状态为：\n"));
	OutputDebugString(ustr);
	for(int sy = 0;sy < height;sy++ )
	{
		for(int sx = 0;sx < width;sx++)
		{
			CString ustr;
			ustr.Format(_T("%d\t"),m_data.data[sy][sx].value);
			//ustr.Format(_T("%d\t"),tempdata[sy][sx].value);
			OutputDebugString(ustr);
		}
		CString ustr;
		ustr.Format(_T("\n"));
		OutputDebugString(ustr);
	}


	//这里～～～
	//bool ismisoka = IsPuzzleSolve();
	//if(ismisoka == true)
	//	return;

	for(int y = 0;y < height;y++ )
	{
		for(int x = 0;x < width;x++)
		{
			//数据
			tempdata[y][x].value	= m_data.data[y][x].value;
			tempdata[y][x].colorindex = m_data.data[y][x].colorindex;

			//info	x
			xinfot[y][x].isok		= m_data.xindexinfo[y][x].isok;
			xinfot[y][x].startpos	= m_data.xindexinfo[y][x].startpos;
			xinfot[y][x].endpos		= m_data.xindexinfo[y][x].endpos;
			xinfot[y][x].withnum	= m_data.xindexinfo[y][x].withnum;
			xinfot[y][x].withoutnum	= m_data.xindexinfo[y][x].withoutnum;

			for(int i = 0;i < xinfot[y][x].withnum;i++)
				xinfot[y][x].with[i] = m_data.xindexinfo[y][x].with[i];
			for(int i = 0;i < xinfot[y][x].withoutnum;i++)
				xinfot[y][x].without[i] = m_data.xindexinfo[y][x].without[i];

			//info	y
			yinfot[y][x].isok		= m_data.yindexinfo[y][x].isok;
			yinfot[y][x].startpos	= m_data.yindexinfo[y][x].startpos;
			yinfot[y][x].endpos		= m_data.yindexinfo[y][x].endpos;
			yinfot[y][x].withnum	= m_data.yindexinfo[y][x].withnum;
			yinfot[y][x].withoutnum	= m_data.yindexinfo[y][x].withoutnum;

			for(int i = 0;i < yinfot[y][x].withnum;i++)
				yinfot[y][x].with[i] = m_data.yindexinfo[y][x].with[i];
			for(int i = 0;i < yinfot[y][x].withoutnum;i++)
				yinfot[y][x].without[i] = m_data.yindexinfo[y][x].without[i];
			
		}
	}

	//获得无法分析格数
	for(int y = 0;y < height;y++ )
	{
		for(int x = 0;x < width;x++)
		{
			if(m_data.data[y][x].value==DVNO)
			{
				m_data.data[y][x].value=DVYES;
				m_data.data[y][x].colorindex = 1;

				CString tstr;
				tstr.Format(_T("函数 0007 假设 第 %d 行，第 %d 列 有值，开始\n"),y + 1,x + 1);
				OutputDebugString(tstr);

				
				tstr.Format(_T("当前状态为：\n"));
				OutputDebugString(tstr);
				for(int sy = 0;sy < height;sy++ )
				{
					for(int sx = 0;sx < width;sx++)
					{
						CString tstr;
						tstr.Format(_T("%d\t"),m_data.data[sy][sx].value);
						OutputDebugString(tstr);
					}
					CString tstr;
					tstr.Format(_T("\n"));
					OutputDebugString(tstr);
				}
				bool ismisok = false;
				m_nomorechange = false;
				m_anaiswrong = false;
				while(ismisok == false && m_nomorechange == false && m_anaiswrong == false)
				{
					CString tstr;
					tstr.Format(_T("函数 0000 第 %d 遍开始\n"),cnt);
					OutputDebugString(tstr);

					m_nomorechange = true;
					UpdateIndexInfo(cnt);//0004
					UpdateData(cnt);	//0005
					ismisok = IsPuzzleSolve();
					cnt++;
				}
				if(ismisok == false && m_anaiswrong == false)//未解开，继续假设
				{
					CString tstr;
					tstr.Format(_T("函数 0007 循环结束，谜题还没解开，继续假设\n"));
					OutputDebugString(tstr);

					//假设开始
					cnt++;
					Analysis_IF(cnt);
					ismisok = IsPuzzleSolve();
				}

				if(ismisok == true)	//解开，返回
				{
					CString tstr;
					tstr.Format(_T("函数 0007 已解开\n"));
					OutputDebugString(tstr);
					return;
				}
				else
				{
					CString tstr;

					tstr.Format(_T("函数 0007 未解开，假设失败，最后数据为：\n"));
					OutputDebugString(tstr);
					for(int sy = 0;sy < height;sy++ )
					{
						for(int sx = 0;sx < width;sx++)
						{
							CString tstr;
							tstr.Format(_T("%d\t"),m_data.data[sy][sx].value);
							OutputDebugString(tstr);
						}
						CString tstr;
						tstr.Format(_T("\n"));
						OutputDebugString(tstr);
					}//数据恢复信息


					tstr.Format(_T("函数 0007 进行下一次假设\n"));
					OutputDebugString(tstr);

					tempdata[y][x].value=DVX;//设置否定值
					for(int ty = 0;ty < height;ty++ )
					{
						for(int tx = 0;tx < width;tx++)
						{
							//数据
							 m_data.data[ty][tx].value		= tempdata[ty][tx].value;
							 m_data.data[ty][tx].colorindex	= tempdata[ty][tx].colorindex;

							//info	x
							m_data.xindexinfo[ty][tx].isok		=xinfot[ty][tx].isok;
							m_data.xindexinfo[ty][tx].startpos	=xinfot[ty][tx].startpos;
							m_data.xindexinfo[ty][tx].endpos	=xinfot[ty][tx].endpos;
							m_data.xindexinfo[ty][tx].withnum	=xinfot[ty][tx].withnum;
							m_data.xindexinfo[ty][tx].withoutnum=xinfot[ty][tx].withoutnum;

							for(int i = 0;i < xinfot[ty][tx].withnum;i++)
								m_data.xindexinfo[ty][tx].with[i] = xinfot[ty][tx].with[i];
							for(int i = 0;i < xinfot[ty][tx].withoutnum;i++)
								m_data.xindexinfo[ty][tx].without[i] = xinfot[ty][tx].without[i];

							//info	y
							m_data.yindexinfo[ty][tx].isok			= yinfot[ty][tx].isok;
							m_data.yindexinfo[ty][tx].startpos		= yinfot[ty][tx].startpos;
							m_data.yindexinfo[ty][tx].endpos		= yinfot[ty][tx].endpos;
							m_data.yindexinfo[ty][tx].withnum		= yinfot[ty][tx].withnum;
							m_data.yindexinfo[ty][tx].withoutnum	= yinfot[ty][tx].withoutnum;

							for(int i = 0;i < yinfot[ty][tx].withnum;i++)
								m_data.yindexinfo[ty][tx].with[i] = yinfot[ty][tx].with[i];
							for(int i = 0;i < yinfot[ty][tx].withoutnum;i++)
								m_data.yindexinfo[ty][tx].without[i] = yinfot[ty][tx].without[i];
			
						}
					}

					

					tstr.Format(_T("数据恢复为：\n"));
					OutputDebugString(tstr);
					for(int sy = 0;sy < height;sy++ )
					{
						for(int sx = 0;sx < width;sx++)
						{
							CString tstr;
							tstr.Format(_T("%d\t"),m_data.data[sy][sx].value);
							OutputDebugString(tstr);
						}
						CString tstr;
						tstr.Format(_T("\n"));
						OutputDebugString(tstr);
					}//数据恢复信息
				}//未解开
			}//该格可以假设
		}//x
	}//y
	bool ismisok = IsPuzzleSolve();
	if(ismisok == false)
	{
		CString tstr;
		tstr.Format(_T("本次没有解开\n"));
		OutputDebugString(tstr);
	}
}