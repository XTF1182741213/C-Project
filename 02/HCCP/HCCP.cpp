// HCCP.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "HCCP.h"
#include "HCCPDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHCCPApp
CString leaf111,leaf11,leaf12,str1112,str1212,str1213;int nCount,qiqi;
BOOL flag123,flag121,flag001;
BEGIN_MESSAGE_MAP(CHCCPApp, CWinApp)
	//{{AFX_MSG_MAP(CHCCPApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHCCPApp construction

CHCCPApp::CHCCPApp()
{
	flag123=true;
	flag121=true;
	flag001=true;
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CHCCPApp object

CHCCPApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CHCCPApp initialization

BOOL CHCCPApp::InitInstance()
{
	AfxEnableControlContainer();

	//��������ʱ�Զ���ԭ���ݿ�

	_bstr_t vSQL;
	_ConnectionPtr m_pConnection;
	CString str1;
	CString filename,ConnectString;
	CString sPath;
	GetModuleFileName(NULL,sPath.GetBufferSetLength (MAX_PATH+1),MAX_PATH);  //��ȡ��ǰ·��
	sPath.ReleaseBuffer();
	int nPos;
	nPos=sPath.ReverseFind('\\');
	sPath=sPath.Left(nPos);
	nPos=sPath.ReverseFind('\\');
	sPath=sPath.Left(nPos);
	filename=sPath+"\\database\\HCBAK";  //��ȡ���ݿⱸ���ļ�·��
	::CoInitialize(NULL);  //��ʼ��OLE/COM�⻷��
    m_pConnection.CreateInstance("ADODB.Connection");  //����connection����	
	m_pConnection->Open("driver={SQL Server};Server=HC\\MSSQL2008;Database=master;","","",adModeUnknown);  //���������ַ���,������BSTR�ͻ���_bstr_t����
	//m_pConnection->Open("driver={SQL Server};Server=HC\\MSSQL2008;Database=master;UID=sa;PWD=","","",adModeUnknown);  //���������ַ���,������BSTR�ͻ���_bstr_t����
	str1.Format("use master restore database HCCP from Disk = '%s' WITH MOVE 'BL_DataBase_Data'  TO  'c:\\HCCP.mdf', MOVE  'BL_DataBase_log'  TO  'c:\\HCCP.ldf'",filename);  //sql������ڻ�ԭ���ݿ�
	vSQL=(_bstr_t)str1;
	m_pConnection->Execute(vSQL,NULL,adCmdText);



#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CHCCPDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
