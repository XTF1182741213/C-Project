// BYSGRDLG.cpp : implementation file
//

#include "stdafx.h"
#include "HCOK.h"
#include "BYSGRDLG.h"
#include "ADOConn.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////

//////
// BYSGRDLG dialog
int k;//�����жϲ˵�����
CString singarea,addsingerna,remenber;
BYSGRDLG::BYSGRDLG(CWnd* pParent /*=NULL*/)
	: CDialog(BYSGRDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(BYSGRDLG)
	//}}AFX_DATA_INIT
}


void BYSGRDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(BYSGRDLG)
	DDX_Control(pDX, IDC_COMBO2, m_combo);
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(BYSGRDLG, CDialog)
	//{{AFX_MSG_MAP(BYSGRDLG)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnItemchangedList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_CBN_SELCHANGE(IDC_COMBO2, OnSelchangeCombo2)
	ON_BN_CLICKED(IDC_UP, OnUp)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////

//////
// BYSGRDLG message handlers

BOOL BYSGRDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	//*************��ʼ��combo************//
	m_combo.InsertString(0,"��½�и���");
	m_combo.InsertString(1,"��½Ů����");
	m_combo.InsertString(2,"����и���");
	m_combo.InsertString(3,"���Ů����");
	m_combo.InsertString(4,"̨���и���");
	m_combo.InsertString(5,"̨��Ů����");
	m_combo.InsertString(6,"�պ��и���");
	m_combo.InsertString(7,"�պ�Ů����");
    m_combo.InsertString(8,"ŷ���и���");
	m_combo.InsertString(9,"ŷ��Ů����");
    m_combo.InsertString(10,"��������");
	m_combo.SetCurSel(0);	   
	//*************��ʼ��list************//
    m_list.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_list.InsertColumn(0,"���",LVCFMT_CENTER,100);
	m_list.InsertColumn(1,"������",LVCFMT_CENTER,270);
	k=2;  //�����жϲ˵�����
	SetTimer(1,5000,NULL); //�趨��ʱ�����ڸ����û���������
	ShowDate();
    GetDlgItem(IDC_INFOR)->SetWindowText("��˫��������ѡ����㲥��!");	
	return TRUE; 
}


void BYSGRDLG::OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult) //�ĵ�list�ؼ���ֵ,��OnDblclkList1�еõ�ֵ����
                                                                  //m_list.GetItemText(m_list.GetSelectionMark(),1);//�õ��б��еڶ��е�ֵ
{                                                                 //�ڰ�ƴ����ѯʱ�õ����ַ���
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
 	int selectrow=pNMListView->iItem;   //�õ�ѡ�����
     addsingerna=m_list.GetItemText(selectrow,1);//�õ��ڶ��е�ֵ,addsingerna�������������,���и�����
     if(k==2)       // ��ʾ���Ǹ�����,����������,�ڷ���ʱ����
	{
	 remenber=addsingerna;
	}
    UpdateData(false);
	*pResult = 0;
}

void BYSGRDLG::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 

////////////////////////���˫��,������һ���˵�
{
	mainshowlist++;
	k--;      //���ļ����仯
	if (k<0)   //��������
	k=0;
    ShowDate() ;   //ˢ������
	GetDlgItem(IDC_UP)->EnableWindow(true);
	*pResult = 0;
}


//*******************�Զ�����ʾ����*************************************//
void BYSGRDLG::ShowDate()    
{
	switch(k)     
	{
	case 0:  addsong();break;//ִ����Ӹ������û���ʱ��
	case 1:  showsong();break;//��ʾ�����ڱ���
	case 2:  showsinger();	break;//��ʾ���ֺ���
	default:  MessageBox("����!");break;
	}
}

//********************ִ����Ӹ������û���ʱ��**********************************************//
void BYSGRDLG::addsong()
{
	ADOConn m_AdoConn;   //�������ݿ��������
	m_AdoConn.OnInitADOConn();  //��������
	_RecordsetPtr m_pRecordset;   //�����¼��ָ��
	_bstr_t sql;
	sql = "select*from musiclist where muname='"+addsingerna+"' ";//����SQL���
    m_pRecordset=m_AdoConn.GetRecordSet(sql); //�õ���¼��
	if(m_pRecordset->adoEOF)    //��������û�и���������¼����
	   {
		m_AdoConn.ExitConnect();//�Ͽ����Ӳ��رռ�¼��
		return;
	   }
	//��Ӹ�������ʱ��
	   sql = "select* from usertemp where tmuname='"+addsingerna+"'\
		   and tsingername = '"+remenber+"'";//����û����и����͸�������ļ�¼��
	   m_pRecordset=m_AdoConn.GetRecordSet(sql); //�õ�����Ҫ��ļ�¼��
	   if(!m_pRecordset->adoEOF)    //����ø����Ѿ�����,��������Ӹ���
	   {
		   GetDlgItem(IDC_INFOR)->SetWindowText("�ø������Ѿ��㲥��!");	
		   return;
	   }
	   else
	   {  //����ø���������,�������ݿ⸴�����,��ӵ�usertemp��
		  sql = "insert into usertemp(tmuname,tformate,tfilename,tsongtype,tsingername,playpath) select  muname,format,fname,mtpye,singernam,path from musiclist where muname ='"+addsingerna+"'and singernam = '"+remenber+"' ";
			  m_AdoConn.ExecuteSQL(sql );//ִ��
		  //*********��ӵ�������ʱ��************//
		  //�������ݿ⸴�����,��ӵ�playlist��
		  sql = "insert into playlist(tmuname,tformate,tfilename,tsongtype,tsingername,playpath) select  muname,format,fname,mtpye,singernam,path from musiclist  where muname ='"+addsingerna+"'and singernam = '"+remenber+"' ";
			  m_AdoConn.ExecuteSQL(sql );//ִ��
		  GetDlgItem(IDC_INFOR)->SetWindowText("�㲥���� "+addsingerna+" �ɹ�!");//�㲥�ɹ�
	   }
	   m_AdoConn.ExitConnect();//�ͷ����ݿ���Դ
	   mainshowlist++;	
	   GetDlgItem(IDC_INFOR)->SetWindowText("�㲥���� "+addsingerna+" �ɹ�!");			
}

//***************************��ʾ�����ڱ���*****************************************************//
void BYSGRDLG::showsong()
{
	   CString songid,  songname;
	   //�����ǰ����ʾ,���³�ʼ��list
	   m_list.DeleteAllItems(); //�����ʾ�ϴ���������
	   m_list.DeleteColumn(0);
	   m_list.DeleteColumn(0);
	   m_list.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	   m_list.InsertColumn(0,"���",LVCFMT_CENTER,100);
	   m_list.InsertColumn(1,"������",LVCFMT_CENTER,270);
	   ADOConn m_AdoConn;    //�������ݿ��������
	   m_AdoConn.OnInitADOConn(); //�������ݿ�����
	   _bstr_t sql;
	   _RecordsetPtr m_pRecordset;	 //��¼��ָ��
	   sql = "select*from musiclist where singernam ='"+remenber+"'"; //�����ѯ�ĸ��ָ��������
	   m_pRecordset=m_AdoConn.GetRecordSet(sql);  //�õ���¼��
	   if(m_pRecordset->adoEOF)  //���û�и���
	   {
		   m_AdoConn.ExitConnect();  //�ͷ����ݿ���Դ
		   return;
	   }
	   
	   int t=0;    //��list�����к�
	   while(!m_pRecordset->adoEOF)  //������¼��
	   {int b=t+1;
	   songid.Format("%d",b); //ת������
	   songname =m_pRecordset->GetFields()->GetItem("muname")->Value.bstrVal;//�õ�������
	   m_list.InsertItem(t,songid);     //��list�в�ֵ
	   m_list.SetItemText(t,1,	songname);
	   m_pRecordset->MoveNext();   //�Ƶ��µ���¼
	   t++;
	   }
	   
	   m_AdoConn.ExitConnect();  //�ͷ����ݿ���Դ

}

//*********************��ʾ���ֺ���********************************************//
void BYSGRDLG::showsinger()
{
	//*****************��ʼ���б�*************************//
	m_list.DeleteAllItems(); 
	m_list.DeleteColumn(0);//�����ʾ�ϴ���������	
	m_list.DeleteColumn(1);
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_list.InsertColumn(0,"���",LVCFMT_CENTER,100);
	m_list.InsertColumn(1,"������",LVCFMT_CENTER,270);
	int L=m_combo.GetCurSel();
	m_combo.GetLBText(L,singarea);  //�õ�combo��ֵ
	   ADOConn m_AdoConn;     //�������ݿ����
	   m_AdoConn.OnInitADOConn();  //��������
	   _bstr_t sql;
	   _RecordsetPtr m_pRecordset;	  //�����¼��ָ��
	   CString  id, //���к�
		   singernameby, //������
		   sex;//�Ա�
	   if(singarea=="��������")
	   {	
		   singarea=singarea.Left(4);   //��ȡ�õ�'����'
		   sql = "select*from singer where sinarea ='"+singarea+"'";  //���ҵ���Ϊ'����'�ĸ���
	   }
	   else
	   {
		   sex=singarea.Right (6);  //�õ�'�Ա�+����'
		   singarea=singarea.Left(singarea.GetLength()-6);   //�õ�����
		   sql = "select*from singer where sinarea ='"+singarea+"'and sinsex='"+sex+"'";//�����Ա�͵�������
	   }
	   m_pRecordset=m_AdoConn.GetRecordSet(sql);   //�õ���¼��
	   if(m_pRecordset->adoEOF) //���������
	   {
		   m_AdoConn.ExitConnect();  //�ͷ����ݿ���Դ
		   return;   //��������
	   }
	   int t=0;    //��list�����к�
	   while(!m_pRecordset->adoEOF)  //������¼��
	   {
		   int b=t+1;
		   id.Format("%d",b);
		   singernameby =m_pRecordset->GetFields()->GetItem("sinnam")->Value.bstrVal;//�õ�������
		   
		   m_list.InsertItem(t,id);  //��ʾ��list�ؼ�
		   m_list.SetItemText(t,1,singernameby); //��ʾ��������
		   m_pRecordset->MoveNext();
		   t++;
	   }
	   m_AdoConn.ExitConnect();	 //�ͷ����ݿ���Դ	   
}

//*****************�������ʾ�����б�,k=2*************************************//
void BYSGRDLG::OnSelchangeCombo2() 
{	
     k=2;   //��ʾ����
	ShowDate() ;

}

//*********************�����ϼ��˵�**********************************//
void BYSGRDLG::OnUp() 
{
  k++;//�˵������仯
 if(k>2)  //������ʾ����
 {k=2; 	GetDlgItem(IDC_UP)->EnableWindow(FALSE);}  //���÷��ؼ�
  ShowDate() ;	//��ʾ����
}

//********************���²���������Ϣ********************************//
void BYSGRDLG::OnTimer(UINT nIDEvent) 
{
   GetDlgItem(IDC_INFOR)->SetWindowText("��˫��������ѡ����㲥��!");	
	CDialog::OnTimer(nIDEvent);
}
