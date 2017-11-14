// ChoiStatusDlg.cpp : implementation file
//

#include "stdafx.h"
#include "gradudemis.h"
#include "ChoiStatusDlg.h"
#include "TecrDclrSubDlg.h"
#include "ChoisubDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChoiStatusDlg dialog


CChoiStatusDlg::CChoiStatusDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChoiStatusDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChoiStatusDlg)
	m_strChoiSubStatus = _T("");
	//}}AFX_DATA_INIT
}


void CChoiStatusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChoiStatusDlg)
	DDX_Text(pDX, IDC_STATIC_ChoiStatus, m_strChoiSubStatus);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChoiStatusDlg, CDialog)
	//{{AFX_MSG_MAP(CChoiStatusDlg)
	ON_BN_CLICKED(IDC_SeeChoisubInfo_BTN, OnSeeChoisubInfoBTN)
	ON_BN_CLICKED(IDC_EnterChoiSub_BTN, OnEnterChoiSubBTN)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChoiStatusDlg message handlers

//ѧ��ѡ�����
BOOL CChoiStatusDlg::OnInitDialog()
{
	CDialog::OnInitDialog();	
	// TODO: Add extra initialization here

	bool choisubStatus;														
	choisubSet.Open();//��ѡ���¼��
	while(!choisubSet.IsEOF())						//������¼��
	{
		if(choisubSet.m_stu_name==strExternUser)	//����ѧ��
		{
			//if(choisubSet.m_stu_choisubStatus)
			choisubStatus=true;						//ѡ��״̬
			break;
		}
		else
			choisubSet.MoveNext();					//�ƶ����µ���¼
	}
	choisubSet.Close();								//�رռ�¼��
	if(choisubStatus==true)							//�ж��Ƿ�ѡ��
	{
        m_strChoiSubStatus="���Ѿ�ѡ�⣡";
		CButton *pBtn1=(CButton *)GetDlgItem(IDC_EnterChoiSub_BTN);//��ȡ�ؼ�ָ��
		pBtn1->ShowWindow(SW_HIDE);					//���ذ�ť
	}
	else
	{
        m_strChoiSubStatus="����δѡ�⣡";			
		CButton *pBtn2=(CButton *)GetDlgItem(IDC_SeeChoisubInfo_BTN);//��ȡ�ؼ�ָ��
		pBtn2->ShowWindow(SW_HIDE);					//���ذ�ť
	}
    UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CChoiStatusDlg::OnSeeChoisubInfoBTN() 
{
	// TODO: Add your control notification handler code here
	OnCancel();
	CTecrDclrSubDlg dlg;
	dlg.DoModal();						//�򿪲鿴ѡ����Ϣ�Ի���
}

void CChoiStatusDlg::OnEnterChoiSubBTN() 
{
	// TODO: Add your control notification handler code here
	OnCancel();
	CChoisubDlg dlg;
	dlg.DoModal();						//��ѡ��Ի���
}

