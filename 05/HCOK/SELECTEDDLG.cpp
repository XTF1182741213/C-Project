// SELECTEDDLG.cpp : implementation file
//

#include "stdafx.h"
#include "HCOK.h"
#include "SELECTEDDLG.h"
#include "ADOConn.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SELECTEDDLG dialog
CString addallsongna;

SELECTEDDLG::SELECTEDDLG(CWnd* pParent /*=NULL*/)
	: CDialog(SELECTEDDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(SELECTEDDLG)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void SELECTEDDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SELECTEDDLG)
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SELECTEDDLG, CDialog)
	//{{AFX_MSG_MAP(SELECTEDDLG)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnItemchangedList1)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SELECTEDDLG message handlers
//************************����ķ����Ƚϵı�,����ȡ���,ע����ǰ��ģ������*****************************************//

void SELECTEDDLG::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CString 	sformat,	sfilename,	stype,	ssname,	spath;

	///////////////////////////////////////////////�õ�������ȫ����Ϣ
	ADOConn m_AdoConn;
	m_AdoConn.OnInitADOConn();
	_RecordsetPtr m_pRecordset;
	_bstr_t sql,addtolist,createlistsql,dellistsql;
	sql = "select*from usertemp where tmuname='"+addallsongna+"' ";
		
	m_pRecordset=m_AdoConn.GetRecordSet(sql);
	if(!m_pRecordset->adoEOF)
	{
	//	sname =m_pRecordset->GetFields()->GetItem("muname")->Value.bstrVal;/////////////////ȡ������
		sformat =m_pRecordset->GetFields()->GetItem("tformate")->Value.bstrVal;/////////////////ȡ���ʽ		
	sfilename =m_pRecordset->GetFields()->GetItem("tfilename")->Value.bstrVal;/////////////////ȡ���ļ���		
	stype =m_pRecordset->GetFields()->GetItem("tsongtype")->Value.bstrVal;	/////////////////ȡ������		
	ssname =m_pRecordset->GetFields()->GetItem("tsingername")->Value.bstrVal;/////////////////ȡ������	
	spath =m_pRecordset->GetFields()->GetItem("playpath")->Value.bstrVal;/////////////////ȡ·��

	}
	else{
				m_AdoConn.ExitConnect();
				return;
		}
				
	m_pRecordset->Close();
	////////////////////////////////////////////////////////////////////��Ӹ�������ʱ��

	//sql = "select* from playlist where tmuname='"+addallsongna+"'";////////////////////
    addtolist="select* from playlist where tmuname='"+addallsongna+"'";////////////////////	
	createlistsql = "Create table playlist(tmuname varchar(50),tformate varchar(50),tfilename varchar(50),tsongtype varchar(50),tsingername varchar(50),tsingerpin varchar(50),playpath  varchar(200))";
	//dellistsql="Drop table  playlist";	

				//m_pRecordset=m_AdoConn.GetRecordSet(sql);
				//if(!m_pRecordset->adoEOF)
			//	MessageBox("�ø������Ѿ��㲥��,��ѡ�����������㲥!","ϵͳ��ʾ��",MB_OK|MB_ICONASTERISK);
				//else{
					
				
				/////////////////////////////////////��ӵ�������ʱ��
				try
				{	
					m_pRecordset=m_AdoConn.GetRecordSet(addtolist);
					//if(!m_pRecordset->adoEOF)
				    if(!m_pRecordset->adoEOF)
					{
	            GetDlgItem(IDC_INFOR)->SetWindowText("�ø����Ѿ��ڲ����б���!");
					//	MessageBox("�ø����Ѿ������Ĳ����б���,��ѡ��������!","ϵͳ��ʾ��",MB_OK|MB_ICONASTERISK);
			           return;
					}
						
						
						m_pRecordset->AddNew();
						m_pRecordset->GetFields()->GetItem("tmuname")->Value=(_bstr_t) addallsongna;	////////////////////ȡ������
						m_pRecordset->GetFields()->GetItem("tformate")->Value=(_bstr_t) 	sformat;///////д����ʽ
						m_pRecordset->GetFields()->GetItem("tfilename")->Value=(_bstr_t) sfilename;////д����ļ���	
						m_pRecordset->GetFields()->GetItem("tsongtype")->Value=(_bstr_t)  	stype;////д�������	
						m_pRecordset->GetFields()->GetItem("tsingername")->Value=(_bstr_t)  ssname;////д�������
						m_pRecordset->GetFields()->GetItem("playpath")->Value=(_bstr_t)  	spath;////д���·��
						m_pRecordset->Update();
						
					
				}
				catch(...)
				{
					//m_AdoConn.ExecuteSQL(dellistsql);
					m_AdoConn.ExecuteSQL(createlistsql);
					m_pRecordset=m_AdoConn.GetRecordSet(addtolist);
					if(!m_pRecordset->adoEOF)
					//	MessageBox("�ø������Ѿ��㲥��,��ѡ�����������㲥!","ϵͳ��ʾ��",MB_OK|MB_ICONASTERISK);
					{	GetDlgItem(IDC_INFOR)->SetWindowText("�ø����Ѿ��ڲ����б���!");}
					else{
						
						
						m_pRecordset->AddNew();
						m_pRecordset->GetFields()->GetItem("tmuname")->Value=(_bstr_t) addallsongna;	////////////////////ȡ������
						m_pRecordset->GetFields()->GetItem("tformate")->Value=(_bstr_t) 	sformat;///////д����ʽ
						m_pRecordset->GetFields()->GetItem("tfilename")->Value=(_bstr_t) sfilename;////д����ļ���	
						m_pRecordset->GetFields()->GetItem("tsongtype")->Value=(_bstr_t)  	stype;////д�������	
						m_pRecordset->GetFields()->GetItem("tsingername")->Value=(_bstr_t)  ssname;////д�������
						m_pRecordset->GetFields()->GetItem("playpath")->Value=(_bstr_t)  	spath;////д���·��
						m_pRecordset->Update();
					}
				
					
			}
				
				mainshowlist++;	
		GetDlgItem(IDC_INFOR)->SetWindowText("��Ӹ��� "+addallsongna+" �������б�ɹ�!");
					
			
    	m_AdoConn.ExitConnect();
	
	*pResult = 0;
}

void SELECTEDDLG::OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
  int selectrow=pNMListView->iItem;

	 addallsongna=m_list.GetItemText(selectrow,1);
     UpdateData(false);

	*pResult = 0;
}

BOOL SELECTEDDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();

 m_list.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	   m_list.InsertColumn(0,"���",LVCFMT_CENTER,100);
	   m_list.InsertColumn(1,"������",LVCFMT_CENTER,150);
	   m_list.InsertColumn(2,"������",LVCFMT_CENTER,150);
	    SetTimer(1,5000,NULL);
		SetTimer(2,1,NULL);
	   ShowDate();
	  	//////////////////////////////////
   GetDlgItem(IDC_INFOR)->SetWindowText("˫�������ӵ������б�!");
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void SELECTEDDLG::ShowDate()
{
	
	CString songid,  songname,		  singername,  songtype,  filename,fileformat;
	   m_list.DeleteAllItems();
	 
	
	   
	//////////////////////////////////////////
	   ADOConn m_AdoConn;
	   m_AdoConn.OnInitADOConn();
	   _bstr_t sql;
	   _RecordsetPtr m_pRecordset;	
	   

	   sql = "select*from usertemp ";
	   
	   m_pRecordset=m_AdoConn.GetRecordSet(sql);
	 if(m_pRecordset->adoEOF)
	  {
		 m_AdoConn.ExitConnect();
		 return;
	 }
	   if(!m_pRecordset->adoEOF)
	   {  
		   int t=0;
		   m_list.DeleteAllItems();
		   while(!m_pRecordset->adoEOF)
		   {int b=t+1;
		   
		   songid.Format("%d",b);
		   
		   songname =m_pRecordset->GetFields()->GetItem("tmuname")->Value.bstrVal;/////////////////ȡ�ֶ�
		  singername =m_pRecordset->GetFields()->GetItem("tsingername")->Value.bstrVal;/////////////////ȡ�ֶ�
		  
		  
		   m_list.InsertItem(t,songid);
		   m_list.SetItemText(t,1,	songname);
           m_list.SetItemText(t,2,	singername );
	
		 
		 
	   
		   m_pRecordset->MoveNext();
		   t++;
		   }
	   }
	   
	   else 
	   {
		   //	GetDlgItem(IDC_INFOR)->SetWindowText("û�и���!");
		   m_list.DeleteAllItems();
	   }
	   
	   m_AdoConn.ExitConnect();
}

void SELECTEDDLG::OnTimer(UINT nIDEvent) 
{
	
	  switch(nIDEvent)   
        {   
                case   1:GetDlgItem(IDC_INFOR)->SetWindowText("˫�������ӵ������б�!");
	                       
	                      CDialog::OnTimer(nIDEvent);  
                case   2:
          
						int num = getSongNum();     //�õ�usertemp���и���������
						int b=m_list.GetItemCount();//�õ��б��еĸ�������
						if(num != b)    //����������ôˢ��
						ShowDate();   //ʵ���б��ˢ��
                
        }   
}

//*****************�õ�usertemp���и���������*************************************//
int SELECTEDDLG::getSongNum()
{
	   int songNum =0 ;
     	ADOConn m_AdoConn;
	    m_AdoConn.OnInitADOConn();
	   _bstr_t sql;
	   _RecordsetPtr m_pRecordset;	
	   sql = "select*from usertemp ";
	   m_pRecordset=m_AdoConn.GetRecordSet(sql);
	   if(m_pRecordset->adoEOF)
	   {
		   m_AdoConn.ExitConnect();
		   return 0;
	   }
	   else{ 
		   while(!m_pRecordset->adoEOF)
		   {
			   songNum++;
			   m_pRecordset->MoveNext();
		   }
		 return songNum ;  //���ظ�������
	   }
	   m_AdoConn.ExitConnect();
}