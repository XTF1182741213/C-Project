// RestoreDlg.cpp : implementation file
//

#include "stdafx.h"
#include "hmsys.h"
#include "RestoreDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRestoreDlg dialog


CRestoreDlg::CRestoreDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRestoreDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRestoreDlg)
	m_strPath = _T("");
	//}}AFX_DATA_INIT
}


void CRestoreDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRestoreDlg)
	DDX_Text(pDX, IDC_PATH, m_strPath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRestoreDlg, CDialog)
	//{{AFX_MSG_MAP(CRestoreDlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_RESTORE, OnRestore)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRestoreDlg message handlers

void CRestoreDlg::OnButton1() 
{
	CFileDialog FileDlg(true, "bak", ".bak", OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY, "���ݿ��ļ�(*.bak)|*.bak|"); 
	if(IDOK != FileDlg.DoModal()) 
	{ 	
		return ;
	}	
	m_strPath = FileDlg.GetPathName();
	UpdateData(FALSE);		
}

void CRestoreDlg::OnRestore() 
{
	UpdateData();					//���ݵĸ���
	if(m_strPath == "")
	{
		MessageBox("��ѡ��·��!");
		return ;
	}
	_ConnectionPtr pConnection;
	try
	{
		HRESULT hr = pConnection.CreateInstance("ADODB.Connection");//����Connection����
		pConnection->Open("driver={SQL Server};Server=HC\\MSSQL2008;DATABASE=master;","","",adModeUnknown);
		//pConnection->Open("driver={SQL Server};Server=HC\\MSSQL2008;DATABASE=master;UID=sa; PWD=","","",adModeUnknown);
		CString sql;//�����ַ�������
		sql.Format("use master restore database HMSys from disk = '%s' with move 'HMSys_data' to 'c:\\HMSys.mdf', move 'HMSys_log' to 'c:\\HMSys.ldf'", m_strPath);
		pConnection->Execute((_bstr_t)sql, NULL, adCmdText);
		MessageBox("��ԭ�ɹ���");
		pConnection->Close();//�ر�����
	}
	CATCH_ERROR;
}
