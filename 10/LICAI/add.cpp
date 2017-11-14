// add.cpp : implementation file
//

#include "stdafx.h"
#include "licai.h"
#include "add.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// add dialog


add::add(CWnd* pParent /*=NULL*/)
	: CDialog(add::IDD, pParent)
{
	//{{AFX_DATA_INIT(add)
	m_id = 0;
	m_time = _T("");
	m_incomenum = 0;
	m_costnum = 0;
	m_about = _T("");
	//}}AFX_DATA_INIT
}


void add::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(add)
	DDX_Control(pDX, IDC_COMBO2, m_costtype);
	DDX_Control(pDX, IDC_COMBO1, m_incometype);
	DDX_Text(pDX, IDC_EDIT1, m_id);
	DDX_Text(pDX, IDC_EDIT5, m_time);
	DDX_Text(pDX, IDC_EDIT2, m_incomenum);
	DDX_Text(pDX, IDC_EDIT3, m_costnum);
	DDX_Text(pDX, IDC_EDIT4, m_about);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(add, CDialog)
	//{{AFX_MSG_MAP(add)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// add message handlers

BOOL add::OnInitDialog() 
{
	CDialog::OnInitDialog();
	int k1=-1,k2=-1;	
    m_incometype.InsertString(0,"ԭ���ʽ�");
    m_incometype.InsertString(1,"��������");
	m_incometype.InsertString(2,"����");
    m_incometype.InsertString(3,"�����������");
	m_incometype.InsertString(4,"��������");
    m_incometype.InsertString(5,"��Ӫ�����ʽ�");
	m_incometype.InsertString(6,"Ͷ������");
    m_incometype.InsertString(7,"������������");

    m_costtype.InsertString(0,"���������֧��");
    m_costtype.InsertString(1,"ҽ�Ʊ���֧��");
	m_costtype.InsertString(2,"ͨ��֧��");
    m_costtype.InsertString(3,"������");
	m_costtype.InsertString(4,"��������֧��");
	m_costtype.InsertString(5,"��������֧��");
    m_costtype.InsertString(6,"���ౣ��ά��֧��");
	m_costtype.InsertString(7,"Ͷ��֧��");
	m_costtype.InsertString(8,"����֧��");
	if(addflag)
	{
		COleDateTime oleDt=COleDateTime::GetCurrentTime();
		CString strFileName=oleDt.Format("%Y-%m-%d %H:%M:%S");
		m_time=strFileName;
	    UpdateData(false);
		m_costtype.SetCurSel(0);
		costtype="���������֧��";
		m_incometype.SetCurSel(0);
		incometype="ԭ���ʽ�";
		SetWindowText("�������֧����Ϣ");
	}	    
	else 
	{
		if(incometype=="ԭ���ʽ�")
			k1=0;
		if(incometype=="��������")
			k1=1;
		if(incometype=="����")
			k1=2;
		if(incometype=="�����������")
			k1=3;
		if(incometype=="��������")
			k1=4;
		if(incometype=="��Ӫ�����ʽ�")
			k1=5;
		if(incometype=="Ͷ������")
			k1=6;
		if(incometype=="������������")
			k1=7;

		if(costtype=="���������֧��")
			k2=0;
		if(costtype=="ҽ�Ʊ���֧��")
			k2=1;
		if(costtype=="ͨ��֧��")
			k2=2;
		if(costtype=="������")
			k2=3;
		if(costtype=="��������֧��")
			k2=4;
		if(costtype=="��������֧��")
			k2=5;
		if(costtype=="���ౣ��ά��֧��")
			k2=6;
		if(costtype=="Ͷ��֧��")
			k2=7;
		if(costtype=="����֧��")
			k2=8;
		m_incometype.SetCurSel(k1);
		m_costtype.SetCurSel(k2);
		SetWindowText("�޸���֧��Ϣ");
	}
	return TRUE;
}

void add::OnOK() 
{
	int i,j;
	i=m_incometype.GetCurSel();
	j=m_costtype.GetCurSel();
    m_incometype.GetLBText(i,incometype);	
    m_costtype.GetLBText(j,costtype);	
	CDialog::OnOK();
}
