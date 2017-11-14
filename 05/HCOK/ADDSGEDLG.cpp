// ADDSGEDLG.cpp : implementation file
//

#include "stdafx.h"
#include "HCOK.h"
#include "ADDSGEDLG.h"
#include "ADOConn.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ADDSGEDLG dialog


ADDSGEDLG::ADDSGEDLG(CWnd* pParent /*=NULL*/)
	: CDialog(ADDSGEDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(ADDSGEDLG)
	m_singer = _T("");
	//}}AFX_DATA_INIT
}


void ADDSGEDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ADDSGEDLG)
	DDX_Control(pDX, IDC_COMBO2, m_combo2);
	DDX_Control(pDX, IDC_COMBO1, m_combo1);
	DDX_Text(pDX, IDC_SINGER, m_singer);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ADDSGEDLG, CDialog)
	//{{AFX_MSG_MAP(ADDSGEDLG)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ADDSGEDLG message handlers

void ADDSGEDLG::OnOK() 
{
	
	CString singername,singersex,singerarea,singerpin;
	
	
	GetDlgItem(IDC_SINGER)->GetWindowText(singername);//�õ�������
	
	int kk=m_combo1.GetCurSel();
	m_combo1.GetLBText(kk,singersex);///////////////////�õ������Ա�
	int kk2=m_combo2.GetCurSel();
	m_combo2.GetLBText(kk2,singerarea);///////////////////�õ����ֵ���
	GetDlgItem(IDC_SGEPIN)->GetWindowText(	singerpin);	//�õ�����ƴ��
    singersex=singersex+"����";  
	////////////////////////////////////////////////////

	ADOConn m_AdoConn;//�������ݿ��������

	m_AdoConn.OnInitADOConn();  //�������ݿ�

	_RecordsetPtr m_pRecordset;  //�����¼��
	_bstr_t sql;
		sql = "select* from singer where sinnam='"+singername+"'";//�ڸ��ֱ��в�ѯ����
			
				m_pRecordset=m_AdoConn.GetRecordSet(sql);//�õ���¼��
				if(!m_pRecordset->adoEOF)  //���ڸô���ʾ��Ϣ
				MessageBox("�ø����Ѵ���,���ʧ��!","ϵͳ��ʾ��",MB_OK|MB_ICONASTERISK);
				else{

	
				m_pRecordset->AddNew();   //���������,�ͽ���Ϣд�����ݿ�
	m_pRecordset->GetFields()->GetItem("sinnam")->Value=(_bstr_t) singername;	///д�������
	m_pRecordset->GetFields()->GetItem("sinsex")->Value=(_bstr_t) singersex;////д���Ա�
	m_pRecordset->GetFields()->GetItem("sinarea")->Value=(_bstr_t) singerarea;////д�����
	m_pRecordset->GetFields()->GetItem("sinpin")->Value=(_bstr_t)  singerpin;////д��ƴ��
		MessageBox("����������ӳɹ�!","ϵͳ��ʾ��",MB_OK|MB_ICONASTERISK);
		m_pRecordset->Update();
				}
    	m_AdoConn.ExitConnect();   //�ͷ����ݿ���Դ
		
	
	CDialog::OnOK();
}

BOOL ADDSGEDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	//*********��ʼ���ؼ�***************************//
    m_combo1.InsertString(0,"��");
    m_combo1.InsertString(1,"Ů");
    m_combo1.SetCurSel(0);
    m_combo2.InsertString(0,"��½");
    m_combo2.InsertString(1,"���");
	m_combo2.InsertString(2,"̨��");
 
	m_combo2.InsertString(3,"�պ�");
	m_combo2.InsertString(4,"ŷ��");
    m_combo2.InsertString(5,"����");
	 m_combo2.SetCurSel(0);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
