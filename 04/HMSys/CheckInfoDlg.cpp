// CheckInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "hmsys.h"
#include "CheckInfoDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCheckInfoDlg dialog
extern CHMSysApp theApp;

CCheckInfoDlg::CCheckInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCheckInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCheckInfoDlg)
	m_strID = _T("");
	m_Date = CTime::GetCurrentTime();
	//}}AFX_DATA_INIT
}


void CCheckInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCheckInfoDlg)
	DDX_Control(pDX, IDC_LIST1, m_ListCrtl);
	DDX_Text(pDX, IDC_ID, m_strID);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_Date);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCheckInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CCheckInfoDlg)
	ON_BN_CLICKED(IDC_INDEX, OnIndex)
	ON_BN_CLICKED(IDC_DEL, OnDel)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnItemchangedList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCheckInfoDlg message handlers

BOOL CCheckInfoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_pRecordset.CreateInstance("ADODB.Recordset");		//������¼��ʵ��
	m_ListCrtl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT );//�����趨������ѡ��
	m_ListCrtl.InsertColumn(0, "����", LVCFMT_CENTER, 80);
	m_ListCrtl.InsertColumn(1, "Ա��ID", LVCFMT_CENTER, 60);
	m_ListCrtl.InsertColumn(2, "ȱ��", LVCFMT_CENTER, 40);
	m_ListCrtl.InsertColumn(3, "����", LVCFMT_CENTER, 40);
	m_ListCrtl.InsertColumn(4, "�ٵ�", LVCFMT_CENTER, 40);
	m_ListCrtl.InsertColumn(5, "��Ϣ", LVCFMT_CENTER, 40);
	m_ListCrtl.InsertColumn(6, "����", LVCFMT_CENTER, 40);
	m_ListCrtl.InsertColumn(7, "����", LVCFMT_CENTER, 40);
	m_ListCrtl.InsertColumn(8, "�¼�", LVCFMT_CENTER, 40);
	m_ListCrtl.InsertColumn(9, "��ע", LVCFMT_CENTER, 120);
	CString strSQL;								//�����ַ�������
	strSQL.Format("select * from checkinfo ");
	try
	{
		m_pRecordset = theApp.m_pConnection->Execute((_bstr_t)strSQL, NULL, adCmdText);//ִ��SQL���
		int i = 0;//�������α���������ֵ0
		while(!m_pRecordset->adoEOF)//�����¼û�е�ĩβ
		{
			m_ListCrtl.InsertItem(i, (char*)_bstr_t(m_pRecordset->GetCollect(_variant_t((long)0))));
			for(int j = 1; j < 9; j++)
				m_ListCrtl.SetItemText(i, j, (char*)_bstr_t(m_pRecordset->GetCollect(_variant_t((long)j))));
			i++;
			m_pRecordset->MoveNext();//�ƶ�����һ����¼
		}
	}
	CATCH_ERROR;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCheckInfoDlg::ShowListData(const CString& sql)
{
	m_ListCrtl.DeleteAllItems();//ɾ���б�ؼ��е���������
	try
	{
		m_pRecordset = theApp.m_pConnection->Execute((_bstr_t)sql, NULL, adCmdText);//ִ��SQL���
		int i = 0;
		while(!m_pRecordset->adoEOF)//�����¼û�е�ĩβ
		{
			m_ListCrtl.InsertItem(i, (char*)_bstr_t(m_pRecordset->GetCollect(_variant_t((long)0))));
			//�����ݲ��뵽�б�ؼ���
			for(int j = 1; j < 9; j++)
				m_ListCrtl.SetItemText(i, j, (char*)_bstr_t(m_pRecordset->GetCollect(_variant_t((long)j))));
			i++;
			m_pRecordset->MoveNext();//�ƶ�����һ����¼
		}
	}
	CATCH_ERROR;
}

void CCheckInfoDlg::OnIndex() 
{
	UpdateData();
	if(m_strID == "")
	{
		MessageBox("������ѯ������");
		return ;
	}
	CString strSQL, strDate;//�����ַ�������
	strDate.Format("%d-%d-%d", m_Date.GetYear(), m_Date.GetMonth(), m_Date.GetDay());
	strSQL.Format("select * from checkinfo where id = %s and date = '%s'", m_strID, strDate);
	ShowListData(strSQL);//
}

void CCheckInfoDlg::OnDel() 
{
	if(m_strID == "")
	{
		MessageBox("��ѡ��һ����¼��");
		return ;
	}
	if(MessageBox("ȷ��ɾ����", "ע��", MB_YESNO) == IDYES)
	{
		CString strSQL, strDate;
		strDate.Format("%d-%d-%d", m_Date.GetYear(), m_Date.GetMonth(), m_Date.GetDay());
		strSQL.Format("delete from checkinfo where id = %s and date = '%s'", m_strID, strDate);
		try 
		{
			theApp.m_pConnection->Execute((_bstr_t)strSQL, NULL, adCmdText);
			ShowListData("select * from checkinfo");
		}
		CATCH_ERROR;
	}
}

void CCheckInfoDlg::OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nSelect = pNMListView->iItem;//��ȡ�б�ؼ���ѡ�е��е�����
	m_strID = m_ListCrtl.GetItemText(nSelect, 1);//��ȡ�б�ؼ�ѡ���еڶ�����ı�
	CString strDate = m_ListCrtl.GetItemText(nSelect, 0);
	COleVariant vtime(strDate);
	vtime.ChangeType(VT_DATE);
	COleDateTime time1=vtime;
	SYSTEMTIME systime;
	VariantTimeToSystemTime(time1, &systime);
	CTime tm(systime); 
	m_Date=tm;
	UpdateData(FALSE);	
	*pResult = 0;
}
