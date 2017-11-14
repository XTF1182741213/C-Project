// GraduDeMISDlg.cpp : implementation file
//
#include "stdafx.h"
#include "GraduDeMIS.h"
#include "GraduDeMISDlg.h"
#include "StudentDlg.h"
#include "TeacherDlg.h"
#include "StuChoiSubDlg.h"
#include "SysLgnDlg.h"
#include "UserDlg.h"
#include "AnswZigeChekDlg.h"
#include "DocChekDlg.h"
#include "ChoiStatusDlg.h"
#include "DclrsubStatusDlg.h"
#include "SubFormView.h"
#include "DabianfenzuDlg.h"
#include "TeacherDlg.h"
#include "SubjectDlg.h"
#include "KaoqinDlg.h"
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
// CGraduDeMISDlg dialog

CGraduDeMISDlg::CGraduDeMISDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGraduDeMISDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGraduDeMISDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGraduDeMISDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGraduDeMISDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGraduDeMISDlg, CDialog)
	//{{AFX_MSG_MAP(CGraduDeMISDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDD_STU_DIALOG, OnStuDialog)
	ON_COMMAND(ID_ExitSys, OnExitSys)
	ON_COMMAND(IDD_SysLog_DLG, OnSysLgnDLG)
	ON_COMMAND(IDD_UserGL, OnUserGL)
	ON_COMMAND(IDD_Choisublist_DLG, OnChoisublistDLG)
	ON_COMMAND(ID_MENUITEMUserHelp, OnMENUITEMUserHelp)
	ON_COMMAND(IDD_AnswZigeChek_DLG, OnAnswZigeChekDLG)
	ON_COMMAND(ID_MENUITEM_DBCopy, OnMENUITEMDBCopy)
	ON_COMMAND(ID_MENUITEM_DBRestore, OnMENUITEMDBRestore)
	ON_COMMAND(ID_MENUITEM_DocChek, OnMENUITEMDocChek)
	ON_COMMAND(IDD_ChoiStatusShow_DLG, OnChoiStatusDLG)
	ON_UPDATE_COMMAND_UI(IDD_STU_DIALOG, OnUpdateStuDialog)
	ON_COMMAND(IDD_DclrSubStatus_DLG, OnDclrSubStatusDLG)
	ON_WM_CLOSE()
	ON_COMMAND(IDD_DabianFenzu_DLG, OnDabianFenzuDLG)
	ON_COMMAND(IDD_TEACHER_DIALOG, OnTeacherDialog)
	ON_COMMAND(IDD_Subject_DLG, OnSubjectDLG)
	ON_UPDATE_COMMAND_UI(IDD_ChoiStatusShow_DLG, OnUpdateChoiStatusShowDLG)
	ON_UPDATE_COMMAND_UI(IDD_DclrSubStatus_DLG, OnUpdateDclrSubStatusDLG)
	ON_UPDATE_COMMAND_UI(ID_MENUITEM_DocChek, OnUpdateMENUITEMDocChek)
	ON_UPDATE_COMMAND_UI(ID_MENUITEM_DBCopy, OnUpdateMENUITEMDBCopy)
	ON_UPDATE_COMMAND_UI(ID_MENUITEM_DBRestore, OnUpdateMENUITEMDBRestore)
	ON_UPDATE_COMMAND_UI(IDD_UserGL, OnUpdateUserGL)
	ON_COMMAND(IDD_Kaoqin_DLG, OnKaoqinDLG)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraduDeMISDlg message handlers

BOOL CGraduDeMISDlg::OnInitDialog()
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
	
	// TODO: Add extra initialization here
	
//		CButton *pBtn=(CButton *)GetDlgItem(IDD_TEACHER_DIALOG);
	//	pBtn->EnableWindow(false);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGraduDeMISDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGraduDeMISDlg::OnPaint() 
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
		CPaintDC dc(this); // device context for painting
		//**********************************************
		//��ӱ���ͼƬ
		CRect rect;
		GetClientRect(&rect);								//��ȡ�ͻ�����С
		HBITMAP hbitmap; 
		hbitmap=::LoadBitmap(::AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP4)); //��ȡλͼ
		HDC hMenDC=::CreateCompatibleDC(NULL);				//�����Ը����ݵ�DC
		SelectObject(hMenDC,hbitmap);
		::StretchBlt(dc.m_hDC,0,0,1024,768,hMenDC,0,0,1024,768,SRCCOPY);//��ʾλͼ
		::DeleteDC(hMenDC);
		::DeleteObject(hbitmap);
		//****************************************************
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGraduDeMISDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//���ݵı��ݵ���Ϣ��Ӧ����
void CGraduDeMISDlg::OnMENUITEMDBCopy() 
{
	// TODO: Add your command handler code here
	if(AfxMessageBox("��ȷ��Ҫ�������ݿ���",MB_OKCANCEL)==IDCANCEL)
	{
		return;
	}
	if(CopyFile("db_gradu.mdb","db_gradu.bak",false))//�����ļ�
	AfxMessageBox("���ݿⱸ�ݳɹ���");
	else
     AfxMessageBox("���ݿⱸ��ʧ�ܣ�");
}
//���ݵĻ�ԭ����Ϣ��Ӧ����
void CGraduDeMISDlg::OnMENUITEMDBRestore() 
{
	// TODO: Add your command handler code here
	if(AfxMessageBox("��ԭ���ݿ⽫����ԭ�������ݿ⡣��ȷ��Ҫ��ԭ���ݿ���",MB_OKCANCEL)==IDCANCEL)
	{
		return;
	}
	if(CopyFile("db_gradu.bak","db_gradu.mdb",false))//�����ļ�
       AfxMessageBox("���ݿ⻹ԭ�ɹ���");
    else
	   AfxMessageBox("���ݿ⻹ԭʧ�ܣ�");
}
//�����˵�����Ϣ��Ӧ����
void CGraduDeMISDlg::OnMENUITEMUserHelp() 
{
	// TODO: Add your command handler code here
	CString Path,sPath;//�������ݿ��ļ�·����
	//��ȡ��ǰ�����·��
	GetModuleFileName(NULL,sPath.GetBufferSetLength (MAX_PATH+1),MAX_PATH);//ΪsPath����洢�ռ�
	Path.ReleaseBuffer();
	int nPos;
	nPos=sPath.ReverseFind('\\');			//�����ַ���/��
	Path=Path.Left(nPos);					//����˽�ȡnPosλ�õ��ַ�����ȡ�ļ���·��
    nPos=Path.ReverseFind('\\');			//�����ַ���/��
    Path=Path.Left(nPos);					//��ȡ�ļ���·��
	ShellExecute(NULL,NULL,_T("ϵͳʹ�ð���.doc"),NULL,_T(Path),NULL);//ִ���ĵ�
}

//��ѧ����Ϣ�Ի���
void CGraduDeMISDlg::OnStuDialog() 
{
	// TODO: Add your command handler code here
	 CStudentDlg dlg;		//����Ի������
	 dlg.DoModal();			//��ʾ�Ի���
}

//���û���½�Ի���
void CGraduDeMISDlg::OnSysLgnDLG() 
{
	// TODO: Add your command handler code here
	CSysLgnDlg dlg;			//����Ի������
	dlg.DoModal();			//��ʾ�Ի���
}		

//���û�����Ի���
void CGraduDeMISDlg::OnUserGL() 
{
	// TODO: Add your command handler code here
	CUserDlg dlg;			//����Ի������
	dlg.DoModal();			//��ʾ�Ի���
}

//�˳�
void CGraduDeMISDlg::OnExitSys() 
{
	// TODO: Add your command handler code here
	OnCancel();
}

//
void CGraduDeMISDlg::OnChoisublistDLG() 
{
	// TODO: Add your command handler code here
	CStuChoiSubDlg dlg;		//����Ի������
	dlg.DoModal();			//��ʾ�Ի���
}

void CGraduDeMISDlg::OnAnswZigeChekDLG() 
{
	// TODO: Add your command handler code here
	AnswZigeChekDlg dlg;	//����Ի������
	dlg.DoModal();			//��ʾ�Ի���
}

void CGraduDeMISDlg::OnMENUITEMDocChek() 
{
	// TODO: Add your command handler code here
	CDocChekDlg dlg;		//����Ի������
	dlg.DoModal();			//��ʾ�Ի���
}

void CGraduDeMISDlg::OnChoiStatusDLG() 
{
	if(strExternUser=="")
	{
		AfxMessageBox("���ȵ�¼��Ȼ��ѡ��");
		return ;
	}
	// TODO: Add your command handler code here
	CChoiStatusDlg dlg;		//����Ի������
	dlg.DoModal();			//��ʾ�Ի���
}

void CGraduDeMISDlg::OnDclrSubStatusDLG() 
{
	// TODO: Add your command handler code here
	CDclrsubStatusDlg dlg;	//����Ի������
	dlg.DoModal();			//��ʾ�Ի���
}	

void CGraduDeMISDlg::OnClose() 
{
    EndDialog(IDD_GRADUDEMIS_DIALOG);		//���һ��ģ̬�Ի���
	//CDialog::OnClose();
}

void CGraduDeMISDlg::OnDabianFenzuDLG() 
{
	// TODO: Add your command handler code here
	CDabianfenzuDlg dlg;	//����Ի������
	dlg.DoModal();			//��ʾ�Ի���
}

void CGraduDeMISDlg::OnTeacherDialog() 
{
	// TODO: Add your command handler code here
	CTeacherDlg dlg;		//����Ի������
	dlg.DoModal();			//��ʾ�Ի���
}

void CGraduDeMISDlg::OnSubjectDLG() 
{
	// TODO: Add your command handler code here
	CSubjectDlg dlg;		//����Ի������
	dlg.DoModal();			//��ʾ�Ի���
}

//�������ڶԻ���
void CGraduDeMISDlg::OnKaoqinDLG() 
{
	// TODO: Add your command handler code here
	CKaoqinDlg dlg;			//����Ի������
	dlg.DoModal();
}
/////////////////////////////////////////////////////////////////////////////
//һ��Ϊ��Ӧ�Ĳ˵��ĸ��£�������Ӧ�Ĳ˵�
void CGraduDeMISDlg::OnUpdateStuDialog(CCmdUI* pCmdUI) 
{
   	pCmdUI->Enable(true);	//������ָ��˵�
}

void CGraduDeMISDlg::OnUpdateChoiStatusShowDLG(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(true);	//������ָ��˵�
}

void CGraduDeMISDlg::OnUpdateDclrSubStatusDLG(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(true);	//������ָ��˵�
}

void CGraduDeMISDlg::OnUpdateMENUITEMDocChek(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(true);	//������ָ��˵�
}


void CGraduDeMISDlg::OnUpdateMENUITEMDBCopy(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(true);	//������ָ��˵�
}

void CGraduDeMISDlg::OnUpdateMENUITEMDBRestore(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(true);	//������ָ��˵�
}

void CGraduDeMISDlg::OnUpdateUserGL(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(true);	//������ָ��˵�
}


