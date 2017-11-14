// PAGE3.cpp : implementation file
//

#include "stdafx.h"
#include "LICAI.h"
#include "PAGE3.h"
#include "LCSet.h"
#include "VcPlot.h"
#include "VcAxis.h"
#include "VcValueScale.h"
#include "VcSeriesCollection.h"
#include "VcSeries.h"
#include "VcPen.h"
#include "VcCategoryScale.h"
#include "VcColor.h"
#include "VcDataGrid.h"
#include "VcBackdrop.h"
#include "VcFill.h"
#include "VcBrush.h"
#include "VcDataPoints.h"
#include "VcDataPoint.h"
#include "VcDataPointLabel.h"
#include "VcAxisTitle.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PAGE3 dialog


PAGE3::PAGE3(CWnd* pParent /*=NULL*/)
	: CDialog(PAGE3::IDD, pParent)
{
	//{{AFX_DATA_INIT(PAGE3)
	//}}AFX_DATA_INIT
}


void PAGE3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PAGE3)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PAGE3, CDialog)
	//{{AFX_MSG_MAP(PAGE3)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_DRAWLINE, OnDrawline)
	ON_BN_CLICKED(IDC_DRAWCOMBI, OnDrawcombi)
	ON_BN_CLICKED(IDC_DRAWPIE, OnDrawpie)
//	ON_COMMAND_RANGE(IDC_DRAWLINE,IDC_DRAWPIE,)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PAGE3 message handlers

BOOL PAGE3::OnInitDialog() 
{
	CDialog::OnInitDialog();

		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int PAGE3::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	CRect rc1;
	GetClientRect(&rc1);
	CRect rc(rc1.left,rc1.top,rc1.right,rc1.bottom-50);
	WCHAR pwchLicenseKey[] =
	{
		    0x0038, 0x0045, 0x0031, 0x0034, 0x0037, 0x0043,    
			0x0036, 0x0039, 0x002D, 0x0042, 0x0044, 0x0035,    
			0x0030, 0x002D, 0x0031, 0x0031, 0x0064, 0x0031,    
			0x002D, 0x0042, 0x0031, 0x0033, 0x0037, 0x002D,    
			0x0030, 0x0030, 0x0030, 0x0030, 0x0046, 0x0038,    
			0x0037, 0x0035, 0x0033, 0x0046, 0x0035, 0x0044
	};
	BSTR bstrLicense = ::SysAllocStringLen(pwchLicenseKey,sizeof(pwchLicenseKey)/sizeof(WCHAR));
	BOOL bResult = m_Chart.Create("mschart", WS_CHILD| WS_VISIBLE, rc, this, 20000, NULL, FALSE, bstrLicense);
	::SysFreeString(bstrLicense);
	InitChart();
	DrawChart();	
	return 0;
}

void PAGE3::DrawChart()
{
	LCSet mySet;
	mySet.Open();
	mySet.MoveFirst();
	int incomenum=0,costnum=0,total;//incomenum��ʾ�����룬costnum��ʾ֧����Ŀ��total��ʾʣ�����Ŀ
	while(!mySet.IsEOF())
	{   
		incomenum+=mySet.m_incomenum;
		costnum+=mySet.m_costnum;
		mySet.MoveNext();
	}
	total=incomenum-costnum;
	if(mySet.IsOpen())
		mySet.Close();
	mySet.Open();
	bool tflag1,tflag2,tflag3;   //���Ƿֱ������ж��Ƿ������ַ���ƥ��
	mySet.Requery();
	int incomenum1=0,costnum1=0,total1=0,incomenum2=0;
	int costnum2=0,total2=0,incomenum3=0,costnum3=0,total3=0;
	COleDateTime oleDt=COleDateTime::GetCurrentTime();
	CString stime=oleDt.Format("%Y-%m-%d %H:%M:%S");
	while(!mySet.IsEOF())
	{   
		for(int i=0;i<10;i++)     //i����ָ���ַ����±�
		{
			if(mySet.m_time[i]==stime[i])
				tflag1=true;
			else 
			{
				tflag1=false;
				break;
			}
		}
		if(tflag1)
		{
			incomenum1=incomenum1+mySet.m_incomenum;
			costnum1=costnum1+mySet.m_costnum;
		}
		for(int j=0;j<7;j++)     //j����ָ���ַ����±�
		{
			if(mySet.m_time[j]==stime[j])
				tflag2=true;
			else 
			{
				tflag2=false;
				break;
			}
		}
		if(tflag2)
		{
			incomenum2=incomenum2+mySet.m_incomenum;
			costnum2=costnum2+mySet.m_costnum;
		}
		for(int n=0;n<4;n++)     //n����ָ���ַ����±�
		{
			if(mySet.m_time[n]==stime[n])
				tflag3=true;
			else 
			{
				tflag3=false;
				break;
			}
		}
		if(tflag3)
		{
			incomenum3=incomenum3+mySet.m_incomenum;
			costnum3=costnum3+mySet.m_costnum;
		}
		mySet.MoveNext();
	}
	total1=incomenum1-costnum1;
	total2=incomenum2-costnum2;
    total3=incomenum3-costnum3;
    int nRowCount = 3;
	m_Chart.SetRowCount(nRowCount);
	VARIANT var;
	m_Chart.GetPlot().GetAxis(0,var).GetCategoryScale().SetAuto(FALSE);			// ���Զ���עX��̶�
	m_Chart.GetPlot().GetAxis(0,var).GetCategoryScale().SetDivisionsPerLabel(1);// ÿ�̶�һ����ע
	m_Chart.GetPlot().GetAxis(0,var).GetCategoryScale().SetDivisionsPerTick(1); // ÿ�̶�һ���̶���
	m_Chart.GetPlot().GetAxis(0,var).GetAxisTitle().SetText("��֧���");			// X������
	int benri[4]={incomenum1,costnum1,total1};
    int benyue[4]={incomenum2,costnum2,total2};
	int bennian[4]={incomenum3,costnum3,total3};
    int zong[4]={incomenum,costnum,total};
	char *buf[]={"�û�����","�û�֧��","�û�������Ŀ"};
	char b[32];
	srand( (unsigned)time( NULL ) );
	for(int row = 1; row <= nRowCount; ++row)
	{
		m_Chart.SetRow(row);
		sprintf(b, buf[row-1]);
		m_Chart.SetRowLabel((LPCTSTR)b);
		m_Chart.GetDataGrid().SetData(row, 1, benri[row-1], 0);
		m_Chart.GetDataGrid().SetData(row, 2, benyue[row-1], 0);
		m_Chart.GetDataGrid().SetData(row, 3, bennian[row-1], 0);
		m_Chart.GetDataGrid().SetData(row, 4, zong[row-1], 0);
    }
	m_Chart.Refresh();	
}


void PAGE3::InitChart()
{
	// ���ñ���
	m_Chart.SetTitleText("��֧ͳ��ͼ��               ͳ���ˣ�HC");

	// ��������ı䱳��ɫ
	m_Chart.GetBackdrop().GetFill().SetStyle(1);
	m_Chart.GetBackdrop().GetFill().GetBrush().GetFillColor().Set(255, 255, 255);

	// ��ʾͼ��
	m_Chart.SetShowLegend(TRUE);
	m_Chart.SetColumn(1);
	m_Chart.SetColumnLabel((LPCTSTR)"����");
	m_Chart.SetColumn(2);
	m_Chart.SetColumnLabel((LPCTSTR)"����");
	m_Chart.SetColumn(3);
	m_Chart.SetColumnLabel((LPCTSTR)"�����");
	m_Chart.SetColumn(4);
	m_Chart.SetColumnLabel((LPCTSTR)"����֧ͳ��");

	// ջģʽ
	m_Chart.SetStacking(FALSE);

	// Y������
	VARIANT var;
	m_Chart.GetPlot().GetAxis(1,var).GetValueScale().SetAuto(true);	// ���Զ���עY��̶�
//	m_Chart.GetPlot().GetAxis(1,var).GetValueScale().SetMaximum(200);	// Y�����̶�
//	m_Chart.GetPlot().GetAxis(1,var).GetValueScale().SetMinimum(0);		// Y����С�̶�
	m_Chart.GetPlot().GetAxis(1,var).GetValueScale().SetMajorDivision(10);	// Y��̶�5�ȷ�
	m_Chart.GetPlot().GetAxis(1,var).GetValueScale().SetMinorDivision(7);	// ÿ�̶�һ���̶���
//	m_Chart.GetPlot().GetAxis(1,var).GetAxisTitle().SetText(" �ʽ���(Ԫ) ");	// Y������

	// 3������
	m_Chart.SetColumnCount(4); 

	// ��ɫ
	m_Chart.GetPlot().GetSeriesCollection().GetItem(1).GetPen().GetVtColor().Set(0, 0, 255);
	m_Chart.GetPlot().GetSeriesCollection().GetItem(2).GetPen().GetVtColor().Set(0, 0, 0);
	m_Chart.GetPlot().GetSeriesCollection().GetItem(3).GetPen().GetVtColor().Set(0, 0, 0);

	// �߿�(�Ե���ͼ��Ч)
	m_Chart.GetPlot().GetSeriesCollection().GetItem(1).GetPen().SetWidth(50);
	m_Chart.GetPlot().GetSeriesCollection().GetItem(2).GetPen().SetWidth(100);
	m_Chart.GetPlot().GetSeriesCollection().GetItem(3).GetPen().SetWidth(2);

	// ���ݵ�������ʾ����ֵ��ģʽ(������״ͼ�͵���ͼ��Ч)
	// 0: ����ʾ	1: ��ʾ����״ͼ��
	// 2: ��ʾ����״ͼ���Ϸ�	3: ��ʾ����״ͼ���м�	4: ��ʾ����״ͼ���·�
	m_Chart.GetPlot().GetSeriesCollection().GetItem(1).GetDataPoints().GetItem(-1).GetDataPointLabel().SetLocationType(1);
	m_Chart.GetPlot().GetSeriesCollection().GetItem(2).GetDataPoints().GetItem(-1).GetDataPointLabel().SetLocationType(1);
	m_Chart.GetPlot().GetSeriesCollection().GetItem(3).GetDataPoints().GetItem(-1).GetDataPointLabel().SetLocationType(1);
	m_Chart.GetPlot().GetSeriesCollection().GetItem(4).GetDataPoints().GetItem(-1).GetDataPointLabel().SetLocationType(1);
}

void PAGE3::OnDrawline() 
{
	m_Chart.SetChartType(0); 
	DrawChart();
}

void PAGE3::OnDrawcombi() 
{
	m_Chart.SetChartType(5); 
	DrawChart();
	
}

void PAGE3::OnDrawpie() 
{
	m_Chart.SetChartType(6); 
	DrawChart();	
}
