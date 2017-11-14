// BYZISHUDLG.cpp : implementation file
//

#include "stdafx.h"
#include "HCOK.h"
#include "BYZISHUDLG.h"
#include "ADOConn.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
CString munum,addnsingerna;
/////////////////////////////////////////////////////////////////////////////
// BYZISHUDLG dialog


BYZISHUDLG::BYZISHUDLG(CWnd* pParent /*=NULL*/)
	: CDialog(BYZISHUDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(BYZISHUDLG)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void BYZISHUDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(BYZISHUDLG)
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_COMBO1, m_combo1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(BYZISHUDLG, CDialog)
	//{{AFX_MSG_MAP(BYZISHUDLG)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// BYZISHUDLG message handlers


BOOL BYZISHUDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();	
    m_combo1.InsertString(0,"1");//��ʼ��combo�ؼ�
	m_combo1.InsertString(1,"2");
	m_combo1.InsertString(2,"3");
	m_combo1.InsertString(3,"4");
	m_combo1.InsertString(4,"5");
	m_combo1.InsertString(5,"6");
    m_combo1.InsertString(6,"7");
	m_combo1.InsertString(7,"8");
	m_combo1.InsertString(8,"9");
	m_combo1.InsertString(9,"10");
	m_combo1.InsertString(10,"11");
	m_combo1.InsertString(11,"12");
    m_combo1.SetCurSel(0);   //��Ĭ��ֵ
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);	//��ʼ��list�ؼ�
	m_list.InsertColumn(0,"���",LVCFMT_CENTER,100);
	m_list.InsertColumn(1,"������",LVCFMT_CENTER,270);
	SetTimer(1,5000,NULL);//��ʾˢ����ʾ��ʱ��
	showsong();   //��ʾ����
	GetDlgItem(IDC_INFOR)->SetWindowText("��˫��������ѡ��!");	 //����Ĭ����Ϣ
	return TRUE;
}




void BYZISHUDLG::OnSelchangeCombo1() //ѡ��ı�ʱˢ����ʾ
{
	showsong();	
}



//*************************��������ʾ****************************************//

void BYZISHUDLG::showsong()
{
	int ktype=m_combo1.GetCurSel();
	m_combo1.GetLBText(ktype,munum);///////////////////�õ�������
    CString songid,  songname;
	ADOConn m_AdoConn;  //�������ݿ��������
	m_AdoConn.OnInitADOConn();  //����
	_RecordsetPtr m_pRecordset;  //��¼��ָ��
	_bstr_t sql;
	sql = "select*from musiclist where mnum ='"+munum+"'"; //����SQL��ѯ���
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


void BYZISHUDLG::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
    CString addtsongname;
	addtsongname=m_list.GetItemText(m_list.GetSelectionMark(),1);//�õ�Ҫ��ӵĸ�����	
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
	sql = "select* from usertemp where tmuname='"+addtsongname+"'";//��ѯ�ø�������ʱ��ļ�¼
	m_pRecordset=m_AdoConn.GetRecordSet(sql);  //�õ���¼��
	if(!m_pRecordset->adoEOF)     //�������,�������ʾ,������
	{
		GetDlgItem(IDC_INFOR)->SetWindowText("�ø������Ѿ��㲥��,��ѡ�����������㲥!");
		return;
	}
	//�������ݿ⸴�����,��ӵ�usertemp��
	sql = "insert into usertemp(tmuname,tformate,tfilename,tsongtype,tsingername,playpath)select  muname,format,fname,mtpye,singernam,path from musiclist where muname ='"+addtsongname+"' ";
	m_AdoConn.ExecuteSQL(sql );//ִ��
	//�������ݿ⸴�����,��ӵ�playlist��
	sql = "insert into playlist (tmuname,tformate,tfilename,tsongtype,tsingername,playpath)select  muname,format,fname,mtpye,singernam,path from musiclist where muname ='"+addtsongname+"' ";
	m_AdoConn.ExecuteSQL(sql );//ִ��
	GetDlgItem(IDC_INFOR)->SetWindowText("�㲥����  "+addtsongname+"  �ɹ�!");  //������ʾ				
	m_AdoConn.ExitConnect();//�ͷ����ݿ���Դ	
    GetDlgItem(IDC_INFOR)->SetWindowText("��Ӹ���  "+addtsongname+"  �ɹ�!");	
	*pResult = 0;
}

void BYZISHUDLG::OnTimer(UINT nIDEvent)  //ˢ����ʾ��Ϣ
{
    
	GetDlgItem(IDC_INFOR)->SetWindowText("��˫��������ѡ��!");	
	CDialog::OnTimer(nIDEvent);
}
