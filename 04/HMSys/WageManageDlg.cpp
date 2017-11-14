// WageManageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "hmsys.h"
#include "WageManageDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWageManageDlg dialog
extern CHMSysApp theApp;

CWageManageDlg::CWageManageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWageManageDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWageManageDlg)
	m_strID = _T("");
	m_nWage = 0;
	m_Date = CTime::GetCurrentTime();
	//}}AFX_DATA_INIT
	m_nFlag = -1;
}


void CWageManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWageManageDlg)
	DDX_Control(pDX, IDC_COMBO1, m_Depart);
	DDX_Control(pDX, IDC_LIST1, m_ListCrtl);
	DDX_Control(pDX, IDC_TREE1, m_TreeCrtl);
	DDX_Text(pDX, IDC_ID, m_strID);
	DDX_Text(pDX, IDC_WAGE, m_nWage);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_Date);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWageManageDlg, CDialog)
	//{{AFX_MSG_MAP(CWageManageDlg)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE1, OnDblclkTree1)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_DEL, OnDel)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnItemchangedList1)
	ON_BN_CLICKED(IDC_INDEX, OnIndex)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWageManageDlg message handlers

BOOL CWageManageDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_pRecordset.CreateInstance("ADODB.Recordset");	
	ShowTreeData();
	m_ListCrtl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT );//�����趨
	m_ListCrtl.InsertColumn(0, "Ա��ID", LVCFMT_CENTER, 60);//�б�����趨
	m_ListCrtl.InsertColumn(1, "��н", LVCFMT_CENTER, 60);
	m_ListCrtl.InsertColumn(2, "����", LVCFMT_CENTER, 100);
	m_ListCrtl.InsertColumn(3, "����ʱ��", LVCFMT_CENTER, 100);
	GetDlgItem(IDC_SAVE)->EnableWindow(FALSE);//�ؼ��Ľ���
	CString strSQL;//�����ַ�������
	strSQL.Format("select name from dep");
	try
	{
		m_pRecordset = theApp.m_pConnection->Execute((_bstr_t)strSQL, NULL, adCmdText);
		while(!m_pRecordset->adoEOF)//��¼û�е�ĩβ
		{
			m_Depart.AddString((char*)_bstr_t(m_pRecordset->GetCollect(_variant_t((long)0))));
			m_pRecordset->MoveNext();//�ƶ���������¼
		}
	}
	CATCH_ERROR;
	m_Depart.SetCurSel(0);
	ShowListData("select * from wageinfo");
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CWageManageDlg::ShowTreeData()
{
	m_TreeCrtl.DeleteAllItems();
	HTREEITEM hItem;
	TVINSERTSTRUCT tvInsert;
	tvInsert.hParent = NULL;
	tvInsert.hInsertAfter = NULL;
	tvInsert.item.mask = TVIF_TEXT;
	tvInsert.item.pszText = _T("ĳ��λ");
	m_hParent = m_TreeCrtl.InsertItem(&tvInsert);
	_variant_t vName;
	CString strSQL;
	strSQL.Format("select [name] from dep");
	try
	{
		m_pRecordset = theApp.m_pConnection->Execute((_bstr_t)strSQL, NULL, adCmdText);
		while(!m_pRecordset->adoEOF)
		{
			vName = m_pRecordset->GetCollect(_variant_t((long)0));
			hItem = m_TreeCrtl.InsertItem((char*)_bstr_t(vName), m_hParent);
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
		m_TreeCrtl.Expand(m_hParent,TVE_EXPAND);
	}
	CATCH_ERROR;
}

void CWageManageDlg::ShowListData(const CString& sql)
{
	m_ListCrtl.DeleteAllItems();
	try
	{
		m_pRecordset = theApp.m_pConnection->Execute((_bstr_t)sql, NULL, adCmdText);
		int i = 0;
		while(!m_pRecordset->adoEOF)
		{
			m_ListCrtl.InsertItem(i, (char*)_bstr_t(m_pRecordset->GetCollect(_variant_t((long)0))));
			m_ListCrtl.SetItemText(i, 1, (char*)_bstr_t(m_pRecordset->GetCollect(_variant_t((long)1))));
			m_ListCrtl.SetItemText(i, 2, (char*)_bstr_t(m_pRecordset->GetCollect(_variant_t((long)2))));
			m_ListCrtl.SetItemText(i, 3, (char*)_bstr_t(m_pRecordset->GetCollect(_variant_t((long)3))));
			i++;
			m_pRecordset->MoveNext();
		}
	}
	CATCH_ERROR;
}

void CWageManageDlg::OnDblclkTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	_variant_t va;
	CString strSQL;
	HTREEITEM hSelect;
	hSelect = m_TreeCrtl.GetSelectedItem();
	CString strName;
	if(hSelect != m_hParent)
	{
		strName = m_TreeCrtl.GetItemText(hSelect);
		if(m_TreeCrtl.GetParentItem(hSelect) == m_hParent)
		{
			strSQL.Format("select * from wageinfo where dep = '%s'", strName);
			ShowListData(strSQL);
		}
	}
	*pResult = 0;
}

void CWageManageDlg::OnAdd() 
{
	m_strID = "";
	m_nFlag = 1;			//��ǵ��趨
	m_nWage = 0;
	GetDlgItem(IDC_SAVE)->EnableWindow();//�ؼ��Ļָ�
	UpdateData(FALSE);
}

void CWageManageDlg::OnUpdate() 
{
	UpdateData();
	if(m_strID == "")
	{
		MessageBox("��ѡ��һ����¼��");
		return ;
	}
	GetDlgItem(IDC_SAVE)->EnableWindow();	//�ؼ��Ļָ�
	m_nFlag = 2;	//��ǵ��趨
}

void CWageManageDlg::OnSave() 
{
	UpdateData();				//���ݵĸ���
	if(m_strID == "")
	{
		MessageBox("ID����Ϊ�գ�");
		return ;
	}
	CString strSQL, strDep, strDate;//�����ַ�������
	_variant_t va;
	strSQL.Format("select count(*) from emp  where [id] = %s", m_strID);
	try
	{
		m_pRecordset = theApp.m_pConnection->Execute((_bstr_t)strSQL, NULL, adCmdText);
		va = m_pRecordset->GetCollect(_variant_t((long)0));//��ȡ��¼��ֵ
		if(va.iVal == 0)
		{
			MessageBox("û�д�Ա����");
			return ;
		}
	}
	CATCH_ERROR;
	int nIndex = m_Depart.GetCurSel();//��ȡѡ�е�����
	m_Depart.GetLBText(nIndex, strDep);//��ȡѡ�е��ı�
	strDate.Format("%d-%d-%d", m_Date.GetYear(), m_Date.GetMonth(), m_Date.GetDay());
	if(m_nFlag == 1)//�������
	{	
		strSQL.Format("insert into wageinfo values(%s, %d, '%s', '%s')",
			m_strID, m_nWage, strDep, strDate);
	}
	if(m_nFlag == 2)//�޸Ĳ���
	{
		strSQL.Format("update wageinfo set wage = %d, date = '%s' where id = %s", m_nWage, strDate, m_strID);
	}
	try
	{
		theApp.m_pConnection->Execute((_bstr_t)strSQL, NULL, adCmdText);
		GetDlgItem(IDC_SAVE)->EnableWindow(FALSE);//�ؼ��Ľ���
		m_strID = "";
		m_nFlag = -1;
		m_nWage = 0;
		MessageBox("�����ɹ���");
		ShowListData("select * from wageinfo");
		ShowTreeData();
	}
	CATCH_ERROR;
	UpdateData(FALSE);
}

void CWageManageDlg::OnDel() 
{
	UpdateData();						//���ݵĸ���
	if(m_strID == "")
	{
		MessageBox("��ѡ��һ����¼��");
		return ;
	}
	if(MessageBox("ȷ��ɾ����", "ע��", MB_YESNO) == IDYES)
	{
		CString strSQL;					//�����ַ�������
		strSQL.Format("delete wageinfo where id = '%s'", m_strID);
		try
		{
			theApp.m_pConnection->Execute((_bstr_t)strSQL, NULL, adCmdText);
			MessageBox("ɾ���ɹ���");
			ShowTreeData();
			ShowListData("select * from wageinfo");
		}
		CATCH_ERROR;
	}		
}

void CWageManageDlg::OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nSelect = pNMListView->iItem;
	m_strID = m_ListCrtl.GetItemText(nSelect, 0);
	m_nWage = atoi(m_ListCrtl.GetItemText(nSelect, 1));
	GetDlgItem(IDC_COMBO1)->SetWindowText(m_ListCrtl.GetItemText(nSelect, 2));
	CString strDate = m_ListCrtl.GetItemText(nSelect, 3);

	COleVariant vtime(strDate);
	vtime.ChangeType(VT_DATE);
	COleDateTime time1=vtime;
	SYSTEMTIME systime;
	VariantTimeToSystemTime(time1, &systime);
	CTime tm(systime);
	m_Date   =   tm;  
	UpdateData(FALSE);	
	*pResult = 0;
}

void CWageManageDlg::OnIndex() 
{
	UpdateData();
	CString strSQL, strDate;
	strDate.Format("%d-%d-%d", m_Date.GetYear(), m_Date.GetMonth(), m_Date.GetDay());
	strSQL.Format("select * from wageinfo where id like '%%%s%%' and wage like '%%%d%%' and date like '%%%s%%'",
		m_strID, m_nWage, strDate);
	ShowListData(strSQL);
}
