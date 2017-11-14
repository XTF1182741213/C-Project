// StudentDlg.cpp : implementation file
//

#include "stdafx.h"
#include "gradudemis.h"
#include "StudentDlg.h"
#include "StudentTab1.h"
#include "StudentTab2.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStudentDlg dialog


CStudentDlg::CStudentDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStudentDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStudentDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CStudentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStudentDlg)
	DDX_Control(pDX, IDC_TAB1, m_Tab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStudentDlg, CDialog)
	//{{AFX_MSG_MAP(CStudentDlg)
	ON_WM_DESTROY()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStudentDlg message handlers

void CStudentDlg::SetDlgState(CWnd *pWnd,BOOL bShow)
{
	pWnd->EnableWindow(bShow);				//���ڵ���������ʾ���ݱ�����ֵ
	if(bShow)								//�ж�
	{
		pWnd->ShowWindow(SW_SHOW);			//��ʾ�����ǩ�����Ĵ���
		pWnd->CenterWindow();				//���ھ���
		if(bTab[1])								
			m_pTab2Dlg->OnShow();			//��ʾ����
	}
	else 
		pWnd->ShowWindow(SW_HIDE);			//���ش���
}

void CStudentDlg::DoTab(int nTab)		
{
	if(nTab>1)nTab=1;						//�߽���ж�
	if(nTab<0)nTab=0;
	bTab[0]=bTab[1]=false;					//���岼��������ʼֵfalse
	bTab[nTab]=TRUE;						//����ĸ���ǩ��Ϊtrue
	SetDlgState(m_pTab1Dlg,bTab[0]);		//���Ĵ��ڵ�״̬
	SetDlgState(m_pTab2Dlg,bTab[1]);		//���Ĵ��ڵ�״̬
}

void CStudentDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	if(m_pTab1Dlg) delete m_pTab1Dlg;		//�ͷŴ��ڵ�ָ��
	if(m_pTab2Dlg) delete m_pTab2Dlg;		//�ͷŴ��ڵ�ָ��	
}

void CStudentDlg::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nSelect=m_Tab.GetCurSel();			//��ȡ�û������ǩ��������
	if (nSelect>=0)
		DoTab(nSelect);						//���ú����ı䴰��״̬
	*pResult = 0;
}
BOOL CStudentDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CStudentTab1 *p=(CStudentTab1 *)AfxGetApp();
	m_pTab1Dlg=new CStudentTab1();			//newһ���Ի���ָ��
	m_pTab2Dlg=new CStudentTab2();
	m_pTab1Dlg->Create(IDD_STU_DIALOG1,&m_Tab);//�����Ի���
	m_pTab2Dlg->Create(IDD_STU_DIALOG2,&m_Tab);
	m_Tab.InsertItem(0,"ѧ����Ϣ��ѯ",0);	//Ϊ��ǩ�������
	m_Tab.InsertItem(1,"ѧ����Ϣ����",1);
	m_Tab.SetMinTabWidth(80);				//���ñ�ǩ�Ŀ��
	m_Tab.SetPadding(CSize(6,2));			//���óߴ�
	m_Tab.SetCurSel(0);						//Ĭ��ѡ�е�һ����ǩ
	DoTab(0);								//��ʾ��һ����ǩ�����Ĵ���
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
