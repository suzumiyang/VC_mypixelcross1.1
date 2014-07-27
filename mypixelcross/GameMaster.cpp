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

void GameMaster::InitData()		//��ʼ������
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
bool GameMaster::IsPuzzleCorrect()	//�жϵ�ǰ���Ƿ���ȷ ��ȷ������TRUE ���󣺷���FALSE
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
				//�ж��Ϸ�����ָ����ɫ����
				if(m_data.xindex[y][x].colorindex == ncolor && m_data.xindex[y][x].value > 0)
					xnum[ncolor] += m_data.xindex[y][x].value;
				else if(m_data.xindex[y][x].colorindex > m_data.datacolorcnt)	//ʹ��δָ����ɫ
					return false;

				//�ж�������ָ����ɫ����
				if(m_data.yindex[y][x].colorindex == ncolor && m_data.yindex[y][x].value > 0)
					ynum[ncolor] += m_data.yindex[y][x].value;
				else if(m_data.yindex[y][x].colorindex > m_data.datacolorcnt)	//ʹ��δָ����ɫ
					return false;
			}
		}
		if(xnum[ncolor]!= ynum[ncolor])	//��ͬ��ɫ�������ȣ����ش���
			return false;
		if(xnum[ncolor] > 0)
			allcnt = 1;	//��ֵ
		m_data.bakdatacnt[ncolor] = xnum[ncolor];
	}
	if(allcnt == 0)	//û��ֵ
		return false;
	return true;

}
/////**************���֣��϶��룬�����
bool GameMaster::IsPuzzleSolve()	//��ǰ���Ƿ��Ѿ����	���������TRUE	δ���������FALSE 
{
	//1���жϸ�����ɫ���Ƿ���ȣ������ֱ�ӷ���FALSE
	//��õ�ǰ��Ϸ����ɫ����
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

	//2:�ж�λ��+��ɫ�Ƿ���ȷ
	//�ж�����
	for(int x = 0;x < m_data.width;x++)	//xpos
	{
		int xy = 0;		//����ֵ��index
		int datacnt = 0;//����
		int firstdata=0;
		int oldcolor = -1;
		for(int temp = 0;temp < m_data.height;temp++)
		{
			if(m_data.data[temp][x].value == DVYES)
			{
				firstdata = temp;
				oldcolor = m_data.data[firstdata][x].colorindex;	//��ǰ��ɫ
				break;
			}
		}
		for(int y = firstdata;y < m_data.height;y++)//ypos
		{
			if(m_data.data[y][x].value == DVYES && m_data.data[y][x].colorindex == oldcolor)	//�����ֵ����Ϊ��ǰ��ɫ
				datacnt++;
			else//���ûֵ������ɫ�ı�
			{
				if(datacnt != m_data.xindex[xy][x].value || oldcolor != m_data.xindex[xy][x].colorindex)//��ָ��ֵ��ͬ
					return false;
				else
				{
					xy++;//��һ������
					datacnt = 0;
				}
				//Ѱ���µ�
				while(m_data.data[y][x].value != DVYES && y < m_data.height)
					y++;
				if(y < m_data.height)//����µ�
				{
					oldcolor = m_data.data[y][x].colorindex;
					y--;
				}
			}//�жϱ仯����
		}//yѭ������
		if(datacnt > 0)
		{
			if(datacnt != m_data.xindex[xy][x].value || oldcolor != m_data.xindex[xy][x].colorindex)//��ָ��ֵ��ͬ
				return false;
		}
	}//xѭ������

	//�жϺ���
	for(int y = 0;y < m_data.height;y++)	//xpos
	{
		int xy = 0;		//����ֵ��index
		int datacnt   = 0;//����
		int firstdata =0;
		int oldcolor = -1;
		for(int temp = 0;temp < m_data.width;temp++)
		{
			if(m_data.data[y][temp].value == DVYES)
			{
				firstdata = temp;
				oldcolor = m_data.data[y][firstdata].colorindex;	//��ǰ��ɫ
				break;
			}
		}
		
		for(int x = firstdata;x < m_data.width;x++)//ypos
		{
			if(m_data.data[y][x].value == DVYES && m_data.data[y][x].colorindex == oldcolor)	//�����ֵ����Ϊ��ǰ��ɫ
				datacnt++;
			else//���ûֵ������ɫ�ı�
			{
				if(datacnt != m_data.yindex[y][xy].value || oldcolor != m_data.yindex[y][xy].colorindex)//��ָ��ֵ��ͬ
					return false;
				else
				{
					xy++;//��һ������
					datacnt = 0;
				}
				//Ѱ���µ�
				while(m_data.data[y][x].value != DVYES && x < m_data.width)
					x++;
				if(x < m_data.width)//����µ�
				{
					oldcolor = m_data.data[y][x].colorindex;
					x--;
				}
			}//�жϱ仯����
		}//xѭ������
		if(datacnt > 0)
		{
			if(datacnt != m_data.yindex[y][xy].value || oldcolor != m_data.yindex[y][xy].colorindex)//��ָ��ֵ��ͬ
				return false;
		}
	}//yѭ������

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
		colorindex = m_data.datacolorcnt + 1;	//ֻ����һ��
		m_data.datacolorcnt++;
	}

	m_data.datacolor.clindex[colorindex] = ncolor;
	
}


void GameMaster::ComputeLT()		//���������ϱߵı�
{
	//��������
	for(int x = 0;x < m_data.width;x++)	//xpos
	{
		int xy = 0;		//����ֵ��index
		int datacnt = 0;//����
		int firstdata=0;
		int oldcolor = -1;
		for(int y = 0;y < m_data.height;y++)//���
		{
			m_data.xindex[y][x].value = 0;
			m_data.xindex[y][x].colorindex = 0;
		}
		for(int temp = 0;temp < m_data.height;temp++)//Ѱ�ҵ�һ��ֵ
		{
			if(m_data.data[temp][x].value == DVYES)
			{
				firstdata = temp;
				oldcolor = m_data.data[firstdata][x].colorindex;	//��ǰ��ɫ
				break;
			}
		}
		for(int y = firstdata;y < m_data.height;y++)//ypos
		{
			if(m_data.data[y][x].value == DVYES && m_data.data[y][x].colorindex == oldcolor)	//�����ֵ����Ϊ��ǰ��ɫ
				datacnt++;
			else//���ûֵ������ɫ�ı�
			{
				m_data.xindex[xy][x].value = datacnt;
				m_data.xindex[xy][x].colorindex = oldcolor;
				xy++;
				datacnt = 0;
				//Ѱ���µ�
				while(m_data.data[y][x].value != DVYES && y < m_data.height)
					y++;
				if(y < m_data.height)//����µ�
				{
					
					oldcolor = m_data.data[y][x].colorindex;
					y--;
				}
			}//�жϱ仯����
		}//yѭ������
		if(datacnt > 0)//ĩ��
		{
			m_data.xindex[xy][x].value = datacnt;
			m_data.xindex[xy][x].colorindex = oldcolor;
		}
	}//xѭ������

	//��������
	for(int y = 0;y < m_data.height;y++)	//xpos
	{
		int xy = 0;		//����ֵ��index
		int datacnt = 0;//����
		int firstdata=0;
		int oldcolor = -1;

		for(int x = 0;x < m_data.width;x++)//���
		{
			m_data.yindex[y][x].value = 0;
			m_data.yindex[y][x].colorindex = 0;
		}
		for(int temp = 0;temp < m_data.width;temp++)
		{
			if(m_data.data[y][temp].value == DVYES)
			{
				firstdata = temp;
				oldcolor = m_data.data[y][firstdata].colorindex;	//��ǰ��ɫ
				break;
			}
		}
		
		for(int x = firstdata;x < m_data.width;x++)//ypos
		{
			if(m_data.data[y][x].value == DVYES && m_data.data[y][x].colorindex == oldcolor)	//�����ֵ����Ϊ��ǰ��ɫ
				datacnt++;
			else//���ûֵ������ɫ�ı�
			{
				m_data.yindex[y][xy].value = datacnt;
				m_data.yindex[y][xy].colorindex = oldcolor;
				xy++;
				datacnt = 0;
				//Ѱ���µ�
				while(m_data.data[y][x].value != DVYES && x < m_data.width)
					x++;
				if(x < m_data.width)//����µ�
				{
					
					oldcolor = m_data.data[y][x].colorindex;
					x--;
				}
			}//�жϱ仯����
		}//xѭ������
		if(datacnt > 0)//ĩ��
		{
			m_data.yindex[y][xy].value = datacnt;
			m_data.yindex[y][xy].colorindex = oldcolor;
		}
	}//yѭ������

}
void GameMaster::Rad()
{
	ClearData();

	int numofdata;
	if(m_isbl == false)
		numofdata= rand()%(m_data.width * m_data.height);//������ɸ���
	else
	{
		int allnum = m_data.width * m_data.height;
		if(m_blto > m_blfrom)
			numofdata = rand() % ( allnum * m_blto / 100 - allnum * m_blfrom / 100 ) + m_blfrom;//���������ɸ���
		else
			numofdata = allnum * m_blto / 100;//�̶�
	}
	//if(numofdata < 5 )
	//	numofdata = rand()%(m_data.width * m_data.height);//��������

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

//ans start	����0000
bool GameMaster::Analysis()
{
	//�г���������
	CString pmemo;
	pmemo.Format(_T("����0001:Ѱ���б����У��У�ȫΪ0����Ŀ���������У��У�����λ����X\n"));
	OutputDebugString(pmemo);
	pmemo.Format(_T("����0002:Ѱ���б����У��У�ȫ��Ԥ�����Ŀ���������У��У�ÿ��λ�ø���Ԥ��ֵ\n"));
	OutputDebugString(pmemo);
	pmemo.Format(_T("����0003:��ʼ��ÿһ����0��INDEX�Ŀ���λ��\n"));
	OutputDebugString(pmemo);
	pmemo.Format(_T("����0004:����ÿһ��λ�ø���ÿһ����0������ɵ�INDEX�Ŀ���λ��\n"));
	OutputDebugString(pmemo);
	pmemo.Format(_T("����0005:����ÿһ��INDEX����Ϣ����λ��\n"));
	OutputDebugString(pmemo);
	pmemo.Format(_T("����0006:�ж�ĳһλ���Ƿ񲻱�����indexʹ�ã�����ǣ���X\n"));
	OutputDebugString(pmemo);

	//�г��������� ����
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
		tstr.Format(_T("���� 0000 �� %d �鿪ʼ\n"),nloop);
		OutputDebugString(tstr);

		m_nomorechange = true;
		UpdateIndexInfo(nloop);//0004
		UpdateData(nloop);	//0005
		ismisok = IsPuzzleSolve();
		nloop++;
	}
	if(ismisok == false)//δ�⿪����ʼ����
	{
		CString tstr;
		tstr.Format(_T("���� 0000 ѭ�����������⻹û�⿪�����迪ʼ\n"),nloop);
		OutputDebugString(tstr);

		//���迪ʼ
		nloop = 0;
		Analysis_IF(nloop);
		ismisok = IsPuzzleSolve();

		tstr.Format(_T("���� 0000 �������\n"));
		OutputDebugString(tstr);
	}

	return ismisok;
}

//�ҳ���ȫΪ�յ��У��У�������	����0001
void GameMaster::Analysis_setzero()
{
	int width = m_data.width;
	int height = m_data.height;
	int tmax = 0;
	//����
	for(int x = 0;x < width;x++)
	{
		for(int y = 0;y < height;y++)
		{
			tmax += m_data.xindex[y][x].value;
			if(tmax > 0)
				break;
		}
		if(tmax == 0)//������ֵ
		{
			CString tstr;
			tstr.Format(_T("���� 0001����Ϊ���� %d ������ȫΪ0��"),x+1);
			for(int y = 0;y < height;y++)
			{
				m_data.data[y][x].value = DVX;
				m_data.data[y][x].colorindex = 1;
				CString tstr2;
				tstr2.Format(_T("���ԣ�λ�� x = %d , y = %d һ��Ϊ��"),x+1,y+1);
				CString tstr3;
				tstr3 = tstr + tstr2 + _T("\n");
				OutputDebugString(tstr3);
				//TRACE(tstr3);
			}
		}
		tmax = 0;
	}
	//���
	for(int y = 0;y < height;y++)
	{
		for(int x = 0;x < width;x++)
		{
			tmax += m_data.yindex[y][x].value;
			if(tmax > 0)
				break;
		}
		if(tmax == 0)//������ֵ
		{
			CString tstr;
			tstr.Format(_T("���� 0001����Ϊ���� %d ������ȫΪ0��"),y+1);
			for(int x = 0;x < width;x++)
			{
				m_data.data[y][x].value = DVX;
				m_data.data[y][x].colorindex = 1;
				CString tstr2;
				tstr2.Format(_T("���ԣ�λ�� x = %d , y = %d һ��Ϊ��"),x+1,y+1);
				CString tstr3;
				tstr3 = tstr + tstr2 + _T("\n");
				OutputDebugString(tstr3);
			}
		}
		tmax = 0;
	}
}

//�ҳ���ȫ�ɿص��У��У�����ֵ	����0002
void GameMaster::Analysis_setfull()
{
	int width = m_data.width;
	int height = m_data.height;
	int tmax = 0;
	bool isbegin = false;
	//����
	for(int x = 0;x < width;x++)
	{
		for(int y = 0;y < height;y++)
		{
			tmax += m_data.xindex[y][x].value;
			if(tmax > 0 && isbegin == false)
			{
				isbegin = true;
			}
			if(isbegin == true && y<height - 1 && m_data.xindex[y][x].value > 0 && m_data.xindex[y+1][x].value > 0)	//û�������ּ���һ�����������һ�����ֺ󲻿�.  ��ֹ�϶���
				tmax++;
		}
		if(tmax == height)//���пɿ�
		{
			CString tstr;
			tstr.Format(_T("���� 0002����Ϊ���� %d ��������ȫ�ɿأ�"),x+1);
			int ty = 0;
			for(int y = 0;y < height;y++)
			{
				int tnum = m_data.xindex[y][x].value;
				if(tnum ==0)//����0��
					continue;
				for(int ti = 0;ti < tnum;ti++)
				{
					m_data.data[ty][x].value = DVYES;
					m_data.data[ty++][x].colorindex = 1;
					CString tstr2;
					tstr2.Format(_T("���ԣ�λ�� x = %d , y = %d һ����ֵ"),x+1,ty);
					CString tstr3;
					tstr3 = tstr + tstr2 + _T("\n");
					OutputDebugString(tstr3);
				}
				if(ty < height)
				{
					m_data.data[ty][x].value = DVX;
					m_data.data[ty++][x].colorindex = 1;
					CString tstr2;
					tstr2.Format(_T("���ԣ�λ�� x = %d , y = %d һ��Ϊ��"),x+1,ty);
					CString tstr3;
					tstr3 = tstr + tstr2 + _T("\n");
					OutputDebugString(tstr3);
				}
			}
		}
		tmax = 0;
		isbegin = false;
	}
	//���
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
			if(isbegin == true && x<width - 1 && m_data.yindex[y][x].value > 0 && m_data.yindex[y][x+1].value > 0)	//û�������ּ���һ�����������һ�����ֺ󲻿�.  ��ֹ�����
				tmax++;
		}
		if(tmax == width)//���пɿ�
		{
			CString tstr;
			int tx = 0;
			tstr.Format(_T("���� 0002����Ϊ���� %d ��������ȫ�ɿأ�"),y+1);
			for(int x = 0;x < width;x++)
			{
				int tnum = m_data.yindex[y][x].value;
				if(tnum ==0)//����0��
					continue;
				for(int ti = 0;ti < tnum;ti++)
				{
					m_data.data[y][tx].value = DVYES;
					m_data.data[y][tx++].colorindex = 1;
					CString tstr2;
					tstr2.Format(_T("���ԣ�λ�� x = %d , y = %d һ����ֵ"),tx,y + 1);
					CString tstr3;
					tstr3 = tstr + tstr2 + _T("\n");
					OutputDebugString(tstr3);
				}
				if(tx < width)
				{
					m_data.data[y][tx].value = DVX;
					m_data.data[y][tx++].colorindex = 1;
					CString tstr2;
					tstr2.Format(_T("���ԣ�λ�� x = %d , y = %d һ��Ϊ��"),tx,y + 1);
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


//��ʼ�� Indexinfo	����0003
void GameMaster::InitIndexInfo()
{
	int width = m_data.width;
	int height = m_data.height;
	int tmax = 0;
	//����
	for(int x = 0;x < width;x++)
	{
		for(int y = 0;y < height;y++)
		{
			if(m_data.xindex[y][x].value > 0)
			{
				m_data.xindexinfo[y][x].isok = false;
				//���ÿ�ʼλ��
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

				//���ý���λ��
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
				tstr.Format(_T("���� 0003��������Ϣ���ϣ���λ�� �� %d �У��� %d �п��÷�ΧΪ %d �е� %d��\n"),x + 1,y + 1,m_data.xindexinfo[y][x].startpos + 1,m_data.xindexinfo[y][x].endpos + 1);
				OutputDebugString(tstr);

				m_data.xindexinfo[y][x].withoutnum = 0;
				m_data.xindexinfo[y][x].withnum = 0;
			}
			else
				m_data.xindexinfo[y][x].isok = true;
		}
	}

	//����
	for(int y = 0;y < height;y++)
	{
		for(int x = 0;x < width;x++)
		{
			if(m_data.yindex[y][x].value > 0)
			{
				m_data.yindexinfo[y][x].isok = false;
				//���ÿ�ʼλ��
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

				//���ý���λ��
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
				tstr.Format(_T("���� 0003��������Ϣ���󣩣�λ�� �� %d �У��� %d �п��÷�ΧΪ %d �е� %d��\n"),y + 1,x + 1,m_data.yindexinfo[y][x].startpos + 1,m_data.yindexinfo[y][x].endpos + 1);
				OutputDebugString(tstr);

				m_data.yindexinfo[y][x].withoutnum = 0;
				m_data.yindexinfo[y][x].withnum = 0;
			}
			else
				m_data.yindexinfo[y][x].isok = true;
		}
	}
}

//���� Indexinfo		����0004
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
				//����(ֻ����ǰ��)
				for(int y = 0;y < height;y++)
				{
					if(m_data.xindexinfo[y][dx].isok == false )//ֻ��δ�����
					{
						if(m_data.xindexinfo[y][dx].startpos <= dy && m_data.xindexinfo[y][dx].endpos >= dy)//���ܷ�Χ��
						{
							if(m_data.data[dy][dx].value == DVYES)
							{
								bool isfound = false;
								for(int i = 0 ;i < m_data.xindexinfo[y][dx].withnum;i++)
								{
									if(m_data.xindexinfo[y][dx].with[i]==dy)//�����б��У�����Ҫ����
										isfound = true;
								}
								if(isfound == false)//�����б��У���Ҫ���
								{
									//20131022 start
									//�ж��������Ƿ�����
									bool isotheruse = false;
									for(int ty = 0; ty < height;ty++)
									{
										if(m_data.xindexinfo[ty][dx].isok == true || ty == y)//�ų��Ѿ�ok�ĵ㣨������ֵ�ĵ㣩�͵�ǰ��
											continue;
										if(m_data.xindexinfo[ty][dx].startpos<= dy && m_data.xindexinfo[ty][dx].endpos>=dy )
											isotheruse = true;//�б�ĵ����õ�ǰ��
									}
									//20131022 end

									if(isotheruse == false)//���������㹫�ô˵�ʱ�����
									{
										m_data.xindexinfo[y][dx].with[m_data.xindexinfo[y][dx].withnum] = dy;
										m_data.xindexinfo[y][dx].withnum++;	//����+1
										CString tstr;
										tstr.Format(_T("���� 0004 �� %d �飺������Ϣ���ϣ���λ�� �� %d �У��� %d ��ȷ��λ����ӣ� %d ��\n"),cnt,dx + 1,y + 1,dy + 1);
										OutputDebugString(tstr);
									}

									if(m_data.xindexinfo[y][dx].withnum > m_data.xindex[y][dx].value)//�����֪�����ֵ
									{
										m_anaiswrong = true;//����
										return;
									}
								}
							}
							else	//DVX
							{
								bool isfound = false;
								for(int i = 0 ;i < m_data.xindexinfo[y][dx].withoutnum;i++)
								{
									if(m_data.xindexinfo[y][dx].without[i]==dy)//�����б��У�����Ҫ����
										isfound = true;
								}
								if(isfound == false)//�����б��У���Ҫ���
								{
									m_data.xindexinfo[y][dx].without[m_data.xindexinfo[y][dx].withoutnum] = dy;
									m_data.xindexinfo[y][dx].withoutnum++;	//����+1

									CString tstr;
									tstr.Format(_T("���� 0004 �� %d �飺������Ϣ���ϣ���λ�� �� %d �У��� %d �з�λ����ӣ� %d ��\n"),cnt,dx + 1,y + 1,dy + 1);
									OutputDebugString(tstr);
								}
							}//if(m_data.data[dy][dx].value == DVYES)

						}//if(m_data.xindexinfo[y][dx].startpos <= dy && m_data.xindexinfo[y][dx].endpos >= dy)//���ܷ�Χ��
					}//if(m_data.xindexinfo[y][dx].isok == false )//ֻ��δ�����
				}//for(int y = 0;y < height;y++)

				//����(ֻ��һ��)
				for(int x = 0;x < width;x++)
				{
					if(m_data.yindexinfo[dy][x].isok == false )//ֻ��δ�����
					{
						if(m_data.yindexinfo[dy][x].startpos <= dx && m_data.yindexinfo[dy][x].endpos >= dx)//���ܷ�Χ��
						{
							if(m_data.data[dy][dx].value == DVYES)
							{
								bool isfound = false;
								for(int i = 0 ;i < m_data.yindexinfo[dy][x].withnum;i++)
								{
									if(m_data.yindexinfo[dy][x].with[i]==dx)//�����б��У�����Ҫ����
										isfound = true;
								}
								if(isfound == false)//�����б��У���Ҫ���
								{
									//20131022 start
									//�ж��������Ƿ�����
									bool isotheruse = false;
									for(int tx = 0; tx < width;tx++)
									{
										if(m_data.xindexinfo[dy][tx].isok == true || tx == x)//�ų��Ѿ�ok�ĵ㣨������ֵ�ĵ㣩�͵�ǰ��
											continue;
										if(m_data.xindexinfo[dy][tx].startpos<= dx && m_data.xindexinfo[dy][tx].endpos>=dx )
											isotheruse = true;//�б�ĵ����õ�ǰ��
									}
									//20131022 end

									if(isotheruse == false)//���������㹫�ô˵�ʱ�����
									{
										m_data.yindexinfo[dy][x].with[m_data.yindexinfo[dy][x].withnum] = dx;
										m_data.yindexinfo[dy][x].withnum++;	//����+1
										CString tstr;
										tstr.Format(_T("���� 0004 �� %d �飺������Ϣ���󣩣�λ�� �� %d �У��� %d ��ȷ��λ����ӣ� %d ��\n"),cnt,dy + 1,x + 1,dx + 1);
										OutputDebugString(tstr);
									}

									if(m_data.yindexinfo[dy][x].withnum > m_data.yindex[dy][x].value)//�����֪�����ֵ
									{
										m_anaiswrong = true;//����
										return;
									}
								}
							}
							else	//DVX
							{
								bool isfound = false;
								for(int i = 0 ;i < m_data.yindexinfo[dy][x].withoutnum;i++)
								{
									if(m_data.yindexinfo[dy][x].without[i]==dx)//�����б��У�����Ҫ����
										isfound = true;
								}
								if(isfound == false)//�����б��У���Ҫ���
								{
									m_data.yindexinfo[dy][x].without[m_data.yindexinfo[dy][x].withoutnum] = dx;
									m_data.yindexinfo[dy][x].withoutnum++;	//����+1
									CString tstr;
									tstr.Format(_T("���� 0004 �� %d �飺������Ϣ���󣩣�λ�� �� %d �У��� %d �з�λ����ӣ� %d ��\n"),cnt,dy + 1,x + 1,dx + 1);
									OutputDebugString(tstr);
								}
							}//if(m_data.data[dy][dx].value == DVYES)

						}//if(m_data.yindexinfo[dy][x].startpos <= dx && m_data.yindexinfo[dy][x].endpos >= dx)//���ܷ�Χ��
					}//if(m_data.yindexinfo[dy][x].isok == false )//ֻ��δ�����
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

//���� indexinfo ���� data ֵ	����0005
void GameMaster::UpdateData(int cnt)
{
	int width = m_data.width;
	int height = m_data.height;

	//����
	for(int x = 0;x < width;x++)
	{
		for(int y = 0;y < height;y++)
		{
			if(m_data.xindexinfo[y][x].isok == true)
				continue;
			//�жϷ�Χ�Ƿ����С
			for(int i = 0;i < m_data.xindexinfo[y][x].withnum;i++)//�ж�ȷ��λ��
			{
				int pos = m_data.xindexinfo[y][x].with[i];
				//�ж��Ƿ���������Ŀ��ܷ�Χ��
				bool isotheruse = false;
				for(int dy = 0; dy < height;dy++)
				{
					if(m_data.xindexinfo[dy][x].isok == true || dy == y)//�ų��Ѿ�ok�ĵ㣨������ֵ�ĵ㣩�͵�ǰ��
						continue;
					for(int tnum = 0;tnum < m_data.xindexinfo[dy][x].withnum;tnum++)
					{
						int tpos = m_data.xindexinfo[dy][x].with[tnum];
						if(tpos == pos)
							isotheruse = true;//�б�ĵ����õ�ǰ��
					}
				}//for(int dy = 0; dy < height;dy++)
				
				if(isotheruse == true)//����б�ĵ����ã�����
					continue;

				// ��С��Χ
				// ���ӣ�����Ϊ����
				// ���ȣ�3
				// λ�ã�0	1	2	3	4	5	6	7	8	9
				//          |                   |
				//        start                end
				//��λ��5ȷ����ֵʱ������ֵΪ3��5��4��6��5��7����Ϊ7 > endֵ(6)������5��7��ȥ��ʵ�ʷ�Χ��Ϊ3~6
				if((pos - m_data.xindex[y][x].value + 1) > m_data.xindexinfo[y][x].startpos)
				{
					m_data.xindexinfo[y][x].startpos = pos - m_data.xindex[y][x].value + 1;
					m_nomorechange = false;
				}

				if((pos + m_data.xindex[y][x].value - 1)>=0 &&(pos + m_data.xindex[y][x].value - 1) < m_data.xindexinfo[y][x].endpos)
				{
					CString tstr;
					tstr.Format(_T("���� 0005 �� %d �飺������Ϣ���ϣ���λ�� �� %d �У��� %d �н���λ���� %d ��� %d\n"),cnt,x + 1,y + 1,m_data.xindexinfo[y][x].endpos + 1,pos + m_data.xindex[y][x].value);
					OutputDebugString(tstr);
					m_data.xindexinfo[y][x].endpos = pos + m_data.xindex[y][x].value - 1;
					m_nomorechange = false;
				}
			}//�ж�ȷ��λ��


			for(int i = 0;i < m_data.xindexinfo[y][x].withoutnum;i++)//�жϷ���λ��
			{
				// ���ӣ�����Ϊ����
				// ���ȣ�3
				// λ�ã�0	1	2	3	4	5	6	7	8	9
				//          |                   |
				//        start                end
				//��λ��4ȷ����ֵʱ�����÷�Χ��Ϊ1��3��5��6��ʵ�ʷ�Χ��Ϊ1~3
				int pos = m_data.xindexinfo[y][x].without[i];
				if((m_data.xindexinfo[y][x].endpos - pos) >= 0 && (m_data.xindexinfo[y][x].endpos - pos) < m_data.xindex[y][x].value)//��������  if(6 - 4 < 3)
				{
					m_data.xindexinfo[y][x].endpos = pos - 1;						//          end = 3
					m_nomorechange = false;
				}
				if((pos - m_data.xindexinfo[y][x].startpos) >= 0 && (pos - m_data.xindexinfo[y][x].startpos)< m_data.xindex[y][x].value)
				{
					CString tstr;
					tstr.Format(_T("���� 0005 �� %d �飺������Ϣ���ϣ���λ�� �� %d �У��� %d �п�ʼλ���� %d ��� %d\n"),cnt,x + 1,y + 1,m_data.xindexinfo[y][x].startpos + 1,pos + 2);
					OutputDebugString(tstr);

					m_data.xindexinfo[y][x].startpos = pos + 1;
					m_nomorechange = false;
				}

			}//�жϷ���λ��
			CString tstr;
			tstr.Format(_T("���� 0005 �� %d �飺������Ϣ���ϣ���λ�� �� %d �У��� %d �з�Χ�� %d �� �� %d ��\n"),cnt,x + 1,y + 1,m_data.xindexinfo[y][x].startpos + 1,m_data.xindexinfo[y][x].endpos + 1);
			OutputDebugString(tstr);

			//�жϷ�Χ���Ƿ񲿷ֻ���ȫ�ɿ�
			int nlen = m_data.xindexinfo[y][x].endpos - m_data.xindexinfo[y][x].startpos + 1;
			// ��ȫ�ɿ����ӣ�����Ϊ����
			// ���ȣ�6
			// λ�ã�0	1	2	3	4	5	6	7	8	9
			//          |                   |
			//        start                end
			if(nlen == m_data.xindex[y][x].value)//��ȫ�ɿ�
			{
				for(int i = m_data.xindexinfo[y][x].startpos;i <= m_data.xindexinfo[y][x].endpos;i++)
				{
					if(m_data.data[i][x].value == DVNO)
					{
						m_data.data[i][x].colorindex = 1;
						m_data.data[i][x].value = DVYES;
						m_nomorechange = false;
						CString tstr;
						tstr.Format(_T("���� 0005 �� %d �飺������Ϣ���ϣ���λ�� �� %d �У��� %d ����ȫ�ɿأ����� %d �У�%d �� ����ֵ\n"),cnt,x + 1,y + 1,x + 1,i + 1);
						OutputDebugString(tstr);
					}
					else if(m_data.data[i][x].value == DVX)	//���������г�ͻ��ʧ��
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
			else if(m_data.xindex[y][x].value == m_data.xindexinfo[y][x].withnum)//��һ����ȫ�ɿ� ��֪�϶���=������
			{
				m_data.xindexinfo[y][x].isok = true;
				//��Χ����������ΪX
				for(int i = m_data.xindexinfo[y][x].startpos;i <=m_data.xindexinfo[y][x].endpos;i++)
				{
					if(m_data.data[i][x].value==DVYES)
						continue;

					//�ж��������Ƿ�����
					bool isotheruse = false;
					for(int dy = 0; dy < height;dy++)
					{
						if(m_data.xindexinfo[dy][x].isok == true || dy == y)//�ų��Ѿ�ok�ĵ㣨������ֵ�ĵ㣩�͵�ǰ��
							continue;
						if(m_data.xindexinfo[dy][x].startpos<= i && m_data.xindexinfo[dy][x].endpos>=i )
							isotheruse = true;//�б�ĵ����õ�ǰ��
						
					}//for(int dy = 0; dy < height;dy++)

					if(isotheruse == false)
					{
						m_data.data[i][x].value=DVX;
						CString tstr;
						tstr.Format(_T("���� 0005 �� %d �飺������Ϣ���ϣ���λ�� �� %d �У��� %d ����ȫ�ɿأ����� %d �У�%d �� ����ֵ\n"),cnt,x + 1,y + 1,x + 1,i + 1);
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
			else if(m_data.xindex[y][x].value * 2 > nlen)//���ֿɿ�
			{
				// ���ֿɿ����ӣ�����Ϊ����
				// ���ȣ�4
				// λ�ã�0	1	2	3	4	5	6	7	8	9
				//         |                    |
				//       start                 end
				//����ʱֵΪ1��4������ʱֵΪ3��6������3��4����һ����ֵ
				for(int i = 0;i <(m_data.xindex[y][x].value * 2 - nlen);i++)//������  for(int i = 0;i < (4*2 - 6);i++)	//i:0~1
				{
					int pos = m_data.xindexinfo[y][x].startpos + (nlen - m_data.xindex[y][x].value)+ i;//������  pos = 1 + (6 - 4) + i  = 3 + i	//pos :3~4
					
					
					if( pos >= 0 && pos<= height &&m_data.data[pos][x].value == DVNO)
					{
						m_data.data[pos][x].colorindex = 1;
						m_data.data[pos][x].value = DVYES;
						m_nomorechange = false;
						CString tstr;
						tstr.Format(_T("���� 0005 �� %d �飺������Ϣ���ϣ���λ�� �� %d �У��� %d �в��ֿɿأ����� %d �У�%d �� ����ֵ\n"),cnt,x + 1,y + 1,x + 1,pos + 1);
						OutputDebugString(tstr);
					}
					else if(m_data.data[pos][x].value == DVX)	//���������г�ͻ��ʧ��
					{
						m_anaiswrong = true;
						return;
					}
				}//for end
			}//if~else if end(��ȫ�����ֿɿ��ж�)
		}//yѭ������
	}//xѭ������
	CleanData(cnt);//ˢ�²��ø�
	//��������
	/////////////////////////////////////////////////////////////////////////////////////////////
	//��ߵı�
	for(int y = 0;y < height;y++)
	{
		for(int x = 0;x < width;x++)
		{
			if(m_data.yindexinfo[y][x].isok == true)
				continue;
			//�жϷ�Χ�Ƿ����С
			for(int i = 0;i < m_data.yindexinfo[y][x].withnum;i++)//�ж�ȷ��λ��
			{
				int pos = m_data.yindexinfo[y][x].with[i];
				//�ж��Ƿ���������Ŀ��ܷ�Χ��
				bool isotheruse = false;
				for(int dx = 0; dx < width;dx++)
				{
					if(m_data.yindexinfo[y][dx].isok == true || dx == x)//�ų��Ѿ�ok�ĵ㣨������ֵ�ĵ㣩�͵�ǰ��
						continue;
					for(int tnum = 0;tnum < m_data.yindexinfo[y][dx].withnum;tnum++)
					{
						int tpos = m_data.yindexinfo[y][dx].with[tnum];
						if(tpos == pos)
							isotheruse = true;//�б�ĵ����õ�ǰ��
					}
				}//for(int dx = 0; dx < width;dx++)
				
				if(isotheruse == true)//����б�ĵ����ã�����
					continue;

				// ��С��Χ
				// ���ӣ�����Ϊ����
				// ���ȣ�3
				// λ�ã�0	1	2	3	4	5	6	7	8	9
				//         |                    |
				//        start                end
				//��λ��5ȷ����ֵʱ������ֵΪ3��5��4��6��5��7����Ϊ7 > endֵ(6)������5��7��ȥ��ʵ�ʷ�Χ��Ϊ3~6
				if((pos - m_data.yindex[y][x].value + 1) > m_data.yindexinfo[y][x].startpos)
				{
					m_data.yindexinfo[y][x].startpos = pos - m_data.yindex[y][x].value + 1;
					m_nomorechange = false;
				}

				if((pos + m_data.yindex[y][x].value - 1)>= 0 && ((pos + m_data.yindex[y][x].value - 1)) < m_data.yindexinfo[y][x].endpos)
				{
					CString tstr;
					tstr.Format(_T("���� 0005 �� %d �飺������Ϣ���󣩣�λ�� �� %d �У��� %d �н���λ���� %d ��� %d\n"),cnt,x + 1,y + 1,m_data.yindexinfo[y][x].endpos + 1,pos + m_data.yindex[y][x].value);
					OutputDebugString(tstr);

					m_data.yindexinfo[y][x].endpos = pos + m_data.yindex[y][x].value - 1;
					m_nomorechange = false;
				}
			}//�ж�ȷ��λ��


			for(int i = 0;i < m_data.yindexinfo[y][x].withoutnum;i++)//�жϷ���λ��
			{
				// ���ӣ�����Ϊ����
				// ���ȣ�3
				// λ�ã�0	1	2	3	4	5	6	7	8	9
				//         |                    |
				//        start                end
				//��λ��4ȷ����ֵʱ�����÷�Χ��Ϊ1��3��5��6��ʵ�ʷ�Χ��Ϊ1~3
				int pos = m_data.yindexinfo[y][x].without[i];
				if((m_data.yindexinfo[y][x].endpos - pos)>=0 && (m_data.yindexinfo[y][x].endpos - pos) < m_data.yindex[y][x].value)//��������  if(6 - 4 < 3)
				{
					m_data.yindexinfo[y][x].endpos = pos - 1;						//          end = 3
					m_nomorechange = false;
				}
				if((pos - m_data.yindexinfo[y][x].startpos) >=0 && (pos - m_data.yindexinfo[y][x].startpos) < m_data.yindex[y][x].value)
				{
					CString tstr;
					tstr.Format(_T("���� 0005 �� %d �飺������Ϣ���󣩣�λ�� �� %d �У��� %d �п�ʼλ���� %d ��� %d\n"),cnt,x + 1,y + 1,m_data.yindexinfo[y][x].startpos,pos + 2);
					OutputDebugString(tstr);

					m_data.yindexinfo[y][x].startpos = pos + 1;
					m_nomorechange = false;
				}

			}//�жϷ���λ��
			CString tstr;
			tstr.Format(_T("���� 0005 �� %d �飺������Ϣ���󣩣�λ�� �� %d �У��� %d �з�Χ�� %d �� �� %d ��\n"),cnt,y + 1,x + 1,m_data.yindexinfo[y][x].startpos + 1,m_data.yindexinfo[y][x].endpos + 1);
			OutputDebugString(tstr);

			//�жϷ�Χ���Ƿ񲿷ֻ���ȫ�ɿ�
			int nlen = m_data.yindexinfo[y][x].endpos - m_data.yindexinfo[y][x].startpos + 1;
			// ��ȫ�ɿ����ӣ�����Ϊ����
			// ���ȣ�6
			// λ�ã�0	1	2	3	4	5	6	7	8	9
			//          |                   |
			//        start                end
			if(nlen == m_data.yindex[y][x].value)//��ȫ�ɿ�
			{
				for(int i = m_data.yindexinfo[y][x].startpos;i <= m_data.yindexinfo[y][x].endpos;i++)
				{
					if(m_data.data[y][i].value == DVNO)
					{
						m_data.data[y][i].colorindex = 1;
						m_data.data[y][i].value = DVYES;
						CString tstr;
						tstr.Format(_T("���� 0005 �� %d �飺������Ϣ���󣩣�λ�� �� %d �У��� %d ����ȫ�ɿأ����� %d �У�%d �� ����ֵ\n"),cnt,y + 1,x + 1,y + 1,i + 1);
						OutputDebugString(tstr);
						m_nomorechange = false;
					}
					else if(m_data.data[y][i].value == DVX)	//���������г�ͻ��ʧ��
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
			else if(m_data.yindex[y][x].value == m_data.yindexinfo[y][x].withnum)//��һ����ȫ�ɿ� ��֪�϶���=������
			{
				m_data.yindexinfo[y][x].isok = true;
				//��Χ����������ΪX
				for(int i = m_data.yindexinfo[y][x].startpos;i <=m_data.yindexinfo[y][x].endpos;i++)
				{
					if(m_data.data[y][i].value==DVYES)
						continue;

					//�ж��������Ƿ�����
					bool isotheruse = false;
					for(int dx = 0; dx < width;dx++)
					{
						if(m_data.yindexinfo[y][dx].isok == true || dx == x)//�ų��Ѿ�ok�ĵ㣨������ֵ�ĵ㣩�͵�ǰ��
							continue;
						if(m_data.yindexinfo[y][dx].startpos<= i && m_data.yindexinfo[y][dx].endpos>=i )
							isotheruse = true;//�б�ĵ����õ�ǰ��
						
					}//for(int dx = 0; dx < width;dx++)

					if(isotheruse == false)
					{
						m_data.data[y][i].value=DVX;
						CString tstr;
						tstr.Format(_T("���� 0005 �� %d �飺������Ϣ���󣩣�λ�� �� %d �У��� %d ����ȫ�ɿأ����� %d �У�%d �� ����ֵ\n"),cnt,x + 1,y + 1,x + 1,i + 1);
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
			else if(m_data.yindex[y][x].value * 2 > nlen)//���ֿɿ�
			{
				// ���ֿɿ����ӣ�����Ϊ����
				// ���ȣ�4
				// λ�ã�0	1	2	3	4	5	6	7	8	9
				//          |                   |
				//        start                end
				//����ʱֵΪ1��4������ʱֵΪ3��6������3��4����һ����ֵ
				for(int i = 0;i <(m_data.yindex[y][x].value * 2 - nlen);i++)//������  for(int i = 0;i < (4*2 - 6);i++)	//i:0~1
				{
					int pos = m_data.yindexinfo[y][x].startpos + (nlen - m_data.yindex[y][x].value)+ i;//������  pos = 1 + (6 - 4) + i  = 3 + i	//pos :3~4
					if(pos >= 0 && pos <= width && m_data.data[y][pos].value != DVNO)
					{
						m_data.data[y][pos].colorindex = 1;
						m_data.data[y][pos].value = DVYES;
						m_nomorechange = false;
						CString tstr;
						tstr.Format(_T("���� 0005 �� %d �飺������Ϣ���󣩣�λ�� �� %d �У��� %d �в��ֿɿأ����� %d �У�%d �� ����ֵ\n"),cnt,y + 1,x + 1,y + 1,pos + 1);
						OutputDebugString(tstr);
					}
					else if(m_data.data[y][pos].value == DVX)	//���������г�ͻ��ʧ��
					{
						m_anaiswrong = true;
						return;
					}
				}//for end
			}//if~else if end(��ȫ�����ֿɿ��ж�)
		}//xѭ������
	}//yѭ������
	CleanData(cnt);//ˢ�²��ø�
	//��������

}


//�Ѳ����κε㷶Χ�ڵķ�����X	����0006	

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
				//����
				for(int dy = 0;dy < height;dy++)
				{
					if(m_data.xindexinfo[dy][x].isok == true)
						continue;
					if(m_data.xindexinfo[dy][x].startpos <= y && m_data.xindexinfo[dy][x].endpos >= y)
						isyused = true;
				}

				//���� 
				for(int dx = 0;dx < width;dx++)
				{
					if(m_data.yindexinfo[y][dx].isok == true)
						continue;
					if(m_data.yindexinfo[y][dx].startpos <= x && m_data.yindexinfo[y][dx].endpos >= x)
						isxused = true;
				}

				if(isyused == false || isxused == false)//�����������һ�����õģ���Ϊ��
				{
					if(m_data.data[y][x].value != DVX)
					{
						m_data.data[y][x].value = DVX;
						m_nomorechange = false;
						CString tstr;
						tstr.Format(_T("���� 0006 �� %d �飺��Ϊ����ʹ�ã�λ�� �� %d �У��� %d �б���ֵ\n"),cnt,y + 1,x + 1);
						OutputDebugString(tstr);
					}

					//������һ����
					if(isyused == true)//�����Ϸ�������ʹ��
					{
						for(int dy = 0;dy < height;dy++)//������
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

								if(isinwithout == false)//��ӵ� without �б�
								{
									m_data.xindexinfo[dy][x].without[m_data.xindexinfo[dy][x].withoutnum] = y;
									m_data.xindexinfo[dy][x].withoutnum++;

									CString tstr;
									tstr.Format(_T("���� 0006 �� %d �飺������Ϣ���ϣ���λ�� �� %d �У��� %d �з�λ����ӣ� %d ��\n"),cnt,x + 1,dy + 1,y + 1);
									OutputDebugString(tstr);
								}

							}//end if(m_data.xindexinfo[dy][x].startpos <= y && m_data.xindexinfo[dy][x].endpos >= y)
						}// end for(int dy = 0;dy < height;dy++)//������
					}//end if(isyused == true)//�����Ϸ�������ʹ��

					if(isxused == true)//�����󷽱�����ʹ��
					{
						for(int dx = 0;dx < width;dx++)//������
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

								if(isinwithout == false)//��ӵ� without �б�
								{
									m_data.yindexinfo[y][dx].without[m_data.yindexinfo[y][dx].withoutnum] = x;
									m_data.yindexinfo[y][dx].withoutnum++;

									CString tstr;
									tstr.Format(_T("���� 0006 �� %d �飺������Ϣ���󣩣�λ�� �� %d �У��� %d �з�λ����ӣ� %d ��\n"),cnt,y + 1,dx + 1,x + 1);
									OutputDebugString(tstr);
								}

							}//end if(m_data.yindexinfo[y][dx].startpos <= x && m_data.yindexinfo[y][dx].endpos >= x)
						}// end for(int dx = 0;dx < width;dx++)//������
					}//end if(isxused == true)//�����Ϸ�������ʹ��
				}
			}
		}
	}
}


//����ĳ����ֵ�������Ƶ�		����0007
void GameMaster::Analysis_IF(int cnt)
{

	int width = GetPuzzleWidth();
	int height = GetPuzzleHeight();
	//��������
	//Index tempdata[MAXY][MAXX];		//��ʱ���������ݣ��Զ��Ƶ��ã�
	//Indexinfo xinfot[MAXY][MAXX];	//�����ϱߵ�ֵ���Զ��Ƶ������ã�
	//Indexinfo yinfot[MAXY][MAXX];	//������ߵ�ֵ���Զ��Ƶ������ã�

	//�ٴ�ͳ����ˡ���
	Index tempdata[15][15];		//��ʱ���������ݣ��Զ��Ƶ��ã�
	Indexinfo xinfot[15][15];	//�����ϱߵ�ֵ���Զ��Ƶ������ã�
	Indexinfo yinfot[15][15];	//������ߵ�ֵ���Զ��Ƶ������ã�


	CString ustr;
	ustr.Format(_T("��ǰ����Ϊ��%d\n"),cnt);
	if(cnt == 20)
	{
		int lsdjfjshjakjsdfnlasdhjf = 0;
	}
	OutputDebugString(ustr);
	ustr.Format(_T("��ǰ״̬Ϊ��\n"));
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


	//�������
	//bool ismisoka = IsPuzzleSolve();
	//if(ismisoka == true)
	//	return;

	for(int y = 0;y < height;y++ )
	{
		for(int x = 0;x < width;x++)
		{
			//����
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

	//����޷���������
	for(int y = 0;y < height;y++ )
	{
		for(int x = 0;x < width;x++)
		{
			if(m_data.data[y][x].value==DVNO)
			{
				m_data.data[y][x].value=DVYES;
				m_data.data[y][x].colorindex = 1;

				CString tstr;
				tstr.Format(_T("���� 0007 ���� �� %d �У��� %d �� ��ֵ����ʼ\n"),y + 1,x + 1);
				OutputDebugString(tstr);

				
				tstr.Format(_T("��ǰ״̬Ϊ��\n"));
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
					tstr.Format(_T("���� 0000 �� %d �鿪ʼ\n"),cnt);
					OutputDebugString(tstr);

					m_nomorechange = true;
					UpdateIndexInfo(cnt);//0004
					UpdateData(cnt);	//0005
					ismisok = IsPuzzleSolve();
					cnt++;
				}
				if(ismisok == false && m_anaiswrong == false)//δ�⿪����������
				{
					CString tstr;
					tstr.Format(_T("���� 0007 ѭ�����������⻹û�⿪����������\n"));
					OutputDebugString(tstr);

					//���迪ʼ
					cnt++;
					Analysis_IF(cnt);
					ismisok = IsPuzzleSolve();
				}

				if(ismisok == true)	//�⿪������
				{
					CString tstr;
					tstr.Format(_T("���� 0007 �ѽ⿪\n"));
					OutputDebugString(tstr);
					return;
				}
				else
				{
					CString tstr;

					tstr.Format(_T("���� 0007 δ�⿪������ʧ�ܣ��������Ϊ��\n"));
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
					}//���ݻָ���Ϣ


					tstr.Format(_T("���� 0007 ������һ�μ���\n"));
					OutputDebugString(tstr);

					tempdata[y][x].value=DVX;//���÷�ֵ
					for(int ty = 0;ty < height;ty++ )
					{
						for(int tx = 0;tx < width;tx++)
						{
							//����
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

					

					tstr.Format(_T("���ݻָ�Ϊ��\n"));
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
					}//���ݻָ���Ϣ
				}//δ�⿪
			}//�ø���Լ���
		}//x
	}//y
	bool ismisok = IsPuzzleSolve();
	if(ismisok == false)
	{
		CString tstr;
		tstr.Format(_T("����û�н⿪\n"));
		OutputDebugString(tstr);
	}
}