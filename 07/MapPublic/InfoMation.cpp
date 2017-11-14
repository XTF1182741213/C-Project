// InfoMation.cpp: implementation of the CInfoMation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MapPublic.h"
#include "InfoMation.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//CMapPublicApp *app=(CMapPublicApp *)AfxGetApp();
CInfoMation::CInfoMation()
{
	Num_BusRoad=0;
	s_road=e_road=0;
    Num=0;
	m_percept="";
}

CInfoMation::~CInfoMation()
{

}


double CInfoMation::CalcScale(CMap1* map)
{
	HWND hWnd = (HWND)map->GetHWnd();
	HDC hDC = GetDC(hWnd);
	double dpix = GetDeviceCaps(hDC, LOGPIXELSX);
	
	MPoint* pts = new MPoint[2];
	CMoRectangle extent = map->GetExtent();
	pts[0].x = extent.GetLeft();
	pts[0].y = extent.GetTop();
	pts[1].x = extent.GetRight();
	pts[1].y = extent.GetTop();
	// ����pts��������鶨��ĵ�֮��ĳ���
	double dLen1 = CalcLenght(pts,2);
	CRect rect;
	map->GetWindowRect(&rect);
	double dLen2 = rect.Width() / dpix * 2.54 /100;

	delete pts;
	pts = NULL;

	return dLen1 / dLen2;
}
//-----------------------------------------------------------------------------------------
// ����һ���ߵĳ���
// ����MPoint*��ʾһ���������
// ����nSize��ʾ����������е����ĸ���
// ����ֵΪ�ߵĳ���
double CInfoMation::CalcLenght(MPoint* pt,int nSize)
{
	double dLength = 0;
	double x1=0,x2=0,y1=0,y2=0;
	int nCenterL = ((int)(pt[0].x)/6+1)*6-3; 

	for(int i=0;i<nSize-1;i++)
	{
		CalGuassFromLB(pt[i].x, pt[i].y, &x1, &y1, nCenterL);
		CalGuassFromLB(pt[i+1].x, pt[i+1].y, &x2, &y2, nCenterL);
		dLength += sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
	}

	return dLength;
}
void CInfoMation::CalGuassFromLB(double dLongitude, double dLatitude, 
								  double* dX, double* dY, long nCenterL)
{			
	int CenterL = (int)nCenterL;

	SubGussFs(dX, dY, dLatitude, dLongitude, CenterL);
	nCenterL = (long)CenterL;
}
//-----------------------------------------------------------------------------------------
void CInfoMation::SubGussFs(double X,double Y,double L0, double* B, double* L)
{
	double p=57.29577951472;
	const double a=6.378245000e+06;
	const double e2=0.00669342162297;
	const double e12=0.00673852541468;
	const double c0=0.157046064172e-06;
	const double c1=0.005051773759;
	const double c2=0.000029837302;
	const double c3=0.000000238189;

	double bf0 = c0*X;
	double bf0c = cos(bf0);
	double bf0s = sin(bf0);
	double bf = bf0 + bf0c * (c1 * bf0s - c2 * pow(bf0s, 3) + c3 * pow(bf0s, 5));
	double bt = tan(bf);
	double bc = cos(bf);
	double bs = sin(bf);
	double bi = e12 * pow(bc,2);
	double v2 = 1.0e+0 +bi;
	double bn = a/sqrt(1.0-e2* pow(bs,2));
	double yn=Y/bn;

	// ����γ��
	double b1 = -v2 * bt * pow(yn, 2) / 2.0;
	double b2 = -(5.0 + 3.0 * pow(bt, 2) + bi - 9.0 * bi* pow(bt, 2)) 
		        * b1 * pow(yn, 2) / 12.0;
	double b3 = (61.0 + 90.0 * pow(bt, 2) + 45.0 * pow(bt, 4)) * b1 * pow(yn, 4)/ 360.0;
	*B = bf + b1 + b2 + b3;
	*B = *B * p;

	// ���㾭��
	double l1 = yn/bc;
	double l2 = -(1.0 + 2.0 * pow(bt, 2) + bi) * l1 * pow(yn, 2) / 6.0;
	double l3 = (5.0 + 28.0 * pow(bt , 2) + 24.0 * pow(bt, 4) 
		         + 6.0 * bi + 8.0 * bi * pow(bt, 2)) 
				 * l1 * pow(yn, 4) / 120.0;
	*L = l1 + l2 + l3;
	*L = *L * p;

	*L += L0;
	if(*L > 360.0)
		*L -= 360.0;
}
//-----------------------------------------------------------------------------------------
void CInfoMation::SubGussFs(double* X, double* Y,double B,double L,int nCenterLongi)
{
	//��˹ͶӰ�ִ�
	int nzonenum;
	if(nCenterLongi==0)
	{
		nzonenum = (int)L/6+1;
		nCenterLongi = nzonenum*6-3;
	}
	else
		nzonenum = (int)nCenterLongi/6+1;

	//�Ի���Ϊ��λ�ľ�γ����ֵ
	double rB = B / 180 * 3.1415926;
	double rL = (L - nCenterLongi) / 180 * 3.1415926;		//ͬʱ���������뾭��
	//1980����ϵ����
	const double a = 6378245.00;		//����
	const double b = 6356863.50;		//����
	double sqre1 = ( a * a - b * b) / ( a * a);	//��һƫ����ƽ��
	//B:γ��
	//L:����
	//����Ȧ���ʰ뾶
	double sinb = sin(rB);
	double cosb = cos(rB);
	double M = a *(1 - sqre1) / (1 - sqre1 * sinb * sinb) / sqrt( 1 - sqre1 * sinb * sinb);
	//î��Ȧ���ʰ뾶
	double N = a / sqrt(1 - sqre1 * sinb * sinb);
	double sqrita = N / M - 1;

	//��γ�ȵ㵽����������߻���
	double s = a * (1 - sqre1 ) * (1.00505117739 * rB - 0.00506237764 / 2 
		        * sin(2*rB) + 0.0000106245 / 4 * sin(4*rB) - 0.00000002081 / 
				6 * sin(6 * rB));

	double tanb = tan(rB);
	*X = s + rL * rL * N / 2 * sinb * cosb + rL * rL * rL * rL * N / 24 
		 * sinb * cosb * cosb *cosb * (5 - tanb * tanb + 9 * sqrita * sqrita + 4 * sqrita);
	*Y = rL * N * cosb + rL * rL * rL * N / 6 * cosb * cosb * cosb * 
		(1 - tanb * tanb + sqrita) + rL * rL * rL * rL * rL * N / 120 
		* cosb * cosb * cosb * cosb * cosb * 
		(5 - 18 * tanb * tanb + tanb * tanb * tanb * tanb);
	*Y = *Y + 500000 + nzonenum * 1.0e+6;
}
//-----------------------------------------------------------------------------------------

//*********************************************************
void CInfoMation::Init()
{
	m_BusInfo[0].RoadWay="-1";
	m_BusInfo[0].StationName="";
	m_BusInfo[1].RoadWay="-2";
	m_BusInfo[1].StationName="";
	busnum=0;
	startflag=false;

}
BOOL CInfoMation::Query(CWnd *pwnd,CString start,CString end)
{
	Num=0;
	CMapPublicApp *app=(CMapPublicApp *)AfxGetApp();
	app->m_show="";
	Num_BusRoad=0;
	s_road=e_road=0;
   if(Same_RoadWay(pwnd,start,end))
	{
		app->m_show+="\r\n�Ƽ�����������"+BestMode();
	    return 1;
	}
   else  if(!Dif_RoadWay(start,end))
	{
		AfxMessageBox("�˷��������ڣ�");
         return 0;
	}
	app->m_show+="\r\n�Ƽ�����������"+BestMode();
	return 1;
}
//----------------------------------------------------
BOOL CInfoMation::Same_RoadWay(CWnd *pwnd,CString start,CString end)
{
	CString str,m_sNum;//��ʾ�˳�����
	CStationSet m_StationSet;
	CMapPublicApp *app=(CMapPublicApp *)AfxGetApp();
	Init();
	if(!m_StationSet.IsOpen())
		m_StationSet.Open();
    m_StationSet.MoveFirst();
	while(!m_StationSet.IsEOF())
	{
		if(m_StationSet.m_STATION==start)//��ʼվ
		{
			startflag=!startflag;
			m_BusInfo[0].RoadWay=m_StationSet.m_ID;
			m_station=m_StationSet.m_ID;
			m_BusInfo[0].StationName=m_StationSet.m_STATION;
		}
		else if(m_StationSet.m_STATION==end)//Ŀ��վ
		{
			startflag=!startflag;
			m_BusInfo[1].RoadWay=m_StationSet.m_ID;
			m_station=m_StationSet.m_ID;
		    m_BusInfo[1].StationName=m_StationSet.m_STATION;
		}
		if(m_BusInfo[1].RoadWay==m_BusInfo[0].RoadWay)
		{
		    str.Format("\r\n����%d����%s�� %s· ����%s�³�",Num,start,m_BusInfo[0].RoadWay,end);
	        app->m_show+=str;
			m_BusRoad[Num_BusRoad].Precept=Num++;
            m_BusRoad[Num_BusRoad++].Number=busnum;//��¼����������վ����
			Init();
          
		}
		//---------------------------------
		//����վ��ͳ��
		if(startflag)
		{			
			if(m_StationSet.m_ID!=m_station)
				busnum=0;
			else
				busnum++;
		}
		//-----------------------------------------
		m_StationSet.MoveNext();
		
	}
	if(app->m_show!="")
		return 1;
	
	if(m_StationSet.IsEOF())
	{
	   return 0;
	}
	else return 1;
	
}
CString CInfoMation::BestMode()//�ҳ���ѳ˳���ʽ
{
	int n=m_BusRoad[0].Number,j=m_BusRoad[0].Precept;
    for(int i=0;i<Num_BusRoad;i++)
	{	
	   if(m_BusRoad[i].Number<n)
	   {
		   n=m_BusRoad[i].Number;
		   j=m_BusRoad[i].Precept;
	   }
	}
	CString str;
	str.Format("%d",j);
	return str;
}
//-------------------------------------------------------
BOOL CInfoMation::Dif_RoadWay(CString start,CString end)
{CString str;
    CStationSet m_StationSet;
	if(!m_StationSet.IsOpen())
		m_StationSet.Open();
    m_StationSet.MoveFirst();
	while(!m_StationSet.IsEOF())
	{
		if(m_StationSet.m_STATION==start)
	    	S_RoadWay[s_road++]=m_StationSet.m_ID;
		else if(m_StationSet.m_STATION==end)
	    	E_RoadWay[e_road++]=m_StationSet.m_ID;
		m_StationSet.MoveNext();
	}
	m_StationSet.Close();
	return Precept(start,end);
	
    
}
BOOL CInfoMation::Precept(CString start,CString end)
{
	CString str;
	CStationSet m_StationSet;
	CMapPublicApp *app=(CMapPublicApp *)AfxGetApp();
	if(!m_StationSet.IsOpen())
		    m_StationSet.Open();
		m_StationSet.MoveFirst();
	for(int i=0;i<s_road;i++)
	{
		
		while(!m_StationSet.IsEOF())
		{
			if(m_StationSet.m_ID==S_RoadWay[i])
			{
				if(Match(m_StationSet.m_ID,m_StationSet.m_STATION))//����ʼվ��ĳ��κ͸ó��ε�ÿһվ����Ŀ�ĳ��ε�ÿһվ��Ƚ�
				{
					str.Format("\r\n����%d�� ��%s�� %s· �� %sת�� %s· ��%s�³�",Num,start,m_StationSet.m_ID,m_StationSet.m_STATION,m_percept,end);
					app->m_show+=str;
					m_BusRoad[Num_BusRoad].Precept=Num++;
                    m_BusRoad[Num_BusRoad++].Number=Dif_StationNum(start,m_StationSet.m_ID,m_StationSet.m_STATION,m_percept,end);
					//��¼����������վ����
					m_percept="";
					break;
				}

			}
			m_StationSet.MoveNext();

		}
		
      
	}
	m_StationSet.Close();
    if(str!="")
		return 1;
	else
		return 0;

}
BOOL CInfoMation::Match(CString percept,CString station)
{
	CStationSet m_StationSet;
	bool flag=false;
	if(!m_StationSet.IsOpen())
		m_StationSet.Open();
	 for(int i=0;i<e_road;i++)
	 {
		 m_StationSet.MoveFirst();
	 while(!m_StationSet.IsEOF())
	 {
		 if(m_StationSet.m_ID==E_RoadWay[i]&&m_StationSet.m_ID!=percept&&m_StationSet.m_STATION==station)
		 {
			 m_percept=m_StationSet.m_ID;
			 flag=true;
			 return 1;
		 }
		 else
			 m_StationSet.MoveNext();
	 }
	 
	 }
   if(!flag)
	   return 0;
   else 
	   return 1;
}
//��s_start�� first_roadway· �� s_middleת�� second_roadway· ��s_end�³�
int CInfoMation::Dif_StationNum(CString s_start,CString first_roadway,CString s_middle,CString second_roadway,CString s_end)
{
	return Num_Station(s_start,first_roadway,s_middle)+Num_Station(s_middle,second_roadway,s_end);

}
int CInfoMation::Num_Station(CString s_start,CString roadway,CString s_end)
{
	CStationSet m_StationSet;
	bool flag=false;
	Init();
	if(!m_StationSet.IsOpen())
		m_StationSet.Open();
    m_StationSet.MoveFirst();
	while(!m_StationSet.IsEOF())
	{
		if(m_StationSet.m_ID==roadway)
		{
			if(m_StationSet.m_STATION==s_start||m_StationSet.m_STATION==s_end)
				flag=!flag;
			if(flag)
			 busnum++;
		}
		m_StationSet.MoveNext();
	}
	m_StationSet.Close();
	return busnum;


}
//*************************************************************
