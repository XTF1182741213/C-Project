// UserManageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HMSys.h"
#include "UserManageDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserManageDlg dialog

extern CHMSysApp theApp;
CUserManageDlg::CUserManageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserManageDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUserManageDlg)
	m_strPwd1 = _T("");
	m_strPwd2 = _T("");
	m_strUsers = _T("");
	//}}AFX_DATA_INIT
}


void CUserManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserManageDlg)
	DDX_Control(pDX, IDC_LIST1, m_UsersCtrl);
	DDX_Control(pDX, IDC_COMBO1, m_TyprCtrl);
	DDX_Text(pDX, IDC_PWD1, m_strPwd1);
	DDX_Text(pDX, IDC_PWD2, m_strPwd2);
	DDX_Text(pDX, IDC_USER, m_strUsers);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUserManageDlg, CDialog)
	//{{AFX_MSG_MAP(CUserManageDlg)
	ON_BN_CLICKED(IDC_CLEAN, OnClean)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_DEL, OnDel)
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelchangeList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserManageDlg message handlers

BOOL CUserManageDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_TyprCtrl.SetCurSel(0);								//Ĭ�ϵ�һ��ѡ��
	m_pRecordset.CreateInstance("ADODB.Recordset");			//����һ����¼������
	RefushListBox();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CUserManageDlg::RefushListBox()
{
	for( ; m_UsersCtrl.GetCount(); )			
		m_UsersCtrl.DeleteString(0);						//ɾ������
	CString strSQL;											//�����ַ�������
	strSQL.Format("select users from users ");				
	_variant_t r;
	try
	{
		m_pRecordset = theApp.m_pConnection->Execute((_bstr_t)strSQL, NULL, adCmdText);
		while(!m_pRecordset->adoEOF)//��¼û�е�ĩβ
		{
			m_UsersCtrl.AddString((char*)_bstr_t(m_pRecordset->GetCollect(_variant_t((long)0))));
			m_pRecordset->MoveNext();//�ƶ���������¼
		}
	}
	CATCH_ERROR;
}

void CUserManageDlg::OnClean() 
{
	m_strUsers = m_strPwd1 = m_strPwd2 = "";//�ؼ������				
	GetDlgItem(IDC_USER)->SetFocus();//���ý���
	UpdateData(FALSE);
}

void CUserManageDlg::OnAdd() 
{
	UpdateData();					//���ݵĸ���
	if(m_strUsers == "")			//�������ж�
	{
		MessageBox("�������û�����");
		return ;
	}
	if(m_strPwd1 == "")
	{
		MessageBox("���������룡");
		return ;
	}
	if(m_strPwd1 != m_strPwd2)
	{
		MessageBox("������������Ĳ�һ�£�");
		return ;
	}
	int nType = m_TyprCtrl.GetCurSel();//��ȡѡ�е�����
	CString strSQL;//�����ַ�������
	strSQL.Format("insert into users values ('%s', '%s', %d)", m_strUsers, m_strPwd1, nType);
	try
	{
		theApp.m_pConnection->Execute((_bstr_t)strSQL, NULL, adCmdText);
	}
	catch(...)
	{
		MessageBox("�û����Ѿ����ڣ�");
		return ;
	}
	RefushListBox();
	OnClean();
}

void CUserManageDlg::OnDel() 
{
	UpdateData();			//���ݵĸ���
	if(m_strUsers == "")
	{
		MessageBox("��ѡ��һ���û���");
		return ;
	}
	CString strSQL;			//�����ַ�������
	strSQL.Format("delete from users where users = '%s'", m_strUsers);
	if(MessageBox("ȷ��ɾ����", "ע��", MB_YESNO) == IDYES)
	{
		try
		{
			theApp.m_pConnection->Execute((_bstr_t)strSQL, NULL, adCmdText);
		}
		CATCH_ERROR;
		RefushListBox();
		OnClean();
	}
}

void CUserManageDlg::OnSelchangeList1() 
{
	int nIndex = m_UsersCtrl.GetCurSel();
	if(nIndex!=-1)
	m_UsersCtrl.GetText(nIndex, m_strUsers);
	UpdateData(FALSE);
}
