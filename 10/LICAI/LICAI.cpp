// LICAI.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "LICAI.h"
#include "LICAIDlg.h"
#include "odbcinst.h"
#include "LOGIN.h"
#include "PWSet.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
bool addflag,authorflag,loginflag=true,glflag=true;//�����ж�����ִ�е�����Ӳ��������޸Ĳ���;authorflag�������жϵ�ǰΪ���ֵ�½Ȩ��;loginflag������¼���������ϵ����ĸ�Ȩ�ޣ��ǹ���Ա���Ǳ���
CString ID,lpszFileName,logFileName,mianFileName;//ID����������ڵ�½���û�����ʲô,logFileName������ȡ��־·����lpszFileName������ȡ���ݿ�·��,mianFileName��¼������·��
int static num1=1,num2=1;//num1������¼����ԱȨ�޵��ʺŵ�½�Ĵ�����num2������¼����Ȩ�޵��ʺŵ�½�Ĵ���
/////////////////////////////////////////////////////////////////////////////
// CLICAIApp

BEGIN_MESSAGE_MAP(CLICAIApp, CWinApp)
	//{{AFX_MSG_MAP(CLICAIApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLICAIApp construction

CLICAIApp::CLICAIApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CLICAIApp object

CLICAIApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CLICAIApp initialization

BOOL CLICAIApp::InitInstance()
{
    CString sPath,user;//�������ݿ��ļ�·����
	GetModuleFileName(NULL,sPath.GetBufferSetLength (MAX_PATH+1),MAX_PATH);//ΪsPath����洢�ռ�
	sPath.ReleaseBuffer();
	int nPos;
	nPos=sPath.ReverseFind('\\');
	sPath=sPath.Left(nPos);//��ȡ�ļ���Debug·��,������Ϊ���а��ʱ�����ݿ���Է���ͬһĿ¼�¡�
	nPos=sPath.ReverseFind('\\');
	sPath=sPath.Left(nPos);//��ȡ�ļ��Ĺ����ļ���·��
    lpszFileName = sPath + "\\message.mdb";//�������ݿ��ļ�����       
    logFileName = sPath + "\\log.txt";
	CFileFind  fFind;
	if(!fFind.FindFile(lpszFileName))
	{
		::AfxMessageBox("û���ҵ����ݿ�message");
		exit(0);
	}
	CString szDesc;//���������Դ������
	szDesc.Format( "DSN=LICAI;FIL=Microsoft Access;DEFAULTDIR=%s;DBQ=%s;" ,sPath,lpszFileName);      
	//�������Դ
	if(!::SQLConfigDataSource(NULL,ODBC_ADD_DSN, "Microsoft Access Driver (*.mdb)",(LPCSTR)szDesc))
	{
		::AfxMessageBox("32λODBC����Դ���ô���!");
		exit(0);
	}
	bool passflag=false;//�����ж��Ƿ��½�ɹ�
	PWSet mySet;
	mySet.Open();
	LOGIN mydlg;
begin:	 
	mySet.Requery(); 
	if(mydlg.DoModal()==IDOK)
	{  
		if(mydlg.m_id==""||mydlg.m_password=="")
		{
			AfxMessageBox("�û������벻��Ϊ��");
			return false;
		}		
		if(mydlg.author=="����Ա")
		{
			loginflag=true;
			user="����Ա";
		}
		else
		{
			loginflag=false;
			user="����";
		}
		while(!mySet.IsEOF()) 
		{						
			mySet.m_ID.TrimLeft();
			mySet.m_ID.TrimRight();
            if(mySet.m_ID==mydlg.m_id&&mySet.m_PASSWORD==mydlg.m_password&&mySet.m_AUTHOR==mydlg.author)
			{ 
					mySet.Close();
					passflag=true;
					authorflag=true;
					ID=mydlg.m_id;
					COleDateTime oleDt=COleDateTime::GetCurrentTime();//��ȡ���صĵ�ǰʱ��
					CString strFileName=oleDt.Format("%Y��%m��%d�� %Hʱ%M��%S��");
					CString strTmp=strFileName+"\r\n\n"+user+ID+" ��½ϵͳ\r\n\n\n\n\n";
					CStdioFile file(logFileName,CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite);
					file.SeekToEnd();//�ȶ�λ���ļ�β��
					file.WriteString(strTmp);
					file.Close();
					break;
			}
			else 
					mySet.MoveNext();		
		}

		if(!passflag)
		{
			AfxMessageBox("��¼ʧ�ܣ�������");
			mydlg.m_password="";
			mydlg.m_id="";
			mydlg.m_password="";
			goto begin;
		}
	}
	else 
		return false;




	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CLICAIDlg dlg;
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
