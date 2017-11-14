// BYPINYINDLG.cpp : implementation file
//

#include "stdafx.h"
#include "HCOK.h"
#include "BYPINYINDLG.h"
#include "ADOConn.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// BYPINYINDLG dialog

CString 
pinyin,   //�༭���ֵ
add,      //��list�еĵ��ĵڶ��е�ֵ
singername;   //��������

int k1;       //�����жϲ˵�����

BYPINYINDLG::BYPINYINDLG(CWnd* pParent /*=NULL*/)
: CDialog(BYPINYINDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(BYPINYINDLG)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void BYPINYINDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(BYPINYINDLG)
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(BYPINYINDLG, CDialog)
//{{AFX_MSG_MAP(BYPINYINDLG)
ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
ON_BN_CLICKED(IDC_UP, OnUp)
ON_WM_TIMER()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// BYPINYINDLG message handlers

BOOL BYPINYINDLG::OnInitDialog() 
{
	   CDialog::OnInitDialog();
	   m_list.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT); //��ʼ���б�ؼ�
	   m_list.InsertColumn(0,"���",LVCFMT_CENTER,100);
	   m_list.InsertColumn(1,"������",LVCFMT_CENTER,270);
	   SetTimer(1,5000,NULL);  //�趨������ʾ������ʾ�Ķ�ʱ��
	   k1=2;                  //�趨��ʾ����Ϊ2��
	   ShowDate();             //��ʾ�������
	   GetDlgItem(IDC_INFOR)->SetWindowText("��˫��������ѡ����㲥��!");	
	   return false;  
}

//*****************�����༭������ֵ�ı仯***********************************//
void BYPINYINDLG::OnChangeEdit1() 
{
    m_list.DeleteAllItems();   //����б�����������
	GetDlgItem(IDC_EDIT1)->GetWindowText( pinyin);  //�ĵ������ƴ��ֵ
	k1=2;      // ���˵���������Ϊ��ʾ���ֵļ���        
	ShowDate() ;  //��ʾ���������ĸ���
	
}

//*********************�б������˫���¼�****************************************//
void BYPINYINDLG::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{ 
    add=m_list.GetItemText(m_list.GetSelectionMark(),1);//�õ��б��еڶ��е�ֵ
    
	if(k1==2)//����������,�ڷ���ʱ����
		
	{
		
		singername=add;
		
	}
	
	k1--;       //����һ��           
	if (k1<0)    //���˶��
		k1=0;
	
	ShowDate() ;     //��ʾ����
	GetDlgItem(IDC_UP)->EnableWindow(true);  //�����˰�����Ϊ����
				
	*pResult = 0;
}

//******************�Զ�����ʾ����*****************************************//

void BYPINYINDLG::ShowDate()   
{
	switch(k1)  //�ж�ִ��ʲô ����
	{
	case 0:  addsong();break;       //ִ����Ӹ������û���ʱ��
	case 1:  showsong();break;      //��ʾ�����ڱ���
	case 2:  showsinger();	break;  //��ʾ���ֺ���
	default:  MessageBox("����!");break;
	}
}

//*********************ִ����Ӹ������û���ʱ�� �� �����б� ����*****************************************//
void BYPINYINDLG::addsong()
{
    CString 	sformat,	sfilename,	stype,	ssname,	spath;
	
    
	ADOConn m_AdoConn;          //����һ����װ���ݿ���Ķ���
	m_AdoConn.OnInitADOConn();  //�������ݿ�
	
	_RecordsetPtr m_pRecordset;
	_bstr_t sql,addtolist; 
	
	sql = "select*from musiclist where muname='"+add+"' and singernam ='"+singername+"' ";   //�������и����͸�������ļ�¼��
	
	addtolist="select* from playlist where tmuname='"+add+"' and  tsingername = '"+singername+"'";//��������б� ���и����͸�������ļ�¼��	
	
	
	
	m_pRecordset=m_AdoConn.GetRecordSet(sql);    // ��musiclistȡ�÷���Ҫ��ļ�¼��
	
	   if(m_pRecordset->adoEOF)    //��������û�и���������¼����
	   {
		   m_AdoConn.ExitConnect();//�Ͽ����Ӳ��رռ�¼��
		   return;
	   }
	   
	   ////////////////////////////////////////////////////////////////////��Ӹ�������ʱ��
	   
	   sql = "select* from usertemp where tmuname='"+add+"' and tsingername = '"+singername+"'";//����û����и����͸�������ļ�¼��
	   m_pRecordset=m_AdoConn.GetRecordSet(sql); //�õ�����Ҫ��ļ�¼��
	   if(!m_pRecordset->adoEOF)    //����ø����Ѿ�����,��������Ӹ���
	   {
		   GetDlgItem(IDC_INFOR)->SetWindowText("�ø������Ѿ��㲥��,��ѡ�����������㲥!");	
		   return;
	   }
	   else{  //����ø���������
		   //�������ݿ⸴�����,��ӵ�usertemp��
		   sql = "insert into usertemp (tmuname,tformate,tfilename,tsongtype,tsingername,playpath) select  muname,format,fname,mtpye,singernam,path from musiclist where muname ='"+add+"' ";
		   m_AdoConn.ExecuteSQL(sql );//ִ��
		   
		   //************************��ӵ�������ʱ��*******************************************///
		   //�������ݿ⸴�����,��ӵ�playlist��
		   sql = "insert into playlist (tmuname,tformate,tfilename,tsongtype,tsingername,playpath) select  muname,format,fname,mtpye,singernam,path from musiclist where muname ='"+add+"' ";
		   m_AdoConn.ExecuteSQL(sql );//ִ��
		   GetDlgItem(IDC_INFOR)->SetWindowText("�㲥����   "+add+"   �ɹ�!");//�㲥�ɹ�
	   }
	   m_AdoConn.ExitConnect();//�ͷ����ݿ���Դ
	   
}

//*************************��ʾ�����ڱ���**********************************************//
void BYPINYINDLG::showsong()
{
	CString songid,  songname;
	
	   m_list.DeleteColumn(0);    //�����ʾ�ϴ���������
	   m_list.DeleteColumn(0);
	   m_list.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	   m_list.InsertColumn(0,"���",LVCFMT_CENTER,100);
	   m_list.InsertColumn(1,"������",LVCFMT_CENTER,270);
	   
	   ADOConn m_AdoConn;     //����һ����װ���ݿ���Ķ���
	   m_AdoConn.OnInitADOConn();//�������ݿ�
	   _bstr_t sql;           
	   _RecordsetPtr m_pRecordset;	//�����¼��ָ��
	   
	   sql = "select * from musiclist where singernam ='"+add+"'";  //���ø��ֵ����и�����ʾ
	   
	   m_pRecordset=m_AdoConn.GetRecordSet(sql); //�ĵ�������¼��
	   if(m_pRecordset->adoEOF)    //���û������������
	   {
		   m_AdoConn.ExitConnect();
		   return;
	   }
	   if(!m_pRecordset->adoEOF)     //�ø����и���
	   {  
		   int t=0;
		   m_list.DeleteAllItems();  //ɾ����ǰ����ʾ
		   while(!m_pRecordset->adoEOF)   //������¼��
		   {
			   int b=t+1; //�����
			   songid.Format("%d",b);  //ת������
			   songname =m_pRecordset->GetFields()->GetItem("muname")->Value.bstrVal; //�ø���
			   m_list.InsertItem(t,songid);   //���������
			   m_list.SetItemText(t,1,	songname);  //���ø���
			   m_pRecordset->MoveNext();  //�Ƶ�������¼
			   t++;
		   }
	   }
	   
	   else 
	   {
		   m_list.DeleteAllItems();//ɾ�����и�����¼
	   }
	   
	   m_AdoConn.ExitConnect();//�Ͽ����ݿ�����
	   
}

//***********************��ʾ���ֺ���**************************************//
void BYPINYINDLG::showsinger()
{
	//m_list.DeleteAllItems();   //ɾ���б�Ԫ��
	   m_list.DeleteColumn(0);    //�����ʾ�ϴ���������
	   m_list.DeleteColumn(0); 
	   m_list.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT); //��ʼ���б�ؼ�
	   m_list.InsertColumn(0,"���",LVCFMT_CENTER,100);
	   m_list.InsertColumn(1,"������",LVCFMT_CENTER,270);
	   
	   ADOConn m_AdoConn;
	   m_AdoConn.OnInitADOConn();
	   _bstr_t sql;
	   CString songid,  singernameby, songtotal,sex;
	   _RecordsetPtr m_pRecordset;	
	   sql = "select * from singer where 1=1";//û������ʱ��ʾ���и���
	  
	

	   if(pinyin !="")   //û������������
	   {
		   sql = sql +"and sinpin like '"+pinyin+"%'";//������ݸ���ƴ��ģ����ѯ���
		  
	   }
	   m_pRecordset=m_AdoConn.GetRecordSet(sql);   //�õ���¼��
	   if(m_pRecordset->adoEOF)    //���û�з�������ļ�¼,������
	   {
		   m_AdoConn.ExitConnect();
		   return;
	   }
	   if(!m_pRecordset->adoEOF)    //�м�¼
	   {    
		   int t=0;    
		   m_list.DeleteAllItems();    //ɾ���б�ؼ�Ԫ��
		   while(!m_pRecordset->adoEOF) //������¼��
		   {
			   int b=t+1;
			   songid.Format("%d",b);
			   singernameby =m_pRecordset->GetFields()->GetItem("sinnam")->Value.bstrVal;//ȡ������
			   m_list.InsertItem(t,songid);    //������к�
			   m_list.SetItemText(t,1,singernameby);  //��Ӹ�����
			   m_pRecordset->MoveNext();  //�Ƶ�����
			   t++;
		   }
	   }
	   
	   else 
	   {
		   m_list.DeleteAllItems(); //�����ʾ
	   }
	   
	   m_AdoConn.ExitConnect();	
	   
}
//********************���ؼ�*************************************//
void BYPINYINDLG::OnUp() 
{
	if(k1==0) //���������������ʾ��Ĭ�ϼ���� 1
		k1=1;
	k1++;   //����ʾ�ļ���� 1
	if(k1>2)  //���K1>�趨ֵ
	{k1=2; 	GetDlgItem(IDC_UP)->EnableWindow(FALSE);} //�ָ�����ֵ,�����ú��˰�ť
	ShowDate() ;//������ʾ����	
}

void BYPINYINDLG::OnTimer(UINT nIDEvent) //������ʾ��Ϣ
{
    GetDlgItem(IDC_INFOR)->SetWindowText("��˫��������ѡ��!");
	CDialog::OnTimer(nIDEvent);
}
