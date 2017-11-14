// MODIFISINGER.cpp : implementation file
//

#include "stdafx.h"
#include "HCOK.h"
#include "MODIFISINGER.h"
#include "ADOConn.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MODIFISINGER dialog


MODIFISINGER::MODIFISINGER(CWnd* pParent /*=NULL*/)
	: CDialog(MODIFISINGER::IDD, pParent)
{
	//{{AFX_DATA_INIT(MODIFISINGER)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void MODIFISINGER::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MODIFISINGER)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MODIFISINGER, CDialog)
	//{{AFX_MSG_MAP(MODIFISINGER)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MODIFISINGER message handlers

BOOL MODIFISINGER::OnInitDialog() 
{
	CDialog::OnInitDialog();


	CString temp=mkusingerarea.Left(4);	
	CString temp2=	mkusingersex.Left(2);	

    GetDlgItem(IDC_SINGER)->SetWindowText( mkusingername);
	
    GetDlgItem(IDC_SINGERSEX)->SetWindowText(temp2);
	GetDlgItem(IDC_SGEAREA)->SetWindowText(temp);
	GetDlgItem(IDC_SGEPIN)->SetWindowText(	mkusingerpin);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void MODIFISINGER::OnOK() 
{
    CString newkusingername,newkusingersex,newkusingerarea,newkusingerpin;
	
	
	GetDlgItem(IDC_SINGER)->GetWindowText( newkusingername);//�õ��µ�����
		
	GetDlgItem(IDC_SINGERSEX)->GetWindowText(	newkusingersex);//�õ��µ��Ա�
	GetDlgItem(IDC_SGEAREA)->GetWindowText(newkusingerarea);  //�õ��µĵ���
	GetDlgItem(IDC_SGEPIN)->GetWindowText(	newkusingerpin);  //�õ��µ�ƴ��
    newkusingerarea=newkusingerarea+"����";
    newkusingersex=newkusingersex+"����";
	////////////////////////////////////////////////////
	ADOConn m_AdoConn;//�������ݿ��������

	m_AdoConn.OnInitADOConn(); //�������ݿ�

	_RecordsetPtr m_pRecordset;
	_bstr_t sql;
    sql = "select*from singer where sinnam='"+mkusingername+"'";
	m_pRecordset=m_AdoConn.GetRecordSet(sql);//�ü�¼�����ǵ�ǰ��
	m_pRecordset->GetFields()->GetItem("sinnam")->Value=(_bstr_t) newkusingername ;	///д�������
	m_pRecordset->GetFields()->GetItem("sinsex")->Value=(_bstr_t) newkusingersex;////д���Ա�
	m_pRecordset->GetFields()->GetItem("sinarea")->Value=(_bstr_t) newkusingerarea;////д�����
	m_pRecordset->GetFields()->GetItem("sinpin")->Value=(_bstr_t)  newkusingerpin;////д��ƴ��
	
		m_pRecordset->Update();
    	m_AdoConn.ExitConnect();//�ͷ����ݿ���Դ
		MessageBox("�������ϸ��³ɹ�!","ϵͳ��ʾ��",MB_OK|MB_ICONASTERISK);
	CDialog::OnOK();
}
