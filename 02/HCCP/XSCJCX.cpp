// XSCJCX.cpp : implementation file
//

#include "stdafx.h"
#include "HCCP.h"
#include "XSCJCX.h"
#include "JIEGUO.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// XSCJCX dialog


XSCJCX::XSCJCX(CWnd* pParent /*=NULL*/)
: CDialog(XSCJCX::IDD, pParent)
{
	//{{AFX_DATA_INIT(XSCJCX)
	m_guanjian = _T("");
	//}}AFX_DATA_INIT
}


void XSCJCX::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(XSCJCX)
	DDX_Control(pDX, IDC_FANWEI, m_fanwei);
	DDX_Text(pDX, IDC_GUANJIAN, m_guanjian);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(XSCJCX, CDialog)
//{{AFX_MSG_MAP(XSCJCX)
ON_BN_CLICKED(IDC_FIND, OnFind)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// XSCJCX message handlers

BOOL XSCJCX::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_fanwei.SetCurSel(0);  //��ʼ�������˵�Ϊ��ʾ��һ��
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void XSCJCX::OnFind() 
{
	if(nCount==4)
	{
		UpdateData();
		int k=m_fanwei.GetCurSel();
		m_fanwei.GetLBText(k,temp);  //ѡ����ҷ�Χ
		if(temp=="ѧ��")
			temp="sno";
		else if(temp=="����")
			temp="sname";
		else if(temp=="�ɼ�")
			temp="sgrade";
		str1212=temp;
		str1213=m_guanjian;
		JIEGUO jgdlg;
	    jgdlg.DoModal();  //����JIEGUO�Ի�����ʾ��ѯ���
	}
	else
		AfxMessageBox("��ѡ��ѧ���ɼ���!");
}

void XSCJCX::DuiHua()
{

}
