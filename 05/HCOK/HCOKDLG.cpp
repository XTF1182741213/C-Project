// HCOKDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HCOK.h"
#include "HCOKDlg.h"
#include "ADMIN.h"
#include "ManageDLG.h"
#include "ADOConn.h"
#include "SINGIN.h"
#include "BYSGRDLG.h"
#include "BYPINYINDLG.h"
#include "BYZISHUDLG.h"
#include "BYSONGTYPDLG.h"
#include "SELECTEDDLG.h"
#include "UserPrintDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
CString playsongname;//////////////////////////���ŵĸ�����
CString  playpath;///////////////////////////////�����ļ�·��
CString playsongformat;//////////////////////////���ŵĸ�����ʽ
CString delmuname1;////////////////////////////////Ҫɾ���ĸ�����
CString seepath;
int row;
int radiocheck;
bool     Menutype;
int mode;////////////////////��ʽ
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
// CHCOKDlg dialog

CHCOKDlg::CHCOKDlg(CWnd* pParent /*=NULL*/)
: CDialog(CHCOKDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHCOKDlg)
	m_text = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHCOKDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHCOKDlg)
	DDX_Control(pDX, IDC_SHOWTEXT, m_textctrl);
	DDX_Control(pDX, IDC_LIST2, m_list);
	DDX_Control(pDX, IDC_MEDIAPLAYER1, m_mediaplayer);
	DDX_Text(pDX, IDC_SHOWTEXT, m_text);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHCOKDlg, CDialog)
//{{AFX_MSG_MAP(CHCOKDlg)
ON_COMMAND_RANGE(IDC_RADIOdb,IDC_RADIOlx, GetPlayMode)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_VOLUP, OnVolup)
ON_BN_CLICKED(IDC_VOLDOWN, OnVoldown)
ON_BN_CLICKED(IDC_QIUC, OnQiuc)
ON_BN_CLICKED(IDC_QBACK, OnQback)
ON_BN_CLICKED(IDC_PLAYPAUSE, OnPlaypause)
ON_BN_CLICKED(IDC_STOP, OnStop)
ON_BN_CLICKED(IDC_MANAGE, OnManage)
ON_BN_CLICKED(IDC_LOGOUT, OnLogout)
ON_BN_CLICKED(IDC_CHECKINOUT, OnCheckinout)
ON_WM_TIMER()
ON_BN_CLICKED(IDC_SINFIND, OnSinfind)
ON_BN_CLICKED(IDC_PYFIND, OnPyfind)
ON_BN_CLICKED(IDC_NUFIND, OnNufind)
ON_BN_CLICKED(IDC_TFIND, OnTfind)
ON_BN_CLICKED(IDC_SELECTED, OnSelected)
ON_NOTIFY(NM_DBLCLK, IDC_LIST2, OnDblclkList2)
ON_BN_CLICKED(IDC_PREVIOUS, OnPrevious)
ON_BN_CLICKED(IDC_NEXT, OnNext)
ON_WM_CONTEXTMENU()
ON_COMMAND(ID_MENUDANXUN, OnMenudanxun)
ON_COMMAND(ID_MENUDELALL, OnMenudelall)
ON_COMMAND(ID_MENUDELDAN, OnMenudeldan)
ON_COMMAND(ID_MENUNANQU, OnMenunanqu)
ON_COMMAND(ID_MENUSHUBO, OnMenushubo)
ON_COMMAND(ID_MENUXUNBO, OnMenuxunbo)
ON_BN_CLICKED(IDC_DELLIST, OnDellist)
ON_WM_CLOSE()
ON_NOTIFY(NM_RCLICK, IDC_LIST2, OnRclickList2)
ON_BN_CLICKED(IDC_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHCOKDlg message handlers

BOOL CHCOKDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// Add "About..." menu item to system menu.
	
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	//***********��ʼ������ָ��***********************//	
	seleceddlg  =  NULL ; //�ѵ����
	bysingerdlg = NULL;  //�����ֲ�ѯ
	bypinyindlg = NULL;   //��ƴ����ѯ 
	bynumdlg =NULL;       //��������������ѯ
	bysongtypedlg = NULL;  //����������ѯ	
	//**************************************************///
	m_text="���ϵͳ";            //m_text���ַ�����Ӧ��ֵ���� 
	m_textctrl.SetFontSize(27);
	m_textctrl.SetTextColor(RGB(0,255,0));
	m_textctrl.SetBkColor(RGB(247,247,247));
	m_textctrl.SetFontBold(TRUE);
	m_textctrl.SetText(m_text);	
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_list.InsertColumn(0,"���",LVCFMT_CENTER,140);
	m_list.InsertColumn(1,"��Ŀ����",LVCFMT_CENTER,140);
	m_list.InsertColumn(2,"����",LVCFMT_CENTER,140);
	m_list.InsertColumn(3,"�������",LVCFMT_CENTER,140);
	m_list.InsertColumn(4,"�ļ���",LVCFMT_CENTER,140);
	m_list.InsertColumn(5,"�ļ���ʽ",LVCFMT_CENTER,140);	   
	///////////////////////////////////////////////////////////////
	timenum=-1;     //��ʼ��ʱ����Ч
	SetTimer(1,1000,NULL);   //�趨��ʱ��
	row=0;    //��ʼ���ڵ�һ��
	m_list.SetItemState(row,LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
	m_list.SetFocus();     //�趨list�ؼ��Ľ���  
	/////////////////////////////////////
	/////////////////////////////////////////////////////////////��ʱ��������
	   
	_bstr_t createlistsql,  createsql;
	ADOConn m_AdoConn;
	createsql = "Create table usertemp(tmuname varchar(50),tformate varchar(50),tfilename varchar(50),tsongtype varchar(50),tsingername varchar(50),tsingerpin varchar(50),playpath  varchar(200))"; 
	createlistsql = "Create table playlist(tmuname varchar(50),tformate varchar(50),tfilename varchar(50),tsongtype varchar(50),tsingername varchar(50),tsingerpin varchar(50),playpath  varchar(200))";   
	m_AdoConn.ExecuteSQL(createsql);///����usertemp�����ڴ���û���ĸ�      �ڳ���ر�ʱɾ��
	m_AdoConn.ExecuteSQL(createlistsql);//����playlist�����ڴ���û����ڲ��ŵĸ�  �ڳ���ر�ʱɾ��
	//***********************������Ӧ����*******************************************//
	GetDlgItem(IDC_PREVIOUS)->EnableWindow(false);
	   GetDlgItem(IDC_NEXT)->EnableWindow(false);
	   GetDlgItem(IDC_VOLUP)->EnableWindow(false);
	   GetDlgItem(IDC_VOLDOWN)->EnableWindow(false);
	   GetDlgItem(IDC_QIUC)->EnableWindow(false);
	   GetDlgItem(IDC_QBACK)->EnableWindow(false);
	   GetDlgItem(IDC_PLAYPAUSE)->EnableWindow(false);
	   
	   
	   GetDlgItem(IDC_STOP)->EnableWindow(false);
	   GetDlgItem(IDC_SELECTED)->EnableWindow(false);
	   GetDlgItem(IDC_DELLIST)->EnableWindow(false);
	   GetDlgItem(IDC_SINFIND)->EnableWindow(false);
	   GetDlgItem(IDC_PYFIND)->EnableWindow(false);
	   GetDlgItem(IDC_NUFIND)->EnableWindow(false);
	   GetDlgItem(IDC_TFIND)->EnableWindow(false);
	   
	   //************************************************************//
	   ShowListDate();//��ʾ����
	   // TODO: Add extra initialization here
	   /////////////////////////////////////////////////////////����Ĭ�ϲ��ŷ�ʽ
	   mode=3;
	   ((CButton *)GetDlgItem(IDC_RADIOdx))->SetCheck(false);  //���Ʋ���ģʽ��
	   ((CButton *)GetDlgItem(IDC_RADIOdb))->SetCheck(false);
	   ((CButton *)GetDlgItem(IDC_RADIOxb))->SetCheck(false);
	   ((CButton *)GetDlgItem(IDC_RADIOlx))->SetCheck(true);/////////////ѭ�������б�
	   return TRUE;  // return TRUE  unless you set the focus to a control
}

void CHCOKDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CHCOKDlg::OnPaint() 
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
HCURSOR CHCOKDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CHCOKDlg::GetPlayMode(UINT nID)
{
	switch(nID)
	{
	case IDC_RADIOdb:mode=0;break;
	case IDC_RADIOdx:mode=1;break;
	case IDC_RADIOxb:mode=2;break;
	case IDC_RADIOlx:mode=3;break;
	}
}
void CHCOKDlg::OnVolup()  //�������ؼ��Ӵ�����
{
	if(m_mediaplayer.GetPlayState()!=2)return;
	long vl=m_mediaplayer.GetVolume();
	if(vl>=0)return;
	m_mediaplayer.Pause();
	m_mediaplayer.SetVolume(vl+200);	
	m_mediaplayer.Play();
	
}

void CHCOKDlg::OnVoldown()  //�������ؼ���С����
{
	if(m_mediaplayer.GetPlayState()!=2)return;
	long vl=m_mediaplayer.GetVolume();
	if(vl<=-9000)return;
	m_mediaplayer.Pause();
	m_mediaplayer.SetVolume(vl-200);	
	m_mediaplayer.Play();	
	
}

void CHCOKDlg::OnQiuc()   
{
	double pos=0;
	if(m_mediaplayer.GetPlayState()!=2)
		return;
	pos=m_mediaplayer.GetCurrentPosition();
	m_mediaplayer.Pause();
	m_mediaplayer.SetCurrentPosition(pos+5);
	m_mediaplayer.Play();	
}

void CHCOKDlg::OnQback() 
{
	if(m_mediaplayer.GetPlayState()!=2)return;
	double pos=m_mediaplayer.GetCurrentPosition();
	if(pos>5)
	{
		m_mediaplayer.Pause();
		m_mediaplayer.SetCurrentPosition(pos-5);
		m_mediaplayer.Play();
	}		
	
}

void CHCOKDlg::OnPlaypause() 
{
	CString text;
	GetDlgItem(IDC_PLAYPAUSE)->GetWindowText(text);
	if(m_mediaplayer.GetPlayState()!=2&&m_mediaplayer.GetPlayState()!=1)return;
	if(text=="��ͣ")
	{
		m_mediaplayer.Pause();
		GetDlgItem(IDC_PLAYPAUSE)->SetWindowText("����");
	}	
	else
	{
		m_mediaplayer.Play();
		GetDlgItem(IDC_PLAYPAUSE)->SetWindowText("��ͣ");
	}	
	
}

void CHCOKDlg::OnStop() 
{
	m_mediaplayer.Stop();
	m_mediaplayer.SetCurrentPosition(0);
	
	
}

//********************����Ա����****************************************//
void CHCOKDlg::OnManage() 
{
    
	ADMIN mydlg;       //�����������
	ManageDLG mydlg1;
	ADOConn m_AdoConn;    //�������ݿ��������
	m_AdoConn.OnInitADOConn();  //�������ݿ�����
	_bstr_t sql;
	_RecordsetPtr m_pRecordset;	//�����¼��
    
	if(mydlg.DoModal()==IDOK)
	{
		sql = "select*from admin where  adminpwd ='"+mydlg.m_mpassword+"'"; //��ѯ����
		m_pRecordset=m_AdoConn.GetRecordSet(sql);   //�õ���¼��
		if(m_pRecordset->adoEOF)	    //���û��
		{AfxMessageBox("�������");	}   //��ʾ����
		else
		{
			mydlg1.DoModal();     //�������
		}
	}
	m_AdoConn.ExitConnect();//�ͷ����ݿ���Դ
}


//********************ע��****************************************//
void CHCOKDlg::OnLogout()
{
	ADMIN mydlg;   //������������
	ADOConn m_AdoConn;  //�������ݿ��������
	_bstr_t sql,dellistsql,delusersql;
	_RecordsetPtr m_pRecordset;	  //�����¼��
    
	if(mydlg.DoModal()==IDOK)
	{
		sql = "select*from admin where  adminpwd ='"+mydlg.m_mpassword+"'";  //��֤�������
		m_pRecordset=m_AdoConn.GetRecordSet(sql);   //�õ���¼��
		if(m_pRecordset->adoEOF)	//û��
		{AfxMessageBox("�������");	}
		
		else            ///����ע��
		{
			
			GetDlgItem(IDC_CHECKINOUT)->SetWindowText("�������");   //�ı�'�������'��ť����ʾ
			dellistsql = "delete from playlist";     //ɾ�������б��
			delusersql="delete from usertemp";       //ɾ���û���ʱ����
			m_AdoConn.ExecuteSQL (	dellistsql);      //ִ��
			m_AdoConn.ExecuteSQL (	 delusersql);     //ִ��
			ShowListDate();                           //ˢ����ʾ
			OnStop() ;                            //ֹͣ����
		}
		MessageBox("ע���ɹ�!","ϵͳ��ʾ��",MB_OK|MB_ICONASTERISK);  //������ʾ��Ϣ
		
		//**********************���ý�����ذ�ť******************************************//
		GetDlgItem(IDC_PREVIOUS)->EnableWindow(false);
		GetDlgItem(IDC_NEXT)->EnableWindow(false);
		GetDlgItem(IDC_VOLUP)->EnableWindow(false);
		GetDlgItem(IDC_VOLDOWN)->EnableWindow(false);
		GetDlgItem(IDC_QIUC)->EnableWindow(false);
		GetDlgItem(IDC_QBACK)->EnableWindow(false);
		GetDlgItem(IDC_PLAYPAUSE)->EnableWindow(false);
		
		
		GetDlgItem(IDC_STOP)->EnableWindow(false);
		GetDlgItem(IDC_SELECTED)->EnableWindow(false);
		GetDlgItem(IDC_DELLIST)->EnableWindow(false);
		GetDlgItem(IDC_SINFIND)->EnableWindow(false);
		GetDlgItem(IDC_PYFIND)->EnableWindow(false);
		GetDlgItem(IDC_NUFIND)->EnableWindow(false);
		GetDlgItem(IDC_TFIND)->EnableWindow(false);
		//*************************************************************************//
		
		m_AdoConn.ExitConnect(); //�ͷ����ݿ���Դ
	}	
}


//********************������������****************************************//

void CHCOKDlg::OnCheckinout() 
{	
	ADMIN mydlg;          //��������
    CString price,abate,str;
	_bstr_t 	dellistsql, delusersql;	
	dellistsql ="delete from playlist";    //��ղ��ű�,���¸��û�ʹ��,�ڴ˲�ɾ��
    delusersql="delete from usertemp";      //����û�����,���¸��û�ʹ��,�ڴ˲�ɾ��
	ADOConn m_AdoConn;         //�������ݿ��������
	m_AdoConn.OnInitADOConn();  //�������ݿ�
	_bstr_t sql;
	_RecordsetPtr m_pRecordset;	   //�����¼��
	//*********************���������**********************//
    if(mydlg.DoModal()==IDOK)
	{	
		sql = "select*from admin where  adminname ='"+mydlg.m_user+"'"+"and adminpwd ='"+mydlg.m_mpassword+"'";//��֤����
		m_pRecordset=m_AdoConn.GetRecordSet(sql);
		if(m_pRecordset->adoEOF)	
		{
			MessageBox("�������,��Ȩ����!","ϵͳ��ʾ��",MB_OK|MB_ICONASTERISK);
			return ;
		}
		CString text;
		GetDlgItem(IDC_CHECKINOUT)->GetWindowText(text);//�жϰ�ť�ı���
		if(text=="�������")	
		{   //----------------������Ԥ��������õ���ʱ��---------------------------///
			SINGIN indlg;     //�����Ի���
			if(indlg.DoModal()==IDOK)
			{
				GetDlgItem(IDC_CHECKINOUT)->SetWindowText("����");//���ð�����,�ı�״̬
				//-----------------------��ʼ����------------------------//
				//�õ�����۸�
				ADOConn m_AdoConn;
				m_AdoConn.OnInitADOConn();
				_RecordsetPtr m_pRecordset;
				_bstr_t sql;
				sql = "select*from room where roomtype='"+addroomtype+"' ";//��ѯ��Ӧ����
				m_pRecordset=m_AdoConn.GetRecordSet(sql);   //�õ���¼��
				if(m_pRecordset->adoEOF) //���û�м�¼
				{		
					MessageBox("��û��Ϊ"+addroomtype+"���üƷѱ�׼,�������ü۸�!","ϵͳ��ʾ��",MB_OK|MB_ICONASTERISK);
					GetDlgItem(IDC_CHECKINOUT)->SetWindowText("�������");   //����ʧ��
					return;
				}
				else{
					price =m_pRecordset->GetFields()->GetItem("price")->Value.bstrVal;//�õ���Ӧ����ļ۸�
					printprice=price;
				}
				m_pRecordset->Close();   //�رռ�¼��
				sql = "select*from abate where cardtype='"+addcardtype+"' ";   //����ѡ�������ѯ������
				m_pRecordset=m_AdoConn.GetRecordSet(sql);  //�õ���¼��
				if(m_pRecordset->adoEOF)   //���û�������򿪻�ʧ��
				{
					MessageBox("��û��Ϊ"+addcardtype+"���ô�����,��������!","ϵͳ��ʾ��",MB_OK|MB_ICONASTERISK);
					GetDlgItem(IDC_CHECKINOUT)->SetWindowText("�������");
					return;
				}
				else
				{
					abate =m_pRecordset->GetFields()->GetItem("abate")->Value.bstrVal;//���ɹ�,��ȡ��������
					printabate=	abate;
				}
				m_pRecordset->Close();
				CTime t=CTime::GetCurrentTime();
				timestr1=t.Format("%y��%m��%d��%H��%Mʱ");/////////////////����û�����ʱ��
				timenum=int(atof(givenmoney)*3600/atof(price)/atof(abate));//���û�����Ǯ���ݰ���ۺʹ����ʼ���õ�����ʱ��
				if(timenum==0)  //���ʱ��Ϊ0,����ʾ����Ǯ,����ʧ��
				{
					GetDlgItem(IDC_CHECKINOUT)->SetWindowText("�������");
					MessageBox("��û������Ԥ����!","ϵͳ��ʾ��",MB_OK|MB_ICONASTERISK);	
					return;
				}			
				if(timenum<300)  //�������ʱ��С��5���и�����ʾ
					MessageBox("����Ԥ���Ѳ���5���ӵĵ㲥ʱ��,��ע��ϵͳ����ʱ�ر�!","ϵͳ��ʾ��",MB_OK|MB_ICONASTERISK);
				//------------------------��ť��ÿ���-------------------------------------------------//
				GetDlgItem(IDC_PREVIOUS)->EnableWindow(true);
				GetDlgItem(IDC_NEXT)->EnableWindow(true);
				GetDlgItem(IDC_VOLUP)->EnableWindow(true);
				GetDlgItem(IDC_VOLDOWN)->EnableWindow(true);
				GetDlgItem(IDC_QIUC)->EnableWindow(true);
				GetDlgItem(IDC_QBACK)->EnableWindow(true);
				GetDlgItem(IDC_PLAYPAUSE)->EnableWindow(true);
				GetDlgItem(IDC_STOP)->EnableWindow(true);
				GetDlgItem(IDC_SELECTED)->EnableWindow(true);
				GetDlgItem(IDC_DELLIST)->EnableWindow(true);
				GetDlgItem(IDC_SINFIND)->EnableWindow(true);
				GetDlgItem(IDC_PYFIND)->EnableWindow(true);
				GetDlgItem(IDC_NUFIND)->EnableWindow(true);
				GetDlgItem(IDC_TFIND)->EnableWindow(true);
				MessageBox("������ϵͳ,��ʼ�Ʒ�!","ϵͳ��ʾ��",MB_OK|MB_ICONASTERISK); //�ɹ�����
			}
		}	
		else//-------------------����------------------------------//
		{	
			sql = "select*from room where roomtype='"+addroomtype+"' ";
			m_pRecordset=m_AdoConn.GetRecordSet(sql);
			price =m_pRecordset->GetFields()->GetItem("price")->Value.bstrVal;//�õ�����۸�
			sql = "select*from abate where cardtype='"+addcardtype+"' ";
			m_pRecordset=m_AdoConn.GetRecordSet(sql);
			if(m_pRecordset->adoEOF)
			{	AfxMessageBox("��û��Ϊ"+addcardtype+"���ô�����,��������!");}
			else
			{
				abate =m_pRecordset->GetFields()->GetItem("abate")->Value.bstrVal;	//�õ�������
			}
			float moneybake=double(timenum)*atof(price)*atof(abate)/3600;   //������ʣʱ�����Ӧ�һ�Ǯ��
			if(moneybake<=0)           //�������ö�ʱ����ʱ���,�����п���Ϊ��
				moneybake=0;
			CString strmoney;
			strmoney.Format("%.1f",moneybake); //�ҳ�Ӧ�ҵ�Ǯ��
			printmoneybake=strmoney;
			CTime t1=CTime::GetCurrentTime();
			timestr2=t1.Format("%y��%m��%d��%H��%Mʱ");/////////////////����û��뿪ʱ��
			m_AdoConn.ExecuteSQL (	dellistsql);   //��ձ�
			m_AdoConn.ExecuteSQL (	 delusersql);   //��ձ�
		    ShowListDate();                   //ˢ����ʾ
			OnStop() ;                         //ֹͣ����
			UserPrintDlg printdlg;//��ӡ
			printdlg.DoModal();//��ӡ
			GetDlgItem(IDC_CHECKINOUT)->SetWindowText("�������");//�ı䰴ť����
			//----------------------���ð�ť----------------------------------------//
			GetDlgItem(IDC_PREVIOUS)->EnableWindow(false);
			GetDlgItem(IDC_NEXT)->EnableWindow(false);
			GetDlgItem(IDC_VOLUP)->EnableWindow(false);
			GetDlgItem(IDC_VOLDOWN)->EnableWindow(false);
			GetDlgItem(IDC_QIUC)->EnableWindow(false);
			GetDlgItem(IDC_QBACK)->EnableWindow(false);
			GetDlgItem(IDC_PLAYPAUSE)->EnableWindow(false);
			GetDlgItem(IDC_STOP)->EnableWindow(false);
			GetDlgItem(IDC_SELECTED)->EnableWindow(false);
			GetDlgItem(IDC_DELLIST)->EnableWindow(false);
			GetDlgItem(IDC_SINFIND)->EnableWindow(false);
			GetDlgItem(IDC_PYFIND)->EnableWindow(false);
			GetDlgItem(IDC_NUFIND)->EnableWindow(false);
			GetDlgItem(IDC_TFIND)->EnableWindow(false);
		}	
		m_AdoConn.ExitConnect();	//�ͷ����ݿ���Դ
	}
}

void CHCOKDlg::OnTimer(UINT nIDEvent) 
{
	
	timenum--;  //����Ԥ���������ʱ��ÿ���1
	
	if(timenum==300)
	{	
		MessageBox("������5���ӵĵ��ʱ��,����ϵ����Ա��ֵ,�����Զ��ر�!","ϵͳ��ʾ��",MB_OK|MB_ICONASTERISK);
	}
	if(timenum==0)//////////ʵ�ֺ�ע��һ���Ĺ���
	{
		
		
		GetDlgItem(IDC_PREVIOUS)->EnableWindow(false);
		GetDlgItem(IDC_NEXT)->EnableWindow(false);
		GetDlgItem(IDC_VOLUP)->EnableWindow(false);
		GetDlgItem(IDC_VOLDOWN)->EnableWindow(false);
		GetDlgItem(IDC_QIUC)->EnableWindow(false);
		GetDlgItem(IDC_QBACK)->EnableWindow(false);
		GetDlgItem(IDC_PLAYPAUSE)->EnableWindow(false);
		
		
		GetDlgItem(IDC_STOP)->EnableWindow(false);
		GetDlgItem(IDC_SELECTED)->EnableWindow(false);
		GetDlgItem(IDC_DELLIST)->EnableWindow(false);
		GetDlgItem(IDC_SINFIND)->EnableWindow(false);
		GetDlgItem(IDC_PYFIND)->EnableWindow(false);
		GetDlgItem(IDC_NUFIND)->EnableWindow(false);
		GetDlgItem(IDC_TFIND)->EnableWindow(false);
		
		///////////////////////////////////////////////////////////////
		
		ADOConn m_AdoConn;
		_bstr_t dellistsql,delusersql;
		GetDlgItem(IDC_CHECKINOUT)->SetWindowText("�������");
		dellistsql = "delete from playlist";
		delusersql="delete from usertemp";
		m_AdoConn.ExecuteSQL (	dellistsql);
		m_AdoConn.ExecuteSQL (	 delusersql);
		ShowListDate();
		OnStop() ;  
		
	}	
    
	
	
	
	int num = getSongNum();     //�õ�usertemp���и���������
	int b=m_list.GetItemCount();//�õ��б��еĸ�������
	if(num != b)    //����������ôˢ��
	{ShowListDate();}
	
	
	if(m_list.GetItemCount()==1)//////////////////////ʵ�������������
	{  
		playsongname=m_list.GetItemText(0,1);
		playsongformat=m_list.GetItemText(0,5);
		if(m_mediaplayer.GetPlayState()!=2&&m_mediaplayer.GetPlayState()!=1&&mode!=1)///////////������ǲ��ź���ͣ״̬,�Ҳ�Ϊ��������
			play();
	}
	
	
    //char szFilter[] =" ý���ļ� (��������)|*.mp3;*.wma;*.wmv;*.wav;*.avi;*.rm;*.rmvb|��Ƶ�ļ� |*.wmv;*.avi;*.rm;*.rmvb|��Ƶ�ļ�|*.mp3;*.wma;*.wav|�����ļ� (*.*)|*.*||";
	
    // CFileDialog filedlg( TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter ); 
    //	 filedlg.m_ofn.lpstrInitialDir   = ""; 
	CDialog::OnTimer(nIDEvent);
	
	
}

//********************�����ֲ�ѯ****************************************//
void CHCOKDlg::OnSinfind() 
{
	//���ָ��ΪNULL,��˵�����廹û����,��ô��̬����
	if(bysingerdlg == NULL)
	{  // ��̬�����Ի������
		bysingerdlg = new  BYSGRDLG;
		bysingerdlg->Create(IDD_BYSINGER,NULL);
	}
	
	bysingerdlg->ShowWindow(SW_SHOW);
}

//********************������ƴ����ѯ****************************************//
void CHCOKDlg::OnPyfind() 
{
	
	//���ָ��ΪNULL,��˵�����廹û����,��ô��̬����
	if(bypinyindlg == NULL)
	{  // ��̬�����Ի������
		bypinyindlg = new  BYPINYINDLG;
		bypinyindlg->Create(IDD_BYPINYIN,NULL);
	}
	bypinyindlg->ShowWindow(SW_SHOW);
	
}


//********************��������������ѯ****************************************//
void CHCOKDlg::OnNufind() 
{
	//���ָ��ΪNULL,��˵�����廹û����,��ô��̬����
	if(bynumdlg == NULL)
	{  // ��̬�����Ի������
		bynumdlg = new  BYZISHUDLG;
		bynumdlg->Create(IDD_BYZISHU,NULL);
	}
	bynumdlg->ShowWindow(SW_SHOW);
}


//********************����������ѯ****************************************//
void CHCOKDlg::OnTfind() 
{
	//BYSONGTYPDLG bysongtypedlg;
	//bysongtypedlg.DoModal ();	
	//���ָ��ΪNULL,��˵�����廹û����,��ô��̬����
	if(bysongtypedlg == NULL)
	{  // ��̬�����Ի������
		bysongtypedlg = new  BYSONGTYPDLG;
		bysongtypedlg->Create(IDD_BYSONGTYP,NULL);
	}
	bysongtypedlg->ShowWindow(SW_SHOW);
}

void CHCOKDlg::ShowListDate() /////////////////////////���ڲ����б�����ʾ����
{
	CString songid,  songname,		  singername,  songtype,  filename,fileformat;
	   m_list.DeleteAllItems();//ɾ������
	   
	   ADOConn m_AdoConn;   //�������ݿ��������
	   m_AdoConn.OnInitADOConn();  //�������ݿ�
	   _bstr_t sql;
	   _RecordsetPtr m_pRecordset;	
	   sql = "select*from playlist ";    //��ѯ playlist��
	   m_pRecordset=m_AdoConn.GetRecordSet(sql);  //�õ���¼��
	   if(m_pRecordset->adoEOF)    //���û�и������˳�
	   {
		   m_AdoConn.ExitConnect();
		   return;
	   }     
	   if(!m_pRecordset->adoEOF)
	   {  
		   int t=0;
		   m_list.DeleteAllItems();
		   while(!m_pRecordset->adoEOF)//������¼��
		   {int b=t+1;
		   
		   songid.Format("%d",b);
		   
		   songname =m_pRecordset->GetFields()->GetItem("tmuname")->Value.bstrVal;/////////////////ȡ����
		   singername =m_pRecordset->GetFields()->GetItem("tsingername")->Value.bstrVal;/////////////////ȡ������
		   songtype =m_pRecordset->GetFields()->GetItem("tsongtype")->Value.bstrVal;/////////////////ȡ�������
		   filename =m_pRecordset->GetFields()->GetItem("tfilename")->Value.bstrVal;/////////////////ȡ����ļ���
		   fileformat =m_pRecordset->GetFields()->GetItem("tformate")->Value.bstrVal;/////////////////ȡ��ĸ�ʽ
		   //************************����Ϣ��ʾ�ڱ���************************************//
		   m_list.InsertItem(t,songid);
		   m_list.SetItemText(t,1,	songname);
           m_list.SetItemText(t,2,	singername );
		   m_list.SetItemText(t,3,	songtype);
		   m_list.SetItemText(t,4,	filename);
		   m_list.SetItemText(t,5,	 fileformat);
		   m_pRecordset->MoveNext();
		   t++;
		   }
	   }
	   m_AdoConn.ExitConnect();  //�ͷ����ݿ���Դ
}

//**************��ʾ��ѡ�����б�,�û����Խ����еĸ�����ӵ������б���*********************************//
void CHCOKDlg::OnSelected() 
{
	//SELECTEDDLG seleceddlg;
	
	
	//���ָ��ΪNULL,��˵�����廹û����,��ô��̬����
	if(seleceddlg == NULL)
	{  // ��̬�����Ի������
		seleceddlg = new  SELECTEDDLG;
		seleceddlg->Create(IDD_SELECTED,NULL);
	}
	
	seleceddlg->ShowWindow(SW_SHOW);
	
}



void CHCOKDlg::OnDblclkList2(NMHDR* pNMHDR, LRESULT* pResult) ///////////////////˫��
{
	
    playsongname=m_list.GetItemText(m_list.GetSelectionMark(),1);
    playsongformat=m_list.GetItemText(m_list.GetSelectionMark(),5);
	play();
	
	*pResult = 0;
}

//*********************���Ÿ�������*****************************************//
void CHCOKDlg::	play()
{	
    ADOConn m_AdoConn;
	m_AdoConn.OnInitADOConn();
	_bstr_t sql;
	CString tempplaypath1,tempplaypath ;
	CString sPath ;
	int nPos;
    _RecordsetPtr m_pRecordset;
	sql = "select*from playlist where tmuname ='"+playsongname+"'";
	m_pRecordset=m_AdoConn.GetRecordSet(sql);
	if(m_pRecordset->adoEOF)
	{
		m_AdoConn.ExitConnect();
		return;
	}
	if(!m_pRecordset->adoEOF)
	{    
		while(!m_pRecordset->adoEOF)
		{
			tempplaypath1 =m_pRecordset->GetFields()->GetItem("playpath")->Value.bstrVal;/////////////////ȡ�ֶ�
			tempplaypath=tempplaypath1;
			tempplaypath.TrimRight ();
			if(tempplaypath=="ϵͳ�ļ�����")
			{
				GetModuleFileName(NULL,sPath.GetBufferSetLength (MAX_PATH+1),MAX_PATH);
				nPos=sPath.ReverseFind('\\');
				sPath=sPath.Left(nPos);
				nPos=sPath.ReverseFind('\\');
				sPath=sPath.Left(nPos);
				sPath=sPath+"\\����ļ���";
				playpath=sPath+	"\\"+playsongname+'.'+ playsongformat;
			}
			else
				playpath=tempplaypath1;
			m_pRecordset->MoveNext();	
		}
	}
	m_AdoConn.ExitConnect();	
	seepath=playpath;
	m_mediaplayer.Open(playpath);	
}

void CHCOKDlg::OnPrevious() ////////////////////��һ��
{
	row=row-1;     //�б� - 1  
	playsongname=m_list.GetItemText(row,1);   //�õ�����
    playsongformat=m_list.GetItemText(row,5);  //������ʽ
	
	if(playsongname=="")    //����������
	{ 
		row=m_list.GetItemCount()-1;	//ѭ������һ��	 
		playsongname=m_list.GetItemText(row,1);
		playsongformat=m_list.GetItemText(row,5);
	} 
	play(); 	 //����
	ShowListDate() ;   //��ʾ����
	m_list.SetItemState(row,LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
	m_list.SetFocus();   //���ý���
	
}

void CHCOKDlg::OnNext() ///////////////////��һ��
{
	row=row+1;  //�б�+1
	playsongname=m_list.GetItemText(row,1);
	playsongformat=m_list.GetItemText(row,5);
	
	if(playsongname=="")    //��������һ��������һ��
	{ 
		row=0;
		playsongname=m_list.GetItemText(row,1);
		playsongformat=m_list.GetItemText(row,5);
	} 
	play(); 	 //����
	ShowListDate() ;  //��ʾ
	m_list.SetItemState(row,LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
	m_list.SetFocus(); //���ý���
	
}

void CHCOKDlg::OnContextMenu(CWnd* pWnd, CPoint point) /////////////////////////�һ��˵�
{
  		
}
//*************************����ĺ������ò˵�������**************************************//
void CHCOKDlg::OnMenudanxun() //////////////////////////////////////����ѭ��
{
	mode=0;
	((CButton *)GetDlgItem(IDC_RADIOdx))->SetCheck(TRUE);
	((CButton *)GetDlgItem(IDC_RADIOdb))->SetCheck(false);
	((CButton *)GetDlgItem(IDC_RADIOxb))->SetCheck(false);
	((CButton *)GetDlgItem(IDC_RADIOlx))->SetCheck(false);////////////////////����ѭ��
}

void CHCOKDlg::OnMenudelall() ////////////////////////////////////////����б�
{
	OnDellist();//���ú���
}

void CHCOKDlg::OnMenudeldan() ////////////////////////////////////ɾ����ѡ��Ŀ
{
	ADOConn m_AdoConn; //���ݿ��������
	_bstr_t sql;
	sql = "delete from playlist where tmuname= '"+delmuname1+"'";//ɾ�����
	
	m_AdoConn.ExecuteSQL (sql);  //ִ��
	ShowListDate();   //ˢ��
    m_AdoConn.ExitConnect();
	
	
}

void CHCOKDlg::OnMenunanqu() ////////////////////////////////////��������
{
	mode=1;
	((CButton *)GetDlgItem(IDC_RADIOdx))->SetCheck(false);
	((CButton *)GetDlgItem(IDC_RADIOdb))->SetCheck(true);
	((CButton *)GetDlgItem(IDC_RADIOxb))->SetCheck(false);
	((CButton *)GetDlgItem(IDC_RADIOlx))->SetCheck(false);/////////////////��������
	
}

void CHCOKDlg::OnMenushubo() ////////////////////////////////////˳�򲥷�
{
	mode=2;
	((CButton *)GetDlgItem(IDC_RADIOdx))->SetCheck(false);
	((CButton *)GetDlgItem(IDC_RADIOdb))->SetCheck(false);
	((CButton *)GetDlgItem(IDC_RADIOxb))->SetCheck(true);
	((CButton *)GetDlgItem(IDC_RADIOlx))->SetCheck(false);/////////////˳�򲥷�
	
}

void CHCOKDlg::OnMenuxunbo() ////////////////////////////////ѭ������
{
	mode=3;
	((CButton *)GetDlgItem(IDC_RADIOdx))->SetCheck(false);
	((CButton *)GetDlgItem(IDC_RADIOdb))->SetCheck(false);
	((CButton *)GetDlgItem(IDC_RADIOxb))->SetCheck(false);
	((CButton *)GetDlgItem(IDC_RADIOlx))->SetCheck(true);/////////////ѭ�������б�
	
}




BEGIN_EVENTSINK_MAP(CHCOKDlg, CDialog)
//{{AFX_EVENTSINK_MAP(CHCOKDlg)
ON_EVENT(CHCOKDlg, IDC_MEDIAPLAYER1, 3002 /* EndOfStream */, OnEndOfStreamMediaplayer1, VTS_I4)
//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

//****************���Ž����ؼ��Զ����øú���************************************//
void CHCOKDlg::OnEndOfStreamMediaplayer1(long Result) 
{
	
	int b=m_list.GetItemCount();
	
	switch(mode)
	{
	case 0:  	play();break;        //����ѭ��
		
	case 1:  OnStop() ;	break;  //��������
		
	case 2:    row++;            //˳�򲥷�
		if(row==b)
			OnStop() ;
		else play();
		break;
		
	case 3:  OnNext();break;      //ѭ�������б�
		
	default:  m_mediaplayer.SetCurrentPosition(0);break;
	}
	
}

//*********************��ղ����б�***********************************//
void CHCOKDlg::OnDellist() 
{
	ADOConn m_AdoConn; //�������ݿ��������
	_bstr_t sql;
	sql = "delete from playlist";   //����SQL���
	if(AfxMessageBox("�Ƿ����Ҫ��ղ����б�?",MB_YESNO) == IDYES)
	{	
		OnStop();
		m_AdoConn.ExecuteSQL (sql);  //ִ�����
		ShowListDate();     //ˢ��
        m_AdoConn.ExitConnect();   //�ͷ����ݿ���Դ
	}
}

//************************** ���ڹرպ���***********************************************//
void CHCOKDlg::OnClose() 
{
	//********���������������****************** //
	ADMIN mydlg;        //������������
    ADOConn m_AdoConn;
	m_AdoConn.OnInitADOConn();
	_bstr_t sql;
	_RecordsetPtr m_pRecordset;	
    if(mydlg.DoModal()==IDOK)    //����������ȷ����
	{
		sql = "select*from admin where  adminpwd ='"+mydlg.m_mpassword+"'";
		m_pRecordset=m_AdoConn.GetRecordSet(sql);
		if(m_pRecordset->adoEOF)	
		{
			MessageBox("�������,����Ȩ�ر�!","ϵͳ��ʾ��",MB_OK|MB_ICONASTERISK);	return;
		}
		
		//************�ͷŷ�ģָ̬��ռ�***************// 
		if(seleceddlg  !=  NULL)
			seleceddlg  =  NULL ; //�ѵ����
		
		if(bysingerdlg  !=  NULL)
			bysingerdlg = NULL;    //�����ֲ�ѯ
		
		if(bypinyindlg  !=  NULL)  //��ƴ����ѯ
			bypinyindlg = NULL; 
		
		if(bynumdlg  !=  NULL)  //��������������ѯ
			bynumdlg = NULL; 
		
		if(bysongtypedlg  !=  NULL)  //���������Ͳ�ѯ
			bysongtypedlg = NULL; 
		
		//********************************************//
		CDialog::OnClose();
		
	}
	
}


BOOL CHCOKDlg::PreTranslateMessage(MSG* pMsg) //////////////////������Ϣ����
{
	if(pMsg->message   ==   WM_KEYDOWN)   
	{   
		if(pMsg->wParam   ==   VK_ESCAPE   ||   pMsg->wParam   ==   VK_RETURN)  /////////���λس���ȡ���� 
		{   
			return   -1;   
		}   
		switch(pMsg->wParam)   
		{   
        case VK_SPACE:OnPlaypause() ;break;////////////////��ͣ����
		case VK_LEFT:OnQback() ;break;    ////////////////////����
		case VK_RIGHT:OnQiuc() ;break;   ////////////////////���
		case VK_UP:OnPrevious() ;break;  ///////////////////////��������
		case VK_DOWN:OnNext() ;break;    //////////////////////��С����
			
		}   
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CHCOKDlg::OnRclickList2(NMHDR* pNMHDR, LRESULT* pResult) /////////////////////////�һ��˵�
{
	delmuname1=m_list.GetItemText(m_list.GetSelectionMark(),1);  //�õ�Ҫɾ������������
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    int selectrow=pNMListView->iItem;  //�õ���ѡ�ĵ�ǰ����,��û��ѡ��Ԫ��ʱֵΪ -1
    if(selectrow != -1)   //���ѡ����һ�׸���,�������ʾ�˵�
	{
		LPPOINT lpoint=new tagPOINT;   
		::GetCursorPos(lpoint);     //��õ�ǰ����λ��
		CMenu   menu,*pSubMenu; 
		menu.LoadMenu(IDR_MENU);                //��Ӳ˵��Զ�����Դ
		pSubMenu=menu.GetSubMenu(0);           //���ò˵�������Ŀ��ʼλ��
		pSubMenu->TrackPopupMenu(TPM_LEFTALIGN,lpoint->x,lpoint->y,this);    //������λ��
	}
	*pResult = 0;
}

//*********************����***************************************//
void CHCOKDlg::OnHelp() 
{
	CString sPath ;
	int nPos;
	GetModuleFileName(NULL,sPath.GetBufferSetLength (MAX_PATH+1),MAX_PATH);
	nPos=sPath.ReverseFind('\\');
	sPath=sPath.Left(nPos);                //���ϵ��˵õ�DEBUG·��
    CString filename=sPath+"\\help.txt";   //�õ������ĵ���ȫ·��
	ShellExecute(NULL, "open",filename, NULL, NULL,SW_SHOWNORMAL);//�򿪰����ļ�
	
	//����ԭ��-------ShellExecute(handle, "open", path_to_folder, NULL, NULL, SW_SHOWNORMAL)---//
	
}


//*****************�õ�playlist���и���������*************************************//
int CHCOKDlg::getSongNum()
{
	   int songNum =0 ;
	   ADOConn m_AdoConn;
	   m_AdoConn.OnInitADOConn();
	   _bstr_t sql;
	   _RecordsetPtr m_pRecordset;	
	   sql = "select*from playlist ";
	   m_pRecordset=m_AdoConn.GetRecordSet(sql);
	   if(m_pRecordset->adoEOF)
	   {
		   m_AdoConn.ExitConnect();
		   return 0;
	   }
	   else{ 
		   while(!m_pRecordset->adoEOF)
		   {
			   songNum++;
			   m_pRecordset->MoveNext();
		   }
		   return songNum ;  //���ظ�������
	   }
	   m_AdoConn.ExitConnect();
}

