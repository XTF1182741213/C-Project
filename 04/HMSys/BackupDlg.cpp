// BackupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "hmsys.h"
#include "BackupDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBackupDlg dialog


CBackupDlg::CBackupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBackupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBackupDlg)
	m_strPath = _T("");
	//}}AFX_DATA_INIT
}


void CBackupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBackupDlg)
	DDX_Text(pDX, IDC_PATH, m_strPath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBackupDlg, CDialog)
	//{{AFX_MSG_MAP(CBackupDlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BACKUP, OnBackup)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBackupDlg message handlers

void CBackupDlg::OnButton1() 
{
	CFileDialog FileDlg(false, "bak", ".bak", OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY, "���ݿ��ļ�(*.bak)|*.bak|"); 
	if(IDOK != FileDlg.DoModal())				//�򿪴��ļ��Ի���
	{ 	
		return ;
	}	
	m_strPath = FileDlg.GetPathName();			//��ȡѡ���ļ���·��
	UpdateData(FALSE);							//���ݵĸ���
}

void CBackupDlg::OnBackup() 
{
	UpdateData();								//���ݵĸ���
	if(m_strPath == "")							//�������ж�
	{
		MessageBox("��ѡ��·��!");				//��ʾ��Ϣ
		return ;			
	}
	_ConnectionPtr pConnection;
	try
	{
		HRESULT hr = pConnection.CreateInstance("ADODB.Connection");//����Connection����
		pConnection->Open("driver={SQL Server};Server=HC\\MSSQL2008;DATABASE=master;","","",adModeUnknown);
		//pConnection->Open("driver={SQL Server};Server=HC\\MSSQL2008;DATABASE=master;UID=sa; PWD=","","",adModeUnknown);
		//�������ݿ�
		CString sql;						//�����ַ�������
		sql.Format("Backup Database HMSys to Disk = '%s' ", m_strPath);
		pConnection->Execute((_bstr_t)sql, NULL, adCmdText);//ִ��SQL���
		MessageBox("���ݳɹ���");
		pConnection->Close();				//�ر�����
	}
	CATCH_ERROR;	
}
