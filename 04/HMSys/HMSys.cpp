// HMSys.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "HMSys.h"
#include "LoadDlg.h"
#include "MainFrm.h"
#include "HMSysDoc.h"
#include "HMSysView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHMSysApp

BEGIN_MESSAGE_MAP(CHMSysApp, CWinApp)
	//{{AFX_MSG_MAP(CHMSysApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHMSysApp construction

CHMSysApp::CHMSysApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	m_strEmpID = "";
	m_strUser = "";;
	m_strType = "";
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CHMSysApp object

CHMSysApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CHMSysApp initialization

CString FindFilePath()
{
	CFileFind finder;
	finder.FindFile("*.bak");
	finder.FindNextFile();
	return  finder.GetFilePath();	
}

BOOL CHMSysApp::InitInstance()
{
	AfxEnableControlContainer();
	if(!AfxOleInit()) 
	{ 
		AfxMessageBox("OLE��ʼ������!"); 
		return FALSE; 
	}
	///
	//-----���ݿ�Ļ�ԭ
	//-----����master���ݿ�
	_ConnectionPtr pConnection;
	try
	{
		HRESULT hr = pConnection.CreateInstance("ADODB.Connection");//����Connection����
		if(SUCCEEDED(hr))
		{
			//hr = pConnection->Open("driver={SQL Server};Server=.;DATABASE=master;UID=sa;PWD=","","",adModeUnknown);//2000�汾
			hr = pConnection->Open("driver={SQL Server};Server=HC\\MSSQL2008;DATABASE=master;","","",adModeUnknown);//2005�����ϰ汾
			//hr = pConnection->Open("driver={SQL Server};Server=HC\\MSSQL2008;DATABASE=master; UID=sa; PWD=", "","",adModeUnknown);
		}
	}
	catch (_com_error e) //COM����ȡ��,��ִ��COM���ܵ�ʱ������������Բ�׽��_com_error���쳣
	{  
		CString strComError;
		strComError.Format("������: %08lx\n������Ϣ: %s\n����Դ: %s\n��������: %s",
			e.Error(),                  // ������
			e.ErrorMessage(),           // ������Ϣ
			(LPCSTR) e.Source(),        // ����Դ
			(LPCSTR) e.Description());  // ��������      
		
		::MessageBox(NULL,strComError,"����",MB_ICONEXCLAMATION);
	}
	//------�ж����ݿ��Ƿ����
	_RecordsetPtr pRecordset;
	pRecordset.CreateInstance("ADODB.Recordset");
	_variant_t vCount;
	try
	{
		_variant_t ra;
		pRecordset = pConnection->Execute("SELECT COUNT(*) FROM sysdatabases WHERE name = 'HMSys'",&ra,adCmdText);
		vCount = pRecordset->GetCollect((_variant_t)(long)(0)); 
	}
	catch(_com_error e)
	{
		AfxMessageBox("error!");
	}
	CString str;
	str.Format("%d", vCount.iVal);
	if(0 == vCount.iVal)
	{
		CString Sql;
		Sql.Format("USE MASTER RESTORE DATABASE HMSys FROM DISK = '%s' WITH MOVE 'HMSys_Data'  TO  'c:\\HMSys.mdf', MOVE  'HMSys_Log'  TO  'c:\\HMSys.ldf'", FindFilePath()) ;
		try
		{
			_variant_t ra;
			pRecordset = pConnection->Execute((_bstr_t)Sql,&ra,adCmdText);
			pRecordset->Close();
		}
		catch(_com_error e)
		{

		}
	}
	pConnection->Close();
	///////////////
	//-----����HMSys���ݿ�
	HRESULT hr = m_pConnection.CreateInstance("ADODB.Connection");//����Connection����
	try
	{
		if(SUCCEEDED(hr))
		{
			//hr = m_pConnection->Open("driver={SQL Server};Server=.;DATABASE=HMSys;UID=sa;PWD=1","","",adModeUnknown);//2000�汾
		    hr = m_pConnection->Open("driver={SQL Server};Server=HC\\MSSQL2008;DATABASE=HMSys;","","",adModeUnknown);//2005�����ϰ汾
			//hr = pConnection->Open("driver={SQL Server};Server=HC\\MSSQL2008;DATABASE=HMSys; UID=sa; PWD=", "","",adModeUnknown);
		}
	}
	catch (_com_error e) //COM����ȡ��,��ִ��COM���ܵ�ʱ������������Բ�׽��_com_error���쳣
	{  
		CString strComError;
		strComError.Format("������: %08lx\n������Ϣ: %s\n����Դ: %s\n��������: %s",
			e.Error(),                  // ������
			e.ErrorMessage(),           // ������Ϣ
			(LPCSTR) e.Source(),        // ����Դ
			(LPCSTR) e.Description());  // ��������      
		::MessageBox(NULL,strComError,"����",MB_ICONEXCLAMATION);
	}
	//�û���¼
	CLoadDlg load;
	BOOL flag = FALSE;
	while(!flag)
	{
		if(load.DoModal() == IDOK)
		{
			if(load.m_bFlag)
			{
				flag = TRUE;
				m_strUser = load.m_strUser;
			}
			else
			{
				AfxMessageBox("�û����������");
				load.m_strUser = load.m_strPwd = "";
			}
		}
		else
			return FALSE;
	}
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CHMSysDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CHMSysView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CHMSysApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CHMSysApp message handlers

