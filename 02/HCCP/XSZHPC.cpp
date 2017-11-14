// XSZHPC.cpp : implementation file
//

#include "stdafx.h"
#include "HCCP.h"
#include "XSZHPC.h"
#include "ZHPCDLG.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// XSZHPC dialog


XSZHPC::XSZHPC(CWnd* pParent /*=NULL*/)
: CDialog(XSZHPC::IDD, pParent)
{
	
	//{{AFX_DATA_INIT(XSZHPC)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void XSZHPC::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(XSZHPC)
	DDX_Control(pDX, IDC_BANJI, m_banji);
	DDX_Control(pDX, IDC_XUEYUAN, m_xueyuan);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(XSZHPC, CDialog)
//{{AFX_MSG_MAP(XSZHPC)
ON_BN_CLICKED(IDC_ZHPCBT, OnZhpcbt)
ON_CBN_SELCHANGE(IDC_XUEYUAN, OnSelchangeXueyuan)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// XSZHPC message handlers

BOOL XSZHPC::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_xueyuan.SetCurSel(0);
	m_banji.SetCurSel(0);
	row=3;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

/*---------------------ѡ���ۺϲ����༶----------------------*/

void XSZHPC::OnZhpcbt() 
{
	int k=m_xueyuan.GetCurSel();
	m_xueyuan.GetLBText(k,temp);
	int l=m_banji.GetCurSel();
	m_banji.GetLBText(l,temp1);
	str1212=temp1;
	ZHPCDLG zhpcdlg;
	zhpcdlg.DoModal();	
}

/*---------------------ͨ���¼�����----------------------*/

void XSZHPC::OnSelchangeXueyuan() 
{
	CString str,zhao;
	int k=m_xueyuan.GetCurSel();
	m_xueyuan.GetLBText(k,zhao);
	str.Format("select * from tree where root='%s'",zhao);  
	_bstr_t vSQL;
	vSQL=(_bstr_t)str;
	m_pRc=myado.GetRecordSet(vSQL);  //��ȡ����������ӽ���¼��
	for(;row>=0;row--)  //ͨ��forѭ��ɾ�������˵���������
		m_banji.DeleteString(row);  
	k=0;
	_bstr_t leaf;
	CString str1;
	do
	{
		leaf=m_pRc->GetCollect("leaf");  //��ȡ�ӽ���¼
		
		str1=(LPCTSTR)(_bstr_t)leaf;
		str1.TrimRight();
		m_banji.InsertString(k,str1);  //��Ӱ༶�����˵��е�����	
		m_pRc->MoveNext();  //ָ��ָ����һ����¼
		k++;
	}
	while
		(!m_pRc->adoEOF);
	row=k;
	m_banji.SetCurSel(0);
}

