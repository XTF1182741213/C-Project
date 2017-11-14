// LOGIN.cpp : implementation file
//

#include "stdafx.h"
#include "licai.h"
#include "LOGIN.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// LOGIN dialog


LOGIN::LOGIN(CWnd* pParent /*=NULL*/)
	: CDialog(LOGIN::IDD, pParent)
{
	//{{AFX_DATA_INIT(LOGIN)
	m_id = _T("");
	m_password = _T("");
	//}}AFX_DATA_INIT
}


void LOGIN::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(LOGIN)
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_id);
	DDX_Text(pDX, IDC_EDIT2, m_password);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(LOGIN, CDialog)
	//{{AFX_MSG_MAP(LOGIN)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// LOGIN message handlers

BOOL LOGIN::OnInitDialog() 
{
	CDialog::OnInitDialog();
	MessageBox("˵��������Ա�ʺ�Ϊhc����123","��ͥ���ϵͳ",MB_OK);
	m_combo.InsertString(0,"����Ա");
    m_combo.InsertString(1,"����");
	if(loginflag)
	{	
		m_combo.SetCurSel(0);
		author="����Ա";
	}	
	else
	{	
		m_combo.SetCurSel(1);
		author="����";
	}
	return TRUE;
}
void LOGIN::OnOK() 
{
	int i;
	i=m_combo.GetCurSel();
    m_combo.GetLBText(i,author);	
	CDialog::OnOK();
}
