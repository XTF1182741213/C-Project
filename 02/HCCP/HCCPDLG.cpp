// HCCPDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HCCP.h"
#include "HCCPDlg.h"
#include "ADOConn.h"
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
// CHCCPDlg dialog

CHCCPDlg::CHCCPDlg(CWnd* pParent /*=NULL*/)
: CDialog(CHCCPDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHCCPDlg)
	m_text = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHCCPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHCCPDlg)
	DDX_Control(pDX, IDC_LIST1, m_list1);
	DDX_Control(pDX, IDC_TAB1, m_tab);
	DDX_Control(pDX, IDC_TREE1, m_tree);
	DDX_Text(pDX, IDC_BIAOTI, m_text);
	DDX_Control(pDX, IDC_BIAOTI, m_textctrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHCCPDlg, CDialog)
//{{AFX_MSG_MAP(CHCCPDlg)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab1)
ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, OnSelchangedTree1)
ON_WM_TIMER()
ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnItemchangedList1)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHCCPDlg message handlers

BOOL CHCCPDlg::OnInitDialog()
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
	
	m_text="��ӭʹ���ۺϲ���ϵͳ";  
	m_textctrl.SetFontSize(27);  //���þ�̬�ؼ�����ʾ�����С
	m_textctrl.SetTextColor(RGB(0,255,0));  //���þ�̬�ؼ�������ɫ
	m_textctrl.SetBkColor(RGB(0,0,0));  //���þ�̬�ؼ�������ɫ
	m_textctrl.SetFontBold(TRUE);  //��������Ϊ����
	m_textctrl.SetText(m_text);  //���þ�̬�ؼ��ı�����
	
	m_list1.SetExtendedStyle(LVS_EX_FULLROWSELECT);  //����list�б���
	m_list1.InsertColumn(0,"ѧ��",LVCFMT_CENTER,164);  //�����б���
	m_list1.InsertColumn(1,"����",LVCFMT_CENTER,164);
	m_list1.InsertColumn(2,"����",LVCFMT_CENTER,164);	
	
	m_TreeBootImage.Create ( IDB_BITMAP1,20,1,ILC_COLOR8);  //�������οؼ�������
	m_tree.SetImageList ( &m_TreeBootImage,TVSIL_NORMAL );  //�������οؼ����
	m_tree.SetTextColor (RGB(7,145,13));  //�������οؼ�������ɫ
	
	InitTab();
	ShowDlg();
	CreateTree();
	SetTimer(1,250,NULL);  //�򿪶�ʱ����ʱ����Ϊ250ms
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

/*------------------��ʼ��tab�ؼ�---------------------*/

void CHCCPDlg::InitTab()
{
	showdlgnum=0;
	
	m_tab.InsertItem(0,"ѧ���ɼ��޸�");  //���tab�ؼ�����
	m_tab.InsertItem(1,"ѧ���ɼ���ѯ");
	m_tab.InsertItem(2,"ѧ���ɼ�����");	
	m_tab.InsertItem(3,"ѧ��ѧ���޸�");
	m_tab.InsertItem(4,"ѧ���ۺϲ���");

	modifydlg.Create(IDD_XSCJXG,&m_tab);  //����tab�ؼ�child�Ի������
	finddlg.Create(IDD_XSCJCX,&m_tab);
	sortdlg.Create(IDD_XSCJPX,&m_tab);
	zhcpdlg.Create(IDD_XSZHPC,&m_tab);
	xkxgdlg.Create(IDD_XKXFXG,&m_tab);
	CRect rc;
	m_tab.GetClientRect(rc);  //��ȡ�ͻ�����С
	rc.top += 20;
	rc.bottom -= 8;
	rc.left += 8;
	rc.right -= 8;
	modifydlg.MoveWindow(&rc);  //����tab�ؼ�child�Ի�����ʾ����
	finddlg.MoveWindow(&rc);
	sortdlg.MoveWindow(&rc);
	zhcpdlg.MoveWindow(&rc);
	xkxgdlg.MoveWindow(&rc);

	pdlg[0]=&modifydlg;  //��ȡchild�Ի���ָ��
	pdlg[1]=&finddlg;
	pdlg[2]=&sortdlg;
	pdlg[3]=&xkxgdlg;
	pdlg[4]=&zhcpdlg;
	
}

/*------------------tab�ؼ���Ӧ����---------------------*/

void CHCCPDlg::ShowDlg()
{
	switch(showdlgnum)
	{
	case 0:
		{
			pdlg[0]->ShowWindow(SW_SHOW);		
			pdlg[1]->ShowWindow(SW_HIDE);
			pdlg[2]->ShowWindow(SW_HIDE);
			pdlg[3]->ShowWindow(SW_HIDE);
			pdlg[4]->ShowWindow(SW_HIDE);
		}break;
	case 1:
		{
			pdlg[0]->ShowWindow(SW_HIDE);
			pdlg[1]->ShowWindow(SW_SHOW);
			pdlg[2]->ShowWindow(SW_HIDE);
			pdlg[3]->ShowWindow(SW_HIDE);
			pdlg[4]->ShowWindow(SW_HIDE);
		}break;
	case 2:
		{
			pdlg[0]->ShowWindow(SW_HIDE);
			pdlg[1]->ShowWindow(SW_HIDE);
			pdlg[2]->ShowWindow(SW_SHOW);
			pdlg[3]->ShowWindow(SW_HIDE);
			pdlg[4]->ShowWindow(SW_HIDE);
		}break;
	case 3:
		{
			pdlg[0]->ShowWindow(SW_HIDE);
			pdlg[1]->ShowWindow(SW_HIDE);
			pdlg[2]->ShowWindow(SW_HIDE);
			pdlg[3]->ShowWindow(SW_SHOW);
			pdlg[4]->ShowWindow(SW_HIDE);
		}break;
	case 4:
		{
			pdlg[0]->ShowWindow(SW_HIDE);
			pdlg[1]->ShowWindow(SW_HIDE);
			pdlg[2]->ShowWindow(SW_HIDE);
			pdlg[3]->ShowWindow(SW_HIDE);
			pdlg[4]->ShowWindow(SW_SHOW);
			
		}break;
		
	}
}

/*------------------ˢ����ʾlist�б�---------------------*/

void CHCCPDlg::ShowList(CString cnamedd)
{
	ADOConn m_AdoConn;
	m_AdoConn.OnInitDBConnect();
	_bstr_t vSQL;
	CString str00;
	if(flag121==false&&sortdlg.temp!="sno")
	{
		str00.Format("select student.sno,sname,sgrade from student ,grade where student.sno=grade.sno and cno='%s' order by %s DESC",cnamedd,sortdlg.temp);  //������Ͽ���������
		flag121=true;
	}
	else
		str00.Format("select student.sno,sname,sgrade from student ,grade where student.sno=grade.sno and cno='%s'",cnamedd);  //���ݿγ�����ȡ���ݿ�ɼ�
	vSQL=(_bstr_t)str00;

	_RecordsetPtr m_pRs;
	m_pRs=m_AdoConn.GetRecordSet(vSQL);  //��ȡ�ɼ���¼��
	
	int k=0;
	
	_variant_t cno,cname,cgrade;
	
	while(!m_pRs->adoEOF)  //�жϼ�¼��������־
	{
		cno=m_pRs->GetCollect("sno");  //��ȡ��¼����ѧ��
		cname=m_pRs->GetCollect("sname");  //��ȡ��¼��������
		cgrade=m_pRs->GetCollect("sgrade");  //��ȡ��¼���гɼ�
		
		CString str1=(LPCTSTR)(_bstr_t)cname;
		CString str2=(LPCTSTR)(_bstr_t)cgrade;
		
		m_list1.InsertItem(k,(_bstr_t)cno);  //��ѧ����ӵ���һ��
		m_list1.SetItemText(k,1,str1);  //��������ӵ��ڶ���
		m_list1.SetItemText(k,2,str2);  //���ɼ���ӵ�������
		m_pRs->MoveNext();  //ָ��ָ����һ����¼
		k++;
	}
}

/*---------------------����tree���οؼ�---------------------*/

void CHCCPDlg::CreateTree()
{
	m_tree.DeleteAllItems();
	m_AdoConn.OnInitDBConnect();	
	TVINSERTSTRUCT tvInsert;  
	HTREEITEM hParent;
	tvInsert.hParent = NULL;
	tvInsert.hInsertAfter = NULL;
	tvInsert.item.mask = TVIF_TEXT;
	tvInsert.item.pszText = _T("���ݴ�ѧ");  //���������
	hParent = m_tree.InsertItem(&tvInsert);	
	vSQL="SELECT * FROM tree where root='���ݴ�ѧ'";  //ͨ�����ڵ�ѡȡ2�����
	m_pRs1=m_AdoConn.GetRecordSet(vSQL);
	CString yezi="leaf";  
	while(!m_pRs1->adoEOF)  //ͨ���ݹ����select����������
	{	
		Select(yezi,hParent,m_pRs1);  //����select��������Ҷ�ӽ��		
		CString str1;
		str1.Format("SELECT * FROM tree where root='%s'",str);  //ͨ�����ڵ�ѡȡ�ӽ��
		vSQL1=(_bstr_t)str1;
		m_pRs2=m_AdoConn.GetRecordSet(vSQL1); //��ȡ��¼��
		
		leaf1=leaf;
		while(!m_pRs2->adoEOF)
		{	
			Select(yezi,leaf1,m_pRs2);			
			CString str2;
			str2.Format("SELECT * FROM tree where root='%s'",str);
			vSQL2=(_bstr_t)str2;
			m_pRs3=m_AdoConn.GetRecordSet(vSQL2);	
			leaf2=leaf;
			while(!m_pRs3->adoEOF)
			{
				Select(yezi,leaf2,m_pRs3);
			}
		}		
	}	
	m_tree.Expand(hParent,TVE_EXPAND);  //չ��һ�����
	m_tree.Expand(m_tree.GetChildItem(hParent),TVE_EXPAND);  //չ��2�����
	m_tree.Expand(m_tree.GetChildItem(m_tree.GetChildItem(hParent)),TVE_EXPAND);  //չ��3�����	
}

void CHCCPDlg::Select(CString ming,HTREEITEM root,_RecordsetPtr m_pRs)  //����Ҷ�ӽ��
{		
	name=m_pRs->GetCollect((_bstr_t)ming);  //��ȡ�ӽ���¼��
	str=(LPCTSTR)(_bstr_t)name;
	leaf=m_tree.InsertItem(str,0,1,root,TVI_LAST);	//����ӽ��
	m_pRs->MoveNext();  //ָ��ָ����һ����¼				
}

void CHCCPDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CHCCPDlg::OnPaint() 
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
HCURSOR CHCCPDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/*---------------------ͨ���¼�������ѡ��tab�ؼ�---------------------*/

void CHCCPDlg::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int sel=0;
	sel=m_tab.GetCurSel();
	switch(sel)
	{
	case 0:
		showdlgnum=0;
		break;
		
	case 1:
		showdlgnum=1;
		break;
		
	case 2:
		showdlgnum=2;
		break;
		
	case 3:
		showdlgnum=3;
		break;
		
	case 4:
		  showdlgnum=4;
		  break;
			
	}
	ShowDlg();		  
	*pResult = 0;
}

/*---------------------ͨ���¼�������ѡ��Tree�Ϳؼ�---------------------*/

void CHCCPDlg::OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	
	m_list1.DeleteAllItems();  //ɾ��list�ؼ�����
	leaf111=m_tree.GetItemText(pNMTreeView->itemNew.hItem);  //��ȡ��ǰ�������
	leaf11=m_tree.GetItemText(m_tree.GetParentItem(pNMTreeView->itemNew.hItem));  //��ȡ���������
	leaf12=m_tree.GetItemText(m_tree.GetParentItem(m_tree.GetParentItem(pNMTreeView->itemNew.hItem)));  //��ȡ�����ĸ��������
	HTREEITEM   hItem =pNMTreeView->itemNew.hItem;   
	HTREEITEM   hItemTmp=hItem;
	CString biaoti;
	biaoti=leaf111;
	biaoti.TrimRight();
	int nCount1=0;
	while(hItemTmp)  //ͨ��whileѭ���жϵ�ǰ���ļ���
	{		
		hItemTmp= m_tree.GetParentItem(hItemTmp);  //��ȡ�����ָ���ж��Ƿ�Ϊ��
		nCount1++;
	}
	
	_bstr_t vSQL4;
	_RecordsetPtr m_pRs4;
	_variant_t cnamed;
	
	nCount=nCount1;
	CString str001,str002,str003;
	str002=leaf111;
	str002.TrimRight();
	if(nCount==3)
	{
		m_text=biaoti+"��ѧ��������";  
		str001.Format("select * from student where sclass='%s'",str002);  //��ȡ��ǰ�༶��ѧ������
		vSQL4=(_bstr_t)str001;
		m_pRs4=m_AdoConn.GetRecordSet(vSQL4);
		
		int k=0;
		
		_variant_t sno,sname,cgrade,cname3;
		
		while(!m_pRs4->adoEOF)
		{
			sno=m_pRs4->GetCollect("sno");  //ͨ����¼��ѡȡѧ��
			sname=m_pRs4->GetCollect("sname");  //ͨ����¼��ѡȡѧ������
			
			CString str1=(LPCTSTR)(_bstr_t)sname;
			
			m_list1.InsertItem(k,(_bstr_t)sno);  //��ѧ����ӵ�list�ؼ�
			m_list1.SetItemText(k,1,str1);  //��������ӵ�list�ؼ�
			
			m_pRs4->MoveNext();  //ָ��������һ����¼
			k++;
		}
	}
	else if(nCount==4)
	{
		m_text=biaoti+"�γ���ĩ�ɼ���";
		try{
			str001.Format("select * from class where cname='%s'",str002);  //��ȡ��ǰ�γ���ѧ���ɼ�
			vSQL4=(_bstr_t)str001;
			m_pRs4=m_AdoConn.GetRecordSet(vSQL4);
			cnamed=m_pRs4->GetCollect("cno");  //ͨ����¼����ȡ�γ̺�
			str003=(LPCTSTR)(_bstr_t)cnamed;
			str1112=str003;
			ShowList(str003);  
		}
		catch(...)  //�����쳣
		{}
	}
	else
		m_text="��ӭʹ���ۺϲ���ϵͳ";
	
	if(nCount==4)
	{
		xkxgdlg.m_xkm=biaoti;
		str001.Format("select * from class where cname='%s'",biaoti);
		vSQL4=(_bstr_t)str001;
		m_pRs4=m_AdoConn.GetRecordSet(vSQL4);
		cnamed=m_pRs4->GetCollect("cgrade");
		str003=(LPCTSTR)(_bstr_t)cnamed;
		xkxgdlg.m_xuekf=atof(str003);	
	}
	else
	{
		xkxgdlg.m_xkm="";
		xkxgdlg.m_xuekf=0;
	}	
	xkxgdlg.UpdateData(false);

	*pResult = 0;
}

/*---------------------��ʱ��---------------------*/

void CHCCPDlg::OnTimer(UINT nIDEvent) 
{
	i=i+5;j=j-3;k=k+2;
	color=RGB(k,j,i);  //ͨ����ʱ���ı���ɫ
	if(i==255)
		i=0;
	if(j==15)
		j=255;
	if(k==255)
		k=1;
	if(flag123==false||flag121==false)
	{
		m_list1.DeleteAllItems();  //ɾ��list�ؼ�ȫ������
		ShowList(str1112);  //��ʾlist�ؼ�
		flag121=flag123=true;
	}
	m_textctrl.SetTextColor(color);  //������ʾ����������ɫ

	CDialog::OnTimer(nIDEvent);
}

void CHCCPDlg::OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int i=pNMListView->iItem;
	qiqi=i;
	modifydlg.m_sno=m_list1.GetItemText(i,0);  //��ȡlist�ؼ���ѡȡ��Ŀ����
	modifydlg.m_sname=m_list1.GetItemText(i,1);  //��ȡlist�ؼ���ѡȡ��Ŀ����
	if (nCount==3)
	{	
		modifydlg.UpdateData(false);
	}
	else if(nCount==4)
	{		
		modifydlg.m_sgrade=atof(m_list1.GetItemText(i,2));  //��String��ǿ��ת����double
		modifydlg.UpdateData(false);
	}
	*pResult = 0;
}

/*-------------------------�������ʱ�Զ��������ݿ�-------------------------*/

void CHCCPDlg::OnClose() 
{
    CDialog::OnClose();
	CString str;
	CString filename;
	CString sPath;
	GetModuleFileName(NULL,sPath.GetBufferSetLength (MAX_PATH+1),MAX_PATH);
	sPath.ReleaseBuffer();
	int nPos;
	nPos=sPath.ReverseFind('\\');
	sPath=sPath.Left(nPos);  //��ȡ������Debug·��
	nPos=sPath.ReverseFind('\\');
	sPath=sPath.Left(nPos);  //��ȡ�����̵�ǰ·��
	filename=sPath+"\\database\\HCBAK1";  //�������ݿ�����
	DeleteFile(filename);  //ɾ���ɵı���
	str.Format("backup database HCCP to Disk='%s'",filename);  //ͨ��sql��䱸�����ݿ�
	vSQL=(_bstr_t)str;
	m_AdoConn.ExecuteSQL(vSQL);  //ִ��sql���
	AfxMessageBox("ϵͳ�Զ��������ݿ�ɹ�!\r\n·����"+filename+"\r\n��ӭ�´�ʹ��!");
	CDialog::OnClose();
}
