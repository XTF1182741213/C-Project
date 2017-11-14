// SubjectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "gradudemis.h"
#include "SubjectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSubjectDlg dialog


CSubjectDlg::CSubjectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSubjectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSubjectDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSubjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSubjectDlg)
	DDX_Control(pDX, IDC_TAB1, m_Tab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSubjectDlg, CDialog)
	//{{AFX_MSG_MAP(CSubjectDlg)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab1)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSubjectDlg message handlers

BOOL CSubjectDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_pTab1Dlg= new CSubTab1Dlg();					//����һ���Ի����ָ��
	m_pTab2Dlg= new CSubTab2Dlg();
	m_pTab1Dlg->Create(IDD_SubTab1_DLG,&m_Tab);		//�����Ի���
	m_pTab2Dlg->Create(IDD_SubTab2_DLG,&m_Tab);

	m_Tab.InsertItem(0,"������Ϣ��ѯ",0);			//�趨��ǩ�ı���
	m_Tab.InsertItem(1,"������Ϣ����",1);
	DoTab(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSubjectDlg::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nSelect=m_Tab.GetCurSel();					//��ȡѡ����ǩ������
	if(nSelect>=0)									
		DoTab(nSelect);								//�û��Զ��庯�����ı䴰��״̬

	*pResult = 0;
}

void CSubjectDlg::SetDlgState(CWnd *pWnd,BOOL bShow)
{
    pWnd->EnableWindow(bShow);						
	if(bShow)
	{
		pWnd->ShowWindow(SW_SHOW);					//��ʾ����
		pWnd->CenterWindow();						//ʹ���ھ���
		if(bTab[1])						
		   m_pTab2Dlg->MyShow();		
	}
	else pWnd->ShowWindow(SW_HIDE);					//���ش���
}
void CSubjectDlg::DoTab(int nTab)
{
	if(nTab>1)nTab=1;								//�߽���ж�
	if(nTab<0)nTab=0;
	bTab[0]=bTab[1]=false;							//���岼�������趨��ֵ
	bTab[nTab]=TRUE;								//��ѡ�е�Ϊ��
	SetDlgState(m_pTab1Dlg,bTab[0]);				//�ı䴰�ڵ�״̬
	SetDlgState(m_pTab2Dlg,bTab[1]);
}

void CSubjectDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	if(m_pTab1Dlg) delete m_pTab1Dlg;				//�ͷŴ��ڵ�ָ��
	if(m_pTab2Dlg) delete m_pTab2Dlg;
		
}
