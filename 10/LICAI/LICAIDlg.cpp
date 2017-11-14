// LICAIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LICAI.h"
#include "LICAIDlg.h"
#include "add.h"
#include "PWSet.h"
#include "REGIST.h"
#include "XGMIMA.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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

/////////////////////////////////////////////////////////////////////////////
// CLICAIDlg dialog

CLICAIDlg::CLICAIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLICAIDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLICAIDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLICAIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLICAIDlg)
	DDX_Control(pDX, IDC_RECOVER, m_RECOVER);
	DDX_Control(pDX, IDC_COPY, m_COPY);
	DDX_Control(pDX, IDC_MODIFY, m_MODIFY);
	DDX_Control(pDX, IDC_GUANLI, m_GUANLI);
	DDX_Control(pDX, IDC_ADD, m_ADD);
	DDX_Control(pDX, IDC_TAB1, m_tab);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLICAIDlg, CDialog)
	//{{AFX_MSG_MAP(CLICAIDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab1)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_GUANLI, OnGuanli)
	ON_BN_CLICKED(IDC_MODIFY, OnModify)
	ON_BN_CLICKED(IDC_COPY, OnCopy)
	ON_BN_CLICKED(IDC_RECOVER, OnRecover)
	ON_BN_CLICKED(IDZHUXIAO, OnZhuxiao)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLICAIDlg message handlers

BOOL CLICAIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
    //ΪTab Control�������ҳ��
	m_tab.InsertItem(0, _T("�û���֧��ϸ���"));
    m_tab.InsertItem(1, _T("��֧���ͳ�������"));
	m_tab.InsertItem(2, _T("ͼ��ͳ����Ϣ"));
    m_tab.InsertItem(3, _T("���ʹ����־"));
    //�����Ի���
    m_page1.Create(IDD_PAGE1, &m_tab);
    m_page2.Create(IDD_PAGE2, &m_tab);
	m_page3.Create(IDD_PAGE3, &m_tab);
    m_page4.Create(IDD_PAGE4, &m_tab);
    //�趨��Tab����ʾ�ķ�Χ
    CRect rc;
    m_tab.GetClientRect(rc);
    rc.top += 20;
    rc.bottom -= 8;
    rc.left += 8;
    rc.right -= 8;
	m_page1.MoveWindow(&rc);
    m_page2.MoveWindow(&rc);
	m_page3.MoveWindow(&rc);
    m_page4.MoveWindow(&rc);
//�ѶԻ������ָ�뱣������
    pDialog[0] = &m_page1;
    pDialog[1] = &m_page2;
	pDialog[2] = &m_page3;
    pDialog[3] = &m_page4;
//��ʾ��ʼҳ��
    pDialog[0]->ShowWindow(SW_SHOW);
    pDialog[1]->ShowWindow(SW_HIDE);
	pDialog[2]->ShowWindow(SW_HIDE);
	pDialog[3]->ShowWindow(SW_HIDE);
//���浱ǰѡ��
    m_CurSelTab = 0;
    if(!loginflag)
	{
		m_ADD.EnableWindow(FALSE);
		m_GUANLI.EnableWindow(FALSE);
		m_COPY.EnableWindow(FALSE);
		m_RECOVER.EnableWindow(FALSE);
	}
	return TRUE;
}

void CLICAIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLICAIDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLICAIDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CLICAIDlg::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	pDialog[m_CurSelTab]->ShowWindow(SW_HIDE);
    m_CurSelTab = m_tab.GetCurSel();
    pDialog[m_CurSelTab]->ShowWindow(SW_SHOW);
	*pResult = 0;
}


void CLICAIDlg::OnAdd() 
{
	PWSet mySet;
	mySet.Open();
	REGIST mydlg;
	if(mydlg.DoModal()==IDOK)
	{
		while(!mySet.IsEOF()) 
		{
			if(mySet.m_ID!=mydlg.m_id)
				mySet.MoveNext();
			else 
			{
				MessageBox("�û����Ѵ���","ע��",MB_OK|MB_ICONINFORMATION);
				break;
			}
		}
		if(mydlg.m_id==""||mydlg.m_password==""||mydlg.m_npassword=="")
		{
			MessageBox("�û�������ȷ�����벻��Ϊ��","ע��",MB_OK|MB_ICONINFORMATION);
			return;
		}
		if(mydlg.m_password!=mydlg.m_npassword)
		{
			MessageBox("�����������벻��","ע��",MB_OK|MB_ICONINFORMATION);
			return;
		}
		else 
		{   
			mySet.AddNew();
			CString strTmp;
			COleDateTime oleDt=COleDateTime::GetCurrentTime();//��ȡ���صĵ�ǰʱ��
			CString strFileName=oleDt.Format("%Y��%m��%d�� %Hʱ%M��%S��");
			strTmp=strFileName+"\r\n����Ա "+ID+"����"+mydlg.m_id+"�û�,Ȩ��Ϊ"+mySet.m_AUTHOR+"\r\n\n";
			mySet.m_ID=mydlg.m_id;
			mySet.m_PASSWORD=mydlg.m_password;
			mySet.m_AUTHOR=mydlg.author;
			mySet.Update();
			mySet.Requery();
			MessageBox("�ɹ�����û�","��ͥ�������ϵͳ",MB_OK|MB_ICONINFORMATION);			
    		CStdioFile file(logFileName,CFile::modeNoTruncate|CFile::modeWrite);
        	file.SeekToEnd();//�ȶ�λ���ļ�β��
	       	file.WriteString(strTmp);
        	file.Close();
		}	
	}	
}

void CLICAIDlg::OnGuanli() 
{
	GUANLI mydlg;
	mydlg.DoModal();
	
}

void CLICAIDlg::OnModify() 
{
	PWSet mySet;
	mySet.Open();
begin:          
	mySet.Requery();
	XGMIMA mydlg;
	if(mydlg.DoModal()==IDOK)
	{ 
		while(!mySet.IsEOF()) 
		{
			if(mySet.m_ID!=mydlg.m_id)
				mySet.MoveNext();
			else 
				break;
		}
		if(mydlg.m_id==""||mydlg.m_npassword==""||mydlg.m_anpassword==""||mydlg.m_password=="")
		{
			MessageBox("   �û���ԭ��������ȷ�����벻��Ϊ��  ","��ͥ�������ϵͳ",MB_OK|MB_ICONINFORMATION);
			goto begin;
		}
		mySet.m_ID.TrimLeft();
        mySet.m_ID.TrimRight();
		if(mySet.m_ID!=mydlg.m_id)
		{
			MessageBox("          �û�������           ","��ͥ�������ϵͳ",MB_OK|MB_ICONINFORMATION);
			goto begin;
		}
		if(mySet.m_PASSWORD!=mydlg.m_password)
		{
			MessageBox("       ԭ�������,�޷��޸�         ","��ͥ�������ϵͳ",MB_OK|MB_ICONINFORMATION);
			goto begin;
		}
		if(mydlg.m_npassword!=mydlg.m_anpassword)
		{ 
			MessageBox("       �������������벻��         ","��ͥ�������ϵͳ",MB_OK|MB_ICONINFORMATION);
			goto begin;
		}
		else 
		{        
			mySet.Edit();
			mySet.m_PASSWORD=mydlg.m_npassword;
			mySet.Update();
			mySet.Requery();
			MessageBox("       �û������޸ĳɹ�         ","��ͥ�������ϵͳ",MB_OK|MB_ICONINFORMATION);
	    	COleDateTime oleDt=COleDateTime::GetCurrentTime();//��ȡ���صĵ�ǰʱ��
		   	CString strFileName=oleDt.Format("%Y��%m��%d�� %Hʱ%M��%S��");
       		CString strTmp=strFileName+"\r\n\n�û� "+mydlg.m_id+" �޸Ŀ���ɹ�\r\n\n\n\n\n";
	   		CStdioFile file(logFileName,CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite);
      		file.SeekToEnd();//�ȶ�λ���ļ�β��
	       	file.WriteString(strTmp);
      		file.Close();
		}	
	}
}

void CLICAIDlg::OnCopy()    //���ݿ�� ����
{
    CString   strDes;  
	static   char   BASED_CODE   szFilter[]   =   "ACCSESS   Files   (*.mdb)   |*.mdb||"; //�ɴ򿪵��ļ�����
    CFileDialog   cFileDlg(FALSE,".mdb",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter,this);   //false�������Ϊ����true�����򿪡�
    cFileDlg.m_ofn.lStructSize   =   88;   
	if(cFileDlg.DoModal()   ==   IDOK)   
	{  
		strDes   =   cFileDlg.GetPathName();   //Ҫ���ݵ��ļ���(ȫ·��)   
	    CopyFile(lpszFileName,strDes,FALSE);
	    MessageBox("       ���ݿⱸ�ݳɹ�         ","��ͥ�������ϵͳ",MB_OK|MB_ICONINFORMATION);
		COleDateTime oleDt=COleDateTime::GetCurrentTime();//��ȡ���صĵ�ǰʱ��
	   	CString strFileName=oleDt.Format("%Y��%m��%d�� %Hʱ%M��%S��");
   		CString strTmp=strFileName+"\r\n\n����Ա "+ID+" �ɹ��������ݿ�\r\n\n\n\n\n";
		CStdioFile file(logFileName,CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite);
     	file.SeekToEnd();//�ȶ�λ���ļ�β��
	   	file.WriteString(strTmp);
      	file.Close();
    }	
}

void CLICAIDlg::OnRecover()    //���ݵĻָ�
{
	CString   strDes;  
	static   char   BASED_CODE   szFilter[]   =   "ACCSESS   Files   (*.mdb)   |*.mdb||";   //���ô򿪵��ļ�������ʲô�����һ��|ǰ����Լ������������Ҫ����������
    CFileDialog   cFileDlg(true,".mdb",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter,this);   //true��ʾ�Ǵ򿪵ķ�ʽ��������ʾ���������֡�
    cFileDlg.m_ofn.lStructSize   =   88;   
	if(cFileDlg.DoModal()   ==   IDOK)   
	{  
		strDes   =   cFileDlg.GetPathName();   //ѡ��Ҫ��ԭ�����ݿ���ļ���(ȫ·��)  
		CFile TempFile; 
		CStdioFile file; 
		if(file.Open(logFileName,CFile::modeRead))
		{
			file.Close();
			TempFile.Remove(logFileName);
		}
		CopyFile(strDes,lpszFileName,FALSE);
		MessageBox("       ���ݿ⻹ԭ�ɹ�         ","��ͥ�������ϵͳ",MB_OK|MB_ICONINFORMATION);
		COleDateTime oleDt=COleDateTime::GetCurrentTime();//��ȡ���صĵ�ǰʱ��
	   	CString strFileName=oleDt.Format("%Y��%m��%d�� %Hʱ%M��%S��");
   		CString strTmp=strFileName+"\r\n\n����Ա "+ID+" �ɹ���ԭ���ݿ�\r\n\n\n\n\n";
		CStdioFile sfile(logFileName,CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite);
     	sfile.SeekToEnd();//�ȶ�λ���ļ�β��
	   	sfile.WriteString(strTmp);
      	sfile.Close();
    }
}

void CLICAIDlg::OnCancel()    //�����õ�����������������رմ��� ����
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CLICAIDlg::OnZhuxiao() 
{
	if(MessageBox("          ȷ��ע����ǰϵͳ��?                 ","�Ƿ�ע��",MB_YESNO|MB_ICONINFORMATION)==IDYES)
	{
		OnCancel();
        CString   cmdLine=mianFileName;   
        STARTUPINFO   si;   
        ZeroMemory(&si,sizeof(si));   
        si.cb=sizeof(si);   
        PROCESS_INFORMATION   pi;   
        ZeroMemory(&pi,sizeof(pi));   
		if(CreateProcess(NULL,cmdLine.GetBufferSetLength(MAX_PATH+1),NULL,NULL,FALSE,CREATE_NO_WINDOW,NULL,NULL,&si,&pi))   
		{   
			CloseHandle(pi.hThread);   
            CloseHandle(pi.hProcess);   
		}   
		WaitForSingleObject(pi.hProcess,INFINITE);
		COleDateTime oleDt=COleDateTime::GetCurrentTime();//��ȡ���صĵ�ǰʱ��
	   	CString strFileName=oleDt.Format("%Y��%m��%d�� %Hʱ%M��%S��");
   		CString strTmp=strFileName+"\r\n\n�û� "+ID+" ע��ϵͳ\r\n\n\n\n\n";
		CStdioFile sfile(logFileName,CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite);
     	sfile.SeekToEnd();//�ȶ�λ���ļ�β��
	   	sfile.WriteString(strTmp);
      	sfile.Close();
	}	
}
