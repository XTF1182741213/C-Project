// GraduDeMIS.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "GraduDeMIS.h"
#include "GraduDeMISDlg.h"
#include "odbcinst.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString selectID;
CString strExternUser;
bool bstuExternFlag,btecrExternFlag,badminExternFlag;
/////////////////////////////////////////////////////////////////////////////
// CGraduDeMISApp

BEGIN_MESSAGE_MAP(CGraduDeMISApp, CWinApp)
	//{{AFX_MSG_MAP(CGraduDeMISApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraduDeMISApp construction

CGraduDeMISApp::CGraduDeMISApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CGraduDeMISApp object

CGraduDeMISApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CGraduDeMISApp initialization

BOOL CGraduDeMISApp::InitInstance()
{
	AfxEnableControlContainer();
	CString sPath;					//�������ݿ��ļ�·����
	GetModuleFileName(NULL,sPath.GetBufferSetLength (MAX_PATH+1),MAX_PATH);//ΪsPath����洢�ռ�
	sPath.ReleaseBuffer();
	int nPos;
	nPos=sPath.ReverseFind('\\');//��������ַ�
	sPath=sPath.Left(nPos);//��ȡ�ļ���·��
	nPos=sPath.ReverseFind('\\');
	sPath=sPath.Left(nPos);//��ȡ�ļ���·��
	CString lpszFileName = sPath + "\\db_gradu.mdb";//�������ݿ��ļ�����
	CFileFind  fFind;
	if(!fFind.FindFile(lpszFileName))
	{
		::AfxMessageBox("û���ҵ����ݿ�");
		exit(0);
	}
	CString szDesc;//���������Դ������
	szDesc.Format( "DSN=GraduDeMIS;FIL=Microsoft Access;DEFAULTDIR=%s;DBQ=%s;" ,sPath,lpszFileName);
	//�������Դ
	if(!::SQLConfigDataSource(NULL,ODBC_ADD_DSN, "Microsoft Access Driver (*.mdb)",(LPCSTR)szDesc))
	{
		::AfxMessageBox("32λODBC����Դ���ô���!");
		exit(0);
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

	CGraduDeMISDlg dlg;
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
