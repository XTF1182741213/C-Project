// MapPublic.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MapPublic.h"

#include "MainFrm.h"
#include "MapPublicDoc.h"
#include "MapPublicView.h"
#include "odbcinst.h"

#include "LjxWnd.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapPublicApp

BEGIN_MESSAGE_MAP(CMapPublicApp, CWinApp)
	//{{AFX_MSG_MAP(CMapPublicApp)
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
// CMapPublicApp construction

CMapPublicApp::CMapPublicApp()
{
	m_show="";
	bEnableMenu=false;
	pitcure_name="����";
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMapPublicApp object

CMapPublicApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMapPublicApp initialization

BOOL CMapPublicApp::InitInstance()
{
	// CG: The following block was added by the Splash Screen component.
\
	{
\
		CCommandLineInfo cmdInfo;
\
		ParseCommandLine(cmdInfo);
\

\
	
\
	}
	AfxEnableControlContainer();

     
	CString sPath;//�������ݿ��ļ�·����
	GetModuleFileName(NULL,sPath.GetBufferSetLength (MAX_PATH+1),MAX_PATH);//ΪsPath����洢�ռ�
	sPath.ReleaseBuffer();
	int nPos;
	nPos=sPath.ReverseFind('\\');
	sPath=sPath.Left(nPos);//��ȡ�ļ���·��
    nPos=sPath.ReverseFind('\\');
    sPath=sPath.Left(nPos);//��ȡ�ļ���·��
	CString lpszFileName = sPath + "\\HangzhouBus.mdb";//�������ݿ��ļ�����
	CFileFind  fFind;
	if(!fFind.FindFile(lpszFileName))
	{
		::AfxMessageBox("û���ҵ����ݿ�");
		exit(0);
	}
	CString szDesc;//���������Դ������
	szDesc.Format( "DSN=HangzhouSet;Description=test;DESCRIPTION=The DataBase For show;\
		FIL=MicrosoftAccess;DEFAULTDIR=%s;DBQ=%s;" ,sPath,lpszFileName);
	//�������Դ
	if(!::SQLConfigDataSource(NULL,ODBC_ADD_DSN, "Microsoft Access Driver (*.mdb)",
		(LPCSTR)szDesc))
	{
		::AfxMessageBox("32λODBC����Դ���ô���!");
		exit(0);
	}
   


	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.
/*	
m_Skin.LoadSkinFile("xpgrean.smf");
m_Skin.SetDialogSkin("Dialog");
*/
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CLjxWnd *ljxljx=new CLjxWnd;  //����һ���´��ڶ���
	ljxljx->CreatLjxWnd ();       //��������
	ljxljx->CenterWindow ();      //����Ļ����
	ljxljx->ShowWindow (SW_SHOW); //��ʾ����
	ljxljx->UpdateWindow ();      //���´��ڣ�����OnPait����
	Sleep(1500);                 //�ȴ�����ָ������
	if (ljxljx!=NULL) ljxljx->SendMessage (WM_CLOSE); //�رմ���


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
		RUNTIME_CLASS(CMapPublicDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CMapPublicView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_Skin.SetWindowSkin(m_pMainWnd->m_hWnd, "MainFrame");
	m_pMainWnd->SetWindowText("�����й�����ѯϵͳ");
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
void CMapPublicApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CMapPublicApp message handlers


BOOL CMapPublicApp::PreTranslateMessage(MSG* pMsg)
{
	// CG: The following lines were added by the Splash Screen component.


	return CWinApp::PreTranslateMessage(pMsg);
}
