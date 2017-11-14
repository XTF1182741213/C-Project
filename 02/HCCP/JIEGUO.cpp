// JIEGUO.cpp : implementation file
//

#include "stdafx.h"
#include "HCCP.h"
#include "JIEGUO.h"
#include "XSCJCX.h"
#include "ADOConn.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// JIEGUO dialog


JIEGUO::JIEGUO(CWnd* pParent /*=NULL*/)
	: CDialog(JIEGUO::IDD, pParent)
{
	//{{AFX_DATA_INIT(JIEGUO)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void JIEGUO::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(JIEGUO)
	DDX_Control(pDX, IDC_TIAOMU, m_tiaomu);
	DDX_Control(pDX, IDC_LIST2, m_list2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(JIEGUO, CDialog)
	//{{AFX_MSG_MAP(JIEGUO)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// JIEGUO message handlers

BOOL JIEGUO::OnInitDialog() 
{
	CDialog::OnInitDialog();	
	m_list2.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);  //����list�ؼ����
	m_list2.InsertColumn(0,"ѧ��",LVCFMT_CENTER,114);  //����б���
	m_list2.InsertColumn(1,"����",LVCFMT_CENTER,115);
	m_list2.InsertColumn(2,"����",LVCFMT_CENTER,114);
	XSCJCX finddlg;
	CString sqlstr;
	CString strsno;
	strsno="student.";
	if(str1212=="sno")
		str1212=strsno+str1212;
	sqlstr.Format("select student.sno,sname,sgrade from student ,grade where student.sno=grade.sno \
    and cno='%s' and %s like '%%%s%%'",str1112,str1212,str1213);//ͨ����ѯ��ʽ����ģ����ѯ
	ADOConn m_ado113;
	_RecordsetPtr m_pRs113;
	_bstr_t vSQL113;
	vSQL113=(_bstr_t)sqlstr;
	m_pRs113=m_ado113.GetRecordSet(vSQL113);  //��ȡ��¼��
	int k=0;	
	_variant_t cno,cname,cgrade;	
	while(!m_pRs113->adoEOF)  //ͨ��ѭ����¼��ָ����ʾ���в�ѯ�����list�ؼ�����¼����
	{
		cno=m_pRs113->GetCollect("sno");
		cname=m_pRs113->GetCollect("sname");
		cgrade=m_pRs113->GetCollect("sgrade");
		CString str1=(LPCTSTR)(_bstr_t)cname;
		CString str2=(LPCTSTR)(_bstr_t)cgrade;		
		m_list2.InsertItem(k,(_bstr_t)cno);
		m_list2.SetItemText(k,1,str1);       
		m_list2.SetItemText(k,2,str2);
		m_pRs113->MoveNext();
		k++;
	}	
	CString str9;
	str9.Format("����ѯ��  %d  ����¼!",k);
	m_tiaomu.SetWindowText(str9);  //���öԻ������
	return TRUE;  
}
