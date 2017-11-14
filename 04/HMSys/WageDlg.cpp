// WageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "hmsys.h"
#include "WageDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWageDlg dialog

extern CHMSysApp theApp;
CWageDlg::CWageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWageDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWageDlg)
	m_strID = _T("");
	//}}AFX_DATA_INIT
}


void CWageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWageDlg)
	DDX_Control(pDX, IDC_COMBO1, m_Month);
	DDX_Control(pDX, IDC_LIST1, m_ListCrtl);
	DDX_Text(pDX, IDC_ID, m_strID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWageDlg, CDialog)
	//{{AFX_MSG_MAP(CWageDlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWageDlg message handlers

BOOL CWageDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_pRecordset.CreateInstance("ADODB.Recordset");	
	m_pRecordset1.CreateInstance("ADODB.Recordset");	
	m_ListCrtl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT );//�����趨������ѡ��
	m_ListCrtl.InsertColumn(0, "Ա��ID", LVCFMT_CENTER, 60);
	m_ListCrtl.InsertColumn(1, "��н(Ԫ)", LVCFMT_CENTER, 60);
	m_ListCrtl.InsertColumn(2, "�·�", LVCFMT_CENTER, 60);
	m_ListCrtl.InsertColumn(3, "����(��)", LVCFMT_CENTER, 60);
	m_ListCrtl.InsertColumn(4, "����(��)", LVCFMT_CENTER, 60);
	m_ListCrtl.InsertColumn(5, "�¼�(��)", LVCFMT_CENTER, 60);
	m_ListCrtl.InsertColumn(6, "ƽʱ�Ӱ�(Сʱ)", LVCFMT_CENTER, 100);
	m_ListCrtl.InsertColumn(7, "˫���ռӰ�(Сʱ)", LVCFMT_CENTER, 120);
	m_ListCrtl.InsertColumn(8, "�������ռӰ�(Сʱ)", LVCFMT_CENTER, 120);
	m_ListCrtl.InsertColumn(9, "Ӧ������(Ԫ)", LVCFMT_CENTER, 100);
	CString strSQL;	//������ʱ��
	strSQL.Format("create table temp (id int, wage int, ym varchar(20), chuchai int, bingjia int, shijia int, pingshi int, shuangxiu int, fading int, waged int)");
	try
	{
		theApp.m_pConnection->Execute((_bstr_t)strSQL, NULL, adCmdText);
	}
	catch(...)
	{
		strSQL.Format("drop table temp");
		theApp.m_pConnection->Execute((_bstr_t)strSQL, NULL, adCmdText);
		strSQL.Format("create table temp (id int, wage int, ym varchar(20), chuchai int, bingjia int, shijia int, pingshi int, shuangxiu int, fading int, waged int)");
		theApp.m_pConnection->Execute((_bstr_t)strSQL, NULL, adCmdText);
	}
	try//��ʱ�����������
	{
		CString SQL[9];
		strSQL = "insert into temp (id) select id from emp ;";
		//��Ա�����ж�ȡԱ��ID
		SQL[0] = "update temp set wage = 0, ym = 2008-01, chuchai = 0, bingjia = 0, shijia = 0, pingshi = 0, shuangxiu = 0, fading = 0, waged = 0;";
		//��н�ĸ���
		SQL[1] = "update temp set wage = wageinfo.wage from wageinfo where temp.id = wageinfo.id;";
		//�ӿ��ڱ��ж�ȡ�·�
		SQL[2] = "update temp set ym = checkinfo.ym from checkinfo where temp.id = checkinfo.id;";
		//�����·ݴӿ��ڱ���ͳ�ƿ�����Ϣ��
		SQL[3] = "update temp set chuchai = (select count(*) from checkinfo where temp.ym = checkinfo.ym and checkinfo.chuchai = '��' and temp.id = checkinfo.id);";
		SQL[4] = "update temp set bingjia = (select count(*) from checkinfo where temp.ym = checkinfo.ym and checkinfo.bingjia = '��' and temp.id = checkinfo.id);";
		SQL[5] = "update temp set shijia = (select count(*) from checkinfo where temp.ym = checkinfo.ym and checkinfo.shijia = '��' and temp.id = checkinfo.id);";
		SQL[6] = "update temp set pingshi = (select sum(ot1) from checkinfo where temp.ym = checkinfo.ym and temp.id = checkinfo.id) ;";
		SQL[7] = "update temp set shuangxiu = (select sum(ot2) from checkinfo where temp.ym = checkinfo.ym and temp.id = checkinfo.id) ;";
		SQL[8] = "update temp set fading = (select sum(ot3) from checkinfo where temp.ym = checkinfo.ym and temp.id = checkinfo.id) ;";
		for(int i = 0; i < 9; i++)
			strSQL += SQL[i];
		theApp.m_pConnection->Execute((_bstr_t)strSQL, NULL, adCmdText);
	}
	CATCH_ERROR;
	float chuchai, bingjia, shijia, pingshi, shuangxiu, fading; //��ȡ���ʵļ��㹫ʽ
	_variant_t va;
	strSQL = "select * from wagecal";
	try
	{
		m_pRecordset = theApp.m_pConnection->Execute((_bstr_t)strSQL, NULL, adCmdText);
		va = m_pRecordset->GetCollect(_variant_t((long)0));
		chuchai = va.iVal;
		va = m_pRecordset->GetCollect(_variant_t((long)1));
		bingjia = va.iVal;
		va = m_pRecordset->GetCollect(_variant_t((long)2));
		shijia = va.iVal;
		va = m_pRecordset->GetCollect(_variant_t((long)3));
		pingshi = va.iVal;
		va = m_pRecordset->GetCollect(_variant_t((long)4));
		shuangxiu = va.iVal;
		va = m_pRecordset->GetCollect(_variant_t((long)5));
		fading = va.iVal;
	}
	CATCH_ERROR;
	strSQL.Format("update temp set waged = (wage / 23 * chuchai * %f / 100 + wage / 23 * bingjia * %f / 100 + wage / 23 * shijia * %f / 100 + wage / 23 / 8 * pingshi * %f / 100 + wage / 23 / 8 * shuangxiu * %f / 100 + wage / 23 / 8 * fading * %f / 100 + wage / 23 * (23 - chuchai - bingjia - shijia))",
		chuchai, bingjia, shijia, pingshi, shuangxiu, fading);
	try//����Ա���Ĺ���
	{
		m_pRecordset = theApp.m_pConnection->Execute((_bstr_t)strSQL, NULL, adCmdText);
	}
	CATCH_ERROR;
	strSQL = "select * from temp";//��temp���в�ѯ���������list��
	ShowListData(strSQL);
	strSQL = "select ym from temp group by ym";//����·�combobox
	try
	{
		m_pRecordset = theApp.m_pConnection->Execute((_bstr_t)strSQL, NULL, adCmdText);
		while(!m_pRecordset->adoEOF)
		{
			m_Month.AddString((char*)_bstr_t(m_pRecordset->GetCollect(_variant_t((long)0))));
			m_pRecordset->MoveNext();
		}
	}
	CATCH_ERROR;
	m_Month.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CWageDlg::ShowListData(const CString& sql)
{
	m_ListCrtl.DeleteAllItems();
	try
	{
		m_pRecordset = theApp.m_pConnection->Execute((_bstr_t)sql, NULL, adCmdText);
		int i = 0;
		while(!m_pRecordset->adoEOF)
		{
			m_ListCrtl.InsertItem(i, (char*)_bstr_t(m_pRecordset->GetCollect(_variant_t((long)0))));
			for(int j = 1; j < 10; j++)
			{
				m_ListCrtl.SetItemText(i, j, (char*)_bstr_t(m_pRecordset->GetCollect(_variant_t((long)j))));
			}
			i++;
			m_pRecordset->MoveNext();
		}
	}
	CATCH_ERROR;
}

void CWageDlg::OnButton1() 
{
	UpdateData();			//���ݵĸ�����
	CString strSQL, strMonth;
	int nIndex = m_Month.GetCurSel();//�·ݵĻ�ȡ
	m_Month.GetLBText(nIndex, strMonth);
	strSQL.Format("select * from temp where id = %s and ym = '%s'", m_strID, strMonth);
	ShowListData(strSQL);
}
