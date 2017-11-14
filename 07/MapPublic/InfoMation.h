// InfoMation.h: interface for the CInfoMation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFOMATION_H__2AC3BA67_7EAB_4FFE_BD64_32C89633CD73__INCLUDED_)
#define AFX_INFOMATION_H__2AC3BA67_7EAB_4FFE_BD64_32C89633CD73__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "morectangle.h"
#include "math.h"
#include "StationSet.h"
#include "InfoMation.h"
#include "MapPublic.h"
#define MAX 80
//��ͼ�ϵĵ�
struct MPoint
{
	double x;
	double y;

};

//ͼ����Ϣ
struct LayerInfo
{
	CString szLayerName;   // ͼ������
	int index;//ͼ����
	bool bLable;           // �Ƿ�Ϊ�������ע��
	bool bVisible;//�Ƿ�ɼ�
};
//������վ����Ϣ
struct BusInfo
{
	CString RoadWay;//����
	CString StationName;//վ������
};
struct BestMode//�˳�����
{
	int Precept;//������
	int Number;//����������������վ�����
};


class CInfoMation  
{
public:
	CInfoMation();
	virtual ~CInfoMation();

public:

	//******************************************
	//���������
	double CalcScale(CMap1* map);
	double CalcLenght(MPoint* pt,int nSize);
    void CalGuassFromLB(double dLongitude, double dLatitude, 
								  double* dX, double* dY, long nCenterL);
    void SubGussFs(double X,double Y,double L0, double* B, double* L);
    void SubGussFs(double* X, double* Y,double B,double L,int nCenterLongi);
	//*********************************************


	//*************************************************************
//��������
	
	BusInfo m_BusInfo[2];
	BestMode m_BusRoad[MAX];//�˳�����
	int Num_BusRoad;//��¼���������Ĺ���·��
	int busnum;//��վ���ۼ�
	bool startflag;//��ʼվ�Ŀ���
	int Num;//�������
	CString m_station;//վ��洢
	CString S_RoadWay[MAX];//�洢����ĳһվ������г���
	CString E_RoadWay[MAX];
	int s_road;//�Ծ�����ʼվ�ĳ����ۼ�
	int e_road;
	CString m_percept;//����վ��
	void Init();//��ʼ��
	BOOL Query(CWnd *pwnd,CString start,CString end);//��ѯ����
    BOOL Same_RoadWay(CWnd *pwnd,CString start,CString end);//ͬһ����
	BOOL Dif_RoadWay(CString start,CString end);//һ��ת��
	BOOL Precept(CString start,CString end);//���ɳ˳�����
	BOOL Match(CString percept,CString station);//վ��ƥ��
	int Dif_StationNum(CString s_start,CString first_roadway,CString s_middle,CString second_roadway,CString s_end);
	//����˵������%s�� %s· �� %sת�� %s· ��%s�³�
	int Num_Station(CString s_start,CString roadway,CString s_end);//����ͬһ��·�������վ����
	CString BestMode();//Ѱ�����ŷ���
   //*****************************************************************
};








#endif // !defined(AFX_INFOMATION_H__2AC3BA67_7EAB_4FFE_BD64_32C89633CD73__INCLUDED_)
