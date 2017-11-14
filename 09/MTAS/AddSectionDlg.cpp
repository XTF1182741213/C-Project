// AddSectionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mtas.h"
#include "AddSectionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddSectionDlg dialog


CAddSectionDlg::CAddSectionDlg(CWnd* pParent /*=NULL*/)
	: CNewDialog(CAddSectionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddSectionDlg)
	m_strChapterName = _T("");
	m_strClassName   = _T("");
	m_strSectionName = _T("");
	//}}AFX_DATA_INIT
}


void CAddSectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CNewDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddSectionDlg)
	DDX_Control(pDX, IDC_EDIT_CHAPTER, m_editChapter);
	DDX_Control(pDX, IDC_EDIT_CLASS, m_editClass);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDADD, m_btnAdd);
	DDX_Text(pDX, IDC_EDIT_CHAPTER, m_strChapterName);
	DDX_Text(pDX, IDC_EDIT_CLASS, m_strClassName);
	DDX_Text(pDX, IDC_EDIT_SECTION, m_strSectionName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddSectionDlg, CNewDialog)
	//{{AFX_MSG_MAP(CAddSectionDlg)
	ON_BN_CLICKED(IDADD, OnAdd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddSectionDlg message handlers

BOOL CAddSectionDlg::OnInitDialog() 
{
	CNewDialog::OnInitDialog();
	
	short shBtnColor = 30;
	m_btnAdd.SetIcon(IDI_ADD, 17, 17);
	m_btnAdd.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	m_btnAdd.SetRounded(TRUE);
	m_btnCancel.SetIcon(IDI_CANCEL, 15, 15);
	m_btnCancel.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);	
	m_btnCancel.SetRounded(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAddSectionDlg::OnAdd() 
{
	UpdateData();

	if(m_strSectionName.IsEmpty()) {
		MessageBox(_T("��д����Ϣ������!"), _T("����!"), MB_ICONEXCLAMATION);
		return;
	}

	CNewDialog::OnOK();
}