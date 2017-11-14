// PAGE2.cpp : implementation file
//

#include "stdafx.h"
#include "LICAI.h"
#include "PAGE2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PAGE2 dialog


PAGE2::PAGE2(CWnd* pParent /*=NULL*/)
	: CDialog(PAGE2::IDD, pParent)
{
	//{{AFX_DATA_INIT(PAGE2)
	m_jianyi = _T("");
	//}}AFX_DATA_INIT
}


void PAGE2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PAGE2)
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_EDIT1, m_jianyi);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PAGE2, CDialog)
	//{{AFX_MSG_MAP(PAGE2)
	ON_BN_CLICKED(IDC_REQUERY, OnRequery)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PAGE2 message handlers

BOOL PAGE2::OnInitDialog() 
{
	CDialog::OnInitDialog();	
	pdb=new CDatabase;
	mySet=new LCSet(pdb);
	mySet->Open();	
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
    m_list.InsertColumn(0,"��������Ŀ(Ԫ)",LVCFMT_CENTER,150);
    m_list.InsertColumn(1,"��֧����Ŀ(Ԫ)",LVCFMT_CENTER,150);
    m_list.InsertColumn(2,"��Ŀǰ��ӯ����Ŀ(Ԫ)",LVCFMT_CENTER,150); 
	LOADDATA();	
	LOADJY();	   
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void PAGE2::LOADDATA()                      //��ȡLIST�ؼ�����
{
	mySet->Requery();
	m_list.DeleteAllItems();
	incomenum=0,costnum=0;//incomenum��ʾ�����룬costnum��ʾ֧����Ŀ��total��ʾʣ�����Ŀ
	CString str,str1,str2; 
	while(!mySet->IsEOF())
	{   
		incomenum+=mySet->m_incomenum;
		costnum+=mySet->m_costnum;
		mySet->MoveNext();
	}
	total=incomenum-costnum;
	str.Format("%d",incomenum);
	str1.Format("%d",costnum);
	str2.Format("%d",total);
	m_list.InsertItem(0,str);
	m_list.SetItemText(0,1,str1);
	m_list.SetItemText(0,2,str2);
	mySet->Close();
}

void PAGE2::LOADJY()              //��������뽨��
{
	CString str,str0,str1,str2,str3,str4,str5,str6,str7,str8;
	CString str9,str10,str11,str12,str13,str14,str15; 
	str="�϶࣬����������1/10,�����Ԥ�㣬���ƺ�֧��\r\n";
	xfsm1=0,xfsm2=0,xfsm3=0,xfsm4=0,xfsm5=0;
	xfsm6=0,xfsm7=0,xfsm8=0,xfsm9=0;  //�����ֱ�ͳ�Ƹ���֧��������Ŀ
	mySet->Open();
	while(!mySet->IsEOF())
	{   
		if(mySet->m_costtype=="���������֧��")
			xfsm1+=mySet->m_costnum;
		if(mySet->m_costtype=="ҽ�Ʊ���֧��")
			xfsm2+=mySet->m_costnum;
		if(mySet->m_costtype=="ͨ��֧��")
			xfsm3+=mySet->m_costnum;
		if(mySet->m_costtype=="������")
			xfsm4+=mySet->m_costnum;
		if(mySet->m_costtype=="��������֧��")
			xfsm5+=mySet->m_costnum;
		if(mySet->m_costtype=="��������֧��")
			xfsm6+=mySet->m_costnum;
		if(mySet->m_costtype=="���ౣ��ά��֧��")
			xfsm7+=mySet->m_costnum;
		if(mySet->m_costtype=="Ͷ��֧��")
			xfsm8+=mySet->m_costnum;
		if(mySet->m_costtype=="����֧��")
			xfsm9+=mySet->m_costnum;
		mySet->MoveNext();
	}
	if(costnum>incomenum)
		str0="��֧��"+str;
	if(float(xfsm1)/float(incomenum)>=0.1)	
		str1="�ܻ�����������֧��"+str;
	if(float(xfsm2)/float(incomenum)>=0.1)	
		str2="��ҽ�Ʊ���֧��"+str;
	if(float(xfsm3)/float(incomenum)>=0.1)	
		str3="��ͨ��֧��"+str;
	if(float(xfsm4)/float(incomenum)>=0.1)	
		str4="�ܵĽ�����"+str;
	if(float(xfsm5)/float(incomenum)>=0.1)	
		str5="����������֧��"+str;
	if(float(xfsm6)/float(incomenum)>=0.1)	
		str6="�ܹ�������֧��"+str;
	if(float(xfsm7)/float(incomenum)>=0.1)	
		str7="�ܸ��ౣ��ά��֧��"+str;
	if(float(xfsm8)/float(incomenum)>=0.1)	
		str8="�ܵ�Ͷ��֧��"+str;
	if(float(xfsm9)/float(incomenum)>=0.1)	
		str9="������֧��"+str;
	if(mySet->IsOpen())
		mySet->Close();
	mySet->Open();
	bool tflag1,tflag2,tflag3;
	mySet->Requery();
	int incomenum1=0,costnum1=0,total1=0,incomenum2=0;
	int costnum2=0,total2=0,incomenum3=0,costnum3=0,total3=0;
	CString dstr,dstr1,dstr2,mstr,mstr1,mstr2,ystr,ystr1,ystr2;    //������ת�����ַ���
	COleDateTime oleDt=COleDateTime::GetCurrentTime();
	CString stime=oleDt.Format("%Y-%m-%d %H:%M:%S");
	while(!mySet->IsEOF())
	{   
		for(int i=0;i<10;i++)     //i����ָ���ַ����±�
		{
			if(mySet->m_time[i]==stime[i])
				tflag1=true;
			else 
			{
				tflag1=false;
				break;
			}
		}
		if(tflag1)
		{
			incomenum1=incomenum1+mySet->m_incomenum;
			costnum1=costnum1+mySet->m_costnum;
		}
		for(int j=0;j<7;j++)     //j����ָ���ַ����±�
		{
			if(mySet->m_time[j]==stime[j])
				tflag2=true;
			else 
			{
				tflag2=false;
				break;
			}
		}
		if(tflag2)
		{
			incomenum2=incomenum2+mySet->m_incomenum;
			costnum2=costnum2+mySet->m_costnum;
		}
		for(int n=0;n<4;n++)
		{
			if(mySet->m_time[n]==stime[n])
				tflag3=true;
			else 
			{
				tflag3=false;
				break;
			}
		}
		if(tflag3)
		{
			incomenum3=incomenum3+mySet->m_incomenum;
			costnum3=costnum3+mySet->m_costnum;
		}
		mySet->MoveNext();
	}
	if(float(costnum1)/float(incomenum1)>=0.5&&float(costnum1)/float(incomenum1)<1)	
		str10="�����ܵ�����֧���϶࣬������������һ��,�����Ԥ�㣬���ٽ���֧��\r\n";
	else if(costnum1>incomenum1)
		str11="���������Ѿ����������յ�����,��ע�����������������Լ��֧\r\n\r\n\r\n";
	if(float(costnum2)/float(incomenum2)>=0.5&&float(costnum2)/float(incomenum1)<2)	
		str12="�����ܵ�����֧���϶࣬������������һ��,�����Ԥ�㣬���ٱ��µ�֧��\r\n";
	else if(costnum2>incomenum2)
		str13="���������Ѿ����������µ�����,��ע�������������Լ��֧\r\n\r\n\r\n";
	if(float(costnum3)/float(incomenum3)>=0.5&&float(costnum2)/float(incomenum1)<2)	
		str14="�����������֧���϶࣬�������������һ��,����к���Ԥ�㣬���ٱ����֧��\r\n";
	else if(costnum3>incomenum3)
		str15="����������ѳ���������ܵ�����,��ע���������������Լ��֧\r\n";
		m_jianyi=str0+str1+str2+str3+str4+str5+str6+str7+str8+str9;
		m_jianyi+=str10+str11+str12+str13+str14+str15;//�����������ʾ����
		UpdateData(false);
}


void PAGE2::OnRequery() 
{
	LOADDATA();	
	LOADJY();
}
