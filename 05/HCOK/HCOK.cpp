// HCOK.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "HCOK.h"
#include "HCOKDlg.h"
#include "ADOConn.h"
#include "SkinPlusPlus.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
CString addroomtype,addcardtype,givenmoney,	mkusingername,     printmoneybake,	mkusingersex ,mkusingerarea ,	mkusingerpin,nowp,timestr1,timestr2,printprice ,printabate;;
int tempshow1,tempshow,showsinger1,showsinger2,delsongfresh,mainshowlist;
CRect rectsmall,rectlarge;
/////////////////////////////////////////////////////////////////////////////
// CHCOKApp

BEGIN_MESSAGE_MAP(CHCOKApp, CWinApp)
	//{{AFX_MSG_MAP(CHCOKApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHCOKApp construction

CHCOKApp::CHCOKApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}
CHCOKApp::~CHCOKApp()
{


}

/////////////////////////////////////////////////////////////////////////
// The one and only CHCOKApp object

CHCOKApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CHCOKApp initialization

BOOL CHCOKApp::InitInstance()
{
	AfxEnableControlContainer();
	::CoInitialize(NULL);  //��ʼ��OLE/COM�⻷��
	tempshow1=0;
	tempshow=0;
	showsinger1=0;
	showsinger2=0;
	delsongfresh=0;
	mainshowlist=0;

	//-----����master���ݿ�
	_ConnectionPtr m_pConnection;
	try
	{
		HRESULT hr = m_pConnection.CreateInstance("ADODB.Connection");//����Connection����
		if(SUCCEEDED(hr))
		{
			//hr = pConnection->Open("driver={SQL Server};Server=.;DATABASE=master;UID=sa;PWD=","","",adModeUnknown);//2000�汾
			hr = m_pConnection->Open("driver={SQL Server};Server=HC\\MSSQL2008;DATABASE=master;","","",adModeUnknown);//2005�����ϰ汾
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

	//��������ʱ�Զ���ԭ���ݿ�
	_bstr_t vSQL;
	
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
	filename=sPath+"\\database\\music.bak";  //��ȡ���ݿⱸ���ļ�·��

	//------�ж����ݿ��Ƿ����
	_RecordsetPtr pRecordset;
	pRecordset.CreateInstance("ADODB.Recordset");
	_variant_t vCount;
	try
	{
		_variant_t ra;
		pRecordset = m_pConnection->Execute("SELECT COUNT(*) FROM sysdatabases WHERE name = 'music'",&ra,adCmdText);
		vCount = pRecordset->GetCollect((_variant_t)(long)(0)); 
	}
	catch(_com_error e)
	{
		AfxMessageBox("error!");
		return false;
	}
	CString str;
	str.Format("%d", vCount.iVal);
	if(0 == vCount.iVal)
	{
		str1.Format("use master restore database music from Disk = '%s' WITH MOVE 'music_Data'  TO  'c:\\music.mdf', MOVE  'music_Log'  TO  'c:\\music.ldf'",filename);  //sql������ڻ�ԭ���ݿ�
		vSQL=(_bstr_t)str1;
		m_pConnection->Execute(vSQL,NULL,adCmdText);  //ִ�л�ԭ���ݿ����
	}
		
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CHCOKDlg dlg;
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
		//////////////////////////////////////////////////����
	
	return FALSE;
}
