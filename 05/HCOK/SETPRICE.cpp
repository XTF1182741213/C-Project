// SETPRICE.cpp : implementation file
//

#include "stdafx.h"
#include "HCOK.h"
#include "SETPRICE.h"
#include "ADOConn.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SETPRICE dialog


SETPRICE::SETPRICE(CWnd* pParent /*=NULL*/)
	: CDialog(SETPRICE::IDD, pParent)
{
	//{{AFX_DATA_INIT(SETPRICE)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void SETPRICE::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SETPRICE)
	DDX_Control(pDX, IDC_LIST2, m_list2);
	DDX_Control(pDX, IDC_LIST1, m_list1);
	DDX_Control(pDX, IDC_COMBO2, m_combo2);
	DDX_Control(pDX, IDC_COMBO1, m_combo1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SETPRICE, CDialog)
	//{{AFX_MSG_MAP(SETPRICE)
	ON_BN_CLICKED(IDC_SETROOM, OnSetroom)
	ON_BN_CLICKED(IDC_SETABATE, OnSetabate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SETPRICE message handlers

BOOL SETPRICE::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	(CEdit*)GetDlgItem(IDC_PRICE)->SetFocus();//��ý���
	//*******************��ʼ���ؼ�***********************************//
    m_combo1.InsertString(0,"С����");
	m_combo1.InsertString(1,"�а���");
	m_combo1.InsertString(2,"�����");
	m_combo1.InsertString(3,"��������");
	
    m_combo1.SetCurSel(0);//���ó�ʼֵ
	///////////////////////////////////////
	m_combo2.InsertString(0,"�ǻ�Ա");
	m_combo2.InsertString(1,"һ���Ա");
	m_combo2.InsertString(2,"�м���Ա");
	m_combo2.InsertString(3,"�߼���Ա");
	
    m_combo2.SetCurSel(0);	//���ó�ʼֵ
	///////////////////////////////////////////////
    	m_list1.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	   m_list1.InsertColumn(0,"��������",LVCFMT_CENTER,100);
	   m_list1.InsertColumn(1,"ÿСʱ����(Ԫ)",LVCFMT_CENTER,100);
	   m_list2.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	   m_list2.InsertColumn(0,"��Ա������",LVCFMT_CENTER,100);
	   m_list2.InsertColumn(1,"������",LVCFMT_CENTER,100);
	   
	   ShowabatetDate() ;//��ʾ������
	   ShowroomtDate();//��ʾ����
	return false;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void SETPRICE::OnOK() 
{

	CDialog::OnOK();	

}


void SETPRICE::ShowroomtDate() /////////////////////////��ʾ����۸�
{
	CString room12,  price12;
	   m_list1.DeleteAllItems();//�������
	   //////////////////////////////////////////
	    ADOConn m_AdoConn;   //�������ݿ��������
	   m_AdoConn.OnInitADOConn();//��������
	   _bstr_t sqlroom;
	   _RecordsetPtr m_pRecordset;	  //�����¼��
	   sqlroom = "select*from room ";   //��ѯ���з���
	 
	   m_pRecordset=m_AdoConn.GetRecordSet( sqlroom);
	   if(m_pRecordset->adoEOF)//���û���򷵻�
	   {
		   m_AdoConn.ExitConnect();
		   return;
	   }     
	  
		   int t=0;
		   m_list1.DeleteAllItems();   //���
		   while(!m_pRecordset->adoEOF)
		   {
		    room12 =m_pRecordset->GetFields()->GetItem("roomtype")->Value.bstrVal;/////////////////ȡ�ֶ�
		    price12 =m_pRecordset->GetFields()->GetItem("price")->Value.bstrVal;/////////////////ȡ�ֶ�
		    m_list1.InsertItem(t,room12);   //��ʾ����
		   m_list1.SetItemText(t,1,	price12); //��ʾ�۸�
           m_pRecordset->MoveNext();
		   t++;
		   }
	    m_AdoConn.ExitConnect(); //�ͷ����ݿ���Դ
}
void SETPRICE::ShowabatetDate() ///////////////��ʾ������,ע������������
{
	CString card12,  abate12;
	   m_list2.DeleteAllItems();
	//////////////////////////////////////////
	   ADOConn m_AdoConn; //�������ݿ��������
	   m_AdoConn.OnInitADOConn();
	   _bstr_t sqlroom,sqlabate;
	   _RecordsetPtr m_pRecordset;	

	   sqlabate="select*from abate ";
	   m_pRecordset=m_AdoConn.GetRecordSet(   sqlabate);
	   if(m_pRecordset->adoEOF)
	   {
		   m_AdoConn.ExitConnect();
		   return;
	   }     
	   if(!m_pRecordset->adoEOF)
	   {  
		   int t=0;
		   m_list2.DeleteAllItems();
		   while(!m_pRecordset->adoEOF)
		   {
	
		  	card12 =m_pRecordset->GetFields()->GetItem("cardtype")->Value.bstrVal;/////////////////ȡ�ֶ�
	       abate12 =m_pRecordset->GetFields()->GetItem("abate")->Value.bstrVal;/////////////////ȡ�ֶ�
		  
		   m_list2.InsertItem(t,card12);
		   m_list2.SetItemText(t,1,	abate12);
  
		   m_pRecordset->MoveNext();
		   t++;
		   }
	   }
}



void SETPRICE::OnSetroom() ////////////////���ð���۸�
{
	CString roomtype1;
	int k=m_combo1.GetCurSel();
	m_combo1.GetLBText(k,roomtype1);///////////////////�õ���������	
	CString price1;
	GetDlgItem(IDC_PRICE)->GetWindowText(  price1);
	////////////////////////////////////////////////////�������ݵ����ݿ�
				
	ADOConn m_AdoConn;   //�������ݿ��������
	m_AdoConn.OnInitADOConn();  //��������
	
	_RecordsetPtr m_pRecordset;
	_bstr_t sql;
	
	sql = "select*from room where roomtype='"+roomtype1+"' ";
	 double tempprice=atof( price1);////////////�ж��Ƿ�Ϊ�ַ�,����ȷ�ķ���
	if( tempprice==0)
	{
		MessageBox("��û������ĸ�ʽ����!","ϵͳ��ʾ��",MB_OK|MB_ICONASTERISK);	
		GetDlgItem(IDC_PRICE)->SetWindowText("");
		(CEdit*)GetDlgItem(IDC_PRICE)->SetFocus();	
		return;
	}			
	
	m_pRecordset=m_AdoConn.GetRecordSet(sql);
	if(m_pRecordset->adoEOF)//��������ھ��½�һ����¼,����ھ͸���
	m_pRecordset->AddNew();
				
	m_pRecordset->GetFields()->GetItem("roomtype")->Value=(_bstr_t) roomtype1 ;///д�뷿��
	
	m_pRecordset->GetFields()->GetItem("price")->Value=(_bstr_t)  price1;////д��۸�
	m_pRecordset->Update();
	m_AdoConn.ExitConnect();//�ͷ����ݿ���Դ
	ShowroomtDate();///ˢ��
	GetDlgItem(IDC_PRICE)->SetWindowText("");
	(CEdit*)GetDlgItem(IDC_PRICE)->SetFocus();		
						
}

void SETPRICE::OnSetabate() /////////////////////���û�Ա������,ע������������
{
	CString cardtype1;
	ADOConn m_AdoConn;
	
	_RecordsetPtr m_pRecordset;
	_bstr_t sql;
	int k2=m_combo2.GetCurSel();
	m_combo2.GetLBText(k2,cardtype1);///////////////////�õ���Ա������
	
	CString abate1;
	GetDlgItem(IDC_ABATD)->GetWindowText(  abate1);
	double tempabate=atof( abate1);/////////////�ж��Ƿ�Ϊ�ַ�
	if( tempabate==0)
	{
		MessageBox("��û������ĸ�ʽ����!","ϵͳ��ʾ��",MB_OK|MB_ICONASTERISK);	
		GetDlgItem(IDC_ABATD)->SetWindowText("");
		(CEdit*)GetDlgItem(IDC_ABATD)->SetFocus();	
		return;
	}			
	if(	atof(abate1)>1||atof(abate1)<0)
		
	{
		MessageBox("��������������������С��!","ϵͳ��ʾ��",MB_OK|MB_ICONASTERISK);
	}
	else
	{	
		m_AdoConn.OnInitADOConn();
		sql = "select*from abate where cardtype='"+cardtype1+"' ";
		m_pRecordset=m_AdoConn.GetRecordSet(sql);
		if(m_pRecordset->adoEOF)
			m_pRecordset->AddNew();
		
		m_pRecordset->GetFields()->GetItem("cardtype")->Value=(_bstr_t) cardtype1;////д�����
		
		
		m_pRecordset->GetFields()->GetItem("abate")->Value=(_bstr_t) abate1;////д�������
		
		m_pRecordset->Update();
		
		m_AdoConn.ExitConnect();
		
	}
	ShowabatetDate() ;
	GetDlgItem(IDC_ABATD)->SetWindowText("");
	(CEdit*)GetDlgItem(IDC_ABATD)->SetFocus();	
	
}
