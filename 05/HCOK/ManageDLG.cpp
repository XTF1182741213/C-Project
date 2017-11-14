// ManageDLG.cpp : implementation file
//

#include "stdafx.h"
#include "HCOK.h"
#include "ManageDLG.h"
#include "MADDSONG.h"
#include "SETPRICE.h"
#include "ADOConn.h"
#include "ADDSGEDLG.h"
#include "MODIFISINGER.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
CString desongname,desingername,deformat, delkusinger;
/////////////////////////////////////////////////////////////////////////////
// ManageDLG dialog


ManageDLG::ManageDLG(CWnd* pParent /*=NULL*/)
: CDialog(ManageDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(ManageDLG)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ManageDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ManageDLG)
	DDX_Control(pDX, IDC_LIST2, m_list2);
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ManageDLG, CDialog)
//{{AFX_MSG_MAP(ManageDLG)
ON_BN_CLICKED(IDC_ADDSONG, OnAddsong)
ON_BN_CLICKED(IDC_PRICE, OnPrice)
ON_BN_CLICKED(IDC_DELSONG, OnDelsong)
ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnItemchangedList1)
ON_WM_TIMER()
ON_BN_CLICKED(IDC_ADDSINGER, OnAddsinger)
ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, OnItemchangedList2)
ON_BN_CLICKED(IDC_DEL, OnDel)
ON_BN_CLICKED(IDC_MODIFSINGER, OnModifsinger)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ManageDLG message handlers

void ManageDLG::OnAddsong() 
{
	
	MADDSONG mydlg;
	mydlg.DoModal();
	
}

void ManageDLG::OnPrice() 
{
	SETPRICE mydlg;
	mydlg.DoModal();	
}

BOOL ManageDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	//*********************��ʼ���ؼ�************************************//
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_list.InsertColumn(0,"����",LVCFMT_CENTER,150);
	m_list.InsertColumn(1,"������",LVCFMT_CENTER,100);
	m_list.InsertColumn(2,"�������",LVCFMT_CENTER,80);
	m_list.InsertColumn(3,"��ʽ",LVCFMT_CENTER,80);
	m_list2.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_list2.InsertColumn(0,"������",LVCFMT_CENTER,80);
	
	ShowData() ;
	singerShowData() ;//��ʾ����
	SetTimer(1,10,NULL); //����ˢ���б�ʱ��
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void ManageDLG::ShowData() 
{
	CString  muname, singername, mtype,format;
	m_list.DeleteAllItems();
	int k=0;
	ADOConn m_AdoConn;/////////////////////////////��ADO�������ݿ�
	m_AdoConn.OnInitADOConn();
	_RecordsetPtr m_pRecordset;
	_bstr_t sql;
	sql = "select*from musiclist";
	m_pRecordset=m_AdoConn.GetRecordSet(sql);
	if(m_pRecordset->adoEOF)
	{
		m_AdoConn.ExitConnect();
		return;
	}
	m_pRecordset->MoveFirst();	
	while(!m_pRecordset->adoEOF)
	{   		
		muname=m_pRecordset->GetFields()->GetItem("muname")->Value.bstrVal;/////////////////ȡ�ֶ�
		
		singername=m_pRecordset->GetFields()->GetItem("singernam")->Value.bstrVal;/////////////////ȡ�ֶ�
		
		mtype=m_pRecordset->GetFields()->GetItem("mtpye")->Value.bstrVal;/////////////////ȡ�ֶ�
		format=m_pRecordset->GetFields()->GetItem("format")->Value.bstrVal;/////////////////ȡ�ֶ�
		m_list.InsertItem(k, muname);
		m_list.SetItemText(k,1,singername);
		m_list.SetItemText(k,2, mtype);
		m_list.SetItemText(k,3,format);
		m_pRecordset->MoveNext();
		k++;
				}
				
				m_AdoConn.ExitConnect();
				
}
//***************ע����ɾ����������****************************//
void ManageDLG::OnDelsong() 
{
	ADOConn m_AdoConn;//��ADO�������ݿ�
	m_AdoConn.OnInitADOConn();
	_RecordsetPtr m_pRecordset;
	_bstr_t sql;
	sql = "delete from musiclist where singernam='"+desingername+"'and muname='"+desongname+"'";
	m_pRecordset=m_AdoConn.GetRecordSet(sql);
	CString sPath ;
	int nPos;
	GetModuleFileName(NULL,sPath.GetBufferSetLength (MAX_PATH+1),MAX_PATH);
	nPos=sPath.ReverseFind('\\');
	sPath=sPath.Left(nPos);
	nPos=sPath.ReverseFind('\\');
	sPath=sPath.Left(nPos);
	sPath=sPath+"\\����ļ���";
	desongname.TrimRight();
	CString	defilename=desongname+'.'+deformat;
	CString	filename=sPath+"\\"+defilename;
	DeleteFile(filename);
	ShowData() ;
				
}

void ManageDLG::OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int selectrow=pNMListView->iItem;
	desongname=m_list.GetItemText(selectrow,0);//�õ�list���е�һ�е�ֵ
	desingername=m_list.GetItemText(selectrow,1);//�õ�list���еڶ���ֵ
	deformat=m_list.GetItemText(selectrow,3);//�õ�list���е����е�ֵ
	UpdateData(false);
	
	*pResult = 0;
}

void ManageDLG::OnTimer(UINT nIDEvent) //��������Ӹ����͸���ʱ���Կ�����ı仯
{
	
	if(tempshow1!=tempshow)
	{
		ShowData() ;
		singerShowData();
		tempshow1=0;
		tempshow=0;
	}
	
	if(showsinger1!=showsinger2)
	{
		singerShowData() ;
		showsinger1=0;
		showsinger2=0;
	}
	if(delsongfresh!=0)
	{
		ShowData() ;
		delsongfresh=0;
	}
	CDialog::OnTimer(nIDEvent);
}

void ManageDLG::OnAddsinger() ///////////////////////////////��Ӹ���
{
	GetDlgItem(IDC_INFOR)->SetWindowText("");
	ADDSGEDLG mysgrdlg;
	if(mysgrdlg.DoModal()==IDOK)//������Ӹ��ֶԻ���
	{
		showsinger2++;
		return;
	}
	
}

void ManageDLG::OnItemchangedList2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int selectrow=pNMListView->iItem;
	delkusinger=m_list2.GetItemText(selectrow,0);//�õ�Ҫɾ���ĸ���
	
	UpdateData(false);
	
	*pResult = 0;
}

void ManageDLG::singerShowData() 
{
	
	CString  kusingername;
	m_list2.DeleteAllItems();
	int k=0;
	ADOConn m_AdoConn;//��ADO�������ݿ�
	m_AdoConn.OnInitADOConn();
	_RecordsetPtr m_pRecordset;
	_bstr_t sql;
	sql = "select*from singer";
	m_pRecordset=m_AdoConn.GetRecordSet(sql);
	if(m_pRecordset->adoEOF)
	{
		m_AdoConn.ExitConnect();
		return;
	}
	m_pRecordset->MoveFirst();	
	while(!m_pRecordset->adoEOF)
	{   		
		kusingername=m_pRecordset->GetFields()->GetItem("sinnam")->Value.bstrVal;//ȡ�ֶ�
		m_list2.InsertItem(k, kusingername);
		m_pRecordset->MoveNext();
		k++;
	}
	m_AdoConn.ExitConnect();
				
}
//********����ģ������*************//
void ManageDLG::OnDel() ////////////////////////ɾ������
{
	GetDlgItem(IDC_INFOR)->SetWindowText("");
	
	if (delkusinger=="")
	{
		GetDlgItem(IDC_INFOR)->SetWindowText("����ѡ�����!");
		return;
	}
	
	ADOConn m_AdoConn;/////////////////////////////��ADO�������ݿ�
	_bstr_t delkusinsql;
				
    delkusinsql= "delete from singer where sinnam='"+delkusinger+"'";
	m_AdoConn.ExecuteSQL(delkusinsql);///////////////////ɾ����ʱ��	
	singerShowData() ;
	delkusinger="";
}



void ManageDLG::OnModifsinger() 
{
	GetDlgItem(IDC_INFOR)->SetWindowText("");
	if (delkusinger=="")
	{
		GetDlgItem(IDC_INFOR)->SetWindowText("����ѡ�����!");
		return;
	}
	//�õ����ֵ���Ϣ
	
	ADOConn m_AdoConn;
	m_AdoConn.OnInitADOConn();
	_RecordsetPtr m_pRecordset;
	_bstr_t sql;
	sql = "select*from singer where sinnam='"+delkusinger+"'";
	m_pRecordset=m_AdoConn.GetRecordSet(sql);			
	mkusingername=delkusinger;
	mkusingersex =m_pRecordset->GetFields()->GetItem("sinsex")->Value.bstrVal;/////////////////ȡ�ֶ�
	mkusingerarea =m_pRecordset->GetFields()->GetItem("sinarea")->Value.bstrVal;/////////////////ȡ�ֶ�
	mkusingerpin =m_pRecordset->GetFields()->GetItem("sinpin")->Value.bstrVal;/////////////////ȡ�ֶ�
	
	MODIFISINGER modifidlg;
	modifidlg.DoModal();
	
	GetDlgItem(IDC_INFOR)->SetWindowText("�޸ĸ��� "+delkusinger+" �������!");
	delkusinger="";
	m_AdoConn.ExitConnect();
	
}
