// ADMIN.cpp : implementation file
//

#include "stdafx.h"
#include "HCOK.h"
#include "ADMIN.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ADMIN dialog


ADMIN::ADMIN(CWnd* pParent /*=NULL*/)
	: CDialog(ADMIN::IDD, pParent)
{
	//{{AFX_DATA_INIT(ADMIN)
	m_mpassword = _T("");
	m_user = _T("");
	m_newpass = _T("");
	m_oldpass = _T("");
	//}}AFX_DATA_INIT
}


void ADMIN::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ADMIN)
	DDX_Text(pDX, IDC_GPASSWOER, m_mpassword);
	DDX_Text(pDX, IDC_USER, m_user);
	DDX_Text(pDX, IDC_NEWPASSWORD, m_newpass);
	DDX_Text(pDX, IDC_OLDPASSWORD, m_oldpass);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ADMIN, CDialog)
	//{{AFX_MSG_MAP(ADMIN)
	ON_BN_CLICKED(IDC_MODIFY, OnModify)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ADMIN message handlers

BOOL ADMIN::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_AdoConn.OnInitADOConn();  //�������ݿ�
    (CEdit*)GetDlgItem(IDC_USER)->SetFocus();	//���ý���
	if(rectlarge.IsRectNull())
	{
		CRect rectseparator;
        GetWindowRect(&rectlarge);
		GetDlgItem(IDC_SEPARATOR)->GetWindowRect(&rectseparator);
		rectsmall.left=rectlarge.left;
		rectsmall.top=rectlarge.top;
		rectsmall.right=rectseparator.right;
		rectsmall.bottom=rectseparator.bottom;
	}
	SetWindowPos(NULL,0,0,rectsmall.Width(),rectsmall.Height(),SWP_NOMOVE|SWP_NOZORDER);
	return true;  
}

void ADMIN::OnModify() 
{
	UpdateData();
	CString str;
	if(GetDlgItemText(IDC_MODIFY,str),str=="�޸�����")
	{
		SetDlgItemText(IDC_MODIFY,"����޸�");
	}
    else
	{
		SetDlgItemText(IDC_MODIFY,"�޸�����");
	}
	
	if(rectlarge.IsRectNull())
	{
		CRect rectseparator;
		GetDlgItem(IDC_SEPARATOR)->GetWindowRect(&rectseparator);
		rectsmall.left=rectlarge.left;
		rectsmall.top=rectlarge.top;
		rectsmall.right=rectseparator.right;
		rectsmall.bottom=rectseparator.bottom;
	}
    if(str=="����޸�")
	{
		sql = "select*from admin where  adminname ='"+m_user+"'"+"and adminpwd ='"+m_oldpass+"'";//��֤����
		m_pRecordset=m_AdoConn.GetRecordSet(sql);
		if(m_pRecordset->adoEOF)	
		{
			MessageBox("ԭ�������!","ϵͳ��ʾ��",MB_OK|MB_ICONASTERISK);
		}
		else
		{
		    CString str1;
			str1.Format("update admin set adminpwd='%s'",m_newpass);
			m_pRecordset=m_AdoConn.GetRecordSet(_bstr_t(str1));
			MessageBox("�޸ĳɹ�!","ϵͳ��ʾ��",MB_OK);
		}
		SetWindowPos(NULL,0,0,rectsmall.Width(),rectsmall.Height(),SWP_NOMOVE|SWP_NOZORDER);
	}
	else
	{
		SetWindowPos(NULL,0,0,rectlarge.Width(),rectlarge.Height(),SWP_NOMOVE|SWP_NOZORDER);
	}
}

void ADMIN::OnClose() 
{
	CDialog::OnClose();
}
