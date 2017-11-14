// BYSONGTYPDLG.cpp : implementation file
//

#include "stdafx.h"
#include "HCOK.h"
#include "BYSONGTYPDLG.h"
#include "ADOConn.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
CString bysongtype,singername1;
/////////////////////////////////////////////////////////////////////////////
// BYSONGTYPDLG dialog


BYSONGTYPDLG::BYSONGTYPDLG(CWnd* pParent /*=NULL*/)
: CDialog(BYSONGTYPDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(BYSONGTYPDLG)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void BYSONGTYPDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(BYSONGTYPDLG)
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(BYSONGTYPDLG, CDialog)
//{{AFX_MSG_MAP(BYSONGTYPDLG)
ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)

ON_WM_TIMER()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// BYSONGTYPDLG message handlers
BOOL BYSONGTYPDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
    m_combo.InsertString(0,"����");//��ʼ��combo
	m_combo.InsertString(1,"����");
	m_combo.InsertString(2,"ͨ��");
	m_combo.InsertString(3,"�ŵ�");
	m_combo.InsertString(4,"��ʿ");
	m_combo.InsertString(5,"ҡ��");
    m_combo.InsertString(6,"������");
	m_combo.SetCurSel(0);   //����Ĭ��
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);//��ʼ��list
	m_list.InsertColumn(0,"���",LVCFMT_CENTER,100);
	m_list.InsertColumn(1,"������",LVCFMT_CENTER,270);
	SetTimer(1,5000,NULL);//�趨��ʱ��,����ˢ���û��Ĳ�����Ϣ
	GetDlgItem(IDC_INFOR)->SetWindowText("��˫��������ѡ��!");  //�趨�û���ʾ��Ϣ
	showsong();	         //��ʾ����	
	return TRUE;  
}



void BYSONGTYPDLG::OnSelchangeCombo1() //ѡ��ı�ʱˢ����ʾ
{
	showsong();	
}


//*************************��������ʾ****************************************//

void BYSONGTYPDLG::showsong()
{
	int ktype=m_combo.GetCurSel();
	m_combo.GetLBText(ktype,bysongtype);///////////////////�õ�������
    CString songid,  songname;
	ADOConn m_AdoConn;  //�������ݿ��������
	m_AdoConn.OnInitADOConn();  //����
	_RecordsetPtr m_pRecordset;  //��¼��ָ��
	_bstr_t sql;
	sql = "select*from musiclist where mtpye ='"+bysongtype+"'"; //����SQL��ѯ���
	m_pRecordset=m_AdoConn.GetRecordSet(sql);   //�õ���¼��   
	if(m_pRecordset->adoEOF)    //��������û�и���������¼����
	{
		m_AdoConn.ExitConnect();//�Ͽ����Ӳ��رռ�¼��
		return;
	}  
	int t=0;   //list���
	m_list.DeleteAllItems();  //ɾ������
	while(!m_pRecordset->adoEOF)  //������¼��
	{
		int b=t+1;  
		songid.Format("%d",b); //�õ�list���к�
		songname =m_pRecordset->GetFields()->GetItem("muname")->Value.bstrVal;//�õ�����
		m_list.InsertItem(t,songid);  //��ʾ����
		m_list.SetItemText(t,1,	songname); //��ʾ����
		m_pRecordset->MoveNext(); //�Ƶ�������¼
		t++;
	   }
	m_AdoConn.ExitConnect();//�ͷ����ݿ���Դ
}

void BYSONGTYPDLG::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{

	CString addtsongname =m_list.GetItemText(m_list.GetSelectionMark(),1);//�õ�Ҫ��ӵĸ�����
	ADOConn m_AdoConn;   //�������ݿ��������
	m_AdoConn.OnInitADOConn();  //�������ݿ�����
	_RecordsetPtr m_pRecordset;  //�����¼��ָ��
	_bstr_t sql;
	sql = "select*from musiclist where muname='"+addtsongname+"' "; //����SQL���
	m_pRecordset=m_AdoConn.GetRecordSet(sql);   //�õ���¼��
	if(m_pRecordset->adoEOF)  //���������
	{
		m_AdoConn.ExitConnect();  //�ͷ����ݿ���Դ
		return;   //��������
	}
	
     //---------------------------��Ӹ�������ʱ��--------------------------------------//
	
	sql = "select* from usertemp where tmuname='"+addtsongname+"'";//��ѯ�ø�������ʱ��ļ�¼
	m_pRecordset=m_AdoConn.GetRecordSet(sql);  //�õ���¼��
	if(!m_pRecordset->adoEOF)     //�������,�������ʾ,������
	{
		GetDlgItem(IDC_INFOR)->SetWindowText("�ø������Ѿ��㲥��,��ѡ�����������㲥!");
		return;
	}
	
	//�������ݿ⸴�����,��ӵ�usertemp��
	sql = "insert into usertemp (tmuname,tformate,tfilename,tsongtype,tsingername,playpath) select  muname,format,fname,mtpye,singernam,path from musiclist where muname ='"+addtsongname+"' ";
	m_AdoConn.ExecuteSQL(sql );//ִ��
	//�������ݿ⸴�����,��ӵ�playlist��
	sql = "insert into playlist (tmuname,tformate,tfilename,tsongtype,tsingername,playpath) select  muname,format,fname,mtpye,singernam,path from musiclist where muname ='"+addtsongname+"' ";
	m_AdoConn.ExecuteSQL(sql );//ִ��
	GetDlgItem(IDC_INFOR)->SetWindowText("�㲥����  "+addtsongname+"  �ɹ�!");  //������ʾ
				
	m_AdoConn.ExitConnect();//�ͷ����ݿ���Դ	



	
*pResult = 0;
}

void BYSONGTYPDLG::OnTimer(UINT nIDEvent) //������ʾ
{
    GetDlgItem(IDC_INFOR)->SetWindowText("��˫��������ѡ��!");	
	CDialog::OnTimer(nIDEvent);
}

