// REMDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HCWORD.h"
#include "REMDlg.h"
#include "ADDdlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// REMDlg dialog


REMDlg::REMDlg(CWnd* pParent /*=NULL*/)
	: CDialog(REMDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(REMDlg)
	m_edit = _T("");
	//m_edit="ghsajbdsjabdnsabdnasbdnasndcasmsncsaghgfhgfhjjkkkklllllllllllnnnnnnnnnnn";
	//}}AFX_DATA_INIT
}


void REMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(REMDlg)
	DDX_Text(pDX, IDC_EDIT1, m_edit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(REMDlg, CDialog)
	//{{AFX_MSG_MAP(REMDlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// REMDlg message handlers

BOOL REMDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString str; 
   	CString strLine;  
   	CStdioFile file; 
  	if(!file.Open(logFileName,CFile::modeRead))   
	   	return FALSE;   
   	while(file.ReadString(strLine))   
	{   
	   	str+=strLine;
        str+="\r\n";   
	}   
   	file.Close();   
   	CWnd *pWnd=(CWnd*)GetDlgItem(IDC_EDIT1);   
   	pWnd->SetWindowText(str);
//	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void REMDlg::OnButton1() 
{
    //��ʾ�ļ��򿪶Ի���
	CFileDialog dlg(TRUE, "SQL", "*.txt",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"�ı��ļ�(*.txt)|*.txt|�����ļ�(*.*)|*.*||");
	if ( dlg.DoModal()!=IDOK ) 
		return;
	//��ȡ�ļ��ľ���·��
	CString sFileName=dlg.GetPathName();
	//���ļ�
	CStdioFile out;
	out.Open(sFileName, CFile::modeRead);
	CString sSql="",s;
	//��ȡ�ļ�
	do
	{
		out.ReadString(s);
		sSql=sSql+s+"\r\n"+(char)10;

	}
	while (out.GetPosition()!=out.GetLength());
	out.Close();
	GetDlgItem(IDC_EDIT1)->SetWindowText(sSql);	
}

void REMDlg::OnButton2() 
{
if(MessageBox("          ȷ��ɾ����¼��?                ","���Ӵʵ�ϵͳ",MB_YESNO|MB_ICONINFORMATION)==IDYES)
	{
		CFile TempFile; 
		CStdioFile file; 
		if(file.Open(logFileName,CFile::modeRead))
		{
			file.Close();                                    //�ر��ļ�
    		TempFile.Remove(logFileName);
            m_edit="";
		    UpdateData(false);
		}	
	}	
}

void REMDlg::OnButton3() 
{
	OnInitDialog();
	
}
