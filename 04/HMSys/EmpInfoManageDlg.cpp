// EmpInfoManageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "hmsys.h"
#include "EmpInfoManageDlg.h"
#include "EmpAddDlg.h"
#include "EmpUpdateDlg.h"
#include "EmpIndexDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEmpInfoManageDlg dialog

extern CHMSysApp theApp;
CEmpInfoManageDlg::CEmpInfoManageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEmpInfoManageDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEmpInfoManageDlg)
	//}}AFX_DATA_INIT
}


void CEmpInfoManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEmpInfoManageDlg)
	DDX_Control(pDX, IDC_LIST1, m_ListCrtl);
	DDX_Control(pDX, IDC_TREE1, m_TreeCrtl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEmpInfoManageDlg, CDialog)
	//{{AFX_MSG_MAP(CEmpInfoManageDlg)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE1, OnDblclkTree1)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnItemchangedList1)
	ON_BN_CLICKED(IDC_DEL, OnDel)
	ON_BN_CLICKED(IDC_INDEX, OnIndex)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEmpInfoManageDlg message handlers

BOOL CEmpInfoManageDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_pRecordset.CreateInstance("ADODB.Recordset");
	m_pRecordset1.CreateInstance("ADODB.Recordset");
	m_ListCrtl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT );//�����趨������ѡ��
	m_ListCrtl.InsertColumn(0, "ID", LVCFMT_CENTER, 40);
	m_ListCrtl.InsertColumn(1, "Ա������", LVCFMT_CENTER, 60);
	m_ListCrtl.InsertColumn(2, "����", LVCFMT_CENTER, 40);
	m_ListCrtl.InsertColumn(3, "�Ա�", LVCFMT_CENTER, 40);
	m_ListCrtl.InsertColumn(4, "����", LVCFMT_CENTER, 120);
	m_ListCrtl.InsertColumn(5, "����", LVCFMT_CENTER, 120);
	m_ListCrtl.InsertColumn(6, "��������", LVCFMT_CENTER, 100);
	m_ListCrtl.InsertColumn(7, "�绰", LVCFMT_CENTER, 80);
	m_ListCrtl.InsertColumn(8, "��ע", LVCFMT_CENTER, 200);
	ShowTreeData();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEmpInfoManageDlg::ShowTreeData()
{
	m_TreeCrtl.DeleteAllItems();					//ɾ�����е�����
	HTREEITEM hItem;								//������
	TVINSERTSTRUCT tvInsert;						//����ṹ��
	tvInsert.hParent = NULL;
	tvInsert.hInsertAfter = NULL;
	tvInsert.item.mask = TVIF_TEXT;
	tvInsert.item.pszText = _T("ĳ��λ");			//���ڵ�ĸ�ֵ
	m_hParent = m_TreeCrtl.InsertItem(&tvInsert);	//������ڵ�
	_variant_t vName;
	CString strSQL;									//�����ַ�������
	strSQL.Format("select [name] from dep");
	try
	{
		m_pRecordset = theApp.m_pConnection->Execute((_bstr_t)strSQL, NULL, adCmdText);
		while(!m_pRecordset->adoEOF)				//�����¼û�е�ĩβ
		{
			vName = m_pRecordset->GetCollect(_variant_t((long)0));//��ȡ��¼����һ�е�ֵ
			hItem = m_TreeCrtl.InsertItem((char*)_bstr_t(vName), m_hParent);//���뵽�б�ؼ���
			strSQL.Format("select name from emp");
			m_pRecordset1 = theApp.m_pConnection->Execute((_bstr_t)strSQL, NULL, adCmdText);
			while(!m_pRecordset1->adoEOF)
			{
				vName = m_pRecordset1->GetCollect(_variant_t((long)0));
				m_TreeCrtl.InsertItem((char*)_bstr_t(vName), hItem);
				m_pRecordset1->MoveNext();
			}
			m_pRecordset->MoveNext();
		}
		m_TreeCrtl.Expand(m_hParent,TVE_EXPAND);//չ�����ڵ�
	}
	CATCH_ERROR;
}

void CEmpInfoManageDlg::ShowListData(const CString& sql)
{
	m_ListCrtl.DeleteAllItems();				//ɾ�����е�����
	try
	{
		m_pRecordset = theApp.m_pConnection->Execute((_bstr_t)sql, NULL, adCmdText);
		int i = 0;
		while(!m_pRecordset->adoEOF)//��¼û�е�ĩβ
		{
			m_ListCrtl.InsertItem(i, (char*)_bstr_t(m_pRecordset->GetCollect(_variant_t((long)0))));
			m_ListCrtl.SetItemText(i, 1, (char*)_bstr_t(m_pRecordset->GetCollect(_variant_t((long)1))));
			m_ListCrtl.SetItemText(i, 2, (char*)_bstr_t(m_pRecordset->GetCollect(_variant_t((long)2))));
			m_ListCrtl.SetItemText(i, 3, (char*)_bstr_t(m_pRecordset->GetCollect(_variant_t((long)3))));
			m_ListCrtl.SetItemText(i, 4, (char*)_bstr_t(m_pRecordset->GetCollect(_variant_t((long)4))));
			m_ListCrtl.SetItemText(i, 5, (char*)_bstr_t(m_pRecordset->GetCollect(_variant_t((long)5))));
			m_ListCrtl.SetItemText(i, 6, (char*)_bstr_t(m_pRecordset->GetCollect(_variant_t((long)6))));
			m_ListCrtl.SetItemText(i, 7, (char*)_bstr_t(m_pRecordset->GetCollect(_variant_t((long)7))));
			m_ListCrtl.SetItemText(i, 8, (char*)_bstr_t(m_pRecordset->GetCollect(_variant_t((long)8))));
			i++;
			m_pRecordset->MoveNext();//�ƶ�����һ����¼
		}
	}
	CATCH_ERROR;
}

void CEmpInfoManageDlg::OnDblclkTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	_variant_t va;
	CString strSQL;
	HTREEITEM hSelect;
	hSelect = m_TreeCrtl.GetSelectedItem();			//��ȡѡ�нڵ������
	CString strName;
	if(hSelect != m_hParent)						//�ж��Ƿ�Ϊ���ڵ�
	{
		strName = m_TreeCrtl.GetItemText(hSelect); //��ȡѡ�нڵ���ı�
		if(m_TreeCrtl.GetParentItem(hSelect) == m_hParent)//�ж��Ƿ�Ϊ���ڵ���ӽ��
		{
			strSQL.Format("select * from emp where depart = '%s'", strName);
		}
		else
			strSQL.Format("select * from emp where name = '%s'", strName);
		ShowListData(strSQL);			//��ʾ����
	}
	*pResult = 0;
}

void CEmpInfoManageDlg::OnAdd() 
{
	CEmpAddDlg dlg;
	dlg.DoModal();
}

void CEmpInfoManageDlg::OnUpdate() 
{
	if(theApp.m_strEmpID == "")
	{
		MessageBox("��ѡ��һ����Ϣ��");
		return ;
	}
	CEmpUpdateDlg dlg;
	dlg.DoModal();
}

void CEmpInfoManageDlg::OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nSelect = pNMListView->iItem;						//��ȡѡ�����к�
	theApp.m_strEmpID = m_ListCrtl.GetItemText(nSelect,0);	//ȥ��ѡ���еĵ�һ�е��ı�
	*pResult = 0;
}

void CEmpInfoManageDlg::OnDel() 
{
	if(theApp.m_strEmpID == "")
	{
		MessageBox("��ѡ��һ����Ϣ��");
		return ;
	}
	CString strSQL;					//�����ַ�������
	strSQL.Format("delete from emp where id = %s", theApp.m_strEmpID);
	if(MessageBox("ȷ��ɾ����", "ע��", MB_YESNO) == IDYES)//��Ϣ��ʾ
	{
		try
		{
			theApp.m_pConnection->Execute((_bstr_t)strSQL, NULL, adCmdText);
			MessageBox("ɾ���ɹ���");
			ShowTreeData();
			m_ListCrtl.DeleteAllItems();
		}
		CATCH_ERROR;
	}		
}

void CEmpInfoManageDlg::OnIndex() 
{
	CEmpIndexDlg dlg;						//����Ի������
	UpdateData();
	if(dlg.DoModal() == IDOK)				//�������˲�ѯ��ť
	{
		CString strSQL;						//�����ַ�������
		if(dlg.m_nFlag == 1)				//�жϲ�ѯ�ķ�ʽ
		{
			strSQL.Format("select * from emp where id = %s", dlg.m_strID);
			ShowListData(strSQL);
		}
		if(dlg.m_nFlag == 2)
		{
			strSQL.Format("select * from emp where name = '%s'", dlg.m_strName);
			ShowListData(strSQL);
		}
	}
}
