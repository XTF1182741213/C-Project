// TeacherDlg.cpp : implementation file
//

#include "stdafx.h"
#include "gradudemis.h"
#include "TeacherDlg.h"
#include "TeacherTab1.h"
#include "TeacherTab2.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTeacherDlg dialog


CTeacherDlg::CTeacherDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTeacherDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTeacherDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTeacherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTeacherDlg)
	DDX_Control(pDX, IDC_TEACHER_TAB, m_TeacherTab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTeacherDlg, CDialog)
	//{{AFX_MSG_MAP(CTeacherDlg)
	ON_WM_DESTROY()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TEACHER_TAB, OnSelchangeTeacherTab)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTeacherDlg message handlers
BOOL CTeacherDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	
	m_pTab1Dlg=new CTeacherTab1();					//����Ի���ָ��
	m_pTab2Dlg=new CTeacherTab2();
	
	m_pTab1Dlg->Create(IDD_TEACHER_DIALOG1,&m_TeacherTab);//�����Ի���
	m_pTab2Dlg->Create(IDD_TEACHER_DIALOG2,&m_TeacherTab);

	m_TeacherTab.InsertItem(0,"��ʦ��Ϣ��ѯ",0);	//�趨��ǩ�ı���
	m_TeacherTab.InsertItem(1,"��ʦ��Ϣ����",1);

	m_TeacherTab.SetMinTabWidth(80);				//�趨��ǩ�Ŀ��
	m_TeacherTab.SetPadding(CSize(6,2));			//�趨��ǩ�ĳߴ�
	m_TeacherTab.SetCurSel(0);

	DoTab(0);										//Ĭ��ѡ����һ����ǩ
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTeacherDlg::SetDlgState(CWnd *pWnd,BOOL bShow)
{
	pWnd->EnableWindow(bShow);
	if(bShow)
	{	
		pWnd->ShowWindow(SW_SHOW);					//��ʾ����
		pWnd->CenterWindow();						//���ھ���
        if(bTab[1])
		m_pTab2Dlg->MyShow();	
	}
	else pWnd->ShowWindow(SW_HIDE);					//���ش���
}

void CTeacherDlg::DoTab(int nTab)
{
	if(nTab>1)nTab=1;								//��ݵ��ж�
	if(nTab<0)nTab=0;
	bTab[0]=bTab[1]=false;							//���岼������������ֵ
	bTab[nTab]=TRUE;
	SetDlgState(m_pTab1Dlg,bTab[0]);				//�趨���ڵ�״̬
	SetDlgState(m_pTab2Dlg,bTab[1]);
 
}
void CTeacherDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	if(m_pTab1Dlg) delete m_pTab1Dlg;				//�ͷŶԻ���ungzhizhen
	if(m_pTab2Dlg) delete m_pTab2Dlg;
		
}

void CTeacherDlg::OnSelchangeTeacherTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nSelect=m_TeacherTab.GetCurSel();			//��ȡ�û�ѡ����ǩ������
	if (nSelect>=0)
		DoTab(nSelect);								//���ƴ��ڵ���������ʾ

	*pResult = 0;
}

