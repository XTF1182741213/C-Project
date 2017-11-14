// AnswZigeChekDlg.cpp : implementation file
//

#include "stdafx.h"
#include "gradudemis.h"
#include "AnswZigeChekDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// AnswZigeChekDlg dialog


AnswZigeChekDlg::AnswZigeChekDlg(CWnd* pParent /*=NULL*/)
	: CDialog(AnswZigeChekDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(AnswZigeChekDlg)
	m_strAttDays = _T("");
	m_strCompuLevel = _T("");
	m_strHoliDays = _T("");
	m_strYDaoDays = _T("");
	m_strEngLevel = _T("");
	m_strResult = _T("");
	m_strColiResult = _T("");
	//}}AFX_DATA_INIT
}

void AnswZigeChekDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AnswZigeChekDlg)
	DDX_Control(pDX, IDC_StuName_COMBO, m_ctrlStuName);
	DDX_Control(pDX, IDC_Class_COMBO, m_ctrlClass);
	DDX_Text(pDX, IDC_EDIT_AttDays, m_strAttDays);
	DDX_Text(pDX, IDC_EDIT_CompuLevel, m_strCompuLevel);
	DDX_Text(pDX, IDC_EDIT_HoliDays, m_strHoliDays);
	DDX_Text(pDX, IDC_EDIT_YDaoDays, m_strYDaoDays);
	DDX_Text(pDX, IDC_EDIT_EngLevel, m_strEngLevel);
	DDX_Text(pDX, IDC_EDIT_Result, m_strResult);
	DDX_Text(pDX, IDC_EDIT_ColiResult, m_strColiResult);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(AnswZigeChekDlg, CDialog)
	//{{AFX_MSG_MAP(AnswZigeChekDlg)
	ON_CBN_SELCHANGE(IDC_StuName_COMBO, OnSelchangeStuNameCOMBO)
	ON_CBN_SELCHANGE(IDC_Class_COMBO, OnSelchangeClassCOMBO)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AnswZigeChekDlg message handlers

//��ʼ������
BOOL AnswZigeChekDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
    m_ctrlClass.InsertString(0,"��Ϣ021");					//���������в�������
    m_ctrlClass.InsertString(1,"��Ϣ022");
    m_ctrlClass.SetCurSel(0);
	CString strSQL;
	int i=0;
    strSQL="select * from tab_stu where stu_class='��Ϣ021'";//��ѯ���а༶Ϊ'��Ϣ021'������ѧ����Ϣ
	if(!stuSet.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
	{
		MessageBox("�����ݿ�ʧ�ܣ�");
	    return false;
	}
	while(!stuSet.IsEOF())									//������������
	{
		m_ctrlStuName.InsertString(i,stuSet.m_stu_name);	//��ѧ���������뵽�б����
		stuSet.MoveNext();									//�ƶ�����һ����¼
		i++;
	}
	m_ctrlStuName.SetCurSel(0);								//Ĭ��ѡ���һ��
	stuSet.Close();											//�رռ�¼��
 //	OnSelchangeStuNameCOMBO();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE

}

void AnswZigeChekDlg::OnSelchangeClassCOMBO() 
{
	// TODO: Add your control notification handler code here
	int m=0 ,k=0;
	  m=m_ctrlStuName.GetCount();							//��ȡѧ��������
	for(int i=0;i<m;i++)									
		m_ctrlStuName.DeleteString(0);						//��������б��
	CString strSQL,strClass;
	m_ctrlClass.GetWindowText(strClass);					//�ռ��еĻ�ȡ�ı�
	if(strClass=="��Ϣ021")
	    strSQL="select * from tab_stu where stu_class='��Ϣ021'";//��ѯ�༶Ϊ��Ӧ�ı���������Ϣ
	else
		strSQL="select * from tab_stu where stu_class='��Ϣ022'";
	if(!stuSet.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))		//sql���򿪼�¼��
	{
		MessageBox("�����ݿ�ʧ�ܣ�");
	    return ;
	}
	while(!stuSet.IsEOF())									//�������еļ�¼
	{
		m_ctrlStuName.InsertString(k,stuSet.m_stu_name);	//����ѧ��������
		stuSet.MoveNext();									//�ƶ�����һ����¼
		k++;
	}
	m_ctrlStuName.SetCurSel(0);								//Ĭ��ѡ���һ��
	stuSet.Close();											//�رռ�¼��
}

void AnswZigeChekDlg::OnSelchangeStuNameCOMBO() 
{
	// TODO: Add your control notification handler code here
   	int m=0,i=0;
	m=m_ctrlStuName.GetCount();							//��ȡ����
	CString strStuName;
	m_ctrlStuName.GetWindowText(strStuName);				//��ȡ�ؼ����ı�
	if(kqsumSet.IsOpen())									//�����¼��
		kqsumSet.Close();
	kqsumSet.Open();
    while(!kqsumSet.IsEOF())								//������¼��
	{
		if(kqsumSet.m_stu_name==strStuName)					//���ҵ�ǰѧ��
		{	
			m_strAttDays=kqsumSet.m_stu_attDays;			//��ȡѧ���ĳ�������
			m_strHoliDays=kqsumSet.m_stu_holiDays;			//�������
			m_strYDaoDays=kqsumSet.m_stu_YDaoDays;			//Ӧ������
			break;
		}
		else
			kqsumSet.MoveNext();							//�ƶ���������¼
	}
	kqsumSet.Close();										//�رռ�¼��
	if(!pstuachieveSet.IsOpen())							//��ѧ���Ƿ���Խ��д���¼��
	   pstuachieveSet.Open();
	pstuachieveSet.MoveFirst();								//�ƶ�����һ����¼
    while(!pstuachieveSet.IsEOF())							//������¼
	{
		if(pstuachieveSet.m_stu_name==strStuName)			//��ѯѧ������
		{
            m_strCompuLevel=pstuachieveSet.m_comLevel;		//��ȡ������ȼ����
			m_strEngLevel=pstuachieveSet.m_forlanLevel;		//��ȡ����ȼ�
			m_strColiResult=pstuachieveSet.m_schship;		//��ȡѧ����У��¼
			break;
		}
		else
		  pstuachieveSet.MoveNext();						//�ƶ�����һ����¼
	}
	pstuachieveSet.Close();									//�رռ�¼��
    m_strResult="�����������д��";
	UpdateData(false);										//��������		
}
