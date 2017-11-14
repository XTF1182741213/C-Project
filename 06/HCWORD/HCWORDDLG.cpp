// HCWORDDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HCWORD.h"
#include "HCWORDDlg.h"
//#include "HCWORDApp.h"
#include "ADDdlg.h"
#include "TESTdlg.h"
#include "YUU.h"
#include "YOUXI.h"
#include "TABDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
int mm=0;
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
// CHCWORDDlg dialog

CHCWORDDlg::CHCWORDDlg(CWnd* pParent /*=NULL*/)
: CDialog(CHCWORDDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHCWORDDlg)
	m_find = _T("");
	//	m_sno = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
}

void CHCWORDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHCWORDDlg)
	DDX_Control(pDX, IDC_LIST2, m_list1);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_EDIT1, m_find);
	//	DDX_Text(pDX, IDC_EDIT2, m_sno);
	
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_CLOCKFRAME, m_Clock);
}

BEGIN_MESSAGE_MAP(CHCWORDDlg, CDialog)
//{{AFX_MSG_MAP(CHCWORDDlg)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_WM_KEYUP()
ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnItemchangedList1)
ON_COMMAND(IDC_HU, OnHu)
ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
ON_COMMAND(ID_ciku, Onciku)
ON_COMMAND(ID_BEIFEN, OnBeifen)
ON_COMMAND(ID_HELP, OnHelp)
ON_COMMAND(ID_MENUITEM32778, OnMenuitem32778)
ON_COMMAND(ID_JI, OnJi)
ON_COMMAND(ID_MENUITEM32782, OnMenuitem32782)
ON_COMMAND(ID_JL, OnJl)
ON_WM_CREATE()
ON_COMMAND(ID_BEN, OnBen)
ON_COMMAND(ID_YU, OnYu)
ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHCWORDDlg message handlers

BOOL CHCWORDDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	sndPlaySound("������ɢ.wav",SND_ASYNC); 
    m_list.InsertColumn(0,"        Ŀ¼",LVCFMT_CENTER,160); //����б�ؼ�������
    m_list1.InsertColumn(0,"                                           ���",LVCFMT_CENTER,600);
    m_list.SetTextColor(RGB(0,0,0));
	m_list1.SetTextColor(RGB(0,0,0));  //��ʼ���б����ɫ
	SetWindowLong(m_hWnd, GWL_EXSTYLE, GetWindowLong(m_hWnd, GWL_EXSTYLE)^0x80000);             
    HINSTANCE hInst =LoadLibrary("User32.DLL");   //��ʽ����DLL   
    if (hInst != NULL)   
    {   
		typedef BOOL(WINAPI *MYFUNC)(HWND, COLORREF, BYTE, DWORD);   
		MYFUNC pFunc = (MYFUNC)GetProcAddress(hInst, "SetLayeredWindowAttributes");//ȡ�ú���ָ��     
		if (pFunc!=NULL)   
		{   
			pFunc(m_hWnd, 0, 240, 2);//  240��������͸����, ��ֵ��Χ0-255, 255��ʾ��͸����   
		}   
		FreeLibrary(hInst);   
		hInst = NULL;   
	}  
	SetTimer(1,1000,NULL); //ÿ��1��ִ��OnTimer
	pdb=new CDatabase;   //�������ݿ����ָ��
	pdb->Open("ODBC;DSN=�ʿ�;Trusted_Connection=Yes");	 
	m_pset=new HCset(pdb); //�������ݱ����ָ��
	m_btn.SubclassDlgItem(IDC_BUTTON3,this);     //Ϊ��ť���λͼ
	m_btn.SetIcon(IDI_ICON2);
	m_btn.SetFlat(FALSE); 
	m_btn1.SubclassDlgItem(IDC_BUTTON4,this);
	m_btn1.SetIcon(IDI_ICON3);
	m_btn1.SetFlat(FALSE);
	m_btn2.SubclassDlgItem(IDC_BUTTON5,this);
	m_btn2.SetIcon(IDI_ICON4);
	m_btn2.SetFlat(FALSE);
	m_btn3.SubclassDlgItem(IDC_BUTTON6,this);
	m_btn3.SetIcon(IDI_ICON5);
	m_btn3.SetFlat(FALSE);
	m_Clock.Start(IDB_CLOCKST_PANE, IDB_CLOCKST_SMALL,IDB_CLOCKST_BIG);  //���������ӣ�����λͼ
	return TRUE;  
}

void CHCWORDDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CHCWORDDlg::OnPaint() 
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
	
	
	//	CDialog::OnPaint();
	
	
	
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CHCWORDDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CHCWORDDlg::LoadData()
{
    CString str,str1,str2,str3,str4,str5,str6,str7,str8;    //�����ַ�������
	int i=0,j,n=0;
	str1="Ӣ���ʵ�:";    //�ַ�����ֵ                                       
	str3="    vi:";
	str4="    vt:";
	str5="    n:";
	str6="    adj:";
	str7="    adv:";
	str8="����:";
	str2="��������:";
    m_list.DeleteAllItems();          //����б�ؼ�
	if(m_find!="")
	{                                                                                          
		m_pset->m_eg.TrimRight();
		m_list1.DeleteAllItems();
		m_list1.InsertItem(0,str1);           //0,Ӣ���ʵ�
		str.Format("      %s",m_pset->m_eg);       //�����ݿ��е����ݶ�Ӧ������ʾ
		m_list1.InsertItem(1,str);   //1,����                        
		if(m_pset->m_vi!="")
		{ 
			m_pset->m_vi.TrimRight();
			m_list1.InsertItem(2,str3);
			str.Format("      %s",m_pset->m_vi);
			m_list1.InsertItem(3,str);
		}
		if(m_pset->m_vt!="")
		{
			m_pset->m_vt.TrimRight();
			m_list1.InsertItem(4,str4);
			str.Format("      %s",m_pset->m_vt);
			m_list1.InsertItem(5,str);
		}
		if(m_pset->m_n!="")
		{
			m_pset->m_n.TrimRight();
			m_list1.InsertItem(6,str5);
			str.Format("      %s",m_pset->m_n);
			m_list1.InsertItem(7,str);
		}
		if(m_pset->m_adj!="")
		{ 
			m_pset->m_adj.TrimRight();
			m_list1.InsertItem(8,str6);
			str.Format("      %s",m_pset->m_adj);
			m_list1.InsertItem(9,str);
		}
		if(m_pset->m_adv!="")
		{ 
			m_pset->m_adv.TrimRight();
			m_list1.InsertItem(10,str7);
			str.Format("      %s",m_pset->m_adv);
			m_list1.InsertItem(11,str);
		}
		if(m_pset->m_zw!="")
		{ 
			m_pset->m_zw.TrimRight();
			m_list1.InsertItem(12,str8);
			str.Format("      %s",m_pset->m_zw);
			m_list1.InsertItem(13,str);
		}
		m_list1.InsertItem(14,str2);
		m_list1.InsertItem(15,str);
		while(!m_pset->IsEOF())
		{		          
			m_pset->MoveNext();
			n++;
		}
		if(n!=0)
		{
			m_pset->MoveFirst();          //��¼�ƶ�����һ��
			for(j=n;j>=1;j--)	 
			{
				m_pset->m_eg.TrimRight();
				str.Format("%s",m_pset->m_eg);
				m_list.InsertItem(i,str);
				m_pset->MoveNext();
				i++;
			} 
		}
	}
    m_pset->Close();    //�ر����ݱ�
}

void CHCWORDDlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	UpdateData();       //ˢ������
    CString str1;
	m_pset->m_strSort="eg";
	str1.Format("select * from eh where eg like '%s%%'",m_find);        //ģ����ѯ����
    m_pset->Open(AFX_DB_USE_DEFAULT_TYPE,str1); //������д�����ݿ�
	LoadData();         //���ú���
	CDialog::OnKeyUp(nChar, nRepCnt, nFlags);
}

BOOL CHCWORDDlg::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYUP)   
	{   
		return SendMessage(WM_KEYUP,pMsg->wParam,pMsg->lParam);  //���·���WM_KEYUP��Ϣ   
	}     
	return CDialog::PreTranslateMessage(pMsg);
}

void CHCWORDDlg::OnButton1() 
{
	UpdateData();
	CString str2;
	str2.Format("select * from eh where eg='%s'",m_find);
	m_pset->Open(AFX_DB_USE_DEFAULT_TYPE,str2);
	LoadData();
}
void CHCWORDDlg::ShowData()
{
    CString str;
	
	int i=0;
    m_list1.DeleteAllItems();
	while(!m_pset->IsEOF())
	{		  
		str.Format("%s",m_pset->m_zw);
		m_list1.InsertItem(i,str);
		m_pset->MoveNext();
		i++;
	}
    m_pset->Close();
}

void CHCWORDDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	//	new	CFaderWnd(this, 1000);
	ADDdlg mydlg;        //�����¶���
	mydlg.DoModal();     //������Ϣ����
}

void CHCWORDDlg::OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	CString str,str1,str3,str5,str4,str6,str7,str8;
	str3="    vi:";
	str4="    vt:";
	str5="    n:";
	str6="    adj:";
	str7="    adv:";
	str8="����:";
	int i=0,n=0;
	int selectrow=pNMListView->iItem;
    str1=m_list.GetItemText(selectrow,0);
    str.Format("select * from eh where eg='%s'",str1);
    m_pset->Open(AFX_DB_USE_DEFAULT_TYPE,str);
    m_list1.DeleteAllItems();
	m_list1.InsertItem(0,"Ӣ���ʵ�:");
	str.Format("      %s",m_pset->m_eg);
	m_list1.InsertItem(1,str);
    if(m_pset->m_vi!="")
	{ m_pset->m_vi.TrimRight();
	i=2;
	m_list1.InsertItem(i,str3);
	str.Format("      %s",m_pset->m_vi);
	m_list1.InsertItem(++i,str);
	}
	if(m_pset->m_vt!="")
	{i=4;m_pset->m_vt.TrimLeft();
	m_list1.InsertItem(i,str4);
	str.Format("      %s",m_pset->m_vt);
	m_list1.InsertItem(++i,str);
	}
	if(m_pset->m_n!="")
	{i=6;
	m_list1.InsertItem(i,str5);
	str.Format("      %s",m_pset->m_n);
	m_list1.InsertItem(++i,str);
	}
	if(m_pset->m_adj!="")
	{ i=8;
	m_list1.InsertItem(i,str6);
	str.Format("      %s",m_pset->m_adj);
	m_list1.InsertItem(++i,str);
	}
	if(m_pset->m_adv!="")
	{ i=10;
	m_list1.InsertItem(i,str7);
	str.Format("      %s",m_pset->m_adv);
	m_list1.InsertItem(++i,str);
	}
	   if(m_pset->m_zw!="")
	   { i=12;
	   m_list1.InsertItem(i,str8);
	   str.Format("      %s",m_pset->m_zw);
	   m_list1.InsertItem(++i,str);
	   }
	   
	   m_pset->Close();
	   *pResult = 0;
}

void CHCWORDDlg::OnHu() 
{	
	AfxMessageBox("gyghg");
	
}



void CHCWORDDlg::OnButton3() 
{YUU dlg;
dlg.DoModal();

}

void CHCWORDDlg::OnButton4() 
{
	TABDlg dlg;
	dlg.DoModal();	
}

void CHCWORDDlg::OnButton5() 
{TESTdlg mydlg;
mydlg.DoModal();

}

void CHCWORDDlg::OnButton6() 
{YOUXI mydlg;
mydlg.DoModal();

}

void CHCWORDDlg::Onciku() 
{	
}

void CHCWORDDlg::OnBeifen() 
{
	
	CString   strDes;  
	static   char   BASED_CODE   szFilter[]   =   "ACCSESS   Files   (*.mdb)   |*.mdb||"; //�ɴ򿪵��ļ�����
    CFileDialog   cFileDlg(FALSE,".mdb",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter,this);   //false�������Ϊ����true�����򿪡�
    cFileDlg.m_ofn.lStructSize   =   88;   
	if(cFileDlg.DoModal()   ==   IDOK)   
	{  
		strDes=cFileDlg.GetPathName();     //Ҫ���ݵ��ļ���(ȫ·��)   
		CopyFile(lpszFileName,strDes,FALSE);
		MessageBox("       ���ݿⱸ�ݳɹ�         ","���Ӵʵ�ϵͳ",MB_OK|MB_ICONINFORMATION);
		
	}
	
	
}

void CHCWORDDlg::OnHelp() 
{
	BANZGHU dlg;
	dlg.DoModal();	
	
}

void CHCWORDDlg::OnMenuitem32778() 
{ 
	CString   strDes;  
	static   char   BASED_CODE   szFilter[]   =   "ACCSESS   Files   (*.mdb)   |*.mdb||";   //���ô򿪵��ļ�������ʲô�����һ��|ǰ����Լ������������Ҫ����������
    CFileDialog   cFileDlg(true,".mdb",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter,this);//true��ʾ�Ǵ򿪵ķ�ʽ��������ʾ���������֡�
    cFileDlg.m_ofn.lStructSize   =   88;   
	if(cFileDlg.DoModal()   ==   IDOK)   
	{  
		strDes   =   cFileDlg.GetPathName();  //ѡ��Ҫ��ԭ�����ݿ���ļ���(ȫ·��)  
		CFile TempFile; 
		CStdioFile file; 
		if(file.Open(logFileName,CFile::modeRead))
		{
			file.Close();
			TempFile.Remove(logFileName);
		}
		CopyFile(strDes,lpszFileName,FALSE);
		MessageBox("       ���ݿ⻹ԭ�ɹ�         ","���Ӵʵ�ϵͳ",MB_OK|MB_ICONINFORMATION);
	}
}



void CHCWORDDlg::OnJi() 
{
	ADDdlg dlg;
	dlg.DoModal();
	
}

void CHCWORDDlg::OnMenuitem32782() 
{
	AfxGetMainWnd()->SendMessage(WM_CLOSE);
}

void CHCWORDDlg::OnJl() 
{BANZGHU dlg;
dlg.DoModal();

}

int CHCWORDDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	if(aa==0)	
	{CSplashWnd::ShowSplashScreen(this);    //��ʾ��������
	Sleep(2000);
	}
	return 0;
}

void CHCWORDDlg::OnBen() 
{
	CAboutDlg dlg;
	dlg.DoModal();
	
}


void CHCWORDDlg::OnYu() 
{
	PlaySound(NULL,NULL,NULL);
}

