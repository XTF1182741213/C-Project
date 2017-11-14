// SubTab1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "gradudemis.h"
#include "SubTab1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSubTab1Dlg dialog


CSubTab1Dlg::CSubTab1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSubTab1Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSubTab1Dlg)
	m_find = _T("");
	//}}AFX_DATA_INIT
}


void CSubTab1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSubTab1Dlg)
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Control(pDX, IDC_LIST1, m_ctrlsubTab1list);
	DDX_Text(pDX, IDC_EDIT1, m_find);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSubTab1Dlg, CDialog)
	//{{AFX_MSG_MAP(CSubTab1Dlg)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnItemchangedList1)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSubTab1Dlg message handlers
void CSubTab1Dlg::OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int i=pNMListView->iItem;						//��ȡѡ�����к�
	selectID=m_ctrlsubTab1list.GetItemText(i,0);	//ȥ��ѡ���еĵ�һ�е��ı�
	*pResult = 0;
}


BOOL CSubTab1Dlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_ctrlsubTab1list.InsertColumn(0,"��Ŀ",LVCFMT_LEFT,60,0);//�����б��⣬�趨��ȣ����뷽ʽ
	m_ctrlsubTab1list.InsertColumn(1,"����",LVCFMT_LEFT,80,0);
	m_ctrlsubTab1list.InsertColumn(2,"����",LVCFMT_LEFT,150,0);
	m_ctrlsubTab1list.InsertColumn(3,"Ҫ��",LVCFMT_LEFT,150,0);
	m_ctrlsubTab1list.InsertColumn(4,"��ʦ",LVCFMT_LEFT,80,0);
    m_ctrlsubTab1list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);	
	m_pSet.Open();	
	int i=0;												//�������α���
	while(!m_pSet.IsEOF())									//�����¼�������һ��
	{
		m_ctrlsubTab1list.InsertItem(i,m_pSet.m_sub_title);	//���б�ؼ��в�������
		m_ctrlsubTab1list.SetItemText(i,1,m_pSet.m_sub_type);
		m_ctrlsubTab1list.SetItemText(i,2,m_pSet.m_sub_pro);
		m_ctrlsubTab1list.SetItemText(i,3,m_pSet.m_sub_demand);
		m_ctrlsubTab1list.SetItemText(i,4,m_pSet.m_tecr_name);		
        m_pSet.MoveNext();									//�ƶ���������¼
        i++;
	}
	m_pSet.Close();			
	m_combo.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSubTab1Dlg::OnButton1() 
{
	UpdateData();
	if(m_find == "")
	{
		MessageBox("�������ѯ������");
		return ;
	}
	CString str, sql;
	int nIndex = m_combo.GetCurSel();
	switch(nIndex)
	{
	case 0:
		sql.Format("select * from tab_sub where sub_title like '%%%s%%'", m_find);
		
		break;
	case 1:
		sql.Format("select * from tab_sub where tecr_name like '%%%s%%'", m_find);
		break;
	case 2:
		sql.Format("select * from tab_sub where sub_type like '%%%s%%'", m_find);
		break;
	}
	CDatabase *pDb = new CDatabase();
	CSubjectSet *pSet = new CSubjectSet(pDb);
	pSet->Open(AFX_DB_USE_DEFAULT_TYPE, sql);

	m_ctrlsubTab1list.DeleteAllItems();
	int i=0;												//�������α���
	while(!pSet->IsEOF())									//�����¼�������һ��
	{
		m_ctrlsubTab1list.InsertItem(i,pSet->m_sub_title);	//���б�ؼ��в�������
		m_ctrlsubTab1list.SetItemText(i,1,pSet->m_sub_type);
		m_ctrlsubTab1list.SetItemText(i,2,pSet->m_sub_pro);
		m_ctrlsubTab1list.SetItemText(i,3,pSet->m_sub_demand);
		m_ctrlsubTab1list.SetItemText(i,4,pSet->m_tecr_name);		
        pSet->MoveNext();									//�ƶ���������¼
        i++;
	}
	pSet->Close();
}
