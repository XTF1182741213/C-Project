// HolidayManageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "hmsys.h"
#include "HolidayManageDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHolidayManageDlg dialog
extern CHMSysApp theApp;

CHolidayManageDlg::CHolidayManageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHolidayManageDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHolidayManageDlg)
	m_strName = _T("");
	m_Date = CTime::GetCurrentTime();
	//}}AFX_DATA_INIT
	m_nFlag = -1;
}


void CHolidayManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHolidayManageDlg)
	DDX_Control(pDX, IDC_LIST1, m_ListCrtl);
	DDX_Control(pDX, IDC_SHOWTIME, m_Clock);
	DDX_Text(pDX, IDC_NAME, m_strName);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_Date);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHolidayManageDlg, CDialog)
	//{{AFX_MSG_MAP(CHolidayManageDlg)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
	ON_BN_CLICKED(IDC_DEL, OnDel)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnItemchangedList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHolidayManageDlg message handlers

BOOL CHolidayManageDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_Clock.Start(IDB_CLOCKST_PANE, IDB_CLOCKST_BIG, IDB_CLOCKST_SMALL);
	GetDlgItem(IDC_SAVE)->EnableWindow(FALSE);
	m_pRecordset.CreateInstance("ADODB.Recordset");
	m_ListCrtl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT );//�����趨������ѡ��
	m_ListCrtl.InsertColumn(0, "ID", LVCFMT_CENTER, 40);
	m_ListCrtl.InsertColumn(1, "�ڼ�������", LVCFMT_CENTER, 120);
	m_ListCrtl.InsertColumn(2, "�ڼ�������", LVCFMT_CENTER, 120);
	ShowListData();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CHolidayManageDlg::ShowListData()
{
	CString strSQL;
	strSQL.Format("select * from holiday");
	m_ListCrtl.DeleteAllItems();
	try
	{
		m_pRecordset = theApp.m_pConnection->Execute((_bstr_t)strSQL, NULL, adCmdText);
		int i = 0;
		while(!m_pRecordset->adoEOF)
		{
			m_ListCrtl.InsertItem(i, (char*)_bstr_t(m_pRecordset->GetCollect(_variant_t((long)0))));
			m_ListCrtl.SetItemText(i, 1, (char*)_bstr_t(m_pRecordset->GetCollect(_variant_t((long)1))));
			m_ListCrtl.SetItemText(i, 2, (char*)_bstr_t(m_pRecordset->GetCollect(_variant_t((long)2))));
			i++;
			m_pRecordset->MoveNext();
		}
	}
	CATCH_ERROR;
}

void CHolidayManageDlg::OnAdd() 
{
	GetDlgItem(IDC_SAVE)->EnableWindow();
	m_strName = "";
	m_nFlag = 1;
}

void CHolidayManageDlg::OnUpdate() 
{
	GetDlgItem(IDC_SAVE)->EnableWindow();
	if(m_strID == "")
	{
		MessageBox("��ѡ��һ����¼��");
		return ;
	}
	m_nFlag = 2;
}

void CHolidayManageDlg::OnDel() 
{
	if(m_strID == "")
	{
		MessageBox("��ѡ��һ����¼��");
		return ;
	}
	CString strSQL;
	strSQL.Format("delete from holiday where id = %s", m_strID);
	if(MessageBox("ȷ��ɾ����", "ע��", MB_YESNO) == IDYES)
	{
		try
		{
			theApp.m_pConnection->Execute((_bstr_t)strSQL, NULL, adCmdText);
			MessageBox("ɾ���ɹ���");
			m_strName = "";
			ShowListData();
		}
		CATCH_ERROR;
	}	
	UpdateData(FALSE);
}

void CHolidayManageDlg::OnSave() 
{
	UpdateData();
	if(m_strName == "")
	{
		MessageBox("������ڼ������ƣ�");
		return ;
	}
	CString strSQL, strDate;
	strDate.Format("%d-%d-%d", m_Date.GetYear(), m_Date.GetMonth(), m_Date.GetDay());
	if(m_nFlag == 1)
	{
		strSQL.Format("insert into holiday (name, date) values ('%s', '%s')", m_strName, strDate);
	}
	if(m_nFlag == 2)
	{
		strSQL.Format("update holiday set name = '%s', date = '%s' where id = %s", m_strName, strDate, m_strID);
	}
	try
	{
		theApp.m_pConnection->Execute((_bstr_t)strSQL, NULL, adCmdText);
		MessageBox("�����ɹ���");
		m_strName = "";
		ShowListData();
	}
	CATCH_ERROR;
	GetDlgItem(IDC_SAVE)->EnableWindow(FALSE);
}

void CHolidayManageDlg::OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nSelect = pNMListView->iItem;
	m_strID = m_ListCrtl.GetItemText(nSelect, 0);
	m_strName = m_ListCrtl.GetItemText(nSelect, 1);
	CString strDate = m_ListCrtl.GetItemText(nSelect, 2);
	
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
