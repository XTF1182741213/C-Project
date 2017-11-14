// KaoqinDlg.cpp : implementation file
//

#include "stdafx.h"
#include "gradudemis.h"
#include "KaoqinDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKaoqinDlg dialog


CKaoqinDlg::CKaoqinDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKaoqinDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKaoqinDlg)
	m_strClass = _T("");
	m_strStuName = _T("");
	m_strClass2 = _T("");
	m_strStuName2 = _T("");
	m_strFrom = 0;
	m_strTo = 0;
	m_bCheck = FALSE;
	m_strUnAttRea = _T("");
	//}}AFX_DATA_INIT
}


void CKaoqinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKaoqinDlg)
	DDX_Control(pDX, IDC_EDIT_UnAttRea, m_ctrUnAttRea);
	DDX_Control(pDX, IDC_StuName_COMBO2, m_ctrlStuName2);
	DDX_Control(pDX, IDC_Class_COMBO2, m_ctrlClass2);
	DDX_Control(pDX, IDC_LIST1, m_ctrlList);
	DDX_Control(pDX, IDC_StuName_COMBO, m_ctrlStuName);
	DDX_Control(pDX, IDC_Class_COMBO, m_ctrlClass);
	DDX_CBString(pDX, IDC_Class_COMBO, m_strClass);
	DDX_CBString(pDX, IDC_StuName_COMBO, m_strStuName);
	DDX_CBString(pDX, IDC_Class_COMBO2, m_strClass2);
	DDX_CBString(pDX, IDC_StuName_COMBO2, m_strStuName2);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_From, m_strFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_To, m_strTo);
	DDX_Check(pDX, IDC_CHECK1, m_bCheck);
	DDX_Text(pDX, IDC_EDIT_UnAttRea, m_strUnAttRea);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CKaoqinDlg, CDialog)
	//{{AFX_MSG_MAP(CKaoqinDlg)
	ON_CBN_SELCHANGE(IDC_Class_COMBO, OnSelchangeClassCOMBO)

	ON_BN_CLICKED(IDC_Add_BTN, OnAddBTN)
	ON_CBN_SELCHANGE(IDC_Class_COMBO2, OnSelchangeClassCOMBO2)

	ON_BN_CLICKED(IDC_QUERY_BTN, OnQueryBtn)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////

// CKaoqinDlg message handlers

BOOL CKaoqinDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	m_ctrUnAttRea.EnableWindow(false);								//�ؼ��Ľ���
	m_ctrlList.InsertColumn(0,"���",LVCFMT_LEFT,50,0);				//�б�ؼ��в����б������ÿ�ȶ��뷽ʽ
	m_ctrlList.InsertColumn(1,"      ��      ��",LVCFMT_LEFT,120,0);
	m_ctrlList.InsertColumn(2,"�������",LVCFMT_LEFT,80,0);
	m_ctrlList.InsertColumn(3,"��ע",LVCFMT_LEFT,250,0);
	m_ctrlList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);//�����趨����ѡ������
	m_ctrlClass.InsertString(0,"��Ϣ021");							//�������ݵ������б����
    m_ctrlClass.InsertString(1,"��Ϣ022");
    m_ctrlClass.SetCurSel(0);										//Ĭ��ѡ���һ��
	m_ctrlClass2.InsertString(0,"��Ϣ021");
    m_ctrlClass2.InsertString(1,"��Ϣ022");
    m_ctrlClass2.SetCurSel(0);
	CString strSQL;													//�����ַ�������
	int i=0;
    strSQL="select * from tab_stu where stu_class='��Ϣ021'";		//�����ѯ��Ӧ�༶������ѧ������Ϣ��sql���
	if(!stuSet.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))				//�򿪼�¼��
	{
		MessageBox("�����ݿ�ʧ�ܣ�");
	    return false;
	}	
	while(!stuSet.IsEOF())											//�����¼û�е�ĩβ
	{
		m_ctrlStuName.InsertString(i,stuSet.m_stu_name);			//��������
		m_ctrlStuName2.InsertString(i,stuSet.m_stu_name);
		stuSet.MoveNext();											//�ƶ���������¼
		i++;
	}
	m_ctrlStuName.SetCurSel(0);										//����Ĭ��ѡ���һ��
	m_ctrlStuName2.SetCurSel(0);
	stuSet.Close();													//�رռ�¼��
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
////////////////////////////////////////////////////////////////////////
void CKaoqinDlg::OnSelchangeClassCOMBO() 
{
	// TODO: Add your control notification handler code here
	int m=0 ,k=0;											//�������α���
	m=m_ctrlStuName.GetCount();								//�õ��ؼ������ݵ�����
	for(int i=0;i<m;i++)
		m_ctrlStuName.DeleteString(0);						//ɾ���ؼ��е���������
	CString strSQL,strClass;								//�����ַ�������
	m_ctrlClass.GetWindowText(strClass);					//��ȡ�ؼ��е��ı�
	if(strClass=="��Ϣ021")									//�����ж�
	    strSQL="select * from tab_stu where stu_class='��Ϣ021'";//�����ѯ���а༶Ϊ��Ӧ�༶��ѧ����Ϣ
	else
		strSQL="select * from tab_stu where stu_class='��Ϣ022'";//�����ѯ���а༶Ϊ��Ӧ�༶��ѧ����Ϣ
	if(!stuSet.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))		//�򿪼�¼��
	{
		MessageBox("�����ݿ�ʧ�ܣ�");
	    return ;
	}
	while(!stuSet.IsEOF())									//�����¼û�е�ĩβ
	{
		m_ctrlStuName.InsertString(k,stuSet.m_stu_name);	//�������ݵ��ؼ���
		stuSet.MoveNext();									//�ƶ���������¼
		k++;
	}
	m_ctrlStuName.SetCurSel(0);								//Ĭ��ѡ�еĵ�һ��
	stuSet.Close();											//�رռ�¼��
}

void CKaoqinDlg::OnSelchangeClassCOMBO2() 
{
	// TODO: Add your control notification handler code here
	int m=0 ,k=0;											//�������α���
	    m=m_ctrlStuName2.GetCount();							//�õ��ؼ������ݵ�����
	for(int i=0;i<m;i++)
		m_ctrlStuName2.DeleteString(0);						//ɾ���ؼ��е���������
	CString strSQL,strClass;								//�����ַ�������
	m_ctrlClass2.GetWindowText(strClass);					//��ȡ�ؼ��е��ı�
	if(strClass=="��Ϣ021")									//�����ж�
	    strSQL="select * from tab_stu where stu_class='��Ϣ021'";//�����ѯ���а༶Ϊ��Ӧ�༶��ѧ����Ϣ
	else
		strSQL="select * from tab_stu where stu_class='��Ϣ022'";//�����ѯ���а༶Ϊ��Ӧ�༶��ѧ����Ϣ
	if(!stuSet.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))//�򿪼�¼��
	{
		MessageBox("�����ݿ�ʧ�ܣ�");
	    return ;
	}
	while(!stuSet.IsEOF())
	{
		m_ctrlStuName2.InsertString(k,stuSet.m_stu_name);	//��������
		stuSet.MoveNext();									//�ƶ���������¼
		k++;
	}
	m_ctrlStuName2.SetCurSel(0);							//Ĭ��ѡ���һ��
	stuSet.Close();											//�رռ�¼��
}


void CKaoqinDlg::OnCheck1() 
{
	// TODO: Add your control notification handler code here
	m_ctrUnAttRea.EnableWindow(!m_bCheck);					//�ؼ��Ľ���
}

void CKaoqinDlg::OnQueryBtn() 
{
	// TODO: Add your control notification handler code here
	m_ctrlList.DeleteAllItems();							//ɾ������
	UpdateData();											//��������
	int i=0;												//�������α���
	CString strI;											//�����ַ�������
	if(!kaoqinSet.IsOpen())
		kaoqinSet.Open();									//�򿪼�¼��
	kaoqinSet.MoveFirst();
	while(!kaoqinSet.IsEOF())								//�����¼��Ī�е����
	{
		if(kaoqinSet.m_stu_name==m_strStuName)				//�����ж�
		{
			strI.Format("%d",i+1);							//���θ�ʽ���ַ���
			m_ctrlList.InsertItem(i,strI);					//���б�ؼ��в�������
			m_ctrlList.SetItemText(i,1,kaoqinSet.m_stu_ChuQinTime);
			if(kaoqinSet.m_stu_ChuQinStatus)
				m_ctrlList.SetItemText(i,2,"��");
			else
				m_ctrlList.SetItemText(i,2,"��");
			m_ctrlList.SetItemText(i,3,kaoqinSet.m_stu_UnAtedReason);
			i++;
		}
		kaoqinSet.MoveNext();								//�ƶ���������¼
	}
	kaoqinSet.Close();										//�رռ�¼��
}

void CKaoqinDlg::OnAddBTN() 
{
	m_ctrlList.DeleteAllItems();							//ɾ������
	CTime time=CTime::GetCurrentTime();						//��ȡ��ǰʱ��
	CString strtime=time.Format("%Y-%m-%d");				//��ʱ�䰴��ʽ��ʽ��
    UpdateData();											//��������
	if(!kaoqinSet.IsOpen())									//�򿪼�¼��
		kaoqinSet.Open();
	kaoqinSet.AddNew();										//����µļ�¼
    kaoqinSet.m_stu_ChuQinStatus=!m_bCheck;					//�¼�¼��ֵ
	kaoqinSet.m_stu_ChuQinTime=strtime;
	kaoqinSet.m_stu_name=m_strStuName2;
	kaoqinSet.m_stu_UnAtedReason=m_strUnAttRea;
	kaoqinSet.Update();										//��ϸ����
	kaoqinSet.Requery();									//ˢ�¼�¼��
	kaoqinSet.Close();										//�رռ�¼��
	MessageBox("��ӳɹ�!");								//��Ϣ��ʾ
}


